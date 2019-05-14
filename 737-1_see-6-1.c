#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int comb_sort(int *a, unsigned n) {
    double fact = 1.2473309;
    double step = n - 1;

    while (step >= 1) {
        for (unsigned i = 0; i + step < n; ++i) {
            if (a[i] > a[i+ (unsigned)step]) {
                swap(&a[i], &a[i + (unsigned)step]);
            }
        }

        step /= fact;
    }

    for (unsigned i = 0; i < n-1; ++i) {
        int swapped = false;

        for (unsigned j = 0; j < n-i-1; ++j) {
            if (a[j] > a[j+1]) {
                swap(&a[j], &a[j+1]);
                swapped = true;
            }
        }

        if ( !swapped ) {
            break;
        }
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
    comb_sort(a, n);
    print_array(a, n);

    return 0;

}
