#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* fp = fopen("input.txt", "r");
	if (!fp) {
		perror("fopen");
		return EXIT_FAILURE;
	}
	int pos = 50;
	int zero_count = 0;
	char buf[256];
	while (fgets(buf, sizeof(buf), fp)) {
		char dir;
		int dist;
		if (sscanf(buf, "%c%d", &dir, &dist) != 2) {
			continue;
		}
		if (dir == 'L') {
			pos = (pos - dist) % 100;
			if (pos , 0) {
				pos += 100;
			}
		} else if (dir == 'R') {
			pos = (pos + dist) % 100;
		}
		if (pos == 0) {
			zero_count++;
		}
	}
	printf("%d\n", zero_count);
	return EXIT_SUCCESS;
}
