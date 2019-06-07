import pickle
import sqlite3

names = []
prices = []
cals = []

with sqlite3.connect('saizeriya.db') as conn:
    cur = conn.cursor()
    for (n, p, c) in cur.execute('SELECT name, price, calorie FROM menu'):
        names.append(n)
        prices.append(p)
        cals.append(c)

with open('saizeriya.pickle', 'wb') as f:
    pickle.dump((names, prices, cals), f)
