from sympy.abc import x
from sympy import expand

X = input().split()
X = list(map(float, X))

Y = input().split()
Y = list(map(float, Y))

def aux_pol(X, k):
    M = X
    x_k = M[k]
    pol = 1
    M.remove(x_k)
    for i in M:
        pol *= x - i
    for i in M:
        pol /= x_k - i
    return pol

ans = 0
for i in range(len(X)):
    ans += Y[i]*aux_pol(X[:],i)
print(expand(ans))