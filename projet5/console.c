#include "console.h"
#include <stdio.h>
#include <stdlib.h>

void print_header(const char* text) {
    printf("\n" COLOR_BOLD COLOR_CYAN);
    print_separator();
    printf("  %s\n", text);
    print_separator();
    printf(COLOR_RESET);
}

void print_success(const char* text) {
    printf(COLOR_GREEN "✓ %s" COLOR_RESET "\n", text);
}

void print_error(const char* text) {
    printf(COLOR_RED "✗ %s" COLOR_RESET "\n", text);
}

void print_info(const char* text) {
    printf(COLOR_BLUE "ℹ %s" COLOR_RESET "\n", text);
}

void print_warning(const char* text) {
    printf(COLOR_YELLOW "⚠ %s" COLOR_RESET "\n", text);
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void print_separator() {
    printf("═══════════════════════════════════════\n");
}
