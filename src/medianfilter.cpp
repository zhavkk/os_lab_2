#include <vector>
#include <iostream>
#include <algorithm> 
#include <thread>

using namespace std;

void medianFilter(vector<vector<double>>& matrix, int K) {

    cout << "ID потока medianFilter.cpp: " << this_thread::get_id() << "\n";

    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int k = 0; k < K; k++) {

        vector<vector<double>> new_matrix(rows, vector<double>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                vector<double> values;

                for (int ii = -1; ii <= 1; ii++) {
                    for (int jj = -1; jj <= 1; jj++) {

                        if (i + ii >= 0 && i + ii < rows && j + jj >= 0 && j + jj < cols) {
                            values.push_back(matrix[i + ii][j + jj]);
                        }
                    }
                }

                // Сортировка для нахождения медианы
                if (values.size() % 2 == 0) {
                    nth_element(values.begin(), values.begin() + values.size() / 2, values.end());
                    new_matrix[i][j] = values[values.size() / 2];
                } else {
                    nth_element(values.begin(), values.begin() + values.size() / 2, values.end());
                    double median1 = values[values.size() / 2];
                    nth_element(values.begin(), values.begin() + values.size() / 2 + 1, values.end());
                    double median2 = values[values.size() / 2];
                    new_matrix[i][j] = (median1 + median2) / 2.0;
                }
            }
        }

        matrix = new_matrix;
    }
}