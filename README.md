# jcodegen 🐕

**jcodegen** — генератор технически рабочего, но бесполезного кода на 9 языках.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Version](https://img.shields.io/badge/version-v0.1-green)](https://github.com/Wingo12/jcodegen/releases/tag/v0.1)

---

## ⚠️ DISCLAIMER / ДИСКЛЕЙМЕР

> **Автор не несёт ответственности за любые последствия использования программы и сгенерированного кода.**
>
> Полный текст отказа от ответственности: [DISCLAIMER](DISCLAIMER)

---

## 🚀 Установка
``` bash
    git clone https://github.com/Wingo12/jcodegen.git
    cd jcodegen
    make
    sudo make install
```
---

## 🎯 Использование

    jcodegen [ОПЦИИ]

| Опция | Описание |
|-------|----------|
| `-l <lang>` | Язык (c, cpp, py, go, js, java, html, asm, bash) |
| `-n <lines>` | Количество строк (по умолч. 30) |
| `-o <file>` | Выходной файл (по умолч. stdout) |
| `-c` | Добавить комментарии |
| `--seed <int>` | Seed для воспроизводимости |
| `--depth <int>` | Максимальная вложенность (по умолч. 3) |
| `-v` | Подробный вывод |
| `-h` | Помощь |

---

## 🔥 Примеры
```
    # C
    jcodegen -l c -n 50 -o junk.c
    gcc junk.c -o junk
    ./junk
```
```
    # Python
    jcodegen -l py -n 20 -o junk.py
    python3 junk.py
```
```
    # JavaScript
    jcodegen -l js -n 30 -o junk.js
    node junk.js
```
```
    # Go
    jcodegen -l go -n 20 -o junk.go
    go run junk.go
```
```
    # Java
    jcodegen -l java -n 20 -o Junk.java
    javac Junk.java
    java Junk
```
```
    # Bash
    jcodegen -l bash -n 20 -o junk.sh
    chmod +x junk.sh
    ./junk.sh
```
```
    # HTML
    jcodegen -l html -n 20 -o junk.html
```
```
    # ASM
    jcodegen -l asm -n 20 -o junk.asm
    nasm -f elf64 junk.asm -o junk.o
    gcc -no-pie junk.o -o junk
    ./junk
```
---

## 📊 Языки

| Код | Язык | Компилируется | Запускается |
|-----|------|---------------|-------------|
| `c` | C | ✅ | ✅ |
| `cpp` | C++ | ✅ | ✅ |
| `py` | Python | ✅ | ✅ |
| `go` | Go | ✅ | ✅ |
| `js` | JavaScript | ✅ | ✅ |
| `java` | Java | ✅ | ✅ |
| `html` | HTML | ✅ | ✅ (браузер) |
| `asm` | Ассемблер | ✅ | ✅ (с gcc -no-pie) |
| `bash` | Bash | ✅ | ✅ |

---

## 🛡️ Правила

- ✅ Код компилируется
- ✅ Код запускается
- ✅ Вывод только из заготовленных фраз (23 шт.)
- ✅ malloc = free
- ✅ new = delete
- ❌ Без удалений файлов
- ❌ Без syscall
- ❌ Без записи в чужую память
- ❌ Без ввода в бесконечных циклах
- ❌ Без `break` вне цикла
- ❌ Без `continue` вне цикла

---

## 📝 Фразы
```
    junk, out, output, hello, im here, credits to wingo,
    idk what im doing, something, quick brown fox jumps over the lazy dog,
    hiiii, junkyard, useful text, lol, Burmalda,
    check out my other projects at github.com/Wingo12,
    im junk programm, im old, fun::fact('C is mad at you'),
    python('easy'), 10 JUNK \n20 SWEET \n30 GOTO 10
```
И пару пасхалок...
---

## 📄 Лицензия

**GNU GPL v3** — см. [LICENSE](LICENSE)

**Отказ от ответственности** — см. [DISCLAIMER](DISCLAIMER)

---

## 👤 Автор

**Wingo123**  
GitHub: [Wingo12](https://github.com/Wingo12)
