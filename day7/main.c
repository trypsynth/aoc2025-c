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
				grid[rows][i] = '.'; /* treat S as empty for the simulation */
			}
		}
		rows++;
	}
	fclose(f);
	if (srow < 0 || scol < 0) return EXIT_FAILURE;
	int beams[256] = {0};
	int next[256]  = {0};
	long long splits = 0;
	beams[scol] = 1;
	for (int r = srow + 1; r < rows; r++) {
		for (int c = 0; c < cols; c++) next[c] = 0;
		for (int c = 0; c < cols; c++) {
			if (!beams[c]) continue;
			char ch = (c < 256) ? grid[r][c] : '.';
			if (ch == '^') {
				splits++;
				if (c > 0)	  next[c - 1] = 1;
				if (c + 1 < cols) next[c + 1] = 1;
			} else next[c] = 1;
		}
		for (int c = 0; c < cols; c++) beams[c] = next[c];
	}
	printf("%lld\n", splits);
	return EXIT_SUCCESS;
}
