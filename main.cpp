#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// x = 1/2 * 1/sqrt(2) * e^(-1/2) * e^(x^2)

double fun1(double x){
    return 0.5 * pow(2,-0.5) * exp(-0.5 + pow(x,2));
}

// x = (3/2*ln(2) + 1/2 + ln(x))/x

double fun2(double x){
    return (1./2 + 3./2* log(2) + log(x))/x;
}

int main(){
    // y_max = 1./pow(2,0.5)* exp(-1/2);
    // y_max/2 = x*e^(-x^2)

    double x_old = 0;
    double x_new;
    while (true){
        x_new = fun1(x_old);
        if (abs(x_new - x_old) <= 0.5 * pow(10,-3)){
            break;
        }
        x_old = x_new;
    }
    double x1 = x_new;
    cout << setprecision(3) << x_new << endl;
    x_old = 1;
    while (true){
        x_new = fun2(x_old);
        if (abs(x_new - x_old) <= 0.5 * pow(10,-3)){
            break;
        }
        x_old = x_new;
    }
    double x2 = x_new;
    cout << setprecision(4) << x_new << endl;
    cout << x2 - x1;
}