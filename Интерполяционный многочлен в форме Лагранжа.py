import sympy as sym

class Pol_Lagrange:
    
    def __init__(self, X, Y):
        self.x = sym.Symbol('x')
        self.ans = 0
        for i in range(len(X)):
            M = X[:]
            x_k = M[i]
            pol = 1
            M.remove(x_k)
            for j in M:
                pol *= self.x - j
            for k in M:
                pol /= x_k - k
            self.ans += Y[i]*pol
    
    def Value(self, arg):
        return self.ans.subs(self.x, arg)

X = input().split()
X = list(map(float, X))

Y = input().split()
Y = list(map(float, Y))

x = int(input())

Pol = Pol_Lagrange(X, Y)
print(Pol.Value(x))
