/*
 * jcodegen — генератор мусорного кода
 * Copyright (C) 2026 Wingo123
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "jcodegen.h"

static const char *forbidden_common[] = {
    "system(", "popen(", "exec", "fork(",
    "remove(", "unlink(", "rmdir(",
    NULL
};

static const char *forbidden_c[] = {
    "fopen(.*\"w\"", "fopen(.*\"a\"",
    NULL
};

int is_forbidden(const char *line, LangID lang) {
    for (int i = 0; forbidden_common[i]; i++) {
        if (strstr(line, forbidden_common[i])) return 1;
    }
    if (lang == LANG_C || lang == LANG_CPP) {
        for (int i = 0; forbidden_c[i]; i++) {
            if (strstr(line, forbidden_c[i])) return 1;
        }
    }
    return 0;
}

int validate_code(const char *code, LangID lang) {
    (void)lang;
    char *copy = strdup(code);
    char *line = strtok(copy, "\n");
    while (line) {
        if (is_forbidden(line, lang)) {
            free(copy);
            return 0;
        }
        line = strtok(NULL, "\n");
    }
    free(copy);
    return 1;
}
