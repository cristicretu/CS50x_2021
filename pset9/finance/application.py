import os
import requests

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
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
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT * FROM current WHERE user_id IN(?)", session["user_id"])
    user = db.execute("SELECT cash FROM users WHERE id IN(?)", session["user_id"])
    return render_template("index.html", portfolio=portfolio, cash=user)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a symbol")
        if not request.form.get("shares"):
            return apology("must provide no. of shares")
        if int(request.form.get("shares")) < 1:
            return apology("Shares must be >= 1")
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        base_url = f'https://cloud.iexapis.com/stable/stock/{symbol}/quote?token={os.environ.get("API_KEY")}'
        try:
            r = requests.get(base_url)
            data = r.json()
        except:
            return apology("Invalid symbol", 400)

        symbol = data['symbol']
        price = data['latestPrice']
        time = datetime.now().strftime("%Y-%m-%d, %H:%M:%S")

        # total_price = price * shares;
        current_price = db.execute("SELECT cash FROM users WHERE id IN(?)", session["user_id"])
        current_price = current_price[0]['cash']

        cost = int(shares) * price

        if cost > current_price:
            return apology("Not enough money :(", 400)

        db.execute("INSERT INTO stocks (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, shares, price, time)
        db.execute("UPDATE users SET cash = ? WHERE id IN(?)", current_price - cost, session["user_id"])
        curr = db.execute("SELECT shares FROM current WHERE user_id IN(?) AND symbol IN(?)", session["user_id"], symbol)

        if len(curr) < 1:
            db.execute("INSERT INTO current (user_id, symbol, shares) VALUES(?, ?, ?)", session["user_id"], symbol, shares)
        else:
            db.execute("UPDATE current SET shares = shares + ? WHERE user_id IN(?) AND symbol IN(?)", int(shares), session["user_id"], symbol)

        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id IN(?)", session["user_id"])
    return render_template("history.html", stocks=stocks)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash('You were successfully logged in')
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
        if not request.form.get("symbol"):
            return apology("Please input a symbol", 403)

        symbol = request.form.get("symbol")
        base_url = f'https://cloud.iexapis.com/stable/stock/{symbol}/quote?token={os.environ.get("API_KEY")}'

        # Try to get to the URL, return answer if symbol exists else 400
        try:
            r = requests.get(base_url)
            data = r.json()
            return render_template("quoted.html", data=data)
        except:
            return apology("Invalid symbol", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        username = request.form.get("username")
        password = request.form.get("password")

        # This means that a user already uses this username
        checkers = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(checkers) == 1:
            return apology("Username already exists!", 403)

        # Insert new user into database
        password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a symbol")
        if not request.form.get("shares"):
            return apology("must provide no. of shares")
        if int(request.form.get("shares")) < 1:
            return apology("Shares must be >= 1")
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        base_url = f'https://cloud.iexapis.com/stable/stock/{symbol}/quote?token={os.environ.get("API_KEY")}'
        try:
            r = requests.get(base_url)
            data = r.json()
        except:
            return apology("Invalid symbol", 400)

        symbol = data['symbol']
        price = data['latestPrice']
        time = datetime.now().strftime("%Y-%m-%d, %H:%M:%S")

        current_price = db.execute("SELECT cash FROM users WHERE id IN(?)", session["user_id"])
        current_price = current_price[0]['cash']

        cost = int(shares) * price

        shares = int(shares)
        HAIDI = - shares

        curr = db.execute("SELECT shares FROM current WHERE user_id IN(?) AND symbol IN(?)", session["user_id"], symbol)

        current = curr[0]
        current = current['shares']

        if shares > current:
            return apology("Mot enough shares to sell")

        db.execute("INSERT INTO stocks (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, HAIDI , price, time)
        db.execute("UPDATE users SET cash = ? WHERE id IN(?)", current_price + cost, session["user_id"])

        db.execute("UPDATE current SET shares = shares - ? WHERE user_id IN(?) AND symbol IN(?)", int(shares), session["user_id"], symbol)

        flash("Sold!")
        return redirect("/")

    else:
        names = db.execute("SELECT symbol FROM current WHERE user_id IN(?)", session["user_id"])
        return render_template("sell.html", stocks=names)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
