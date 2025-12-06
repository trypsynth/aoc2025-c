#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_largest_k(const char* s, int k, char* out) {
	int n = strlen(s);
	int to_remove = n - k;
	int top = 0;
	for (int i = 0; i < n; i++) {
		char c = s[i];
		while (top > 0 && to_remove > 0 && out[top - 1] < c) {
			top--;
			to_remove--;
		}
		out[top++] = c;
	}
	out[k] = '\0';
}

long long parse_12_digits(const char* s) {
	long long val = 0;
	for (int i = 0; i < 12; i++) {
		val = val * 10 + (s[i] - '0');
	}
	return val;
}

int main() {
	FILE* f = fopen("input.txt", "r");
	if (!f) {
		perror("fopen");
		return EXIT_FAILURE;
	}
	char line[256];
	long long total_part1 = 0;
	long long total_part2 = 0;
	while (fscanf(f, "%s", line) == 1) {
		char best2[3];
		find_largest_k(line, 2, best2);
		int p1 = (best2[0] - '0') * 10 + (best2[1] - '0');
		total_part1 += p1;
		char best12[64];
		find_largest_k(line, 12, best12);
		long long p2 = parse_12_digits(best12);
		total_part2 += p2;
	}
	fclose(f);
	printf("%lld\n", total_part1);
	printf("%lld\n", total_part2);
	return EXIT_SUCCESS;
}
