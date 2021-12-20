#include <iostream>
#include "vector"
#include "algorithm"
#include "cmath"

using namespace std;

//ввод начальных данных
double mu = 0.012277471;
double nu = 1 - mu;
double h = 0.01;

//таблица Бутчера
vector<vector<double>> A = {
        {0, 0, 0, 0, 0, 0, 0},
        {1./5, 0, 0, 0, 0, 0, 0},
        {3./40, 9./40, 0, 0, 0, 0, 0},
        {44./45, -56./15, 32./9, 0, 0, 0, 0},
        {19372./6561, -25360./2187, 64448./6561, -212./729, 0, 0, 0},
        {9017./3168, -355./33, 46732./5247, 49./176, -5103./18656, 0, 0},
        {35./384, 0, 500./1113, 125./192, -2187./6784, 11./84, 0},
};
vector<double> C = {0, 1./5, 3./10, 4./5, 8./9, 1, 1};
vector<vector<double>> D = {
        {35./384, 0, 500./1113, 125./192, -2187./6784, 11./84, 0},
        {5179./57600, 0, 7571./16695, 393./640, -92097./339200, 187./2100, 1./40},
};

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
}

//Нахождение k-коэф. 7-стадийной явной схемы Рунге-Кутты
void Coef(const vector<double>& position, vector<vector<double>>& K){
    vector<double> position_new;
    for (int i = 0; i < A.size(); ++i) {
        position_new = position;
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < position_new.size(); ++k) {
                position_new[k] += h*A[i][j]*K[k][j];
            }
        }
        for (int j = 0; j < position_new.size(); ++j) {
            K[j][i] = Fun(position_new)[j];
        }
    }
}

double Norm(const vector<double>& first,const vector<double>& second){
    double ans = 0;
    for (int i = 0; i < 4; ++i) {
        ans = std::max(abs(first[i] - second[i]), ans);
    }
    return ans;
}

int main() {
    //создание вектора-решения системы уравнения
    vector<vector<double>> Result;
    Result.push_back({0.994,
                      0,
                      0,
                      -2.00158510637908252240537862224});

    //Последовательное нахождение решения задачи
    double accuracy = 1e-9;
    double zero = 1e-16;
    double stepfact = 1.3;
    double guarfact = 0.95;
    vector<double> Ans_1 (4), Ans_2 (4);
    double T = 0;
    double T_border = 40;
    while (T < T_border) {
        vector<vector<double>> K (Result[0].size(), vector<double> (C.size()));
        Coef(Result[Result.size() - 1], K);

        double norm;
        do {
            Ans_1 = Result[Result.size() - 1];
            Ans_2 = Result[Result.size() - 1];
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < C.size(); ++k) {
                    Ans_1[j] += h*D[0][k]* K[j][k];
                    Ans_2[j] += h*D[1][k]* K[j][k];
                }
            }
            norm = Norm(Ans_1, Ans_2);
            if (norm >= accuracy){
                h *= min(pow(accuracy/norm, 1./5.), stepfact);
            }
        } while (norm >= accuracy);

        if (norm <=  zero){
            h *= stepfact;
            h *= guarfact;
        } else{
            h *= min(pow(accuracy/norm, 1./5.), stepfact);
            h *= guarfact;
        }

        T += h;
        Result.push_back(Ans_2);
    }

    for (auto i : Result){
        cout << i[0] << "\t" << i[1] << endl;
    }
    return 0;
}