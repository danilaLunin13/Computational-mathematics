#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Spline{

private:
    vector<double> X, Y;
    int N;
    vector<vector<double>> Coef;

public:
    Spline(vector<double>& x,
           vector<double>& y){
        X = x;
        Y = y;
        N = x.size();

        vector<double> Intervals(N-1);
        for (int i = 0; i < N-1; ++i) {
            Intervals[i] = X[i+1] - X[i];
        }

        vector<double> RelatInter1(N-2);
        for (int i = 0; i < N-2; ++i) {
            RelatInter1[i] = Intervals[i] / (Intervals[i] + Intervals[i+1]);
        }

        vector<double> RelatInter2(N-2);
        for (int i = 0; i < N-2; ++i) {
            RelatInter2[i] = Intervals[i+1] / (Intervals[i+1] + Intervals[i]);
        }

        vector<double> LineDis(N-1);
        for (int i = 0; i < N-2; ++i) {
            LineDis[i] = 6*Dis({X[i], X[i+1], X[i+2]});
        }
        LineDis[N-2] = 6*Dis({X[N-3], X[N-2], X[N-1]});

        vector<vector<double>> Matrix(N-1);
        for (int i = 0; i < N-1; ++i) {
            Matrix[i].resize(N-1);
            for (int j = 0; j < N-1; ++j) {
                Matrix[i][j] = 0;
            }
        }
        for (int i = 1; i < N-1; ++i) {
            Matrix[i][i-1] = RelatInter1[i-1];
        }
        for (int i = 0; i < N-2; ++i) {
            Matrix[i][i+1] = RelatInter2[i];
        }
        for (int i = 0; i < N-1; ++i) {
            Matrix[i][i] = 2;
            }

        vector<double> a(N-1);
        for (int i = 1; i < N; ++i) {
            a[i-1] = Y[i];
        }

        vector<double> c = Method(Matrix, LineDis);

        vector<double> d(N-1);
        d[0] = c[0]/Intervals[0];
        for (int i = 1; i < N-1; ++i) {
            d[i] = (c[i] - c[i-1])/Intervals[i];
        }

        vector<double> b(N-1);
        b[0] = 1/Intervals[0] *
                (a[0]-d[0]/6*pow(Intervals[0],3)+c[0]/2* pow(Intervals[0],2)-Y[0]);
        for (int i = 1; i < N-1; ++i) {
            b[i] = b[i-1] + c[i]*Intervals[i] - d[i]/2*pow(Intervals[i],2);
        }

        Coef.resize(N-1);
        for (int i = 0; i < N-1; ++i) {
            Coef[i] = {a[i], b[i], c[i]/2, d[i]/6};
        }
    }

double Dis(vector<double> x){
    vector<double> arg1(x.begin(), x.end()), arg2(x.begin(), x.end());
    if (x.size() > 2){
        arg1.erase(arg1.begin());
        arg2.erase(arg2.begin() + arg2.size() - 1);
        return (Dis(arg1) - Dis(arg2))/(x[-1] - x[0]);
    } else {
        return (Y[find(X.begin(), X.end(), x[1]) - X.begin()] -
               Y[find(X.begin(), X.end(), x[0]) - X.begin()]) /
               (x[1] - x[0]);
    }
}

vector<double> Method(vector<vector<double>> A, vector<double> b) {
    vector<double> ans(N - 1), v(N - 1), u(N - 1);
    v[0] = A[0][1] / -A[0][0];
    u[0] = b[0] / A[0][0];
    v[N - 2] = 0;
    u[N-2] = (A[N-2][N-3] - b[N-2]) / (-A[N-2][N-2] - A[N-2][N-3]*v[N-3]);
    for (int i = 1; i < N - 2; ++i) {
        v[i] = A[i][i + 1] / -(A[i][i] + A[i][i - 1] * v[i - 1]);
        u[i] = A[i][i - 1] * u[i - 1] - b[i];
    }
    ans[N - 2] = u[N - 2];
    for (int i = N-3; i >= 0; --i) {
        ans[i] = v[i] * ans[i+1] + u[i];
    }
    return ans;
}

vector<vector<double>> SplineCoefficient(){
    return Coef;
    }
};

int main() {
    int N;
    cin >> N;

    vector <double> X(N);
    vector <double> Y(N);

    for (int i = 0; i < N; ++i) {
        double a;
        cin >> a;
        X[i] = a;
    }

    for (int i= 0; i < N; ++i) {
        double a;
        cin >> a;
        Y[i] = a;
    }

    Spline spline(X, Y);
    vector<vector<double>> Ans = spline.SplineCoefficient();
    for (int i = 0; i < N-1; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << Ans[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}