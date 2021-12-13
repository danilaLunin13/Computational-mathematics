#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

int N = 5;
double h = 1./(N-1);
int border = 2;

//таблица Бутчера 4-стадийного явного метода Рунге-Кутты
vector<vector<double>> A = {
        {0, 0, 0, 0},
        {1./2, 0, 0, 0},
        {0, 1./2, 0, 0},
        {0, 0, 1, 0},
};
vector<double> C = {0, 1./2, 1./2, 1};
vector<double> D = {1./6 , 1./3, 1./3, 1./6};

// Создание вектора, показывающий значение y(1) при определённом значение пристрелки y'(0)
vector<vector<double>> Sighting;

// вектор функций
vector<double> Fun(double x,double y,double dydx){
    return {dydx,
            x* pow(y,0.5)};
}

//Нахождение k-коэф. 4-стадийной явной схемы Рунге-Кутты
vector<vector<double>> Coef(double x,double y, double dydx){
    vector<vector<double>> K (2, vector<double> (C.size()));
    double y_new = y;
    double dydx_new = dydx;
    for (int i = 0; i < C.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            y_new += h*A[i][j]*K[0][j];
            dydx_new += h*A[i][j]*K[1][j];
        }
        K[0][i] = Fun(x + h*C[i], y_new, dydx_new)[0];
        K[1][i] = Fun(x + h*C[i], y_new, dydx_new)[1];
    }
    return K;
}

//нахождение шаговых решений задачи, принимающий на вход нач. усл.
vector<vector<double>> Answer(vector<double> Regional){
    vector<vector<double>> Result (N, vector<double> (3));
    for (int i = 1; i < N; ++i) {
        Result[i][0] = h*i;
    }
    Result[0] = Regional;
    for (int i = 1; i < N; ++i) {
        Result[i][1] = Result[i-1][1];
        Result[i][2] = Result[i-1][2];
        vector<vector<double>> K = Coef(Result[i-1][0], Result[i-1][1], Result[i-1][2]);
        for (int j = 0; j < C.size(); ++j) {
            Result[i][1] += h*D[j]* K[0][j];
            Result[i][2] += h*D[j]* K[1][j];
        }
    }
    return Result;
}

int main() {

    //Начальное условие
    vector<double> Regional = {0, 0, 1};

    //Эмпирическим путём подберем два начальных условия y'(0) так, чтобы исходное нач. усл. y(1)
    //лежало между двумя экспериментально полученными значениями y(1).
    double ans = Answer(Regional)[N-1][2];
    Sighting.push_back({Regional[2], ans});
    cout << ans << endl;
    Regional[2] += 1;
    ans = Answer(Regional)[N-1][2];
    cout << ans << endl;
    Sighting.push_back({Regional[2], ans});

    //Воспользуемся метод половинного деления и найдём нужное нам значение y'(0)
    //Эмпирическим путём настраиваю количество итераций
    for (int i = 0; i < 10; ++i) {
        Regional[2] = (Sighting[0][0] + Sighting[1][0])/2.;
        ans = Answer(Regional)[N-1][2];
        cout << ans << endl;
        if (ans > border){
            Sighting[1] = {Regional[2], ans};
        } else {
            Sighting[0] = {Regional[2], ans};
        }
    }

    //Получая ответ задачи Коши
    vector<vector<double>> Ans = Answer(Regional);
    for (int i = 0; i < N; ++i) {
        cout << Ans[i][0] << " " << Ans[i][1] << endl;
    }
    return 0;
}
