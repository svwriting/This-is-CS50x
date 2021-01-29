from cs50 import get_float

N=get_float("Change owed:")
while(N<0):
    N=get_float("Change owed:")
N=int(N*100)

coin=[25,10,5,1]
count_=0
for c in coin:
    count_+=N//c
    N%=c
print(count_)
