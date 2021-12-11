#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

//ввод начальных данных
int N = 1000;
int mu = 1000;

//таблица Бутчера (В матрице A только диаг. элементы)
vector<vector<double>> A = {
        {1./3, 0, 0},
        {0, 1, 0},
        {3./4, -1./12, 1./3},
                    };
vector<double> C = {1./3, 1, 1};
vector<double> D = {3./4 , -1./12, 1./3};

// вектор функций
vector<double> Fun(double t,double x,double dxdt){
    return {dxdt,
            mu*(1 - pow(dxdt,2))*dxdt - x};
}

//Нахождение k-коэф. 3-стадийной неявной схемы Рунге-Кутты
vector<vector<double>> Coef(double t,double x, double dxdt){
    vector<vector<double>> K (2, vector<double> (C.size()));
    double x_new = x;
    double dxdt_new = dxdt;
    for (int i = 0; i < C.size(); ++i) {
        for (int j = 0; j < C.size(); ++j) {
            x_new += A[i][j]*K[0][j];
            dxdt_new += A[i][j]*K[1][j];
        }
        K[0][i] = Fun(t + C[i], x_new, dxdt_new)[0];
        K[1][i] = Fun(t + C[i], x_new, dxdt_new)[1];
    }
    return K;
}

int main() {

    //создание вектора-решения уравнения Релея
    vector<vector<double>> Result (N, vector<double> (3));
    Result[0] = {0, 0, 0.001};

    //Последовательное нахождение решения задачи
    for (int i = 1; i < N; ++i) {
        Result[i][0] = i;
        Result[i][1] = Result[i-1][1];
        Result[i][2] = Result[i-1][2];
        vector<vector<double>> K = Coef(Result[i-1][0], Result[i-1][1], Result[i-1][2]);
        for (int j = 0; j < C.size(); ++j) {
            Result[i][1] += D[j]* K[0][j];
            Result[i][2] += D[j]* K[1][j];
        }
        cout << Result[i][1] << " " << Result[i][2] << endl;
    }

    return 0;
}