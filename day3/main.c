#include <stdio.h>
#include <stdlib.h>

void find_largest_pair(const char* s, int* result) {
	int best = -1;
	int best_tens = -1;
	for (const char* p = s; *p; p++) {
		int d = *p - '0';
		if (best_tens != -1) {
			int val = best_tens * 10 + d;
			if (val > best) best = val;
		}
		if (d > best_tens) best_tens = d;
	}
	*result = best;
}

int main() {
	FILE* f = fopen("input.txt", "r");
	if (!f) {
		perror("fopen");
		return EXIT_FAILURE;
	}
	int total = 0;
	char line[128];
	while (fscanf(f, "%s", line) == 1) {
		int best = 0;
		find_largest_pair(line, &best);
		total += best;
	}
	printf("%d\n", total);
	return EXIT_SUCCESS;
}
