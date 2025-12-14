#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Example RPC-callable functions
 * Each function returns a heap-allocated string.
 * The RPC server is responsible for freeing it.
 */

char* hello(const char *name)
{
    const char *who = name ? name : "world";
    char *result = malloc(64);
    snprintf(result, 64, "Hello, %s!", who);
    return result;
}

char* echo(const char *msg)
{
    if (!msg) return NULL;
    return strdup(msg);
}

char* reverse(const char *msg)
{
    if (!msg) return NULL;

    size_t len = strlen(msg);
    char *out = malloc(len + 1);

    for (size_t i = 0; i < len; i++)
        out[i] = msg[len - 1 - i];

    out[len] = '\0';
    return out;
}

char* uppercase(const char *msg)
{
    if (!msg) return NULL;

    char *out = strdup(msg);
    for (size_t i = 0; out[i]; i++)
        out[i] = toupper((unsigned char)out[i]);

    return out;
}

