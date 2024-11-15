#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

// Function prototypes
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

// Merge Sort implementation
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Quick Sort implementation
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n > MAX_SIZE) {
        printf("Maximum allowed size is %d\n", MAX_SIZE);
        return 1;
    }

    int arr1[MAX_SIZE], arr2[MAX_SIZE];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
        arr2[i] = arr1[i];  // Copy arr1 to arr2 for fair comparison
    }

    // Measure time for Merge Sort
    clock_t start = clock();
    mergeSort(arr1, 0, n - 1);
    clock_t end = clock();
    double time_merge_sort = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array with Merge Sort: ");
    printArray(arr1, n);
    printf("Merge Sort Time: %f seconds\n", time_merge_sort);

    // Measure time for Quick Sort
    start = clock();
    quickSort(arr2, 0, n - 1);
    end = clock();
    double time_quick_sort = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array with Quick Sort: ");
    printArray(arr2, n);
    printf("Quick Sort Time: %f seconds\n", time_quick_sort);

    return 0;
}