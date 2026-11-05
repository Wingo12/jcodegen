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

int main(int argc, char **argv) {
    Config cfg;
    if (parse_args(argc, argv, &cfg) != 0) {
        return 1;
    }

    if (cfg.seed_set) {
        srand(cfg.seed);
    } else {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        srand(tv.tv_sec ^ tv.tv_usec ^ (getpid() << 16));
    }

    LangTemplate *t = get_template(cfg.lang);
    if (!t) {
        printf("❌ Неизвестный язык\n");
        return 1;
    }

    if (cfg.verbose) {
        printf("🐕 jcodegen v%s\n", VERSION);
        printf("   Язык: %s\n", t->name);
        printf("   Строк: %d\n", cfg.lines);
        printf("   Глубина: %d\n", cfg.depth);
        printf("   Файл: %s\n", cfg.output[0] ? cfg.output : "stdout");
        if (cfg.seed_set) {
            printf("   Seed: %u\n", cfg.seed);
        } else {
            printf("   Seed: random\n");
        }
        printf("\n");
    }

    if (cfg.output[0]) {
        if (!freopen(cfg.output, "w", stdout)) {
            printf("❌ Не удалось открыть файл: %s\n", cfg.output);
            return 1;
        }
    }

    Generator g = {0};
    g.t = t;
    g.loop_depth = 0;
    g.switch_depth = 0;
    g.line_count = 0;
    g.alloc_count = 0;
    g.depth = 0;
    g.max_depth = cfg.depth;

    generate(&g, &cfg);

    if (cfg.verbose && cfg.output[0]) {
        printf("✅ Готово! %s\n", cfg.output);
    }

    return 0;
}
