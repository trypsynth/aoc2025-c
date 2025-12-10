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
	long total2 = 0;
	for(int col2 = 0; col2 < len; ) {
		int valid = 0;
		for(int r = 0; r < row_count; r++) if(!isspace((unsigned char)rows[r][col2])) valid = 1;
		if(!valid) {
			col2++;
			continue;
		}
		int end2 = col2;
		for( ; end2 < len; end2++) {
			int v2 = 0;
			for(int r = 0; r < row_count; r++) if(!isspace((unsigned char)rows[r][end2])) v2 = 1;
			if(!v2) break;
		}
		char op2 = '?';
		for(int c = col2; c < end2; c++) if(rows[row_count-1][c] == '+' || rows[row_count-1][c] == '*') op2 = rows[row_count-1][c];
		long acc2 = (op2 == '*') ? 1 : 0;
		for(int c = col2; c < end2; c++) {
			char buf2[64];
			int bi2 = 0;
			for(int r = 0; r < row_count - 1; r++) if(isdigit((unsigned char)rows[r][c])) buf2[bi2++] = rows[r][c];
			if(bi2 == 0) continue;
			buf2[bi2] = 0;
			long v = strtol(buf2, NULL, 10);
			if(op2 == '+') acc2 += v;
			else acc2 *= v;
		}
		total2 += acc2;
		col2 = end2;
	}
	printf("%ld\n", total);
	printf("%ld\n", total2);
	for(int i = 0; i < row_count; i++) free(rows[i]);
	return 0;
}
