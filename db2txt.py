import sqlite3

conn = sqlite3.connect('saizeriya.db')
c = conn.cursor()
fn = open("name.txt","w")
fp = open("price.txt","w")
fc = open("calorie.txt","w")
for (n, p, c) in c.execute('SELECT name, price, calorie FROM menu'):
    fp.write(str(p) + "\n")
    fn.write(str(n) + "\n")
    fc.write(str(c) + "\n")
    print(p,n,c)
conn.close()
