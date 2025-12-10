#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE* fp = fopen("input.txt", "r");
	if(!fp) return EXIT_FAILURE;
	char line[4096];
	char* rows[512];
	int row_count = 0;
	while(fgets(line, sizeof line, fp)) {
		rows[row_count] = strdup(line);
		row_count++;
	}
	fclose(fp);
	int len = strlen(rows[0]);
	long total = 0;
	for(int col = 0; col < len; ) {
		int has_nonspace = 0;
		for(int r = 0; r < row_count; r++) if(!isspace((unsigned char)rows[r][col])) has_nonspace = 1;
		if(!has_nonspace) { col++; continue; }
		int end = col;
		for( ; end < len; end++) {
			int nonspace2 = 0;
			for(int r = 0; r < row_count; r++) if(!isspace((unsigned char)rows[r][end])) nonspace2 = 1;
			if(!nonspace2) break;
		}
		char op = '?';
		for(int c = col; c < end; c++) if(rows[row_count-1][c] == '+' || rows[row_count-1][c] == '*') op = rows[row_count-1][c];
		long acc = (op == '*') ? 1 : 0;
		for(int r = 0; r < row_count - 1; r++) {
			char buf[64];
			int bi = 0;
			for(int c = col; c < end; c++) if(isdigit((unsigned char)rows[r][c])) buf[bi++] = rows[r][c];
			if(bi == 0) continue;
			buf[bi] = 0;
			long v = strtol(buf, NULL, 10);
			if(op == '+') acc += v;
			else acc *= v;
		}
		total += acc;
		col = end;
	}
	printf("%ld\n", total);
	for(int i = 0; i < row_count; i++) free(rows[i]);
	return 0;
}
