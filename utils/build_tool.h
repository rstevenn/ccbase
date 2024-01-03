#ifndef __CCB_BUILD_TOOL_H__
#define __CCB_BUILD_TOOL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ccb_bt_cmd(const char* cmd);
int ccb_bt_auto_rebuild(const char *old, const char* to_compile);

// file mangement
int ccb_bt_file_exists(const char *filename);
int ccb_bt_rm(const char *filename);
int ccb_bt_mv(const char *dest, const char *src);

int ccb_bt_mkdir(const char *dirname);
int ccb_bt_rmdir(const char *dirname);

char* ccb_bt_concat_path(char* dest, const char* a, const char* b);

#define CCB_BUILD_IMPL
#ifdef CCB_BUILD_IMPL
#include <sys/stat.h>


#ifdef __unix__                             /* __unix__ is usually defined by compilers targeting Unix systems */

int ccb_bt_cmd(const char* cmd) {
#ifdef CCB_BUILD_DBG
    printf("[DBUG]: exec: %s\n", cmd);
#endif
    char exec[1024] = "\0";
    
    strcat(exec, "/bin/sh -c \"");
    strcat(exec, cmd);
    strcat(exec, "\"");
    
    return system(exec);
}

int ccb_bt_rmdir(const char *dirname) {
    if (!ccb_bt_file_exists(dirname)) {
        printf("[INFO]: the dir (%s) don't exist\n", dirname);
    } else {
        char cmd[1024] = "\0";
        strcat(cmd, "rm -rf \"");
        strcat(cmd, dirname);
        strcat(cmd, "\"");
    
        return ccb_bt_cmd(cmd);
    }
    return 1;
}

int ccb_bt_rm(const char *filename) {
    if (!ccb_bt_file_exists(filename)) {
        printf("[INFO]: the file (%s) don't exist\n", filename);
    } else {
        char cmd[1024] = "\0";
        strcat(cmd, "rm \"");
        strcat(cmd, filename);
        strcat(cmd, "\"");
        return ccb_bt_cmd(cmd);
    }
    return 1;
}

int ccb_bt_mv(const char *dest, const char *src) {
    char cmd[1024] = "\0";
    strcat(cmd, "mv \"");
    strcat(cmd, src);  strcat(cmd, "\" \"");
    strcat(cmd, dest); strcat(cmd, "\" ");

    return ccb_bt_cmd(cmd);
}

char* ccb_bt_concat_path(char* dest, const char* a, const char* b){
    strcat(dest, a);
    strcat(dest, "/");
    strcat(dest, b);
    return dest;
}

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

int ccb_bt_cmd(const char* cmd) {
#ifdef CCB_BUILD_DBG
    printf("[DBUG]: exec: %s\n", cmd);
#endif
    char exec[1024] = "\0";
    strcat(exec, "cmd.exe /c \"");
    strcat(exec, cmd);
    strcat(exec, "\"");
    
    return system(exec);
}

int ccb_bt_rmdir(const char *dirname) {
    int out = 1;
    if (!ccb_bt_file_exists(dirname)) {
        printf("[INFO]: the dir (%s) don't exist\n", dirname);
    } else {
        char cmd[1024] = "\0";
        strcat(cmd, "del /s /q \"");
        strcat(cmd, dirname);
        strcat(cmd, "\"");
        out &= ccb_bt_cmd(cmd);

        cmd[0] = '\0';
        strcat(cmd, "rmdir /s /q \"");
        strcat(cmd, dirname);
        strcat(cmd, "\"");
        out |= ccb_bt_cmd(cmd);
    }
    return out;
}

int ccb_bt_rm(const char *filename) {
    if (!ccb_bt_file_exists(filename)) {
        printf("[INFO]: the file (%s) don't exist\n", filename);
    } else {
        char cmd[1024] = "\0";
        strcat(cmd, "del /f \"");
        strcat(cmd, filename);
        strcat(cmd, "\"");
        return ccb_bt_cmd(cmd);
    }
    return 1;
}

int ccb_bt_mv(const char *dest, const char *src) {
    char cmd[1024] = "\0";
    strcat(cmd, "move \"");
    strcat(cmd, src);  strcat(cmd, "\" \"");
    strcat(cmd, dest); strcat(cmd, "\" ");

    return ccb_bt_cmd(cmd);
}

char* ccb_bt_concat_path(char* dest, const char* a, const char* b){
    strcat(dest, a);
    strcat(dest, "\\");
    strcat(dest, b);
    return dest;
}

#endif

int ccb_bt_file_exists(const char *filename)
{
    struct stat buffer;
    return stat(filename, &buffer) == 0 ? 1 : 0;
}

int ccb_bt_mkdir(const char *dirname) {
    if (ccb_bt_file_exists(dirname)) {
        printf("[INFO]: the dir (%s) already exist\n", dirname);
    } else {
        char cmd[1024] = "\0";
        strcat(cmd, "mkdir \"");
        strcat(cmd, dirname);
        strcat(cmd, "\"");
    
        return ccb_bt_cmd(cmd);
    }
    return 1;
}


int ccb_bt_auto_rebuild(const char *old, const char* to_compile) {
    struct stat src_attr;
    struct stat exe_attr;
    stat(to_compile, &src_attr);
    stat(old, &exe_attr);
    
    if (src_attr.st_mtime < exe_attr.st_mtime) {
        return 1;
    }

    printf("[INFO]: change detected, rebuild...\n");
    char old_tmp[1024] = "\0";
    strcat(old_tmp, old);
    strcat(old_tmp, ".old");
    ccb_bt_mv(old_tmp, old);

    char cmd[1024] = "\0";
    cmd[0] = '\0';
    strcat(cmd, "gcc \"");
    strcat(cmd, to_compile); strcat(cmd, "\" -o \"");
    strcat(cmd, old); strcat(cmd, "\"");

    if (ccb_bt_cmd(cmd) == 0) {
        ccb_bt_rm(old_tmp);
    } else {
        printf("[EROR]: failed to rebuild the build tool\n");
        ccb_bt_mv(old, old_tmp);
        exit(1);
    }
    exit(ccb_bt_cmd(old));
}




#endif //  CCB_BUILD_IMPL 
#endif // __CCB_BUILD_TOOL_H__
