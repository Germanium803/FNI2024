#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_SZ 256
#define PATH_SZ 1024

#ifdef _WIN32
    #define SEP "\\"
    #define EXE ".exe"
#else
    #define SEP "/"
    #define EXE ""
#endif

/* ================= UTILIDADES ================= */

void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n-1] == '\n') s[n-1] = '\0';
}

void trim_spaces(char *s) {
    char *start = s;
    while (*start == ' ' || *start == '\t') start++;

    char *end = start + strlen(start);
    while (end > start && (*(end-1) == ' ' || *(end-1) == '\t')) end--;

    *end = '\0';
    memmove(s, start, end - start + 1);
}

/* ================= NORMALIZACIÓN ================= */

void normalize_name(char *name) {
    if (strncmp(name, "src/", 4) == 0 || strncmp(name, "src\\", 4) == 0 ||
        strncmp(name, "bin/", 4) == 0 || strncmp(name, "bin\\", 4) == 0) {
        memmove(name, name + 4, strlen(name) - 3);
    }

    size_t len = strlen(name);

    if (len > 2 && strcmp(name + len - 2, ".c") == 0) {
        name[len - 2] = '\0';
        len -= 2;
    }

    if (len > 4 && strcmp(name + len - 4, ".exe") == 0) {
        name[len - 4] = '\0';
    }
}

/* ================= FILE EXISTS ================= */

int file_exists(const char *path) {
    FILE *f = fopen(path, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

/* ================= LISTADO ================= */

void list_files(const char *dir, const char *filter) {
    char cmd[PATH_SZ];

#ifdef _WIN32
    if (filter)
        snprintf(cmd, sizeof(cmd), "dir /b %s\\*%s", dir, filter);
    else
        snprintf(cmd, sizeof(cmd), "dir /b %s", dir);
#else
    if (filter)
        snprintf(cmd, sizeof(cmd), "ls %s/*%s", dir, filter);
    else
        snprintf(cmd, sizeof(cmd), "ls %s", dir);
#endif

    system(cmd);
}

/* ================= MOSTRAR ARCHIVO ================= */

void show_text_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("No se pudo abrir '%s'\n", path);
        return;
    }

    char line[1024];
    printf("---- %s ----\n\n", path);

    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    fclose(f);

    char buf[INPUT_SZ];
    while (1) {
        printf("\nEscriba 'exit' para volver: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        trim_newline(buf);
        if (strcmp(buf, "exit") == 0) break;
    }
}

/* ================= COMPILAR ================= */

int compile_program(const char *name) {
    char cmd[PATH_SZ];

#ifdef _WIN32
    snprintf(cmd, sizeof(cmd),
        "if not exist bin mkdir bin && gcc -Wall -Wextra -o bin\\%s.exe src\\%s.c",
        name, name);
#else
    snprintf(cmd, sizeof(cmd),
        "mkdir -p bin && gcc -Wall -Wextra -o bin/%s src/%s.c",
        name, name);
#endif

    printf("Compilando...\n");
    return system(cmd);
}

/* ================= EJECUTAR ================= */

void run_program(const char *name) {
    char path[PATH_SZ];

#ifdef _WIN32
    snprintf(path, sizeof(path), "bin\\%s.exe", name);
#else
    snprintf(path, sizeof(path), "bin/%s", name);
#endif

    if (!file_exists(path)) {
        printf("Ejecutable no encontrado. Compilando...\n");

        if (compile_program(name) != 0) {
            printf("Error al compilar\n");
            return;
        }
    }

    char cmd[PATH_SZ];

#ifdef _WIN32
    snprintf(cmd, sizeof(cmd), "%s", path);
#else
   if (snprintf(cmd, sizeof(cmd), "./%s", path) >= sizeof(cmd)) {
    fprintf(stderr, "Error: ruta demasiado larga\n");
    return;
}
#endif

    clock_t start = clock();
    int res = system(cmd);
    clock_t end = clock();

    double ms = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    printf("\nCódigo de salida: %d\n", res);
    printf("Tiempo: %.2f ms\n", ms);
}

/* ================= LÓGICA ================= */

void handle_name(char *name) {
    normalize_name(name);

    char enun[PATH_SZ];
    char src[PATH_SZ];

    snprintf(enun, sizeof(enun), "enunciados%s%s.txt", SEP, name);
    snprintf(src, sizeof(src), "src%s%s.c", SEP, name);

    int has_enun = file_exists(enun);
    int has_src  = file_exists(src);

    if (has_enun && has_src) {
        char op[INPUT_SZ];

        printf("Existe enunciado y código para '%s'\n", name);
        printf("(e) ver enunciado | (r) ejecutar | (v) ver código: ");

        fgets(op, sizeof(op), stdin);
        trim_newline(op);

        if (strcmp(op, "e") == 0)
            show_text_file(enun);
        else if (strcmp(op, "r") == 0)
            run_program(name);
        else if (strcmp(op, "v") == 0)
            show_text_file(src);

        return;
    }

    if (has_enun) {
        show_text_file(enun);
        return;
    }

    if (has_src) {
        char op[INPUT_SZ];

        printf("Código encontrado: %s\n", src);
        printf("(r) ejecutar | (v) ver | (c) compilar: ");

        fgets(op, sizeof(op), stdin);
        trim_newline(op);

        if (strcmp(op, "r") == 0)
            run_program(name);
        else if (strcmp(op, "v") == 0)
            show_text_file(src);
        else if (strcmp(op, "c") == 0)
            compile_program(name);

        return;
    }

    printf("No existe '%s'\n", name);
}
/* ================= MAIN ================= */

int main() {
    char input[INPUT_SZ];

    printf("Resolucionario Portable\n");
    printf("Escribe --help para ayuda\n\n");

    while (1) {
        printf("> ");

        if (!fgets(input, sizeof(input), stdin))
            break;

        trim_newline(input);
        trim_spaces(input);

        if (strlen(input) == 0) continue;

        if (strcmp(input, "--help") == 0) {
            printf("Comandos:\n");
            printf("  ls        -> listar código\n");
            printf("  ls -e     -> enunciados\n");
            printf("  exit      -> salir\n");
        }
        else if (strcmp(input, "ls") == 0) {
            list_files("src", ".c");
        }
        else if (strcmp(input, "ls -e") == 0) {
            list_files("enunciados", ".txt");
        }
        else if (strcmp(input, "exit") == 0) {
            break;
        }
        else {
            handle_name(input);
        }
    }

    printf("Bye\n");
    return 0;
}
