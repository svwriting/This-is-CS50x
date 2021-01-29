from cs50 import get_string

STR=get_string("Text:")
WN=STR.count(" ")+1
SN=STR.count("!")+STR.count("?")+STR.count(".")
LN=len(STR)-WN-SN-STR.count('"')-STR.count("-")
bigL=LN/WN
bigS=SN/WN
index = 5.88 * bigL - 29.6 * bigS - 15.8
if index>16:
    print("Grade 16+")
elif index<1:
    print("Before Grade 1")
else:
    print(f"Grade {round(index)}")
    
