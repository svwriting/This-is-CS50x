from cs50 import get_int
import math

inN=get_int("Number:");
Nl=int(math.log(inN,10))+1
if Nl not in [13,15,16]:
    print("INVALID")
nums=[0]*Nl
for i in range(Nl):
    nums[i]=inN%10
    inN//=10
nums=nums[::-1]
oddnums=nums[0::2]
sum_=0;
for num in oddnums:
    num1=2*num if num<5 else (2*num)%10+1
    sum_+=num1
strAns="INVALID"
if((sum_+sum(nums[1::2]))%10==0):
    if Nl==13:
        if (nums[0]==4):
            strAns="VISA"
    elif Nl==15:
        if (nums[0]==3 and (nums[1]==4 or nums[1]==7)):
            strAns="AMEX"
    elif Nl==16:
        if (nums[0]==4):
            strAns="VISA"
        elif(nums[0]==5 and nums[1]>=1 and nums[1]<=5):
            strAns="MASTERCARD"
print(strAns)

