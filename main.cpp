#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;


class Rectangle {
private:
    // Поля класу
    double height;
    double width;
    string color;

public:
    // Конструктор №1: без параметрів
    Rectangle() {
        height = 1.0;
        width = 1.0;
        color = "White";
    }

    // Конструктор №2: з параметрами
    Rectangle(double h, double w, string c) {
        // Перевірка висоти
        if (h > 0) {
            height = h;
        } else {
            height = 1.0;
        }

        // Перевірка ширини
        if (w > 0) {
            width = w;
        } else {
            width = 1.0;
        }

        color = c;
    }

    // Функція встановлення висоти
    void setHeight(double h) {
        if (h > 0) {
            height = h;
        } else {
            cout << "Помилка: висота повинна бути більше 0" << endl;
        }
    }

    // Функція встановлення ширини
    void setWidth(double w) {
        if (w > 0) {
            width = w;
        } else {
            cout << "Помилка: ширина повинна бути більше 0" << endl;
        }
    }

    // Функція встановлення кольору
    void setColor(string c) {
        color = c;
    }

    // Функція отримання висоти
    double getHeight() {
        return height;
    }

    // Функція отримання ширини
    double getWidth() {
        return width;
    }

    // Функція отримання кольору
    string getColor() {
        return color;
    }

    // Обчислення площі
    double calculateArea() {
        double result;
        result = height * width;
        return result;
    }

    // Обчислення периметру
    double calculatePerimeter() {
        double result;
        result = 2 * (height + width);
        return result;
    }

    // Функція друку
    void printInfo() {
        cout << "------------------------------------" << endl;
        cout << "Інформація про прямокутник:" << endl;
        cout << "Висота: " << height << endl;
        cout << "Ширина: " << width << endl;
        cout << "Колір: " << color << endl;
        cout << "Площа: " << calculateArea() << endl;
        cout << "Периметр: " << calculatePerimeter() << endl;
        cout << "------------------------------------" << endl;
    }
};


class Vector {
private:
    double* data;     // Вказівник на масив
    int size;         // Розмір
    int state;        // Стан (0 - ок, 1 - помилка)
    static int count; // Лічильник об'єктів

public:
    // Отримати кількість об'єктів
    static int getCount() {
        return count;
    }

    // Конструктор без параметрів
    Vector() {
        size = 1;
        data = new double[size];
        data[0] = 0.0;
        state = 0;
        count++;
    }

    // Конструктор з одним параметром
    Vector(int n) {
        if (n <= 0) {
            size = 1;
            state = 1; // Помилка розміру
        } else {
            size = n;
            state = 0;
        }
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0.0;
        }
        count++;
    }

    // Конструктор з двома параметрами
    Vector(int n, double value) {
        if (n <= 0) {
            size = 1;
            state = 1;
        } else {
            size = n;
            state = 0;
        }
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = value;
        }
        count++;
    }

    // Конструктор копій
    Vector(const Vector& other) {
        size = other.size;
        state = other.state;
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        count++;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
        count--;
    }

    // Функція присвоєння значення елементу
    void setElement(int index, double val) {
        if (index >= 0 && index < size) {
            data[index] = val;
            state = 0;
        } else {
            state = 1; // Вихід за межі
            cout << "Помилка: Індекс поза межами!" << endl;
        }
    }

    // Одержання елемента
    double getElement(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            state = 1;
            return 0.0;
        }
    }

    // Додавання векторів
    Vector add(Vector& other) {
        if (size != other.size) {
            cout << "Помилка: розміри не збігаються!" << endl;
            Vector empty(1);
            empty.state = 1;
            return empty;
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Віднімання векторів
    Vector subtract(Vector& other) {
        if (size != other.size) {
            cout << "Помилка: розміри не збігаються!" << endl;
            Vector empty(1);
            empty.state = 1;
            return empty;
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Множення на скаляр
    void multiplyByScalar(double scalar) {
        for (int i = 0; i < size; i++) {
            data[i] = data[i] * scalar;
        }
    }

    // Ділення на скаляр
    void divideByScalar(double scalar) {
        if (scalar == 0) {
            state = 1;
            cout << "Помилка: ділення на нуль!" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            data[i] = data[i] / scalar;
        }
    }

    // Функції порівняння
    bool isMore(Vector& other) {
        if (size > other.size) return true;
        return false;
    }

    bool isLess(Vector& other) {
        if (size < other.size) return true;
        return false;
    }

    bool isEqual(Vector& other) {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // Друк вектора
    void print() {
        cout << "Вектор (стан: " << state << "): [ ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "]" << endl;
    }
};
int Vector::count = 0;


class Matrix {
private:
    double* data;
    int rows;
    int cols;
    int state;
    static int count;

public:
    static int getCount() {
        return count;
    }

    // Без параметрів (4 на 3)
    Matrix() {
        rows = 4;
        cols = 3;
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = 0.0;
        }
        state = 0;
        count++;
    }

    // Квадратна матриця n на n
    Matrix(int n) {
        rows = n;
        cols = n;
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = 0.0;
        }
        state = 0;
        count++;
    }

    // Матриця n на m
    Matrix(int n, int m, double value) {
        rows = n;
        cols = m;
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = value;
        }
        state = 0;
        count++;
    }

    // Конструктор копій
    Matrix(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        state = other.state;
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = other.data[i];
        }
        count++;
    }

    // Деструктор
    ~Matrix() {
        delete[] data;
        count--;
    }

    // Присвоїти значення
    void setElement(int i, int j, double val) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            data[i * cols + j] = val;
        } else {
            state = 1;
        }
    }

    // Отримати значення
    double getElement(int i, int j) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            return data[i * cols + j];
        }
        state = 1;
        return 0.0;
    }

    // Додавання матриць
    Matrix add(Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            Matrix empty(1);
            empty.state = 1;
            return empty;
        }
        Matrix result(rows, cols, 0);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Множення на скаляр
    void multiplyByScalar(double scalar) {
        for (int i = 0; i < rows * cols; i++) {
            data[i] = data[i] * scalar;
        }
    }

    // Друк матриці
    void print() {
        cout << "Матриця " << rows << "x" << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << getElement(i, j) << "\t";
            }
            cout << endl;
        }
    }
};
int Matrix::count = 0;



void showMenu() {
    cout << "1. Тестувати клас Прямокутник" << endl;
    cout << "2. Тестувати клас Вектор" << endl;
    cout << "3. Тестувати клас Матриця" << endl;
    cout << "0. Вийти з програми" << endl;
    cout << "========================================" << endl;
    cout << "Ваш вибір: ";
}

void testRectangle() {
    cout << "\n--- ТЕСТУВАННЯ ПРЯМОКУТНИКА ---" << endl;

    // Спосіб 1: Клавіатура
    double h, w;
    string c;
    cout << "Введіть висоту: "; cin >> h;
    cout << "Введіть ширину: "; cin >> w;
    cout << "Введіть колір: "; cin >> c;
    Rectangle r1(h, w, c);
    r1.printInfo();

    // Спосіб 2: Рандом
    cout << "Генерація випадкового прямокутника..." << endl;
    Rectangle r2(rand() % 20 + 1, rand() % 20 + 1, "Green");
    r2.printInfo();

    // Спосіб 3: Файл
    cout << "Спроба прочитати з файлу rect.txt..." << endl;
    ifstream fin("rect.txt");
    if (fin.is_open()) {
        fin >> h >> w >> c;
        Rectangle r3(h, w, c);
        r3.printInfo();
        fin.close();
    } else {
        cout << "Файл не знайдено, пропускаємо." << endl;
    }
}

void testVector() {
    cout << "\n--- ТЕСТУВАННЯ ВЕКТОРА ---" << endl;
    int n;
    cout << "Введіть розмір вектора: "; cin >> n;
    Vector v1(n, 5.0);
    Vector v2(n, 10.0);

    cout << "Вектор 1: "; v1.print();
    cout << "Вектор 2: "; v2.print();

    Vector v3 = v1.add(v2);
    cout << "Сума векторів: "; v3.print();

    v1.multiplyByScalar(2.0);
    cout << "Вектор 1 після множення на 2: "; v1.print();

    cout << "Кількість векторів у системі: " << Vector::getCount() << endl;
}

void testMatrix() {
    cout << "\n--- ТЕСТУВАННЯ МАТРИЦІ ---" << endl;
    Matrix m1(2, 2, 1.0);
    m1.setElement(0, 0, 5.0);
    m1.setElement(0, 1, 10.0);
    m1.setElement(1, 0, 15.0);
    m1.setElement(1, 1, 20.0);

    m1.print();

    Matrix m2 = m1; // Копія
    cout << "Копія матриці:" << endl;
    m2.print();

    cout << "Кількість матриць у системі: " << Matrix::getCount() << endl;
}

int main() {
    // Для підтримки української мови в консолі
    setlocale(LC_ALL, "Ukrainian");
    // Ініціалізація рандому
    srand(time(0));

    int choice = -1;

    // Цикл меню
    while (choice != 0) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            testRectangle();
        }
        else if (choice == 2) {
            testVector();
        }
        else if (choice == 3) {
            testMatrix();
        }
        else if (choice == 0) {
            cout << "Вихід з програми..." << endl;
        }
        else {
            cout << "Невірний вибір! Спробуйте ще раз." << endl;
        }

        cout << "\nНатисніть будь-яку клавішу для продовження...";
        cin.ignore();
        cin.get();
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    return 0;
}