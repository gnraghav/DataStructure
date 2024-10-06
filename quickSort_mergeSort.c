#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int a[], int low, int high) {
    int p = a[high];
    int i = low;
    for(int j=low;j<high;j++) {
        if (a[j]<=p) {
            swap(&a[i], &a[j]);
            i++;
        }
    }
    swap(&a[i], &a[high]);
    return i;
}

void qsort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        qsort(a, low, p - 1);  // Recursively sort elements before partition
        qsort(a, p + 1, high); // Recursively sort elements after partition
    }
}

void merge(int a[],int low, int mid, int high) {
    int n1 = mid-low+1;
    int n2 = high-mid;
    int L[n1], R[n2];
    int i=0, j=0;
    while(i<n1) { L[i] = a[low+i]; i++; }
    while(j<n2) { R[j] = a[mid+1+j]; j++; }
    i=0;
    j=0;
    int k=low;
    while(i<n1 && j<n2) {
        if (L[i] <= R[j]) { a[k++] = L[i++]; }
        else { a[k++] = R[j++]; }
    }

    while(i<n1) {
        a[k++] = L[i++];
    }

    while(j<n2) {
        a[k++] = R[j++];
    }
}

void msort(int a[], int low, int high) {
    if (low<high) {
        int mid = low+(high-low)/2;
        msort(a, low, mid);
        msort(a, mid+1, high);
        merge(a, low, mid, high);
    }
}
int main() {
    int a[] = {10, 2, 3, 4, 20, 40, 6};
    int n = sizeof(a) / sizeof(a[0]);

    //qsort(a, 0, n - 1);
    msort(a, 0, n-1);

    for (int i = 0; i < n; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");

    return 0;
}
