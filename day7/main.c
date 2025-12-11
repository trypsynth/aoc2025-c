#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char grid[256][256];
	int rows = 0;
	int cols = 0;
	int srow = -1;
	int scol = -1;
	FILE* f = fopen("input.txt", "r");
	if (!f) return EXIT_FAILURE;
	while (rows < 256 && fgets(grid[rows], sizeof grid[rows], f)) {
		int len = 0;
		while (grid[rows][len] && grid[rows][len] != '\n' && grid[rows][len] != '\r') len++;
		grid[rows][len] = '\0';
		if (len > cols) cols = len;
		for (int i = 0; i < len; i++) {
			if (grid[rows][i] == 'S') {
				srow = rows;
				scol = i;
				grid[rows][i] = '.';
			}
		}
		rows++;
	}
	fclose(f);
	if (srow < 0) return EXIT_FAILURE;
	long long splits = 0;
	int beams1[256] = {0}, next1[256] = {0};
	beams1[scol] = 1;
	for (int r = srow + 1; r < rows; r++) {
		for (int c = 0; c < cols; c++) next1[c] = 0;
		for (int c = 0; c < cols; c++) {
			if (!beams1[c]) continue;
			char ch = grid[r][c];
			if (ch == '^') {
				splits++;
				if (c > 0) next1[c - 1] = 1;
				if (c + 1 < cols) next1[c + 1] = 1;
			} else next1[c] = 1;
		}
		for (int c = 0; c < cols; c++) beams1[c] = next1[c];
	}
	long long part1 = splits;
	unsigned long long beams2[256] = {0};
	unsigned long long next2[256]  = {0};
	beams2[scol] = 1;
	for (int r = srow + 1; r < rows; r++) {
		for (int c = 0; c < cols; c++) next2[c] = 0;
		for (int c = 0; c < cols; c++) {
			unsigned long long count = beams2[c];
			if (!count) continue;
			char ch = grid[r][c];
			if (ch == '^') {
				if (c > 0) next2[c - 1] += count;
				if (c + 1 < cols) next2[c + 1] += count;
			} else next2[c] += count;
		}
		for (int c = 0; c < cols; c++) beams2[c] = next2[c];
	}
	unsigned long long part2 = 0;
	for (int c = 0; c < cols; c++) part2 += beams2[c];
	printf("%lld\n%llu\n", part1, part2);
	return EXIT_SUCCESS;
}
