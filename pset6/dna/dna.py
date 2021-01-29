import sys #sys.argv
import csv
from cs50 import get_string

# check length of argv
if len(sys.argv)!=3:
    print("Usage: python dna.py [valid CSV file] [valid text file]")
    sys.exit()

# open .csv , record STRs , record STR sequences
with open(sys.argv[1],mode='r',newline='') as csvfile:
    csvDReader=csv.DictReader(csvfile)
    STRs=[]
    count_row=0
    for row in csvDReader:
        STRs.append(row)
keysStr=str(STRs[0].keys())
keysStr=keysStr[keysStr.find("[")+1:keysStr.find("]")].replace("'","").replace(" ","")
STRsequences=keysStr.split(',')[1:]

# open .txt , record DNAsequence
with open(sys.argv[2],mode='r',newline='') as txtfile:
    DNAsequence=txtfile.read()

# build a map_table make [letters]or['\n']->[" "]
in_str="abcdefghijklmnopqrstuvwxyz"
in_str+=in_str.upper()+'\n'
map_table=str.maketrans(in_str," " * 53)
# record targetSTRs
targetSTR=dict.fromkeys(STRsequences)
for STR in STRsequences:
    temp_str=DNAsequence.replace(STR,"|0").replace("0|","0").translate(map_table).replace(" ","")
    temp_list=temp_str.split("|")
    temp_list.sort()
    targetSTR[STR]=len(temp_list[-1])
    #print(temp_list)
for STR in STRs:
    bool_=True
    for key in STRsequences:
        #print(f"name:{STR['name']} key:{key} {targetSTR[key]}vs{STR[key]} type({type(targetSTR[key])}vs{type(STR[key])})")
        if targetSTR[key]!=int(STR[key]):
            bool_=False
            break
        #print("-----------------")
    if (bool_):
        print(STR['name'])
        sys.exit()
print("No match")


