/*
 * ========================= main.cpp ==========================
 *                          -- tpr --
 *                                        CREATE -- 2018.11.21
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#include "pch.h"

//-------------------- Main --------------------//
#include "A.h"
#include "SysConfig.h" // 此文件由 cmake 自己生成，并不在 src/ 目录中


int main( int argc, char* argv[] ){

    
    //===== debug::log 示例：
    debug::log(
        "\n\n" \
        " This is a Empty project. \n" \
        " print some vals:\n" \
        "    int    = {0}\n" \
        "    double = {1}\n" \
        "    str    = {2}\n",
        77, 
        0.134, 
        std::string{"koko"}
    );



    //======= 检查当前所处的 操作系统：
    #if defined TPR_OS_MACOSX_
        debug::log( "\n___OS_MACOSX___\n\n" );
    #elif defined TPR_OS_LINUX_
        debug::log( "\n___OS_LINUX___\n\n" );
    #elif defined TPR_OS_WIN32_
        debug::log( "\n___OS_WIN32___\n\n" );
    #endif 



    return(0);
}


