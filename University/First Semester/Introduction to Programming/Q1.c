// Hubert Jastrzębski | Satori Q1 (Słowo specjalne) | 2024-12-14
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9614772

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MY_DEBUG 0
#define MAX_BUFFER 40

void check(char *buffer, const char *special, FILE *out, int *mode, int line_cnt, int *word_cnt, int *good_cnt, int *buffer_len) {
    if (*mode == 0) {
        memset(buffer, 0, sizeof(char) * MAX_BUFFER);
        *buffer_len = 0;
        return;
    }

    if (*mode != 2 || buffer[0] == 0)
        return;

    *mode = 0;
    int special_len = strlen(special);
    int is_ok = (strcmp(buffer, special) == 0);

    // usunięcie:
    if (!is_ok && *buffer_len == special_len + 1) {
        int is_del = 0, i = 0;
        for (int j = 0; j < special_len; i++, j++) {
            if (buffer[i] != special[j]) {
                if (is_del) break;
                is_del = 1;
                i++;
                if (buffer[i] != special[j]) break;
            }
        }

        if (!is_del || (is_del && i == *buffer_len))
            is_ok = 1;
    }

    // dodanie:
    if (!is_ok && *buffer_len == special_len - 1) {
        int is_add = 0, i = 0;
        for (int j = 0; j < special_len - 1; i++, j++) {
            if (buffer[i] != special[j]) {
                if (is_add) break;
                is_add = 1;
                i--;
            }
        }

        if (!is_add || (is_add && i == *buffer_len - 1 && buffer[*buffer_len - 1] == special[special_len - 1]))
            is_ok = 1;
    }

    // zamiana:
    if (!is_ok && *buffer_len == special_len) {
        int is_swap = 0, i = 0;
        for (int j = 0; j < special_len; i++, j++) {
            if (buffer[i] != special[j]) {
                if (is_swap) break;
                is_swap = 1;
            }
        }

        if (i == *buffer_len)
            is_ok = 1;
    }

    if (is_ok) {
        fprintf(out,
                "Linia %d: %s\n", line_cnt, buffer);
        (*good_cnt)++;
    }
    (*word_cnt)++;
    memset(buffer,0, sizeof(char) * MAX_BUFFER);
    *buffer_len = 0;
}

int main(int argc, char **argv) {
#if MY_DEBUG
    argc = 4;
    char *args[] = {NULL, "0.in", "0.out", "KROPKA"};
    argv = args;
#endif

    if (argc != 4) return 0;

    const char *in_name = argv[1];
    const char *out_name = argv[2];
    char special[MAX_BUFFER];
    strncpy(special, argv[3], MAX_BUFFER);
    for (int i = 0; special[i]; i++)
        special[i] = tolower(special[i]);

    FILE *in = fopen(in_name, "r");
    if (!in) return 0;
    FILE *out = fopen(out_name, "w");

    int line_cnt = 0, comment_cnt = 0, word_cnt = 0, good_cnt = 0;
    int mode = 0; // 0 - none, 1 - comment, 2 - word

    char line[20000];
    char buffer[MAX_BUFFER];
    memset(buffer, 0, sizeof(buffer));
    int buffer_len = 0;

    while (fgets(line, sizeof(line), in)) {
        if (mode != 1) line_cnt++;

        for (int i = 0; line[i]; i++) {
            if (isalpha(line[i])) {
                if (mode != 1) {
                    mode = 2;
                    if (strlen(buffer) < MAX_BUFFER) {}
                    buffer[buffer_len++] = tolower(line[i]);
                }
            } else if (isdigit(line[i])) {
                if (mode == 2 && buffer_len < MAX_BUFFER)
                    buffer[buffer_len++] = line[i];
            } else if (line[i] == '/' && line[i + 1] == '*') {
                mode = 1;
                comment_cnt++;
                i++;
            } else if (mode == 1 && line[i] == '*' && line[i + 1] == '/') {
                comment_cnt--;
                mode = (comment_cnt == 0) ? (buffer_len > 0 ? 2 : 0) : 1;
                i++;
            } else {
                check(buffer, special, out, &mode, line_cnt, &word_cnt, &good_cnt, &buffer_len);
            }
        }
        check(buffer, special, out, &mode, line_cnt, &word_cnt, &good_cnt, &buffer_len);
    }

    fprintf(out, "Wyrazy: %d\n", word_cnt);
    fprintf(out, "Wyrazy specjalne: %d", good_cnt);

    fclose(in);
    fclose(out);

    return 0;
}