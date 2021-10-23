#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double fun(double x){
    return sin(100*x) * exp(-pow(x,2)) * cos(2*x);
}

double three_eighths(vector<double> v){
    double ans = 0;
    vector<double> set = {v[0], (2*v[0]+v[1])/3, (v[0]+2*v[1])/3, v[1]};
    for (auto i : set){
        if (i == (2*v[0]+v[1])/3 or i == (v[0]+2*v[1])/3){
            ans += 3*fun(i);
        } else {
            ans += fun(i);
        }
    }
    ans *= (v[1] - v[0])/8;
    return ans;
}

int main(){
    vector<double> points = {0};
    int n = 10000;
    for (int i = 0; i < n; ++i) {
        points.push_back(points[i] + 3./n);
    }
    double integral = 0;
    for (int i = 0; i < n; ++i) {
        integral += three_eighths({points[i], points[i+1]});
    }
    cout << setprecision(15) << integral;
    return 0;
}
