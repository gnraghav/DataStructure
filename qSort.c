#include <stdio.h>

void swap(int *x,int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int 
partition(int a[], int l, int h) {
    int p = a[l];
    int i=l;
    int j=h;
    while (i<j) {
        while (a[i]<=p) { i++; };
        while (a[j]>p) { j--; };
        if(i<j) swap(&a[i],&a[j]);
    };
    
    swap(&a[l], &a[j]);
    return j;
}

void 
qsort(int a[], int l, int h) {
    if (l<h) {
        int p = partition(a,l,h);
        qsort(a,l,p);
        qsort(a,p+1,h);
    }
}
int main() {
    int a[] = {10, 2, 3, 4, 20, 40, 6};
    int n = sizeof(a)/sizeof(a[0]);
    
    qsort(a, 0, n);
    
    for (int i=0;i<n;i++) {
        printf("%d\t",a[i]);
    }

    return 0;
}
