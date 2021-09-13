from sympy.abc import x
from sympy import expand

X = input().split()
X = list(map(float, X))

Y = input().split()
Y = list(map(float, Y))

def Dis(F_arg):
    print(F_arg)
    if len(F_arg) > 2:
        return (Dis(F_arg[:].pop(0)) - Dis(F_arg[:].pop(-1))) / (F_arg[-1] - F_arg[0])
    elif len(F_arg) > 1:
        return Y[X.index(F_arg[-1])] - Y[X.index(F_arg[0])] / (F_arg[-1] - F_arg[0])
    else:
        return Y[0]

def multi(k):
    ans = 1
    for i in range(k):
        ans *= x - X[i]
    return ans

ans = 0
for i in range(len(X)-1):
    ans += multi(i) * Dis(X[0:i+1])
print(expand(ans))