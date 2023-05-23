#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>

template<typename RandomIt>
void timSort(RandomIt first, RandomIt last) {
    std::sort(first, last);
}

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
    std::vector<double> timSortTimes(128);
    std::vector<double> quickSortTimes(128);

    for (int i = 0; i < 128; i++) {
        std::vector<int> randArr(100000);
        for (int j = 0; j < 100000; j++) {
            randArr[j] = gen() % 100001;
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

        std::cout << "Tim Sort" << std::endl;
        arr = randArr;
        start = std::chrono::high_resolution_clock::now();
        timSort(arr.begin(), arr.end());
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        timSortTimes[i] = duration.count();
        std::cout << "Tim Sort END " << timSortTimes[i] << std::endl;

        std::cout << "QuickSort" << std::endl;
        arr = randArr;
        start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1, 0);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        quickSortTimes[i] = duration.count();
        std::cout << "QuickSort END " << quickSortTimes[i] << std::endl;
    }

    std::ofstream file("data.csv");
    if (!file.is_open()) {
        std::cout << "Error creating CSV file" << std::endl;
        return 1;
    }

    file << "aps,bubble,merge,tim_sort,quick_sort" << std::endl;
    for (int i = 0; i < 128; i++) {
        file << apsTimes[i] << "," << bubbleTimes[i] << "," << mergeTimes[i] << "," << timSortTimes[i] << "," << quickSortTimes[i] << std::endl;
    }

    file.close();

    return 0;
}
