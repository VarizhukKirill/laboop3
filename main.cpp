#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;


enum ErrorState {
    OK = 0,
    MEMORY_ERR = 1,
    OUT_OF_BOUNDS = 2,
    INCOMPATIBLE_DIM = 3,
    DIV_ZERO = 4
};


class Rectangle {
private:
    double height;
    double width;
    string color;

public:
    Rectangle() : height(1.0), width(1.0), color("White") {}

    Rectangle(double h, double w, string c) {
        if (!setHeight(h)) height = 1.0;
        if (!setWidth(w)) width = 1.0;
        color = c;
    }

    bool setHeight(double h) {
        if (h > 0) { height = h; return true; }
        return false;
    }

    bool setWidth(double w) {
        if (w > 0) { width = w; return true; }
        return false;
    }

    void setColor(string c) { color = c; }
    double getHeight() const { return height; }
    double getWidth() const { return width; }
    string getColor() const { return color; }

    double area() const { return height * width; }
    double perimeter() const { return 2 * (height + width); }

    void print() const {
        cout << "\n  дані вашого прямокут" << endl;
        cout << "  Колір: " << color << " | Розміри: " << width << " x " << height << endl;
        cout << "  Площа: " << area() << " | Периметр: " << perimeter() << endl;
        cout << "  ------------------------------------------" << endl;
    }
};


class DoubleVector {
private:
    double* data;
    int size;
    int state;
    static int vectorObjects;

public:
    static int getCount() { return vectorObjects; }

    DoubleVector() : size(1), state(OK) {
        data = new (nothrow) double[1]{0.0};
        if (!data) state = MEMORY_ERR;
        vectorObjects++;
    }

    DoubleVector(int s) : size(s > 0 ? s : 1), state(OK) {
        data = new (nothrow) double[size]();
        if (!data) state = MEMORY_ERR;
        vectorObjects++;
    }

    DoubleVector(int s, double val) : size(s > 0 ? s : 1), state(OK) {
        data = new (nothrow) double[size];
        if (!data) state = MEMORY_ERR;
        else for (int i = 0; i < size; i++) data[i] = val;
        vectorObjects++;
    }

    DoubleVector(const DoubleVector& other) : size(other.size), state(other.state) {
        data = new double[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        vectorObjects++;
    }

    DoubleVector& operator=(const DoubleVector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            state = other.state;
            data = new double[size];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }

    ~DoubleVector() { delete[] data; vectorObjects--; }

    void set(int idx, double val = 0.0) {
        if (idx >= 0 && idx < size) data[idx] = val;
        else state = OUT_OF_BOUNDS;
    }

    double get(int idx) const {
        if (idx >= 0 && idx < size) return data[idx];
        const_cast<DoubleVector*>(this)->state = OUT_OF_BOUNDS;
        return 0.0;
    }

    DoubleVector add(const DoubleVector& other) {
        if (size != other.size) { state = INCOMPATIBLE_DIM; return *this; }
        DoubleVector res(size);
        for (int i = 0; i < size; i++) res.data[i] = data[i] + other.data[i];
        return res;
    }

    void mult(double scalar) {
        for (int i = 0; i < size; i++) data[i] *= scalar;
    }

    void print() const {
        cout << "  Вектор (розмір " << size << ", стан " << state << "): [ ";
        for (int i = 0; i < size; i++) cout << data[i] << (i == size - 1 ? "" : ", ");
        cout << " ]" << endl;
    }
};
int DoubleVector::vectorObjects = 0;


class DoubleMatrix {
private:
    double* data;
    int rows, cols;
    int state;
    static int matrixObjects;

public:
    static int getCount() { return matrixObjects; }

    DoubleMatrix() : rows(4), cols(3), state(OK) {
        data = new (nothrow) double[rows * cols]();
        if (!data) state = MEMORY_ERR;
        matrixObjects++;
    }

    DoubleMatrix(int n, int m, double val) : rows(n), cols(m), state(OK) {
        data = new (nothrow) double[rows * cols];
        if (!data) state = MEMORY_ERR;
        else for (int i = 0; i < rows * cols; i++) data[i] = val;
        matrixObjects++;
    }

    DoubleMatrix(const DoubleMatrix& other) : rows(other.rows), cols(other.cols), state(other.state) {
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) data[i] = other.data[i];
        matrixObjects++;
    }

    ~DoubleMatrix() { delete[] data; matrixObjects--; }

    void set(int i, int j, double val = 0.0) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) data[i * cols + j] = val;
        else state = OUT_OF_BOUNDS;
    }

    double get(int i, int j) const {
        if (i >= 0 && i < rows && j >= 0 && j < cols) return data[i * cols + j];
        const_cast<DoubleMatrix*>(this)->state = OUT_OF_BOUNDS;
        return 0.0;
    }

    void print() const {
        cout << "  Матриця " << rows << "x" << cols << " (Стан: " << state << "):" << endl;
        for (int i = 0; i < rows; i++) {
            cout << "    ";
            for (int j = 0; j < cols; j++) cout << setw(8) << get(i, j);
            cout << endl;
        }
    }
};
int DoubleMatrix::matrixObjects = 0;



void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void runTask1() {
    clearScreen();

    cout << "1. Введення з клавіатури\n2. Випадкові дані\nВибір: ";
    int c; cin >> c;
    if (c == 1) {
        double h, w; string col;
        cout << "Висота Ширина Колір: "; cin >> h >> w >> col;
        Rectangle r(h, w, col); r.print();
    } else {
        Rectangle r(rand()%15+1, rand()%15+1, "Random_Color"); r.print();
    }
    cout << "\nНатисніть будь-яку клавішу..."; cin.ignore(); cin.get();
}

void runTask2() {
    clearScreen();
    cout << "=== ТЕСТУВАННЯ: ВЕКТОР ===\n";
    DoubleVector v1(5, 2.5);
    DoubleVector v2(5, 1.5);
    cout << "Вектор 1: "; v1.print();
    cout << "Вектор 2: "; v2.print();
    DoubleVector v3 = v1.add(v2);
    cout << "Результат додавання: "; v3.print();
    cout << "Кількість активних векторів: " << DoubleVector::getCount() << endl;
    cout << "\nНатисніть будь-яку клавішу..."; cin.ignore(); cin.get();
}

void runTask3() {
    clearScreen();
    cout << "=== ТЕСТУВАННЯ: МАТРИЦЯ ===\n";
    DoubleMatrix m(3, 3, 1.0);
    m.set(1, 1, 55.5);
    m.print();
    cout << "Кількість активних матриць: " << DoubleMatrix::getCount() << endl;
    cout << "\nНатисніть будь-яку клавішу"; cin.ignore(); cin.get();
}

int main() {
    srand(time(0));
    while (true) {
        clearScreen();
        cout << " 1. Задача 1.3 (Прямокутник)\n";
        cout << " 2. Задача 2.3 (Вектор)\n";
        cout << " 3. Задача 3.3 (Матриця)\n";
        cout << "Ваш вибір: ";
        int choice;
        if (!(cin >> choice)) break;
        if (choice == 1) runTask1();
        else if (choice == 2) runTask2();
        else if (choice == 3) runTask3();
        else if (choice == 0) break;
    }
    return 0;
}