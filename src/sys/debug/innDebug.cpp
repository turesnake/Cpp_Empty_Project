/*
 * ======================= innDebug.cpp ==========================
 *                                        CREATE --
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 * POOR DEBUG SYSTEM
 */
#include "pch.h"
#include "innDebug.h"

// 临时版 ...
// 避免在项目的其他位置 include iostream
// 也可替换为 spdlog
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::flush;
using std::string;

namespace debug {//---------- namespace: debug --------------//

void tmp_console_inn( const std::string &str_ ){
    // 可被替换为 spdlog 版实现
    cout << str_ << endl;
}

}//-------------------- namespace: debug end --------------//

