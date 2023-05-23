#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>

void adaptivePartitionSort(std::vector<int>& arr, int threshold);

void quickSort(std::vector<int>& arr, int low, int high, int threshold) {
    if (low >= high) {
        return;
    }

    int pivot = arr[(low + high) / 2];

    int i = low, j = high;
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (j - low + 1 <= threshold) {
        std::sort(arr.begin() + low, arr.begin() + j + 1);
    } else {
        quickSort(arr, low, j, threshold);
    }

    if (high - i + 1 <= threshold) {
        std::sort(arr.begin() + i, arr.begin() + high + 1);
    } else {
        quickSort(arr, i, high, threshold);
    }
}

void mergeSort(std::vector<int>& arr, int low, int high, int threshold) {
    if (low >= high) {
        return;
    }

    int mid = (low + high) / 2;
    mergeSort(arr, low, mid, threshold);
    mergeSort(arr, mid + 1, high, threshold);

    std::vector<int> left(arr.begin() + low, arr.begin() + mid + 1);
    std::vector<int> right(arr.begin() + mid + 1, arr.begin() + high + 1);

    int i = 0, j = 0, k = low;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left.size()) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right.size()) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void adaptivePartitionSort(std::vector<int>& arr, int threshold) {
    quickSort(arr, 0, arr.size() - 1, threshold);
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<double> apsTimes(128);
    std::vector<double> bubbleTimes(128);
    std::vector<double> mergeTimes(128);

    for (int i = 0; i < 128; i++) {
        std::vector<int> randArr(10000);
        for (int j = 0; j < 10000; j++) {
            randArr[j] = gen() % 10001;
        }

        std::cout << "Iteration " << i + 1 << std::endl;

        std::cout << "APS" << std::endl;
        std::vector<int> arr(randArr);
        auto start = std::chrono::high_resolution_clock::now();
        adaptivePartitionSort(arr, 0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        apsTimes[i] = duration.count();
        std::cout << "APS END " << apsTimes[i] << std::endl;

        std::cout << "Bubble" << std::endl;
        arr = randArr;
        start = std::chrono::high_resolution_clock::now();
        bubbleSort(arr);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        bubbleTimes[i] = duration.count();
        std::cout << "Bubble END " << bubbleTimes[i] << std::endl;

        std::cout << "Merge" << std::endl;
        arr = randArr;
        start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1, 0);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        mergeTimes[i] = duration.count();
        std::cout << "Merge END " << mergeTimes[i] << std::endl;
    }

    std::ofstream file("data.csv");
    if (!file.is_open()) {
        std::cout << "Error creating CSV file" << std::endl;
        return 1;
    }

    file << "aps,bubble,merge" << std::endl;
    for (int i = 0; i < 128; i++) {
        file << apsTimes[i] << "," << bubbleTimes[i] << "," << mergeTimes[i] << std::endl;
    }

    file.close();

    return 0;
}
