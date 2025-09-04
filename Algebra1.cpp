#include <iostream>
#include <cmath>
using namespace std;

class LAVector {
private:
    int n;
    double* data;

public:
    LAVector(int size) {
        n = size;
        data = new double[n];
        for (int i = 0; i < n; i++) data[i] = 0.0;
    }

    LAVector(int size, double values[]) {
        n = size;
        data = new double[n];
        for (int i = 0; i < n; i++) data[i] = values[i];
    }

    LAVector(const LAVector& other) {
        n = other.n;
        data = new double[n];
        for (int i = 0; i < n; i++) data[i] = other.data[i];
    }

    ~LAVector() {
        delete[] data;
    }

    LAVector operator+(const LAVector& other) const {
        LAVector result(n);
        for (int i = 0; i < n; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    LAVector operator-(const LAVector& other) const {
        LAVector result(n);
        for (int i = 0; i < n; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    LAVector operator*(double scalar) const {
        LAVector result(n);
        for (int i = 0; i < n; i++) result.data[i] = data[i] * scalar;
        return result;
    }

    double dot_product(const LAVector& other) const {
        double result = 0.0;
        for (int i = 0; i < n; i++) result += data[i] * other.data[i];
        return result;
    }

    double magnitude() const {
        double sum = 0.0;
        for (int i = 0; i < n; i++) sum += data[i] * data[i];
        return sqrt(sum);
    }

    LAVector normalize() const {
        double mag = magnitude();
        LAVector result(n);
        for (int i = 0; i < n; i++) result.data[i] = data[i] / mag;
        return result;
    }

    double get(int i) const { return data[i]; }
    void set(int i, double val) { data[i] = val; }
    int size() const { return n; }

    void print() const {
        cout << "(";
        for (int i = 0; i < n; i++) {
            cout << data[i];
            if (i < n - 1) cout << ", ";
        }
        cout << ")";
    }
};

class Matrix {
private:
    int rows, cols;
    LAVector** data;

public:
    Matrix(int r, int c) {
        rows = r; cols = c;
        data = new LAVector*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new LAVector(cols);
        }
    }

    Matrix(int r, int c, double values[][2]) { 
        rows = r; cols = c;
        data = new LAVector*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new LAVector(cols);
            for (int j = 0; j < cols; j++) {
                data[i]->set(j, values[i][j]);
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) delete data[i];
        delete[] data;
    }

    LAVector multiply(const LAVector& v) const {
        LAVector result(rows);
        for (int i = 0; i < rows; i++) {
            result.set(i, data[i]->dot_product(v));
        }
        return result;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i]->set(j, data[i]->get(j) + other.data[i]->get(j));
            }
        }
        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i]->set(j, data[i]->get(j) * scalar);
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j]->set(i, data[i]->get(j));
            }
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            data[i]->print();
            cout << endl;
        }
    }
};

int main() {
    double vals1[3] = {1, 2, 3};
    double vals2[3] = {4, 5, 6};
    LAVector v1(3, vals1);
    LAVector v2(3, vals2);

    cout << "v1 = "; v1.print(); cout << endl;
    cout << "v2 = "; v2.print(); cout << endl;

    cout << "v1 + v2 = "; (v1 + v2).print(); cout << endl;
    cout << "v1 - v2 = "; (v1 - v2).print(); cout << endl;
    cout << "v1 * 2 = "; (v1 * 2).print(); cout << endl;
    cout << "v1 · v2 = " << v1.dot_product(v2) << endl;
    cout << "|v1| = " << v1.magnitude() << endl;
    cout << "v1 normalizado = "; v1.normalize().print(); cout << endl;

    cout << "\n--- Rotación 2D 45° ---\n";
    double angle = M_PI / 4;
    double rotation_vals[2][2] = {
        {cos(angle), -sin(angle)},
        {sin(angle),  cos(angle)}
    };
    Matrix R(2, 2, rotation_vals);

    double p_vals[2] = {1, 0};
    LAVector p(2, p_vals);

    cout << "Punto original = "; p.print(); cout << endl;
    LAVector rotated = R.multiply(p);
    cout << "Punto rotado 45° = "; rotated.print(); cout << endl;

    return 0;
}
