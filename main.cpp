#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<double>> Reversed_Matrix(vector<double> c){
    vector<vector<double>> ans = {{1, -2 * c[1]},
                                  {1/pow(cos(c[0]),2), 2*c[0]}};
    double a = 2*c[0] + 2*c[1]/pow(cos(c[0]), 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ans[i][j] /= a;
        }
    }
    return ans;
}

vector<double> Newton(vector<vector<double>> J, vector<double> c){
    vector<double> ans = c;
    vector<double> f = {pow(c[0],2) + pow(c[1], 2) - 1,
                        c[1] - tan(c[0])};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ans[i] -= J[i][j]*f[j];
        }
    }
    return ans;
}

int main(){
    vector<double> coord_old = {0.6, 0.8};
    vector<vector<double>> Matrix;
    vector<double> coord_new;
    while (true){
        Matrix = Reversed_Matrix(coord_old);
        coord_new = Newton(Matrix, coord_old);
        if (int(coord_old[0]*pow(10,6)) == int(coord_new[0]*pow(10,6)) and
            int(coord_old[1]*pow(10,6)) == int(coord_new[1]*pow(10,6))){
            break;
        }
        coord_old = coord_new;
    }
    for (auto i : coord_new){
        cout << i << endl;
    }
}
