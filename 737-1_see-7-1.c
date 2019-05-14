#include <stdio.h>
#include <stdlib.h>
#define true 1

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

unsigned partition(int *a, unsigned l, unsigned r) {
    int pivot = a[r-1];
    unsigned i = l-1;

    for (unsigned j = l; j < r; j++) {
        if (a[j-1] <= pivot) {
            i++;
            swap(&a[i-1], &a[j-1]);
            //++i;
        }
    }
    swap(&a[i+1-1], &a[r-1]);
    return i+1;
}


int quicksort(int *a, unsigned l, unsigned r) {
    if (l < r) {
        unsigned q = partition(a, l, r);
        quicksort(a, l, q-1);
        quicksort(a, q+1, r);
    }

    return 0;
}

void read_array(int *a, unsigned n) {
    int x;
    for (unsigned i = 0; i < n; ++i) {
        scanf("%d", &x);
        a[i] = x;
    }
}

void print_array(int *a, unsigned n) {
    for (unsigned i = 0; i < n; ++i) {
        printf("%d", a[i]);

        if (i != n-1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    unsigned n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    read_array(a, n);
    quicksort(a, 1, n);
    print_array(a, n);

    return 0;
}
