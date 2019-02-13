from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Split input to lists of their lines
    a = a.split("\n")
    b = b.split("\n")

    # Prepare list of identical lines
    identical_lines = []

    # Make list of identical lines (without duplicates)
    for i in a:
        if i not in identical_lines and i in b:
            identical_lines.append(i)

    return identical_lines


def sentences(a, b):
    """Return sentences in both a and b"""

    # Make lists of contained sentences in a and b
    a = sent_tokenize(a)
    b = sent_tokenize(b)

    # Prepare list of identical sentences
    identical_sentences = []

    # Make list of identical sentences (without duplicates)
    for i in a:
        if i not in identical_sentences and i in b:
            identical_sentences.append(i)

    return identical_sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # Make lists of size a and b, to be used as indexes to a and b
    a_list = range(len(a))
    b_list = range(len(b))

    # Prepare list of identical substrings
    identical_substrings = []

    # Make list of identical substrings
    for i in a_list:
        substring = a[i:i + n]
        # Ensure substring is as long as we want
        if len(substring) == n:
            for j in b_list:
                # Check if 'substring' is not a duplicate and matches a substring in 'b'
                if substring not in identical_substrings and substring == b[j:j + n]:
                    identical_substrings.append(substring)

    return identical_substrings
