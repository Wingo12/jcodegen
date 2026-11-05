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

#ifndef JCODEGEN_H
#define JCODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#define VERSION "0.1"
#define MAX_NAME 64
#define MAX_LINE 4096
#define DEFAULT_DEPTH 3

typedef enum {
    LANG_C,
    LANG_CPP,
    LANG_PY,
    LANG_GO,
    LANG_JS,
    LANG_JAVA,
    LANG_HTML,
    LANG_ASM,
    LANG_BASH,
    LANG_COUNT
} LangID;

typedef struct {
    LangID id;
    const char *name;
    const char *ext;
    const char *includes[8];
    const char *types[16];
    const char *ops[12];
    const char *keywords[16];
    const char *alloc;
    const char *dealloc;
    const char *comment;
    int has_alloc;
} LangTemplate;

typedef struct {
    LangID lang;
    int lines;
    char output[256];
    int verbose;
    int comments;
    unsigned int seed;
    int seed_set;
    int depth;              // НОВОЕ
} Config;

typedef struct {
    LangTemplate *t;
    int loop_depth;
    int switch_depth;
    int line_count;
    int alloc_count;
    int depth;
    int max_depth;          // НОВОЕ
    char allocs[100][MAX_NAME];
} Generator;

LangTemplate* get_template(LangID id);
LangTemplate* get_template_by_name(const char *name);
void list_langs(void);

void generate(Generator *g, Config *cfg);
void gen_include(Generator *g);
void gen_global_vars(Generator *g);
void gen_function(Generator *g);
void gen_body(Generator *g, int indent);
void gen_loop(Generator *g, int indent);
void gen_condition(Generator *g, int indent);
void gen_switch(Generator *g, int indent);
void gen_alloc(Generator *g, int indent);
void gen_free(Generator *g, int indent);
void gen_print(Generator *g, int indent);
void gen_print_var(Generator *g, int indent);
void gen_break(Generator *g, int indent);
void gen_continue(Generator *g, int indent);
void gen_main(Generator *g);

void random_name(char *buf, int len);
void random_var(char *buf, int len);

int validate_code(const char *code, LangID lang);
int is_forbidden(const char *line, LangID lang);

void print_help(void);
int parse_args(int argc, char **argv, Config *cfg);

void trim(char *str);
int rand_range(int min, int max);
void indent(int level);

#endif
