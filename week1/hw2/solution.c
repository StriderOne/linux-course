#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

int (*math_func)(const int);

bool init_library(const char* lib_name, const char* func_name) {
    void *hdl = dlopen(lib_name, RTLD_LAZY);
    if (NULL == hdl)
        return false;
    
    math_func = (int (*)(const int))dlsym(hdl, func_name);

    if (NULL == math_func)
        return false;
    
    return true;
}

int main(int argc, char* argv[]) {
    // for (int i = 0; i < argc; i++) {
    //     printf("%s\n", argv[i]);
    // }
    if (init_library(argv[1], argv[2])) {
        int ans = math_func(atoi(argv[3]));
        printf("%d\n", ans);
    } else 
        printf("Library was not loaded\n");

    return 0;
}