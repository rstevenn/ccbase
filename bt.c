#define CCB_BUILD_IMPL
//#define CCB_BUILD_DBG
#include "utils/build_tool.h"

 
int main(int argc, char* argv[]) {
    ccb_bt_auto_rebuild(argv[0], __FILE__);

    ccb_bt_mkdir("tmp");
    
    // test mem
    char path[1024] = "\0";
 
    ccb_bt_cmd("gcc tests/test_mem.c -o tmp/test_mem.exe");
    ccb_bt_concat_path(path, ".", "tmp");
    ccb_bt_concat_path(path, "", "test_mem.exe");
    ccb_bt_cmd(path);

    // test trace
    path[0] = '\0';
 
    ccb_bt_cmd("gcc tests/test_trace.c -o tmp/test_trace.exe");
    ccb_bt_concat_path(path, ".", "tmp");
    ccb_bt_concat_path(path, "", "test_trace.exe");
    ccb_bt_cmd(path);

    // test bake

    ccb_bt_cmd("gcc utils/compile_bake.c tests/test2_impl.c -o tmp/bake.exe");
    
    path[0] = '\0';
    ccb_bt_concat_path(path, ".", "tmp");
    ccb_bt_concat_path(path, "", "bake.exe");
    ccb_bt_cmd(path);
    
    
    ccb_bt_cmd("gcc baked.c tests/test2.c -o tmp/test2.exe");
    
    path[0] = '\0';
    ccb_bt_concat_path(path, ".", "tmp");
    ccb_bt_concat_path(path, "", "bake.exe");
    ccb_bt_cmd(path);


    // clean
    ccb_bt_rm("baked.c");
    ccb_bt_rmdir("tmp");

    return 0;
}