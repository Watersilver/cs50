from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Retrieve the total cash of the user
    user_balance = db.execute("SELECT cash FROM users WHERE id = :uid",
                              uid=session["user_id"])[0]["cash"]

    # Grand total of cash + stocks' total value
    grand_total = user_balance

    # Store information about owned stocks on a list of dicts
    portfolio = db.execute("SELECT stock_ownership.amount, stocks.stock_symbol FROM stock_ownership JOIN users ON stock_ownership.user_id = users.id JOIN stocks ON stock_ownership.stock_id = stocks.stock_id WHERE users.id = :uid",
                           uid=session.get('user_id'))

    # Insert the current price of each of the owned stocks in the list of dicts
    for stock in portfolio:
        stock["price_of_one"] = lookup(stock["stock_symbol"])["price"]
        stock["total_price"] = stock["price_of_one"] * stock["amount"]

        # Update grand total
        grand_total += stock["total_price"]

        # Format the cash properly
        stock["price_of_one"] = usd(stock["price_of_one"])
        stock["total_price"] = usd(stock["total_price"])

    # Format rest of the cash
    grand_total = usd(grand_total)
    user_balance = usd(user_balance)

    return render_template("index.html", stocks=portfolio, user_balance=user_balance, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Look for requested stock, apologise if not found
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("couldn't find symbol")

        # Check if given amount to be bought
        amount = request.form.get("shares")
        if amount == '':
            return apology("enter an amount to buy")

        if not amount.isdigit():
            return apology("digits only")

        # Check if input is positive
        amount = int(amount)
        if not amount > 0:
            return apology("enter a positive amount")

        # Check if user has enough money to buy
        if amount * stock["price"] > db.execute("SELECT cash FROM users WHERE id == :user_id",
                                                user_id=session.get('user_id'))[0]["cash"]:
            return apology("you poor fuck")

        # Reduce the users cash appropriately
        db.execute("UPDATE users SET cash = cash - :tprice WHERE id == :user_id",
                   tprice=amount * stock["price"],
                   user_id=session.get('user_id'))

        # Check if stock is already in database. If not add it.
        if not db.execute("SELECT * FROM stocks WHERE stock_symbol == :symbol",
                          symbol=request.form.get("symbol")):
            db.execute("INSERT INTO stocks ('stock_symbol') VALUES (:symbol)",
                       symbol=request.form.get("symbol"))

        # Add transaction to history
        db.execute("INSERT INTO history ('user_id', 'stock_id', 'transaction_type', 'price', 'stock_amount') VALUES (:uid, :sid, :tt, :p, :sa)",
                   uid=session.get('user_id'),
                   sid=db.execute("SELECT stock_id FROM stocks WHERE stock_symbol == :symbol",
                                  symbol=request.form.get("symbol"))[0]["stock_id"],
                   tt=0,
                   p=amount * stock["price"],
                   sa=amount)

        # Add stock to ownership
        if not db.execute("UPDATE stock_ownership SET amount = amount + :amount WHERE stock_id == :sid AND user_id == :uid",
                          amount=amount,
                          sid=db.execute("SELECT stock_id FROM stocks WHERE stock_symbol == :symbol",
                                         symbol=request.form.get("symbol"))[0]["stock_id"],
                          uid=session.get('user_id')):
            db.execute("INSERT INTO stock_ownership ('user_id', 'stock_id', 'amount') VALUES (:uid, :sid, :sa)",
                       uid=session.get('user_id'),
                       sid=db.execute("SELECT stock_id FROM stocks WHERE stock_symbol == :symbol",
                                      symbol=request.form.get("symbol"))[0]["stock_id"],
                       sa=amount)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get transaction history
    history = db.execute("SELECT stocks.stock_symbol, transaction_types.type, history.stock_amount, history.price, history.transaction_date, history.transaction_time FROM history JOIN stocks ON history.stock_id = stocks.stock_id JOIN transaction_types ON history.transaction_type = transaction_types.type_id WHERE history.user_id = :uid",
                         uid=session.get('user_id'))

    # Format price properly
    for transaction in history:
        transaction['price'] = usd(transaction['price'])

    return render_template("history.html", history=history)


@app.route("/changep", methods=["GET", "POST"])
@login_required
def change_password():
    """Allows you to change password"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure previous password was submitted
        if not request.form.get("prev_password"):
            return apology("must provide previous password")

        # Ensure new password was submitted
        if not request.form.get("password"):
            return apology("must provide new password")

        # Ensure confirm password was submitted
        if not request.form.get("confirm"):
            return apology("must provide confirm password")

        # Query database
        rows = db.execute("SELECT hash FROM users WHERE id = :uid",
                          uid=session.get("user_id"))

        # Ensure previous password is correct
        if not check_password_hash(rows[0]["hash"], request.form.get("prev_password")):
            return apology("wrong password")

        # Ensure new provided password matches confirm password
        if not request.form.get("password") == request.form.get("confirm"):
            return apology("new password doesn't match confirm password")

        # Update database
        db.execute("UPDATE users SET hash = :hashed_pass WHERE id = :uid",
                   uid=session.get("user_id"),
                   hashed_pass=generate_password_hash(request.form.get("password")))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("password.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Return apology if symbol not found
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("couldn't find symbol")

        # Return Quote
        return render_template("quoted.html", name=stock["name"], price=usd(stock["price"]), symbol=stock["symbol"])

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password")

        # Ensure password matches confirmation
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("password doesn't match confirm password")

        # Insert new user in database
        else:
            if not db.execute("INSERT INTO users('username', 'hash') VALUES (:username, :hashed_pass)",
                              username=request.form.get("username"),
                              hashed_pass=generate_password_hash(request.form.get("password"))):
                return apology("username already taken")

        # Log newly registered user in
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username",
                                        username=request.form.get("username"))[0]["id"]

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check if symbol field is empty
        if not request.form.get("symbol"):
            return apology("Please provide a stock name to sell")

        # Check if symbol field is of a not owned stock
        if not db.execute("SELECT stocks.stock_symbol FROM stock_ownership JOIN stocks ON stock_ownership.stock_id = stocks.stock_id WHERE stocks.stock_symbol = :sb AND stock_ownership.user_id = :uid",
                          sb=request.form.get("symbol"),
                          uid=session.get('user_id')):
            return apology("You don't have this stock")

        # Check if amount field is empty
        if not request.form.get("shares"):
            return apology("Please provide an amount to sell")

        # Remember amount
        amount = int(request.form.get("shares"))

        # Check if amount field is greater than amount owned
        if int(request.form.get("shares")) > db.execute("SELECT stock_ownership.amount FROM stock_ownership JOIN stocks ON stock_ownership.stock_id = stocks.stock_id WHERE stocks.stock_symbol = :sb AND stock_ownership.user_id = :uid",
                                                        sb=request.form.get("symbol"),
                                                        uid=session.get('user_id'))[0]["amount"]:
            return apology("You don't have enough stocks")

        # Check if amount filed is equal to amount owned
        elif int(request.form.get("shares")) == db.execute("SELECT stock_ownership.amount FROM stock_ownership JOIN stocks ON stock_ownership.stock_id = stocks.stock_id WHERE stocks.stock_symbol = :sb AND stock_ownership.user_id = :uid",
                                                           sb=request.form.get("symbol"),
                                                           uid=session.get('user_id'))[0]["amount"]:
            if not db.execute("DELETE FROM stock_ownership WHERE stock_id == :sid AND user_id == :uid",
                              sid=db.execute("SELECT stock_id FROM stocks WHERE stock_symbol == :symbol",
                                             symbol=request.form.get("symbol"))[0]["stock_id"],
                              uid=session.get('user_id')):
                return apology("Failed to remove stock from table")

        # Delete stock from ownership
        else:
            if not db.execute("UPDATE stock_ownership SET amount = amount - :amount WHERE stock_id == :sid AND user_id == :uid",
                              amount=amount,
                              sid=db.execute("SELECT stock_id FROM stocks WHERE stock_symbol == :symbol",
                                             symbol=request.form.get("symbol"))[0]["stock_id"],
                              uid=session.get('user_id')):
                return apology("Failed to update amount")

        stock = lookup(request.form.get("symbol"))

        # Add transaction to history
        db.execute("INSERT INTO history ('user_id', 'stock_id', 'transaction_type', 'price', 'stock_amount') VALUES (:uid, :sid, :tt, :p, :sa)",
                   uid=session.get('user_id'),
                   sid=db.execute("SELECT stock_id FROM stocks WHERE stock_symbol == :symbol",
                                  symbol=request.form.get("symbol"))[0]["stock_id"],
                   tt=1,
                   p=amount * stock["price"],
                   sa=amount)

        # Give money of transaction to user
        db.execute("UPDATE users SET cash = cash + :p WHERE users.id = :uid",
                   p=amount * stock["price"],
                   uid=session.get('user_id'))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # Present a menu of all stocks owned
        stocks = db.execute("SELECT stocks.stock_symbol FROM stock_ownership JOIN stocks ON stock_ownership.stock_id = stocks.stock_id WHERE stock_ownership.user_id = :uid",
                            uid=session.get('user_id'))
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
