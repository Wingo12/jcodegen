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

static LangTemplate templates[LANG_COUNT] = {
    {
        .id = LANG_C, .name = "c", .ext = "c",
        .includes = {"#include <stdio.h>", "#include <stdlib.h>", "#include <string.h>"},
        .types = {"int", "long", "double", "float", "char", "unsigned int"},
        .ops = {"+", "-", "*", "/", "^", "&", "|", "<<"},
        .keywords = {"if", "else", "while", "for", "return", "switch", "case", "break", "continue"},
        .alloc = "malloc", .dealloc = "free", .comment = "//", .has_alloc = 1
    },
    {
        .id = LANG_CPP, .name = "cpp", .ext = "cpp",
        .includes = {"#include <iostream>", "#include <vector>", "#include <string>"},
        .types = {"int", "long", "double", "float", "char", "bool", "auto"},
        .ops = {"+", "-", "*", "/", "^", "&", "|", "<<"},
        .keywords = {"if", "else", "while", "for", "return", "switch", "case", "break", "continue"},
        .alloc = "new", .dealloc = "delete", .comment = "//", .has_alloc = 1
    },
    {
        .id = LANG_PY, .name = "py", .ext = "py",
        .includes = {"import os", "import sys", "import random"},
        .types = {"", "", ""},
        .ops = {"+", "-", "*", "/", "^", "&", "|", "<<"},
        .keywords = {"if", "elif", "else", "while", "for", "return", "def", "class"},
        .alloc = "", .dealloc = "", .comment = "#", .has_alloc = 0
    },
    {
        .id = LANG_GO, .name = "go", .ext = "go",
        .includes = {"package main", "import \"fmt\""},
        .types = {"int", "int64", "float64", "string", "bool", "byte"},
        .ops = {"+", "-", "*", "/", "^", "&", "|", "<<"},
        .keywords = {"if", "else", "for", "return", "switch", "case", "break", "continue", "func"},
        .alloc = "make", .dealloc = "// GC", .comment = "//", .has_alloc = 1
    },
    {
        .id = LANG_JS, .name = "js", .ext = "js",
        .includes = {},
        .types = {"let", "const", "var"},
        .ops = {"+", "-", "*", "/", "^", "&", "|", "<<"},
        .keywords = {"if", "else", "while", "for", "return", "switch", "case", "break", "continue", "function", "class"},
        .alloc = "[]", .dealloc = "// GC", .comment = "//", .has_alloc = 1
    },
    {
        .id = LANG_JAVA, .name = "java", .ext = "java",
        .includes = {"import java.util.*;", "import java.io.*;"},
        .types = {"int", "long", "double", "float", "boolean", "char", "String"},
        .ops = {"+", "-", "*", "/", "^", "&", "|", "<<"},
        .keywords = {"if", "else", "while", "for", "return", "switch", "case", "break", "continue", "public", "static", "class"},
        .alloc = "new", .dealloc = "// GC", .comment = "//", .has_alloc = 1
    },
    {
        .id = LANG_HTML, .name = "html", .ext = "html",
        .includes = {"<!DOCTYPE html>", "<html>", "<head>", "<meta charset=\"utf-8\">", "</head>", "<body>"},
        .types = {"<div>", "<span>", "<p>"},
        .ops = {},
        .keywords = {},
        .alloc = "", .dealloc = "", .comment = "<!--", .has_alloc = 0
    },
    {
        .id = LANG_ASM, .name = "asm", .ext = "asm",
        .includes = {"section .data", "section .text", "global _start"},
        .types = {"dd", "db", "dw", "dq"},
        .ops = {"add", "sub", "xor", "and", "or", "shl", "shr"},
        .keywords = {"mov", "cmp", "je", "jne", "jg", "jl", "jmp", "push", "pop", "ret"},
        .alloc = "", .dealloc = "", .comment = ";", .has_alloc = 0
    },
    {
        .id = LANG_BASH, .name = "bash", .ext = "sh",
        .includes = {"#!/bin/bash"},
        .types = {"", "", ""},
        .ops = {"+", "-", "*", "/", "^", "&", "|"},
        .keywords = {"if", "else", "while", "for", "return", "case", "break", "continue", "function"},
        .alloc = "", .dealloc = "", .comment = "#", .has_alloc = 0
    }
};

LangTemplate* get_template(LangID id) {
    if (id < 0 || id >= LANG_COUNT) return NULL;
    return &templates[id];
}

LangTemplate* get_template_by_name(const char *name) {
    for (int i = 0; i < LANG_COUNT; i++) {
        if (strcmp(templates[i].name, name) == 0) {
            return &templates[i];
        }
    }
    return NULL;
}

void list_langs(void) {
    printf("Доступные языки:\n");
    for (int i = 0; i < LANG_COUNT; i++) {
        printf("  %-6s — %s\n", templates[i].name, templates[i].ext);
    }
}
