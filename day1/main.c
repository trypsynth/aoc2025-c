#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* fp = fopen("input.txt", "r");
	if (!fp) {
		perror("fopen");
		return EXIT_FAILURE;
	}
	int pos = 50;
	long long zero_count = 0;
	char dir;
	int dist;
	while (fscanf(fp, " %c%d", &dir, &dist) == 2) {
		int step = (dir == 'L') ? -1 : 1;
		for (int i = 0; i < dist; i++) {
			pos = (pos + step + 100) % 100;
			if (pos == 0) {
				zero_count++;
			}
		}
	}
	fclose(fp);
	printf("%lld\n", zero_count);
	return EXIT_SUCCESS;
}
