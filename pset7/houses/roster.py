# TODO
from cs50 import SQL
import sys

# Check command-line arguments
if(len(sys.argv)!=2):
    print("Usage: python import.py [house]")
    sys.exit()

# Query database for all students in house
# Studens should be sorted alphabetically by last names, then first name
db=SQL("sqlite:///students.db")
students_=db.execute("SELECT first||' '||middle||' '||last AS name,birth FROM students WHERE house=? ORDER BY last,first",sys.argv[1])

# Print out each student's full name and birth year
for student in students_:
    print(f"{student['name'].replace('  ',' ')}, born {student['birth']}")
