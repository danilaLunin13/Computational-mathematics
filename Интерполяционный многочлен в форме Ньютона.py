import sympy as sym

class Pol_Newton:
    
    def __init__(self, X, Y):
        self.X = X[:]
        self.Y = Y[:]
        self.x = sym.Symbol('x')
        self.ans = self.Y[0]
        for i in range(1, len(self.X)):
            self.ans += self.Multi(i) * self.Dis(self.X[0:i+1])
        print(sym.expand(self.ans))
     
    def Dis(self, F_arg):
        if len(F_arg) > 2:
            return (self.Dis(F_arg[1:len(F_arg)]) - self.Dis(F_arg[0:len(F_arg)-1])) / (F_arg[-1] - F_arg[0])
        else:
            return (self.Y[self.X.index(F_arg[1])] - self.Y[self.X.index(F_arg[0])]) / (F_arg[1] - F_arg[0])

    def Multi(self, k):
        mlt = 1
        for i in range(k):
            mlt *= self.x - self.X[i]
        return mlt
    
    def Value(self, arg):
        return self.ans.subs(self.x, arg)

X = input().split()
X = list(map(float, X))

Y = input().split()
Y = list(map(float, Y))

x = float(input())

Pol = Pol_Newton(X, Y)
print(Pol.Value(x))
