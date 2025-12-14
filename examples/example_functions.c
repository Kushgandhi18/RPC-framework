#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* hello(const char* name) {
    if (name == NULL) {
        name = "Guest";
    }
    
    char *result = malloc(256);
    if (result == NULL) {
        return NULL;
    }
    
    snprintf(result, 256, "Hello, %s! Welcome to Mini RPC Framework.", name);
    return result;
}

char* echo(const char* input) {
    if (input == NULL) {
        return strdup("NULL");
    }
    
    return strdup(input);
}

char* reverse(const char* input) {
    if (input == NULL) {
        return strdup("NULL");
    }
    
    int len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < len; i++) {
        result[i] = input[len - 1 - i];
    }
    result[len] = '\0';
    
    return result;
}

char* uppercase(const char* input) {
    if (input == NULL) {
        return strdup("NULL");
    }
    
    int len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < len; i++) {
        result[i] = toupper(input[i]);
    }
    result[len] = '\0';
    
    return result;
}

char* add(const char* params) {
    if (params == NULL) {
        return strdup("Error: NULL parameters");
    }
    
    int a = 0, b = 0;
    if (sscanf(params, "%d,%d", &a, &b) != 2) {
        return strdup("Error: Invalid format. Expected: num1,num2");
    }
    
    char *result = malloc(64);
    if (result == NULL) {
        return NULL;
    }
    
    snprintf(result, 64, "%d", a + b);
    return result;
}