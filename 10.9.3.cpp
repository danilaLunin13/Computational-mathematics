#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

//ввод начальных данных
int N = 1000;
int mu = 1000;

//таблица Бутчера 3-стадийного неявного схемы Рунге-Кутты
vector<vector<double>> A = {
        {1./3, 0, 0},
        {0, 1, 0},
        {3./4, -1./12, 1./3},
};
vector<double> C = {1./3, 1, 1};
vector<double> D = {3./4 , -1./12, 1./3};

// вектор функций
vector<double> Fun(double x,double dxdt){
    return {dxdt,
            mu*(1 - pow(dxdt,2))*dxdt - x};
};

//Метод простой итерации для нахождения k-коэф.
void Simple_Iteration(int num,vector<vector<double>>& K, vector<double> now_value){
    K[0][num] = 0.5;
    K[1][num] = 0.5;
    double x_new, dxdt_new;
    for (int i = 0; i < 1; ++i) {
        x_new = now_value[0];
        dxdt_new = now_value[1];
        for (int j = 0; j < C.size(); ++j) {
            x_new += A[num][j]*K[0][j];
            dxdt_new += A[num][j]*K[1][j];
        }
        K[0][num] = Fun(x_new, dxdt_new)[0];
        K[1][num] = Fun(x_new, dxdt_new)[1];
    }
}

//Нахождение k-коэф. 3-стадийной неявной схемы Рунге-Кутты
vector<vector<double>> Coef(double x, double dxdt){
    vector<vector<double>> K (2, vector<double> (C.size()));
    vector<double> coef_now (2);
    for (int i = 0; i < C.size(); ++i) {
        Simple_Iteration(i, K, {x, dxdt});
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
        vector<vector<double>> K = Coef(Result[i-1][1], Result[i-1][2]);
        for (int j = 0; j < C.size(); ++j) {
            Result[i][1] += D[j]* K[0][j];
            Result[i][2] += D[j]* K[1][j];
        }
    }

    //Вывод решения
    for (int i = 0; i < 3; ++i) {
        cout << Result[i][1] << " " << Result[i][2] << endl;
    }

    return 0;
}