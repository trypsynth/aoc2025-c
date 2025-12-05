#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_repeated(const char* s) {
    size_t n = strlen(s);
    if (n % 2 != 0) return false;
    size_t half = n / 2;
    for (size_t i = 0; i < half; i++) {
        if (s[i] != s[i + half]) return false;
    }
    return true;
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
    long long total = 0;
    while ((comma_tok = strsep(&bufp, ","))) {
        char* p = strchr(comma_tok, '-');
        if (!p) break;
        *p = '\0';
        long long left  = strtoll(comma_tok, NULL, 10);
        long long right = strtoll(p + 1, NULL, 10);
        for (long long i = left; i <= right; ++i) {
            char num_buf[32];
            snprintf(num_buf, sizeof(num_buf), "%lld", i);
            if (is_repeated(num_buf)) {
                total += i;
            }
        }
    }
    printf("%lld\n", total);
    return EXIT_SUCCESS;
}
