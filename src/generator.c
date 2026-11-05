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

static const char *allowed_phrases[] = {
    "junk", "out", "output", "hello", "im here",
    "credits to wingo", "idk what im doing", "something",
    "quick brown fox jumps over the lazy dog", "hiiii",
    "junkyard", "useful text", "lol", "Burmalda",
    "check out my other projects at github.com/Wingo12",
    "im junk programm", "im old", "easter egg",
    "deltarune reference(-_-)", "fun::fact('C is mad at you')",
    "python('easy')", "10 JUNK \n20 SWEET \n30 GOTO 10", NULL
};

static int phrase_count = 23;
static int val_counter = 0;

// ==================== C / C++ ====================
void gen_c_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 8);
    switch (choice) {
        case 0: {
            indent(ind);
            printf("printf(\"%s\\n\");\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        }
        case 1: {
            int val = rand_range(0, 255);
            char vname[MAX_NAME];
            snprintf(vname, sizeof(vname), "val%d", val_counter++);
            indent(ind);
            printf("int %s = %d;\n", vname, val);
            indent(ind);
            printf("printf(\"random value: %%d\\n\", %s);\n", vname);
            break;
        }
        case 2: {
            g->depth++;
            indent(ind);
            printf("for (int i = 0; i < %d; i++) {\n", rand_range(3, 10));
            gen_c_body(g, ind + 1);
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        }
        case 3: {
            g->depth++;
            indent(ind);
            printf("if (x > %d) {\n", rand_range(0, 100));
            gen_c_body(g, ind + 1);
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        }
        case 4: {
            char name[MAX_NAME];
            random_var(name, sizeof(name));
            int size = rand_range(5, 20);
            indent(ind);
            printf("int *%s = malloc(%d * sizeof(int));\n", name, size);
            indent(ind);
            printf("if (%s) {\n", name);
            indent(ind + 1);
            printf("for (int j = 0; j < %d; j++) %s[j] = j;\n", size, name);
            indent(ind + 1);
            printf("(void)%s;\n", name);
            indent(ind);
            printf("free(%s);\n", name);
            indent(ind);
            printf("}\n");
            break;
        }
        case 5: {
            g->depth++;
            indent(ind);
            printf("switch (x) {\n");
            for (int i = 0; i < rand_range(2, 3); i++) {
                indent(ind + 1);
                printf("case %d: {\n", i);
                gen_c_body(g, ind + 2);
                indent(ind + 2);
                printf("break;\n");
                indent(ind + 1);
                printf("}\n");
            }
            indent(ind + 1);
            printf("default: {\n");
            indent(ind + 2);
            printf("break;\n");
            indent(ind + 1);
            printf("}\n");
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        }
        case 6: {
            if (g->loop_depth > 0) {
                indent(ind);
                printf("break;\n");
            }
            break;
        }
        case 7: {
            if (g->loop_depth > 0) {
                indent(ind);
                printf("continue;\n");
            }
            break;
        }
        case 8: {
            indent(ind);
            printf("x = x %s %d;\n", (rand_range(0,1)?"+":"-"), rand_range(1, 100));
            break;
        }
    }
    g->line_count++;
}

void gen_c_function(Generator *g) {
    char name[MAX_NAME];
    random_name(name, sizeof(name));
    printf("int func_%s(int n) {\n", name);
    indent(1);
    printf("int x = n;\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_c_body(g, 1);
    }
    indent(1);
    printf("return %d;\n", rand_range(0, 255));
    printf("}\n\n");
    g->line_count += 2;
}

void gen_c_main(Generator *g) {
    printf("int main(void) {\n");
    indent(1);
    printf("int x = %d;\n", rand_range(0, 100));
    g->depth = 0;
    for (int i = 0; i < rand_range(3, 5); i++) {
        gen_c_body(g, 1);
    }
    indent(1);
    printf("return 0;\n");
    printf("}\n");
}

// ==================== PYTHON ====================
void gen_py_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 5);
    switch (choice) {
        case 0:
            indent(ind);
            printf("print(\"%s\")\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 1: {
            int val = rand_range(0, 255);
            indent(ind);
            printf("val = %d\n", val);
            indent(ind);
            printf("print(f\"random value: {val}\")\n");
            break;
        }
        case 2:
            g->depth++;
            indent(ind);
            printf("for i in range(%d):\n", rand_range(3, 10));
            indent(ind + 1);
            printf("x = i * %d\n", rand_range(1, 10));
            g->depth--;
            break;
        case 3:
            g->depth++;
            indent(ind);
            printf("if x > %d:\n", rand_range(0, 100));
            indent(ind + 1);
            printf("x = x ^ %d\n", rand_range(0, 255));
            g->depth--;
            break;
        case 4:
            indent(ind);
            printf("x = x + %d\n", rand_range(1, 100));
            break;
        case 5:
            indent(ind);
            printf("y = %d\n", rand_range(0, 255));
            break;
    }
    g->line_count++;
}

void gen_py_function(Generator *g) {
    char name[MAX_NAME];
    random_name(name, sizeof(name));
    printf("def func_%s(n):\n", name);
    indent(1);
    printf("x = n\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_py_body(g, 1);
    }
    indent(1);
    printf("return x %% %d\n\n", rand_range(2, 100));
    g->line_count += 2;
}

void gen_py_main(Generator *g) {
    printf("if __name__ == \"__main__\":\n");
    indent(1);
    printf("x = %d\n", rand_range(0, 100));
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_py_body(g, 1);
    }
}

// ==================== GO ====================
void gen_go_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 4);
    switch (choice) {
        case 0:
            indent(ind);
            printf("fmt.Println(\"%s\")\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 1: {
            int val = rand_range(0, 255);
            char vname[MAX_NAME];
            snprintf(vname, sizeof(vname), "val%d", val_counter++);
            indent(ind);
            printf("%s := %d\n", vname, val);
            indent(ind);
            printf("fmt.Println(\"random value:\", %s)\n", vname);
            break;
        }
        case 2:
            g->depth++;
            indent(ind);
            printf("for i := 0; i < %d; i++ {\n", rand_range(3, 10));
            indent(ind + 1);
            printf("x = i * %d\n", rand_range(1, 10));
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        case 3:
            g->depth++;
            indent(ind);
            printf("if x > %d {\n", rand_range(0, 100));
            indent(ind + 1);
            printf("x = x ^ %d\n", rand_range(0, 255));
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        case 4:
            indent(ind);
            printf("x = x + %d\n", rand_range(1, 100));
            break;
    }
    g->line_count++;
}

void gen_go_function(Generator *g) {
    char name[MAX_NAME];
    random_name(name, sizeof(name));
    printf("func func%s(n int) int {\n", name);
    indent(1);
    printf("x := n\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_go_body(g, 1);
    }
    indent(1);
    printf("return %d\n", rand_range(0, 255));
    printf("}\n\n");
    g->line_count += 2;
}

void gen_go_main(Generator *g) {
    printf("func main() {\n");
    indent(1);
    printf("x := %d\n", rand_range(0, 100));
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_go_body(g, 1);
    }
    printf("}\n");
}

// ==================== JS ====================
void gen_js_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 4);
    switch (choice) {
        case 0:
            indent(ind);
            printf("console.log(\"%s\");\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 1: {
            int val = rand_range(0, 255);
            char vname[MAX_NAME];
            snprintf(vname, sizeof(vname), "val%d", val_counter++);
            indent(ind);
            printf("let %s = %d;\n", vname, val);
            indent(ind);
            printf("console.log(`random value: ${%s}`);\n", vname);
            break;
        }
        case 2:
            g->depth++;
            indent(ind);
            printf("for (let i = 0; i < %d; i++) {\n", rand_range(3, 10));
            gen_js_body(g, ind + 1);
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        case 3:
            g->depth++;
            indent(ind);
            printf("if (x > %d) {\n", rand_range(0, 100));
            gen_js_body(g, ind + 1);
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        case 4:
            indent(ind);
            printf("x = x + %d;\n", rand_range(1, 100));
            break;
    }
    g->line_count++;
}

void gen_js_function(Generator *g) {
    char name[MAX_NAME];
    random_name(name, sizeof(name));
    printf("function func%s(n) {\n", name);
    indent(1);
    printf("let x = n;\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_js_body(g, 1);
    }
    indent(1);
    printf("return %d;\n", rand_range(0, 255));
    printf("}\n\n");
    g->line_count += 2;
}

void gen_js_main(Generator *g) {
    printf("// main\n");
    printf("let x = %d;\n", rand_range(0, 100));
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_js_body(g, 0);
    }
}

// ==================== JAVA ====================
void gen_java_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 4);
    switch (choice) {
        case 0:
            indent(ind);
            printf("System.out.println(\"%s\");\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 1: {
            int val = rand_range(0, 255);
            char vname[MAX_NAME];
            snprintf(vname, sizeof(vname), "val%d", val_counter++);
            indent(ind);
            printf("int %s = %d;\n", vname, val);
            indent(ind);
            printf("System.out.println(\"random value: \" + %s);\n", vname);
            break;
        }
        case 2:
            g->depth++;
            indent(ind);
            printf("for (int i = 0; i < %d; i++) {\n", rand_range(3, 10));
            gen_java_body(g, ind + 1);
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        case 3:
            g->depth++;
            indent(ind);
            printf("if (x > %d) {\n", rand_range(0, 100));
            gen_java_body(g, ind + 1);
            indent(ind);
            printf("}\n");
            g->depth--;
            break;
        case 4:
            indent(ind);
            printf("x = x + %d;\n", rand_range(1, 100));
            break;
    }
    g->line_count++;
}

void gen_java_function(Generator *g) {
    char name[MAX_NAME];
    random_name(name, sizeof(name));
    printf("    static int func%s(int n) {\n", name);
    indent(2);
    printf("int x = n;\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_java_body(g, 2);
    }
    indent(2);
    printf("return %d;\n", rand_range(0, 255));
    printf("    }\n\n");
    g->line_count += 2;
}

void gen_java_main(Generator *g) {
    printf("    public static void main(String[] args) {\n");
    indent(2);
    printf("int x = %d;\n", rand_range(0, 100));
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_java_body(g, 2);
    }
    printf("    }\n");
}

// ==================== BASH ====================
void gen_bash_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 3);
    switch (choice) {
        case 0:
            indent(ind);
            printf("echo \"%s\"\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 1:
            indent(ind);
            printf("val=%d\n", rand_range(0, 255));
            indent(ind);
            printf("echo \"random value: $val\"\n");
            break;
        case 2:
            g->depth++;
            indent(ind);
            printf("for i in $(seq 1 %d); do\n", rand_range(3, 10));
            indent(ind + 1);
            printf("x=$((i * %d))\n", rand_range(1, 10));
            indent(ind);
            printf("done\n");
            g->depth--;
            break;
        case 3:
            g->depth++;
            indent(ind);
            printf("if [ $x -gt %d ]; then\n", rand_range(0, 100));
            indent(ind + 1);
            printf("x=$((x ^ %d))\n", rand_range(0, 255));
            indent(ind);
            printf("fi\n");
            g->depth--;
            break;
    }
    g->line_count++;
}

void gen_bash_function(Generator *g) {
    char name[MAX_NAME];
    random_name(name, sizeof(name));
    printf("func_%s() {\n", name);
    indent(1);
    printf("x=$1\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_bash_body(g, 1);
    }
    indent(1);
    printf("return %d\n", rand_range(0, 255) % 256);
    printf("}\n\n");
    g->line_count += 2;
}

void gen_bash_main(Generator *g) {
    printf("# main\n");
    printf("x=%d\n", rand_range(0, 100));
    g->depth = 0;
    for (int i = 0; i < rand_range(2, 4); i++) {
        gen_bash_body(g, 0);
    }
}

// ==================== HTML ====================
void gen_html_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 5);
    switch (choice) {
        case 0:
            indent(ind);
            printf("<p>%s</p>\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 1:
            indent(ind);
            printf("<div>%s</div>\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 2:
            g->depth++;
            indent(ind);
            printf("<section>\n");
            gen_html_body(g, ind + 1);
            indent(ind);
            printf("</section>\n");
            g->depth--;
            break;
        case 3:
            indent(ind);
            printf("<span>%s</span>\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 4:
            indent(ind);
            printf("<ul><li>%s</li></ul>\n", allowed_phrases[rand_range(0, phrase_count - 1)]);
            break;
        case 5:
            indent(ind);
            printf("<p>random value: %d</p>\n", rand_range(0, 255));
            break;
    }
    g->line_count++;
}

void gen_html(Generator *g) {
    printf("<!DOCTYPE html>\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<meta charset=\"utf-8\">\n");
    printf("<title>junk</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(3, 6); i++) {
        gen_html_body(g, 0);
    }
    printf("</body>\n");
    printf("</html>\n");
}

// ==================== ASM ====================
void gen_asm_body(Generator *g, int ind) {
    if (g->depth >= g->max_depth) return;
    int choice = rand_range(0, 5);
    switch (choice) {
        case 0:
            indent(ind);
            printf("mov %s, %d\n", (rand_range(0,1) ? "rax" : "rbx"), rand_range(0, 255));
            break;
        case 1:
            indent(ind);
            printf("add %s, %s\n", "rax", "rbx");
            break;
        case 2:
            indent(ind);
            printf("xor %s, %s\n", "rcx", "rdx");
            break;
        case 3:
            indent(ind);
            printf("cmp %s, %d\n", "rax", rand_range(0, 255));
            break;
        case 4:
            g->depth++;
            indent(ind);
            printf("mov ecx, %d\n", rand_range(3, 10));
            indent(ind);
            printf(".loop_%d:\n", rand_range(0, 100));
            gen_asm_body(g, ind + 1);
            indent(ind);
            printf("dec ecx\n");
            indent(ind);
            printf("jnz .loop_%d\n", rand_range(0, 100));
            g->depth--;
            break;
        case 5:
            indent(ind);
            printf("push eax\n");
            indent(ind);
            printf("pop ebx\n");
            break;
    }
    g->line_count++;
}

void gen_asm(Generator *g) {
    printf("section .data\n");
    for (int i = 0; i < rand_range(1, 3); i++) {
        printf("    var%d dd %d\n", i, rand_range(0, 255));
    }
    printf("\nsection .text\n");
    printf("global _start\n\n");
    printf("_start:\n");
    g->depth = 0;
    for (int i = 0; i < rand_range(3, 6); i++) {
        gen_asm_body(g, 0);
    }
    printf("    mov eax, 0\n");
    printf("    ret\n");
}

// ==================== ДИСПЕТЧЕР ====================
void generate(Generator *g, Config *cfg) {
    (void)cfg;
    val_counter = 0;
    g->depth = 0;

    switch (g->t->id) {
        case LANG_PY:
            gen_py_function(g);
            gen_py_main(g);
            break;
        case LANG_HTML:
            gen_html(g);
            break;
        case LANG_ASM:
            gen_asm(g);
            break;
        case LANG_GO:
            printf("package main\nimport \"fmt\"\n\n");
            gen_go_function(g);
            gen_go_main(g);
            break;
        case LANG_JS:
            gen_js_function(g);
            gen_js_main(g);
            break;
        case LANG_JAVA:
            printf("public class Junk {\n");
            gen_java_function(g);
            gen_java_main(g);
            printf("}\n");
            break;
        case LANG_BASH:
            printf("#!/bin/bash\n\n");
            gen_bash_function(g);
            gen_bash_main(g);
            break;
        case LANG_C:
        case LANG_CPP:
        default:
            gen_include(g);
            gen_global_vars(g);
            gen_c_function(g);
            gen_c_main(g);
            break;
    }
}

// Вспомогательные (нужны для C-режима)
void gen_include(Generator *g) {
    if (g->t->id != LANG_C && g->t->id != LANG_CPP) return;
    for (int i = 0; g->t->includes[i]; i++) {
        printf("%s\n", g->t->includes[i]);
    }
    printf("\n");
}

void gen_global_vars(Generator *g) {
    if (g->t->id != LANG_C && g->t->id != LANG_CPP) return;
    for (int i = 0; i < rand_range(0, 2); i++) {
        char name[MAX_NAME];
        random_var(name, sizeof(name));
        printf("%s %s = %d;\n", g->t->types[rand_range(0, 5)], name, rand_range(0, 255));
        g->line_count++;
    }
    if (g->line_count > 0) printf("\n");
}

// Заглушки для старых прототипов
void gen_body(Generator *g, int ind) { (void)g; (void)ind; }
void gen_loop(Generator *g, int ind) { (void)g; (void)ind; }
void gen_condition(Generator *g, int ind) { (void)g; (void)ind; }
void gen_switch(Generator *g, int ind) { (void)g; (void)ind; }
void gen_alloc(Generator *g, int ind) { (void)g; (void)ind; }
void gen_free(Generator *g, int ind) { (void)g; (void)ind; }
void gen_print(Generator *g, int ind) { (void)g; (void)ind; }
void gen_print_var(Generator *g, int ind) { (void)g; (void)ind; }
void gen_break(Generator *g, int ind) { (void)g; (void)ind; }
void gen_continue(Generator *g, int ind) { (void)g; (void)ind; }
void gen_function(Generator *g) { (void)g; }
void gen_main(Generator *g) { (void)g; }
