#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int32_t x;
	int32_t y;
	int32_t z;
} point_t;

typedef struct {
	size_t a;
	size_t b;
	int64_t dist2;
} edge_t;

typedef struct {
	size_t parent;
	size_t size;
} dsu_t;

static size_t dsu_find(dsu_t* dsu, size_t x) {
	if (dsu[x].parent != x) dsu[x].parent = dsu_find(dsu, dsu[x].parent);
	return dsu[x].parent;
}

static bool dsu_union(dsu_t* dsu, size_t a, size_t b) {
	a = dsu_find(dsu, a);
	b = dsu_find(dsu, b);
	if (a == b) return false;
	if (dsu[a].size < dsu[b].size) {
		size_t tmp = a;
		a = b;
		b = tmp;
	}
	dsu[b].parent = a;
	dsu[a].size += dsu[b].size;
	return true;
}

static int cmp_edge(const void* a, const void* b) {
	const edge_t* ea = a;
	const edge_t* eb = b;
	if (ea->dist2 < eb->dist2) return -1;
	if (ea->dist2 > eb->dist2) return 1;
	return 0;
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	if (!fp) return EXIT_FAILURE;
	point_t* points = NULL;
	size_t n = 0;
	size_t cap = 0;
	while (true) {
		point_t p;
		if (fscanf(fp, "%d,%d,%d", &p.x, &p.y, &p.z) != 3) break;
		if (n == cap) {
			cap = cap ? cap * 2 : 64;
			points = realloc(points, cap * sizeof(*points));
		}
		points[n++] = p;
	}
	fclose(fp);
	size_t edge_count = n * (n - 1) / 2;
	edge_t* edges = malloc(edge_count * sizeof(*edges));
	size_t idx = 0;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = i + 1; j < n; j++) {
			int64_t dx = points[i].x - points[j].x;
			int64_t dy = points[i].y - points[j].y;
			int64_t dz = points[i].z - points[j].z;
			edges[idx++] = (edge_t){
				.a = i,
				.b = j,
				.dist2 = dx*dx + dy*dy + dz*dz
			};
		}
	}
	qsort(edges, edge_count, sizeof(*edges), cmp_edge);
	dsu_t* dsu1 = malloc(n * sizeof(*dsu1));
	for (size_t i = 0; i < n; i++) {
		dsu1[i].parent = i;
		dsu1[i].size = 1;
	}
	for (size_t i = 0; i < edge_count && i < 1000; i++) dsu_union(dsu1, edges[i].a, edges[i].b);
	size_t* sizes = calloc(n, sizeof(*sizes));
	for (size_t i = 0; i < n; i++) {
		size_t r = dsu_find(dsu1, i);
		sizes[r] = dsu1[r].size;
	}
	size_t t1 = 0;
	size_t t2 = 0;
	size_t t3 = 0;
	for (size_t i = 0; i < n; i++) {
		size_t s = sizes[i];
		if (s > t1) {
			t3 = t2;
			t2 = t1;
			t1 = s;
		} else if (s > t2) {
			t3 = t2;
			t2 = s;
		} else if (s > t3) {
			t3 = s;
		}
	}
	size_t part1 = t1 * t2 * t3;
	dsu_t* dsu2 = malloc(n * sizeof(*dsu2));
	for (size_t i = 0; i < n; i++) {
		dsu2[i].parent = i;
		dsu2[i].size = 1;
	}
	size_t components = n;
	size_t last_a = 0;
	size_t last_b = 0;
	for (size_t i = 0; i < edge_count && components > 1; i++) {
		if (dsu_union(dsu2, edges[i].a, edges[i].b)) {
			last_a = edges[i].a;
			last_b = edges[i].b;
			components--;
		}
	}
	int64_t part2 = (int64_t)points[last_a].x * (int64_t)points[last_b].x;
	printf("%zu\n", part1);
	printf("%lld\n", (long long)part2);
	free(points);
	free(edges);
	free(dsu1);
	free(dsu2);
	free(sizes);
	return EXIT_SUCCESS;
}
