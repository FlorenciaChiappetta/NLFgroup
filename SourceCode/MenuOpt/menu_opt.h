typedef struct {
    int value;
    char label[];
} menu_opt;

menu_opt *new_menu_opt(const char label[], int value);