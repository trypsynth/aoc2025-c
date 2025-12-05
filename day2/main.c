#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_repeated_p1(const char* s) {
	size_t n = strlen(s);
	if (n % 2 != 0) return false;
	size_t half = n / 2;
	for (size_t i = 0; i < half; i++) {
		if (s[i] != s[i + half]) return false;
	}
	return true;
}

bool is_repeated_p2(const char* s) {
	size_t n = strlen(s);
	for (size_t len = 1; len <= n / 2; len++) {
		if (n % len != 0) continue;
		bool ok = true;
		for (size_t i = len; i < n; i++) {
			if (s[i] != s[i % len]) {
				ok = false;
				break;
			}
		}
		if (ok) return true;
	}
	return false;
}

int main() {
	FILE* f = fopen("input.txt", "r");
	if (!f) {
		perror("fopen");
		return EXIT_FAILURE;
	}
	char buf[512];
	fgets(buf, sizeof(buf), f);
	fclose(f);
	char* comma_tok;
	char* bufp = buf;
	long long total_p1 = 0;
	long long total_p2 = 0;
	while ((comma_tok = strsep(&bufp, ","))) {
		char* p = strchr(comma_tok, '-');
		if (!p) break;
		*p = '\0';
		long long left  = strtoll(comma_tok, NULL, 10);
		long long right = strtoll(p + 1, NULL, 10);
		for (long long i = left; i <= right; ++i) {
			char num_buf[32];
			snprintf(num_buf, sizeof(num_buf), "%lld", i);
			if (is_repeated_p1(num_buf)) {
				total_p1 += i;
			}
			if (is_repeated_p2(num_buf)) {
				total_p2 += i;
			}
		}
	}
	printf("%lld\n", total_p1);
	printf("%lld\n", total_p2);
	return EXIT_SUCCESS;
}
