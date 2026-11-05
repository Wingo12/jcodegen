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

void print_help(void) {
    printf("jcodegen v%s — генератор мусорного кода\n\n", VERSION);
    printf("Использование: jcodegen [ОПЦИИ]\n\n");
    printf("Опции:\n");
    printf("  -l <lang>       Язык (c, cpp, py, go, js, java, html, asm, bash)\n");
    printf("  -n <lines>      Количество строк (по умолч. 30)\n");
    printf("  -o <file>       Выходной файл (по умолч. stdout)\n");
    printf("  -c              Добавить комментарии\n");
    printf("  --seed <int>    Задать seed для воспроизводимости\n");
    printf("  --depth <int>   Максимальная вложенность (по умолч. %d)\n", DEFAULT_DEPTH);
    printf("  -v              Подробный вывод\n");
    printf("  -h              Эта справка\n\n");
    printf("Примеры:\n");
    printf("  jcodegen -l c -n 50 -o junk.c\n");
    printf("  jcodegen -l py -n 20\n");
    printf("  jcodegen -l c -n 30 --seed 12345 --depth 2 -o junk.c\n");
}

int parse_args(int argc, char **argv, Config *cfg) {
    cfg->lang = LANG_C;
    cfg->lines = 30;
    cfg->output[0] = '\0';
    cfg->verbose = 0;
    cfg->comments = 0;
    cfg->seed = 0;
    cfg->seed_set = 0;
    cfg->depth = DEFAULT_DEPTH;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            exit(0);
        } else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
            LangTemplate *t = get_template_by_name(argv[++i]);
            if (!t) {
                printf("❌ Неизвестный язык: %s\n", argv[i]);
                list_langs();
                return -1;
            }
            cfg->lang = t->id;
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            cfg->lines = atoi(argv[++i]);
            if (cfg->lines < 5) cfg->lines = 5;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strncpy(cfg->output, argv[++i], sizeof(cfg->output) - 1);
        } else if (strcmp(argv[i], "-c") == 0) {
            cfg->comments = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            cfg->verbose = 1;
        } else if (strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            cfg->seed = (unsigned int)strtoul(argv[++i], NULL, 10);
            cfg->seed_set = 1;
        } else if (strcmp(argv[i], "--depth") == 0 && i + 1 < argc) {
            cfg->depth = atoi(argv[++i]);
            if (cfg->depth < 1) cfg->depth = 1;
            if (cfg->depth > 10) cfg->depth = 10;
        }
    }
    return 0;
}
