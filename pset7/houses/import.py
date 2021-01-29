# TODO
from cs50 import SQL
import csv
import sys
import os

# Check command-line arguments
if(len(sys.argv)!=2 or not sys.argv[1].endswith(".csv")):
    print("Usage: python import.py [valid CSV file]")
    sys.exit()
if (not os.path.isfile(sys.argv[1])):
    print("csv file not exists")
# Open CSV file given by command-line argument
# For each row, parse name
with open(sys.argv[1],mode='r') as csvfile:
    csvDictReader=csv.DictReader(csvfile)
    Students , stu_i={},0
    for row in csvDictReader:
        Students[stu_i]=row
        if Students[stu_i]['name'].count(' ')==1:
            Students[stu_i]['name']=Students[stu_i]['name'].replace(' ',"  ")
        stu_i+=1
# so we can: db.execute("QUERY")
db=SQL("sqlite:///students.db")
for i in range(stu_i):
    name_=Students[i]['name'].split(" ")
    fn=name_[0]
    mn=name_[1]
    ln=name_[2]
    db.execute("INSERT INTO students (id,first,middle,last,house,birth) VALUES( ?, ?, ?, ?, ?, ? )",
i,fn,mn,ln,Students[i]['house'],int(Students[i]['birth']))

