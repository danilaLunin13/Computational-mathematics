#include "iostream"
#include "vector"
#include "cmath"

using namespace std;

//сетка
int N = 1e3;
double h = 1000./(N - 1);

int mu = 1e3;

//Неявный метод Эйлера с методом Ньютона
vector<double> Newton(vector<double> coord){
    vector<double> coord_new = {coord[0] + h, coord[1] + h*coord[2],
                                coord[2] + h*(mu*(1 - pow(coord[2],2))*coord[2] - coord[1])};
    for (int i = 0; i < 10; ++i) {
        double tmp = coord_new[2];
        coord_new[2] = tmp - (mu*pow(tmp,3) + tmp*(1/h-mu) - coord[2]/h + coord[1])/
                (3*mu* pow(tmp, 2) + (1/h - mu));
    }
    coord_new[1] = coord[1] + h*coord_new[2];
    return coord_new;
}

int main(){
    //вектор нач. усл.
    vector<vector<double>> Result (N);
    Result[0] = {0, 0, 0.001};
    for (int i = 1; i < N; ++i) {
        vector<double> result_new = Newton(Result[i-1]);
        Result[i] = result_new;
    }

    //Ответ
    for (int i = 0; i < N; ++i) {
        cout << Result[i][0] << "\t" << Result[i][1] << endl;
    }
    return 0;
}