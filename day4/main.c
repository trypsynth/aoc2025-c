#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 300

int main(void) {
	static char g[MAX][MAX];
	static char g2[MAX][MAX];
	int rows = 0;
	int cols = 0;
	FILE* fp = fopen("input.txt", "r");
	if (!fp) {
		perror("fopen");
		return EXIT_FAILURE;
	}
	while (fgets(g[rows], MAX, fp)) {
		int c = 0;
		while (g[rows][c] && g[rows][c] != '\n') c++;
		if (c > cols) cols = c;
		rows++;
	}
	fclose(fp);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			g2[r][c] = g[r][c];
	int dr[8] = {-1,-1,-1, 0,0, 1,1,1};
	int dc[8] = {-1, 0, 1,-1,1,-1,0,1};
	int part1 = 0;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (g[r][c] != '@') continue;
			int adj = 0;
			for (int k = 0; k < 8; k++) {
				int rr = r + dr[k], cc = c + dc[k];
				if (rr >= 0 && rr < rows && cc >= 0 && cc < cols)
					if (g[rr][cc] == '@') adj++;
			}
			if (adj < 4) part1++;
		}
	}
	int total_removed = 0;
	while (true) {
		static bool remove_mask[MAX][MAX];
		int removed_this_round = 0;
		for (int r = 0; r < rows; r++)
			for (int c = 0; c < cols; c++)
				remove_mask[r][c] = false;
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				if (g2[r][c] != '@') continue;
				int adj = 0;
				for (int k = 0; k < 8; k++) {
					int rr = r + dr[k], cc = c + dc[k];
					if (rr >= 0 && rr < rows && cc >= 0 && cc < cols)
						if (g2[rr][cc] == '@') adj++;
				}
				if (adj < 4) {
					remove_mask[r][c] = true;
					removed_this_round++;
				}
			}
		}
		if (removed_this_round == 0) break;
		total_removed += removed_this_round;
		for (int r = 0; r < rows; r++)
			for (int c = 0; c < cols; c++)
				if (remove_mask[r][c]) g2[r][c] = '.';
	}
	printf("%d\n", part1);
	printf("%d\n", total_removed);
	return EXIT_SUCCESS;
}
