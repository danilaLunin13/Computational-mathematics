#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

//ввод начальных данных
int N = 100000;
int mu = 1000;
double h = 10./(N - 1);

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
    return {position[2],
            mu*(1 - pow(position[2], 2))*position[2] - position[1]};
};

//Нахождение k-коэф. 3-стадийной неявной схемы Рунге-Кутты с помощью метода простых итераций
void Coef(vector<double> position, vector<vector<double>>& K){
    vector<double> new_position;
    vector<double> F;
    for (int i = 0; i < 10; ++i) {
        new_position = position;
        for (int j = 0; j < C.size(); ++j) {
            new_position[0] += C[j]*h;
            for (int k = 0; k < C.size(); ++k) {
                new_position[1] += h*A[j][k]*K[0][k];
                new_position[2] += h*A[j][k]*K[1][k];
            }
            F = Fun(new_position);
            K[0][j] = F[0];
            K[1][j] = F[1];
        }
    }
}

int main() {

    //создание вектора-решения уравнения Релея
    vector<vector<double>> Result (N, vector<double> (3));
    Result[0] = {0, 0, 1};

    //Последовательное нахождение решения задачи
    for (int i = 1; i < N; ++i) {
        vector<double> F = Fun(Result[i - 1]);
        vector<vector<double>> K = {{F[0], F[0], F[0], F[0]},
                                    {F[1], F[1], F[1], F[2]}};
        Result[i] = {Result[i - 1][0] + h, Result[i-1][1], Result[i-1][2]};
        Coef(Result[i - 1], K);
        for (int j = 0; j < C.size(); ++j) {
            Result[i][1] += h*D[j]* K[0][j];
            Result[i][2] += h*D[j]* K[1][j];
        }
    }

    //Вывод решения
    for (int i = 0; i < N; ++i) {
        cout  << Result[i][0] << "\t" << Result[i][1] << endl;
    }

    return 0;
}