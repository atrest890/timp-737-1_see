#include <stdio.h>

int main() {
    int n, prev, next;
    scanf("%d", &n);
    scanf("%d", &prev);

    for (int i = 0; i < n-1; ++i) {
        scanf("%d", &next);

	if ( !(prev <= next) ) {
	    printf("%d", 0);
	    return 0;
        }

	prev = next;
    }

    printf("%d", 1);

    return 0;
}

