import random
import time
import csv

from aps import adaptive_partition_sort
from bubble import bubbleSort
from tim import timsort
from quick import quick_sort

aps_times = []
bubble_times = []
tim_times = []
quick_times = []

for i in range(128):
    rand = [random.randint(0, 1000000) for _ in range(1000000)]
    arr = rand.copy()

    print(f'Iteration {i + 1}')
    print('APS')
    start = time.time()
    adaptive_partition_sort(arr, 0)
    end = time.time()
    aps_times.append(end - start)
    print(f'APS END {end - start}')

    print('Bubble')
    arr = rand.copy()
    start = time.time()
    bubbleSort(arr)
    end = time.time()
    bubble_times.append(end - start)
    print(f'Bubble END {end - start}')

    print('Tim')
    arr = rand.copy()
    start = time.time()
    timsort(arr)
    end = time.time()
    tim_times.append(end - start)
    print(f'Tim END {end - start}')

    print('Quick')
    arr = rand.copy()
    start = time.time()
    quick_sort(arr)
    end = time.time()
    quick_times.append(end - start)
    print(f'Quick END {end - start}')

# save data to csv
with open('data.csv', 'w', newline='') as csvfile:
    print('writing start')
    writer = csv.writer(csvfile, delimiter=',')
    writer.writerow(['aps', 'bubble', 'tim', 'quick'])
    for i in range(128):
        print(f'writing {i}')
        writer.writerow([aps_times[i], bubble_times[i], tim_times[i], quick_times[i]])
