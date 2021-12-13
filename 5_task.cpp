#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

//ввод начальных данных
int N = 100;
double mu = 0.012277471;
double nu = 1 - mu;
double T = 17.0652165601579625588917206249;

//таблица Бутчера 3-стадийного неявного схемы Рунге-Кутты
vector<vector<double>> A = {
        {1./3, 0, 0},
        {0, 1, 0},
        {3./4, -1./12, 1./3},
};
vector<double> C = {1./3, 1, 1};
vector<double> D = {3./4 , -1./12, 1./3};

// вектор функций
vector<double> Fun(vector<double> position){
    double A = pow(pow(position[0] + mu, 2) + pow(position[1], 2), 1.5);
    double B = pow(pow(position[0] - nu, 2) + pow(position[1], 2), 1.5);
    return {
        position[3],
        position[4],
        position[0] + 2*position[4] - nu*(position[0] + mu)/A - mu*(position[0] - nu)/B,
        position[1] - 2*position[3] - nu*position[1]/A - mu*position[1]/B
    };
};

//Метод простой итерации для нахождения k-коэф.
void Simple_Iteration(int num,vector<vector<double>>& K, vector<double> now_value){
    for (int i = 0; i < K.size(); ++i) {
        K[i][num] = 0;
    }
    vector<double> position_now;
    for (int i = 0; i < 1; ++i) {
        position_now = now_value;
        for (int j = 0; j < C.size(); ++j) {
            for (int k = 0; k < now_value.size(); ++k) {
                position_now[k] += A[num][j] * K[k][j];
            }
        }
        for (int j = 0; j < K.size(); ++j) {
            K[j][num] = Fun(position_now)[j];
        }
    }
}

//Нахождение k-коэф. 3-стадийной неявной схемы Рунге-Кутты
vector<vector<double>> Coef(vector<double> position){
    vector<vector<double>> K (position.size(), vector<double> (C.size()));
    vector<double> coef_now (position.size());
    for (int i = 0; i < C.size(); ++i) {
        Simple_Iteration(i, K, position);
    }
    return K;
}

int main() {

    //создание вектора-решения системы уравнения
    vector<vector<double>> Result (N, vector<double> (4));
    Result[0] = {
            0.994,
            0,
            0,
            -2.00158510637908252240537862224};

    //Последовательное нахождение решения задачи
    for (int i = 1; i < N; ++i) {
        Result[i] = Result[i-1];
        vector<vector<double>> K = Coef(Result[i-1]);
        for (int j = 0; j < C.size(); ++j) {
            for (int k = 0; k < Result[i].size(); ++k) {
                Result[i][k] += D[j]* K[k][j];
            }
        }
    }

    //Вывод решения
    for (int i = 0; i < N; ++i) {
        cout << Result[i][1] << " " << Result[i][2] << endl;
    }

    return 0;
}