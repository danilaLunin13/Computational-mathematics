#include "iostream"
#include "cmath"
#include "vector"

using namespace std;

// Сетка
int N = 10;
double h = M_PI/(N - 1);

//Функция вычисления коэф. одной "строчки"
vector<double> Coef_Line(double x){
    vector<double> ans (4);
    ans[0] = 1;
    ans[1] = -2 - h*(pow(x,2) - 3) + pow(h,2)*(pow(x,2) - 3)* cos(x);
    ans[2] = 1 + h*(pow(x,2) - 3);
    ans[3] = pow(h,2)*(2 - 6*x + 2*pow(x,3) + (pow(x,2) - 3)*exp(x)*
                                              sin(x)*(1 + cos(x)) + cos(x)*(exp(x) + (pow(x,2) - 1) +
                                                                            pow(x, 4) - 3* pow(x,2)));
    return ans;
}

//Используем метод прогонки
vector<double> Method(vector<vector<double>> A, vector<double> b) {
    vector<double> ans(N), v(N), u(N);
    v[0] = A[0][1] / -A[0][0];
    u[0] = b[0] / A[0][0];
    v[N - 1] = 0;
    for (int i = 1; i < N - 1; ++i) {
        v[i] = A[i][i + 1] / -(A[i][i] + A[i][i - 1] * v[i - 1]);
        u[i] = (A[i][i - 1] * u[i - 1] - b[i]) / -(A[i][i] + A[i][i - 1] * v[i - 1]);
    }
    u[N - 1] = (A[N-1][N-2]*u[N-2] - b[N-1]) / (-A[N-1][N-1] - A[N-1][N-2]*v[N-2]);
    ans[N - 1] = u[N - 1];
    for (int i = N-2; i >= 0; --i) {
        ans[i - 1] = v[i - 1] * ans[i] + u[i - 1];
    }
    return ans;
}

//Создание строк матрицы для прогонки
vector<double> Matrix_Line(vector<double> coef, int num){
    vector<double> ans (N);
    for (int i = num; i < num + coef.size(); ++i) {
        ans[i] = coef[i-num];
    }
    return ans;
}

int main(){

    //Создание матрицы и вектора для метода прогонки
    vector<vector<double>> A (N, vector<double> (3));
    vector<double> b (N);
    vector<double> line;
    A[0] = Matrix_Line({1, 0}, 0);
    b[0] = 0;
    for (int i = 1; i < N - 1; ++i) {
        line = Coef_Line(h*i);
        vector<double> coef_matrix(line.begin(), line.begin() + 3);
        cout << endl;
        A[i] = Matrix_Line(coef_matrix,i-1);
        b[i] = line[3];
    }
    A[N-1] = Matrix_Line({0, 1}, N-2);
    b[N-1] = pow(M_PI, 2);

    //Ответ
    vector<double> result = Method(A, b);
    for (int i = 0; i < N; ++i) {
        cout << (i+1)*h << "\t" << result[i] << endl;
    }

    return 0;
}