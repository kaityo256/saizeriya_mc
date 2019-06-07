import pickle
import sqlite3

conn = sqlite3.connect('saizeriya.db')
names = []
prices = []
cals = []

for (n, p, c) in conn.cursor().execute('SELECT name, price, calorie FROM menu'):
    names.append(n)
    prices.append(p)
    cals.append(c)

with open('saizeriya.pickle', 'wb') as f:
    pickle.dump((names, prices, cals), f)
