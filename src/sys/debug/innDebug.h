/*
 * ======================== innDebug.h ==========================
 *                                        CREATE --
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *  POOR DEBUG SYSTEM
 */
#ifndef EMPTY_INN_DEBUG_H
#define EMPTY_INN_DEBUG_H


#include <string>
#include "fmt/format.h"


namespace debug {//---------- namespace: debug --------------//

// 请勿直接调用此函数
void tmp_console_inn( const std::string &str_ );


// 将格式化字符串 打印到终端：
// debug::log( "val AAA = {}", AAA );
template < typename S, typename... Args >
void log(const S& format_str, Args&&... args) {
    // 简单的套娃...
    auto str = fmt::format( format_str, args... );
    tmp_console_inn( str );
}


}//-------------------- namespace: debug end --------------//
#endif 

