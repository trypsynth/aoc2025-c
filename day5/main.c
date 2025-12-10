#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	long long a;
	long long b;
} range;

static int cmp_range(const void* x, const void* y) {
	const range* r1 = x;
	const range* r2 = y;
	if (r1->a < r2->a) return -1;
	if (r1->a > r2->a) return 1;
	return (r1->b > r2->b) - (r1->b < r2->b);
}

int main() {
	FILE* f = fopen("input.txt", "r");
	if (!f) return EXIT_FAILURE;
	range ranges[20000];
	int rc = 0;
	char buf[128];
	int in_ids = 0;
	long long ids[20000];
	int ic = 0;
	while (fgets(buf, sizeof buf, f)) {
		int blank = 1;
		for (char* p = buf; *p; p++) {
			if (!isspace((unsigned char)*p)) {
				blank = 0;
				break;
			}
		}
		if (blank) { 
			in_ids = 1;
			continue;
		}
		if (!in_ids) {
			long long a;
			long long b;
			if (sscanf(buf, "%lld-%lld", &a, &b) == 2) ranges[rc++] = (range){a, b};
		} else {
			long long id;
			if (sscanf(buf, "%lld", &id) == 1) ids[ic++] = id;
		}
	}
	qsort(ranges, rc, sizeof(range), cmp_range);
	range merged[20000];
	int mc = 0;
	for (int i = 0; i < rc; i++) {
		if (mc == 0) {
			merged[mc++] = ranges[i];
			continue;
		}
		range* last = &merged[mc - 1];
		if (ranges[i].a <= last->b + 1) {
			if (ranges[i].b > last->b) last->b = ranges[i].b;
		} else {
			merged[mc++] = ranges[i];
		}
	}
	int fresh = 0;
	for (int i = 0; i < ic; i++) {
		long long id = ids[i];
		int lo = 0;
		int hi = mc - 1;
		int ok = 0;
		while (lo <= hi) {
			int mid = (lo + hi) / 2;
			if (id < merged[mid].a) {
				hi = mid - 1;
			} else if (id > merged[mid].b) {
				lo = mid + 1;
			} else {
				ok = 1;
				break;
			}
		}
		if (ok) fresh++;
	}
	printf("%d\n", fresh);
	return EXIT_SUCCESS;
}
