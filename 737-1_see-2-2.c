#include <stdio.h>

int main() {
    int n, a;
    int sum = 0;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a);
	
	if (i % 2 == 0) {
	    sum -= a*a*a;
	}
	else if (i % 2 != 0) {
	    sum += a*a*a;
	}
    }

    printf("%d", sum);

    return 0;
}
