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

static const char *hex_chars = "0123456789abcdef";

void random_name(char *buf, int len) {
    int n = rand_range(3, 6);
    if (n > len - 1) n = len - 1;
    for (int i = 0; i < n; i++) {
        buf[i] = hex_chars[rand_range(0, 15)];
    }
    buf[n] = '\0';
}

void random_var(char *buf, int len) {
    int n = rand_range(3, 5);
    if (n > len - 2) n = len - 2;
    buf[0] = 'a' + rand_range(0, 25);
    for (int i = 1; i < n; i++) {
        buf[i] = hex_chars[rand_range(0, 15)];
    }
    buf[n] = '\0';
}
