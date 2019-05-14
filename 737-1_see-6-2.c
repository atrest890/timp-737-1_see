#include <stdio.h>
#include <stdlib.h>

int shells_sort(int *a, unsigned n) {
    unsigned i, j, k;
    int t;

    for (k = n/2; k > 0; k /= 2) {
        for (i = k; i < n; ++i) {
            t = a[i];

            for (j = i; j >= k; j -= k) {
                if (t  < a[j-k]) {
                    a[j] = a[j-k];
                }
                else {
                    break;
                }
            }

            a[j] = t;
        }
    }

    return 0;
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

int main()
{
    unsigned n;
    int x;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));

    for (unsigned i = 0; i < n; ++i) {
        scanf("%d", &x);
        a[i] = x;
    }

    shells_sort(a, n);
    print_array(a, n);

    return 0;
}
