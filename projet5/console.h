#ifndef CONSOLE_H
#define CONSOLE_H

/* Couleurs */
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_BOLD    "\033[1m"

/* Prototypes */
void print_header(const char* text);
void print_success(const char* text);
void print_error(const char* text);
void print_info(const char* text);
void print_warning(const char* text);
void clear_screen();
void print_separator();

#endif
