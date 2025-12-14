#ifndef DL_HANDLER_H
#define DL_HANDLER_H

struct Registery {
    const char *name;
    void *function;
    struct Registery *next;
};

struct RegisteryList {
    struct Registery *head;
    struct Registery *tail;
};

/* API */
int function_table_init(const char *lib_path);
int add_function(const char *func_name);
void *get_function(char *s_name);
void destroy_registery(void);

#endif
