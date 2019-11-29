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

    # TODO
    if not request.args.get("geo"):
        raise RuntimeError("missing geo value")
    else:
        # look up news for the geo information provided
        geo = request.args.get("geo")
        articles = lookup(geo)

    # TO TEST: https://ide50-micox.cs50.io/articles?geo=02138
    return jsonify(articles)


@app.route("/search")
def search():
    """Search for places that match query"""

    # TODO
    # For now, assuming the input patten is "City", followed by "State", followed by "Country"

    if not request.args.get("q"):
        raise RuntimeError("missing keyword")
    else:
        # first check if the q contians multiple parts or not
        # then use different query to retreive data from the database

        # search by postal code or city name
        if re.search("^\w+$", request.args.get("q")):
            keyword_1 = request.args.get("q")
            places = db.execute("""SELECT *
                                FROM "places"
                                WHERE "place_name" LIKE :keyword_1
                                OR "admin_code1" LIKE :keyword_1
                                OR "admin_name1" LIKE :keyword_1
                                OR "postal_code" LIKE :keyword_1""", keyword_1=keyword_1 + "%")

        # search by city name and state/province with separator "+"
        elif re.search("^\w+\s\w+$", request.args.get("q")):
            keyword_1, keyword_2 = request.args.get("q").split(" ")
            places = db.execute("""SELECT *
                                FROM "places"
                                WHERE "place_name" LIKE :keyword_1
                                OR "admin_name1" LIKE :keyword_2
                                OR "admin_code1" LIKE :keyword_2""",
                                keyword_1=keyword_1 + "%", keyword_2=keyword_2 + "%")

        # search by city name and state/province with separator ", "
        elif re.search("^\w+\,\s\w+$", request.args.get("q")):
            keyword_1, keyword_2 = request.args.get("q").split(", ")
            places = db.execute("""SELECT *
                                FROM "places"
                                WHERE "place_name" LIKE :keyword_1
                                OR "admin_name1" LIKE :keyword_2
                                OR "admin_code1" LIKE :keyword_2""",
                                keyword_1=keyword_1 + "%", keyword_2=keyword_2 + "%")

        # search by city name, state/province, and country with separator ", "
        elif re.search("^\w+\,\s\w+\,\s\w+$", request.args.get("q")):
            keyword_1, keyword_2, keyword_3 = request.args.get("q").split(", ")
            places = db.execute("""SELECT *
                                FROM "places"
                                WHERE "place_name" LIKE :keyword_1
                                OR "admin_name1" LIKE :keyword_2
                                OR "admin_code1" LIKE :keyword_2
                                AND "country_code" LIKE :keyword_3""",
                                keyword_1=keyword_1 + "%", keyword_2=keyword_2 + "%", keyword_3=keyword_3 + "%")

        else:
            return jsonify([])

        # TO TEST:
        # https://ide50-micox.cs50.io/search?q=02138
        # https://ide50-micox.cs50.io/search?q=Cambridge
        # https://ide50-micox.cs50.io/search?q=Cambridge,+Massachusetts
        # https://ide50-micox.cs50.io/search?q=New%20Haven,+CT,+US
        return jsonify(places)


@app.route("/update")
def update():
    """Find up to 10 places within view"""

    # Ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # Ensure parameters are in lat,lng format
    # "-?" can ensure no matter the negative sign is included
    # '^' indicates the begining; '$' indicates the end
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    print("For testing" + request.args.get("sw"))

    # Explode southwest corner into two variables
    sw_lat, sw_lng = map(float, request.args.get("sw").split(","))

    # Explode northeast corner into two variables
    ne_lat, ne_lng = map(float, request.args.get("ne").split(","))

    # Find 10 cities within view, pseudorandomly chosen if more within view
    if sw_lng <= ne_lng:

        # Doesn't cross the antimeridian
        # The SQL selects the "top 10" cities
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
