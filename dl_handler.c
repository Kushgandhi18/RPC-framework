#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

void *dl_handler = NULL;
struct RegisteryList *funcs = NULL;

//if you want to create an empty registry node both name and func have to empty 
struct Registery *create_registery_node(const char *n, void *f){
    if(!((n == NULL && f == NULL) || (n != NULL && f != NULL))){
        printf("Error function name and function pointer must either not null or both null\n");
        return NULL;
    }
    struct Registery *ret_item = malloc(sizeof(struct Registery));
    if(ret_item == NULL){
        printf("Error unable to allocate memory to create a new entry in the funcs list\n");
        return NULL;
    }

    if(n != NULL && f != NULL){
        ret_item->name = n;
        ret_item->function = f;
    }else{
        ret_item->name = NULL;
        ret_item->function = NULL;
    }

    ret_item->next = NULL;
    return ret_item;
}

struct RegisteryList *create_function_registery(struct Registery *head){
    struct RegisteryList *ret_item = malloc(sizeof(struct RegisteryList));
     if(funcs = NULL){
        printf("Error unable to allocate new memory to create function registry list\n");
        return NULL;
    }
    ret_item->head = ret_item->tail = head;
    return ret_item;
}


int function_table_init(const char *lib_path){
    if(dl_handler != NULL){
        printf("Warning dl_handler no null clearing it\n");
        dlclose(dl_handler);
    }

    dl_handler = dlopen(lib_path, RTLD_NOW);

    if(dl_handler == NULL){
        printf("Error failed to open %s\n", lib_path);
        printf("%s\n", dlerror());
        return -1;
    }

    return 0;
}

int add_function(const char *func_name){
    if(dl_handler == NULL){
        printf("Error please call the init function first!\n");
        return -1;
    }
    
    if(func_name == NULL){
        printf("Error function look up name is null\n");
        return -1;
    }

    void *look_up_func = dlsym(dl_handler, func_name);
    if(look_up_func == NULL){
        printf("Error can not find function with name %s\n", func_name);
        return -1;
    }

    if(funcs == NULL){
        struct Registery *new_node = create_registery_node(func_name, look_up_func);

        if(new_node == NULL){
            printf("Error unable create function registry while creating node\n");
            return -1;
        }
        
        funcs = create_function_registery(new_node);
        
        if(funcs == NULL){
            printf("Error unable create function registry\n");
            return -1;
        }

        funcs->head = funcs->tail = new_node;  

    }else{
        struct Registery *new_node = create_registery_node(func_name, look_up_func);

        if(new_node == NULL){
            printf("Error unable to add new function to registery with name %s\n", func_name);
            return -1;
        }

        funcs->tail->next = new_node;
        funcs->tail = new_node;
    }

    return 0;

}

void *get_function(char *s_name){
    if(funcs == NULL){
        printf("Error create function registry first\n");
        return NULL;
    }
    
    if(s_name == NULL){
        printf("Error look up name is null please use valid string\n");
        return NULL;
    }

    struct Registery *cur = funcs->head;

    while(cur != NULL){
        if(!strcmp(cur->name, s_name)){
            return cur->function;
            break;
        }
        cur = cur->next;
    }

    return NULL;
}

void destroy_registery(){
    if(funcs != NULL){
        struct Registery *cur = funcs->head;
        struct Registery *next = funcs->head->next;

        if(next != NULL){
            while(next != NULL){
                //free(cur->name);
                //free(cur->function);
                free(cur);
                cur = next;
                next = cur->next;
            }
        }

        //free(cur->name);
        //free(cur->function);
        free(cur);
        free(funcs);
    }

    if(dl_handler != NULL){
        dlclose(dl_handler);
    }
}