import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp

from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
import datetime

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
    record = db.execute("SELECT symbol,sum(shares) as total FROM record where id = ? GROUP BY symbol having sum(shares)>0 ",session["user_id"])
    cur = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cur[0]["cash"]= usd(cur[0]["cash"])
    for i in range(len(record)):
        symbol = record[i]["symbol"]
        output =  lookup(symbol)
        company_name = output["name"]
        price = output["price"]
        record[i]["price"]=usd(price)
        record[i]["name"]=company_name
        record[i]["total_money"]= usd(record[i]["total"]*price)

    return render_template("index.html", cash=cur,records=record)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
       symbol = request.form.get("symbol")
       shares =  request.form.get("shares")
       output=   lookup(symbol)
       cur = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
       if output !=None:
          cost = float(output["price"])*int(shares)
          if cur[0]["cash"]>= cost:
             now = str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
             db.execute("INSERT INTO record (id, symbol ,shares, price, time) VALUES(?, ?, ?, ?, ?)", session["user_id"],symbol,int(shares),float(output["price"]),now)
             db.execute("UPDATE users set cash=? where id= ?",cur[0]["cash"]-cost ,session["user_id"])
             return redirect("/")
          else:
              return apology("Can't Afford",403)
       else:
           return apology("Invalid Symbol",403)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    record = db.execute("SELECT * FROM record where id = ? ",session["user_id"])
    return render_template("history.html", records=record)

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
       symbol = request.form.get("symbol")
       output=lookup(symbol)
       if output !=None:
           output["price"]=usd(output["price"])
           return render_template("quote.html" , answer=output)
       else:
           return apology("Invalid Symbol",403)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
       username = request.form.get("username")
       password = request.form.get("password")
       check    = request.form.get("check")

       if not request.form.get("username") or not request.form.get("password")  or not request.form.get("check"):
           return apology("input should not be blank",403)

       if  password != check:
            return apology("the passwords do not match",403)

       rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
       if len(rows) == 1:
            return apology("the username already exists",403)

       db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
       return  redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
       symbol = request.form.get("symbol")
       shares =  request.form.get("shares")
       output=   lookup(symbol)
       earn = float(output["price"])*int(shares)

       check = db.execute("SELECT * FROM record WHERE id = ? and symbol= ? ", session["user_id"],symbol)
       amount = db.execute("SELECT sum(shares) as amount FROM record WHERE id = ? and symbol= ? ", session["user_id"],symbol)
       cur = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
       if len(check) >0 :
          if amount[0]["amount"]>= int(shares) :
             now = str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
             db.execute("INSERT INTO record (id, symbol ,shares, price, time) VALUES(?, ?, ?, ?, ?)", session["user_id"],symbol,-int(shares),float(output["price"]),now)
             db.execute("UPDATE users set cash=? where id= ?",cur[0]["cash"]+earn ,session["user_id"])
             return redirect("/")
          else:
              return apology("Do not have enough shares",403)
       else:
           return apology("Invalid Symbol",403)

    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
