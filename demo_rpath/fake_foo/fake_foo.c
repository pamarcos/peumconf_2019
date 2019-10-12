#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LOG(...) fprintf(stdout, __VA_ARGS__)

void read_secret()
{
    FILE* file = fopen("secret", "r");
    if (!file) {
        LOG("Error opening secret file\n");
    } else {
        char c;
        LOG("secret file content: ");
        while ((c = getc(file)) != EOF)
            LOG("%c", c);

        LOG("\n");
        fclose(file);
    }
}

__attribute__((constructor)) void loaded()
{
    LOG("\n=== fake_foo shared lib loaded ===\n");
    read_secret();
}

__attribute__((destructor)) void unloaded()
{
    LOG("\n=== fake_foo shared lib unloaded ===\n");
}
