package main

import (
	"encoding/csv"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func adaptivePartitionSort(arr []int, threshold int) {
	quickSort(arr, 0, len(arr)-1, threshold)
}

func quickSort(arr []int, low, high, threshold int) {
	if low >= high {
		return
	}

	pivot := arr[(low+high)/2]

	i, j := low, high
	for i <= j {
		for arr[i] < pivot {
			i++
		}
		for arr[j] > pivot {
			j--
		}
		if i <= j {
			arr[i], arr[j] = arr[j], arr[i]
			i++
			j--
		}
	}

	if j-low+1 <= threshold {
		mergeSort(arr, low, j, threshold)
	} else {
		quickSort(arr, low, j, threshold)
	}

	if high-i+1 <= threshold {
		mergeSort(arr, i, high, threshold)
	} else {
		quickSort(arr, i, high, threshold)
	}
}

func mergeSort(arr []int, low, high, threshold int) {
	if low >= high {
		return
	}

	mid := (low + high) / 2
	mergeSort(arr, low, mid, threshold)
	mergeSort(arr, mid+1, high, threshold)

	left := arr[low : mid+1]
	right := arr[mid+1 : high+1]
	i, j, k := 0, 0, low
	for i < len(left) && j < len(right) {
		if left[i] <= right[j] {
			arr[k] = left[i]
			i++
		} else {
			arr[k] = right[j]
			j++
		}
		k++
	}

	for i < len(left) {
		arr[k] = left[i]
		i++
		k++
	}

	for j < len(right) {
		arr[k] = right[j]
		j++
		k++
	}
}

func bubbleSort(arr []int) {
	n := len(arr)
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			println("GO | %d | %d", i, j)
			if arr[j] > arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j]
			}
		}
	}
}

func main() {
	rand.New(rand.NewSource(time.Now().UnixNano()))

	apsTimes := make([]float64, 128)
	bubbleTimes := make([]float64, 128)
	mergeTimes := make([]float64, 128)

	for i := 0; i < 128; i++ {
		randArr := make([]int, 1000000)
		for j := 0; j < 1000000; j++ {
			randArr[j] = rand.Intn(1000001)
		}

		fmt.Printf("Iteration %d\n", i+1)

		fmt.Println("APS")
		arr := make([]int, len(randArr))
		copy(arr, randArr)
		start := time.Now()
		adaptivePartitionSort(arr, 0)
		end := time.Now()
		apsTimes[i] = end.Sub(start).Seconds()
		fmt.Printf("APS END %f\n", apsTimes[i])

		fmt.Println("Bubble")
		arr = make([]int, len(randArr))
		copy(arr, randArr)
		start = time.Now()
		bubbleSort(arr)
		end = time.Now()
		bubbleTimes[i] = end.Sub(start).Seconds()
		fmt.Printf("Bubble END %f\n", bubbleTimes[i])

		fmt.Println("Merge")
		arr = make([]int, len(randArr))
		copy(arr, randArr)
		start = time.Now()
		mergeSort(arr, 0, len(arr)-1, 0)
		end = time.Now()
		mergeTimes[i] = end.Sub(start).Seconds()
		fmt.Printf("Merge END %f\n", mergeTimes[i])
	}

	// Save data to CSV
	file, err := os.Create("data_go.csv")
	if err != nil {
		fmt.Println("Error creating CSV file:", err)
		return
	}
	defer file.Close()

	writer := csv.NewWriter(file)
	defer writer.Flush()

	// Write header
	header := []string{"aps", "bubble", "merge"}
	err = writer.Write(header)
	if err != nil {
		fmt.Println("Error writing header:", err)
		return
	}

	// Write data rows
	for i := 0; i < 128; i++ {
		row := []string{
			strconv.FormatFloat(apsTimes[i], 'f', 6, 64),
			strconv.FormatFloat(bubbleTimes[i], 'f', 6, 64),
			strconv.FormatFloat(mergeTimes[i], 'f', 6, 64),
		}
		err = writer.Write(row)
		if err != nil {
			fmt.Println("Error writing data row:", err)
			return
		}
	}
}
