import sympy as sp

def Maclaur(n,f):
    f_new = sp.lambdify(t,f)
    sum = f_new(0)
    i = 1
    while i < n:
        f = sp.diff(f,t)
        f_new = sp.lambdify(t,f)
        sum = sum + (f_new(0) * (t**i))/sp.factorial(i)
        i += 1
    return sum        

t = sp.symbols('t')
fun_sin1 = sp.sin(t)
fun_e1 = sp.exp(t)
fun_sin2 = sp.sin(10 + t)
fun_e2 = sp.exp(10 + t)
print(Maclaur(6,fun_sin1))
print(Maclaur(6,fun_e1))
print(Maclaur(6,fun_sin2))
print(Maclaur(6,fun_e2))
