#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

//ввод начальных данных
int N = 100;
double mu = 0.012277471;
double nu = 1 - mu;
double h = 17.0652165601579625588917206249;

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
            position[2],
            position[3],
            position[0] + 2*position[3] - nu*(position[0] + mu)/A - mu*(position[0] - nu)/B,
            position[1] - 2*position[2] - nu*position[1]/A - mu*position[1]/B
    };
};

//Нахождение k-коэф. 3-стадийной неявной схемы Рунге-Кутты с помощью метода простых итераций
void Coef(vector<double> position, vector<vector<double>>& K){
    vector<double> new_position;
    vector<double> F;
    //метод простых итераций
    for (int i = 0; i < 10; ++i) {
        new_position = position;
        // нахождение новых k-коэф
        for (int j = 0; j < C.size(); ++j) {
            for (int k = 0; k < C.size(); ++k) {
                //создание новых координат для нахождение коэф.
                for (int l = 0; l < 4; ++l) {
                    new_position[l] += h*A[j][k]*K[l][k];
                }
            }
            F = Fun(new_position);
            for (int k = 0; k < 4; ++k) {
                K[k][j] = F[k];
            }
        }
    }
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
        vector<double> F = Fun(Result[i - 1]);
        vector<vector<double>> K = {{F[0], F[0], F[0], F[0]},
                                    {F[1], F[1], F[1], F[1]},
                                    {F[2], F[2], F[2], F[2]},
                                    {F[3], F[3], F[3], F[3]},};
        Result[i] = Result[i - 1];
        Coef(Result[i - 1], K);
        for (int j = 0; j < C.size(); ++j) {
            for (int k = 0; k < 4; ++k) {
                Result[i][k] += h*D[j]* K[k][j];
            }
        }
    }

    //Вывод решения
    for (int i = 0; i < N; ++i) {
        cout  << Result[i][0] << "\t" << Result[i][1] << endl;
    }

    return 0;
}