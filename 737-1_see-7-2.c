#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

unsigned parent(unsigned i) {
    return i >> 1;
}

unsigned left(unsigned i) {
    return i << 1;
}

unsigned right(unsigned i) {
    return (i << 1) + 1;
}


void max_heapify(int *a, unsigned i, unsigned n) {
    unsigned l = left(i);
    unsigned r = right(i);
    unsigned largest;

    if ( (l < n) && (a[l] > a[i]) ) {
        largest = l;
    }
    else {
        largest = i;
    }

    if ( (r < n) && (a[r] > a[largest]) ) {
        largest = r;
    }

    if (largest != i) {
        swap(&a[i], &a[largest]);
        max_heapify(a, largest, n);
    }
}

void build_max_heap(int *a, unsigned n) {
    for (unsigned i = (n >> 1)-1; i+1 > 0; --i) {
        max_heapify(a, i, n);
    }
}

int heapsort(int *a, unsigned n) {
    build_max_heap(a, n);
    unsigned heapSize = n;

    for (unsigned i = n-1; i+1 > 0; --i) {
        swap(&a[0], &a[i]);
        --heapSize;
        max_heapify(a, 0, heapSize);
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
    scanf("%u", &n);
    int *a = malloc(n * sizeof(int));
    read_array(a, n);
    heapsort(a, n);
    print_array(a, n);
    return 0;
}
 
