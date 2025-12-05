#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_repeated(const char* s) {
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
