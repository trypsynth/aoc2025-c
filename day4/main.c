#include <stdio.h>
#include <stdlib.h>

#define MAX 300

int main(void) {
	static char g[MAX][MAX];
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
	int count = 0;
	int dr[8] = {-1,-1,-1, 0,0, 1,1,1};
	int dc[8] = {-1, 0, 1,-1,1,-1,0,1};
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (g[r][c] != '@') continue;
			int adj = 0;
			for (int k = 0; k < 8; k++) {
				int rr = r + dr[k], cc = c + dc[k];
				if (rr >= 0 && rr < rows && cc >= 0 && cc < cols) {
					if (g[rr][cc] == '@') adj++;
				}
			}
			if (adj < 4) count++;
		}
	}
	printf("%d\n", count);
	return 0;
}
