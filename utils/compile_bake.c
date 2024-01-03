#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bake.h"

void bake_impl(void* (fnct)(size_t*), char* name, FILE* fp) {
    printf("backing %s...\n", name);

    size_t size;
    char* out = fnct(&size);

    fprintf(fp, "void* %s(size_t* size) {\n", name);
    fprintf(fp, "   size[0] = %lu;\n", size);

    fprintf(fp, "   char data[] = {");
    
    for (size_t i=0; i<size; i++) {
        
        fprintf(fp, "%d, ", out[i] );
    }
    
    fprintf(fp, "};\n");
    fprintf(fp, "   void* out = malloc(%ld);\n", size);
    fprintf(fp, "   memmove(out, data, %ld);\n", size);
    fprintf(fp, "   return out;\n");

    fprintf(fp, "}\n\n");

    free(out);
}

#define BAKETYPEIMPL(func, type) {  printf("backing %s...\n", #func);\
                                    type out = func(); \
                                    fprintf(fp, "%s %s(size_t* size) {\n", #type, #func); \
                                    fprintf(fp, "   char data[] = {"); \
                                    for (size_t i=0; i<sizeof(#type); i++) { \
                                        fprintf(fp, "%d, ", ((char*)&out)[i] ); \
                                    }\
                                    fprintf(fp, "};\n"); \
                                    fprintf(fp, "   return *((%s*)data);\n", #type); \
                                    fprintf(fp, "}\n\n"); \
                                }


#define BAKE_EXISTING_TYPE(type, func)
int bakeint(int (func)(void), char func_name[], FILE* fp) {
    printf("backing %s...\n", func_name);

    fprintf(fp, "int %s(size_t* size) {\n", func_name);
    fprintf(fp, "   return %s();\n", func_name);
    fprintf(fp, "}\n\n");
}



void init_file(FILE* fp) {
    fprintf(fp, "#include <stdlib.h>\n");
    fprintf(fp, "#include <string.h>\n\n");
}


int main() {
    FILE* fp = fopen("baked.c", "w");
    init_file(fp);

// macro magic
#define BAKE(func) bake_impl(func, #func, fp);
#define BAKETYPE(func, type) BAKETYPEIMPL(func, type)

#define BAKEINT(func) bakeint(func, #func, fp);
#define BAKELONG(func)
#define BAKELONGLONG(func)

#define BAKEFLOAT(func)
#define BAKELONGFLOAT(func)
#define BAKEDOUBLE(func)
#define BAKELONGDOUBLE(func)

#define BAKECHAR(func)


    Functions()


    fclose(fp);

    return 1;
}