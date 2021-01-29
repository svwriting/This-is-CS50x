from cs50 import get_int

N=get_int("Height:")
while(8<N or N<1):
    N=get_int("Height:")
for i in range(1,N+1):
    print(f"{' '*(N-i)}{'#'*i}")