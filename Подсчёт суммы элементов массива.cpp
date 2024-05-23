#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <random>
#include <functional>
using namespace std;
void calculate_sum(const vector<int>& array, int start, int end, int& result) {
    result = accumulate(array.begin() + start, array.begin() + end, 0);
}

int main() {
    int N = 20;
    int M = 4;

    // Генерация массива случайных чисел
    vector<int> array(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);
    generate(array.begin(), array.end(), bind(dis, gen));

    // Вывод массива
    cout << "Массив: ";
    for (int num : array) {
        cout << num << " ";
    }
    cout << endl;

    // Разделение массива на M частей
    int part_size = N / M;
    vector<thread> threads;
    vector<int> results(M, 0);

    for (int i = 0; i < M; ++i) {
        int start = i * part_size;
        int end = (i == M - 1) ? N : start + part_size;
        threads.emplace_back(calculate_sum, cref(array), start, end, ref(results[i]));
    }

    // Ожидание завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    // Вычисление общей суммы
    int total_sum = accumulate(results.begin(), results.end(), 0);
    cout << "Итоговая сумма: " << total_sum << endl;

    return 0;
}