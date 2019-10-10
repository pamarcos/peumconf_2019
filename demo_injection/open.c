#define _GNU_SOURCE
#define __STDC_WANT_LIB_EXT1__ 1

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <libgen.h>

typedef int (*orig_open_ptr)(const char *pathname, int flags);
orig_open_ptr orig_open = NULL;

#define LOG(...) fprintf(stdout, "open.c: " __VA_ARGS__)

#define FILENAME_SIZE 256

// Initialize file paths to absolute path of this file.
// This will be replaced afterwards via replace_filepath_with_name.
// This simple mechanism should be enough for this to work
// independently on the directory this repo is
char juanjo[FILENAME_SIZE] = __FILE__;
char alex[FILENAME_SIZE] = __FILE__;
char infogon[FILENAME_SIZE] = __FILE__;
char pablo[FILENAME_SIZE] = __FILE__;

void replace_filepath_with_name(char* filepath, const char* name)
{
    char* dir = strrchr(filepath, '/');
    assert(dir != NULL);
    strncpy(dir+1, name, strlen(name));
    LOG("Loading filepath for %s: %s\n", name, filepath);
}

void populate_file_table()
{
    assert(strlen(__FILE__) < FILENAME_SIZE);
    replace_filepath_with_name(juanjo, "replace/juanjo.png");
    replace_filepath_with_name(alex, "replace/alex.png");
    replace_filepath_with_name(infogon, "replace/infogon.png");
    replace_filepath_with_name(pablo, "replace/pablo.png");
}

__attribute__((constructor)) void loaded()
{
    LOG("\n=== open shared lib loaded ===\n");

    orig_open = dlsym(RTLD_NEXT, "open");
    if (!orig_open)
        LOG("Error getting open symbol: %s\n", dlerror());
    populate_file_table();
}

__attribute__((destructor)) void unloaded()
{
    LOG("\n=== open shared lib unloaded ===\n");
}

int open(const char* pathname, int flags, ...)
{
    if (!orig_open)
        return -1;

    if (strstr(pathname, ".jpg") || strstr(pathname, ".jpeg") || strstr(pathname, ".png")) {
        const char* new_pathname = NULL;
        if (strstr(pathname, "juanjo")) {
            new_pathname = juanjo;
        } else if (strstr(pathname, "alex")) {
            new_pathname = alex;
        } else if (strstr(pathname, "infogon")) {
            new_pathname = infogon;
        } else if (strstr(pathname, "pablo")) {
            new_pathname = pablo;
        }

        if (new_pathname != NULL && new_pathname != pathname) {
            LOG("Replacing %s with %s\n", pathname, new_pathname);
            pathname = new_pathname;
        }
    }

    return orig_open(pathname, flags);
}
