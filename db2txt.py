import sqlite3

conn = sqlite3.connect('saizeriya.db')
c = conn.cursor()
for (p, n, c) in c.execute('SELECT name, price, calorie FROM menu'):
    print(p,n,c)
conn.close()

