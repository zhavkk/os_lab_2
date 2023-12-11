#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm> // Для использования функции std::nth_element

using namespace std;

// Медианный фильтр
void medianFilter(vector<vector<double>>& matrix, int K);

// Функция печати итоговой матрицы
void print(const vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    
    cout << "Максимально возможное количество потоков: " << thread::hardware_concurrency() << "\n";
    
    if (atoi(argv[2]) > 15 || atoi(argv[2]) <= 0) {
        cout << "Заданное число потоков не может быть использовано." << "\n";
        return 1;
    }

    string path {"../tests/"};
    string name {argv[1]};
    path += name;
    const int Max = atoi(argv[2]);
    int rows, cols;
    string filename = path;
    int K;
    cout << "Введите количество раз для наложения фильтров: ";
    cin >> K;
    cout << "\n";

    // Начало отсчета времени
    chrono::steady_clock::time_point start_time = chrono::steady_clock::now();

    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Ошибка открытия файла. " << "\n";
        return 1;
    }
    
    input >> rows >> cols;
    vector<vector<double>> matrix(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input >> matrix[i][j];
        }
    }

    input.close();

    vector<vector<double>> result_matrix = matrix;

    cout << "ID потока main.cpp: " << this_thread::get_id() << "\n";

    // Создаем вектор потоков
    vector<thread> threads;

    // Работа с единственным потоком
    if (Max == 1) {
        medianFilter(result_matrix, K);
    }

    // Создаем потоки (если необходимо)
    for (int i = 1; i < Max; ++i) {
        threads.emplace_back(medianFilter, ref(result_matrix), K);
    }
    // Дождаться завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    cout << "Исходная матрица:\n";
    print(matrix);

    cout << "Матрица после наложения " << K << " раз медианного фильтра: \n";
    print(result_matrix);

    // Конец отсчета времени
    chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    
    cout << "Время работы программы: " << duration.count() << " микросекунд. " << "\n";

    return 0;
}
