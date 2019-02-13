import os
import re
from flask import Flask, jsonify, render_template, request

from cs50 import SQL
from helpers import lookup

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Render map"""
    return render_template("index.html")


@app.route("/articles")
def articles():
    """Look up articles for geo"""

    # store contents of the query string in variable geo
    geo = request.args.get('geo')

    # check if geo exists
    if not geo:
        return jsonify([])

    articles = lookup(geo)

    return jsonify(articles)


@app.route("/search")
def search():
    """Search for places that match query"""

    # Get contents of the query string
    q = request.args.get('q')

    # Prepare dict to hold user input
    q_dict = {}

    # input index to be used with the keys of above dict
    ii = 1

    # Split input and add wildcard characters for sql
    for x in re.split(r"[^a-zA-Z0-9_]", q):
        if not x == '':
            q_dict[f"x{ii}"] = x
            ii += 1

    # Create dynamic sql query (also adds wildcards)
    sql_query = "SELECT * FROM places WHERE "
    for x in q_dict:
        if q_dict[x].isnumeric():
            q_dict[x] += "%"
            sql_query += f"postal_code LIKE :{x} AND "
        else:
            q_dict[x] = "%" + q_dict[x] + "%"
            sql_query += f"(place_name LIKE :{x} OR admin_name1 LIKE :{x}) AND "

    # Remove last AND and extra whitespace
    sql_query = sql_query[:len(sql_query) - 5]

    # List of places that the user possibly means
    proposed_matches = db.execute(sql_query, **q_dict)

    return jsonify(proposed_matches)


@app.route("/update")
def update():
    """Find up to 10 places within view"""

    # Ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # Ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # Explode southwest corner into two variables
    sw_lat, sw_lng = map(float, request.args.get("sw").split(","))

    # Explode northeast corner into two variables
    ne_lat, ne_lng = map(float, request.args.get("ne").split(","))

    # Find 10 cities within view, pseudorandomly chosen if more within view
    if sw_lng <= ne_lng:

        # Doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    else:

        # Crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # Output places as JSON
    return jsonify(rows)
