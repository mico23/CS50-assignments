import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

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
# ! Review the lecture about configuring SQL
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Initialize Values
    shares_owned = db.execute("SELECT symbol, shares FROM shares WHERE user_id = :id", id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]['cash']
    value_sum = 0
    shares_summary = []

    # Loop through each stock owned
    for item in shares_owned:

        stock = lookup(item['symbol'])

        if stock:
            stock_name = stock['name']
            stock_price = stock['price']
            current_value = stock_price*item['shares']
            value_sum += current_value
            shares_summary.append((item['symbol'], stock_name, item['shares'], usd(stock_price), usd(current_value)))

        else:
            return apology("Invalid Symbol", 400)

    grand_total = cash + value_sum

    return render_template("index.html", shares_summary=shares_summary, cash=usd(cash),
                           grand_total=usd(grand_total), top='Account Summary')


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # retrieve user info
    share_records = db.execute("SELECT user_id, symbol FROM shares")
    share_records = [(share_record['user_id'], share_record['symbol']) for share_record in share_records]

    balance = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    balance = balance[0]['cash']

    # update user's purchase record
    if request.method == "POST":

        requested_symbol = request.form.get("symbol").upper()

        try:
            if int(request.form.get("shares")) < 0:
                return apology("Invalid Share Value", 400)
        except ValueError:
            return apology("Invalid Share Value", 400)

        requested_shares = int(request.form.get("shares"))

        check = (session["user_id"], requested_symbol)

        stock = lookup(requested_symbol)

        if stock:
            total_cost = stock['price'] * int(requested_shares)
            # Must convert balance[0]['cash'] to int because "balance" is a list
            net_balance = balance - total_cost

            if net_balance >= 0:
                # TO ADD A LINE THAT UPDATES THE SHARES RECORDS
                db.execute("INSERT INTO transactions (price, user_id, symbol, shares, transaction_type) VALUES(:price, :id, :symbol, :shares, :type)",
                           price=stock['price'], id=session["user_id"], symbol=requested_symbol, shares=requested_shares, type='BUY')
                db.execute("UPDATE users SET cash = :balance WHERE id = :id",
                           balance=net_balance, id=session["user_id"])

                # DOUBLE CHECK THE LOGIC HERE
                if check not in share_records:
                    db.execute("INSERT INTO shares (symbol, shares, user_id) VALUES(:symbol, :shares_to_add, :id)",
                               symbol=requested_symbol, shares_to_add=requested_shares, id=session["user_id"])

                else:
                    db.execute("UPDATE shares SET shares = shares + :shares_to_add WHERE user_id = :id AND symbol=:symbol",
                               shares_to_add=requested_shares, id=session["user_id"], symbol=requested_symbol)

                # Must return a result; redirect to home page
                return redirect("/")

            else:
                return apology("Insufficient Balance!", 400)
        else:
            return apology("Invalid Symbol", 400)
    else:
        return render_template("buy.html", balance=usd(balance))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # retrieve user info
    history = db.execute(
        "SELECT symbol, price, shares, transaction_type, date FROM transactions WHERE user_id = :id", id=session["user_id"])
    history = [(record['symbol'], usd(record['price']), record['shares'],
                record['transaction_type'], record['date']) for record in history]

    return render_template("history.html", history=history, top='Transaction History')


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

    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))

        if stock:
            stock_name = stock['name']
            stock_price = usd(stock['price'])
            stock_symbol = stock['symbol']
            message = "Successful Enquiry"
            return render_template("quoted.html", top=message, name=stock_name, price=stock_price, symbol=stock_symbol)

        else:
            '''
            stock_name = "Not Found"
            stock_price = "Not Found"
            stock_symbol = "Not Found"
            message = "Symbol Does Not Exist. Please go back and retry."
            return render_template("quoted.html", top=message, name=stock_name, price=stock_price, symbol=stock_symbol)
            '''
            return apology("invalid stock symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        usernames = db.execute("SELECT username FROM Users")
        usernames = [name['username'] for name in usernames]
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate Username
        if (username in usernames) or (not username):
            return apology("invalid username, please try another", 400)

        # Validate Password
        elif password != confirmation or not password or not confirmation:
            return apology("invalid password", 400)

        else:
            hashed_password = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            # Cannot pass an assigned variable as an argument - e.g. username
            # Need to assign the value to the "variable" as the arugment - e.g. username = request.form.get("username")
            db.execute("INSERT INTO users (username, hash) VALUES(:username, :password)",
                       username=request.form.get("username"), password=hashed_password)

            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                              username=request.form.get("username"))

            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]

            # Redirect the user to the quote page
            return redirect("/quote")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]['cash']

        requested_symbol = request.form.get("symbol").upper()

        # DO NOT FORGET THE INDEX OF THE ARRAY RETURNED FROM DB.EXECUTE
        share_records = db.execute("SELECT shares FROM shares WHERE symbol=:symbol AND user_id=:id",
                                   id=session["user_id"], symbol=requested_symbol)[0]["shares"]

        # Check the user input is valid
        try:
            if int(request.form.get("shares")) < 0:
                return apology("Invalid Share Value", 400)
        except ValueError:
            return apology("Invalid Share Value", 400)

        # Calculate the shares
        requested_shares = int(request.form.get("shares"))
        shares_left = share_records - requested_shares

        # Update the user's shares if the 'shares_left' is a possitve number
        stock = lookup(requested_symbol)

        if stock:
            stock_price = stock['price']

            # TO DO

            if shares_left >= 0:

                stock_sold = stock_price * requested_shares

                db.execute("INSERT INTO transactions (price, user_id, symbol, shares, transaction_type) VALUES(:price, :id, :symbol, :shares, :type)",
                           price=stock['price'], id=session["user_id"], symbol=requested_symbol, shares=requested_shares, type='SELL')
                db.execute("UPDATE users SET cash = :balance WHERE id = :id",
                           balance=cash + stock_sold, id=session["user_id"])

                db.execute("UPDATE shares SET shares = :shares_left WHERE user_id = :id AND symbol=:symbol",
                           shares_left=shares_left, id=session["user_id"], symbol=requested_symbol)

                # Must return a result; redirect to home page
                return redirect("/")

            else:
                return apology("Insufficient Shares!", 400)
        else:
            return apology("Invalid Symbol", 400)

    # If the request is invalid, do nothing.
    else:
        share_symbol = db.execute("SELECT symbol FROM shares WHERE user_id = :id", id=session["user_id"])
        share_symbol = [item["symbol"] for item in share_symbol]
        return render_template("sell.html", share_symbol=share_symbol)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
