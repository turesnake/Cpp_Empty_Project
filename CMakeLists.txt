#===================================================#
#           CMakeLists.txt -- rootFolder
#===================================================#

# 变量解释
# PROJECT_BINARY_DIR       --- cmake 编译所在的目录 path
# CMAKE_CURRENT_SOURCE_DIR --- current CMakeLists.txt path

#---------------------------------------------------#
#                cmake version
#---------------------------------------------------#
cmake_minimum_required(VERSION 3.1)
message( STATUS "cmake: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" )


#---------------------------------------------------#
#                    OS
#---------------------------------------------------#
if( APPLE )
    option( TPR_OS_MACOSX_ " MACOSX " ON )
    option( TPR_OS_UNIX_ " UNIX " ON )
    message( STATUS "___APPLE___" )

elseif( UNIX AND NOT APPLE )
    option( TPR_OS_LINUX_ " LINUX " ON )
    option( TPR_OS_UNIX_ " UNIX " ON )
    message( STATUS "___UNIX___" )

#-- 当使用 Virsual Studio 编译 cmake项目时，可用 WIN32
#   如果出错，尝试改用 MSVC
elseif( WIN32 )
    option( TPR_OS_WIN32_ " WIN32 " ON )
    message( STATUS "___WIN32___" )

endif( APPLE )
#---- Must before project!!! ----


#-- c++17
set (CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)


#---------------------------------------------------#
#                project name
#---------------------------------------------------#
project ( cppEmptyProject )


#-- *** test: 0.1 ***
set ( VERSION_MAJOR 0 )
set ( VERSION_MINOR 1 )


#---------------------------------------------------#
#                   build/publish/
#---------------------------------------------------#
#-- change finally exe out-path: build/publish
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/publish)


#---------------------------------------------------#
#                 SySconfig
#             暂未添加用途，测试用
#---------------------------------------------------#
#-- 配置 一个 h文件，用来 从 cmake 传递一些 变量 到 源文件 中。
#-- 我们需要手动编写 .h.in 文件。
#-- 然后，cmake调用会 帮我们自动生成对应的 h文件。
#-- 最后，正式 make编译时。源文件 就能 include 这些生成的 h文件。
option( SWITCH_1
    " option test: switch 1 " ON )
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sysconfig/SysConfig.h.in"
    "${EXECUTABLE_OUTPUT_PATH}/sysconfig/SysConfig.h"
)


#---------------------------------------------------#
#                     src
#---------------------------------------------------#
#-- 创建变量 PIXEL_FILES （是个 list）
#-- 包含 主进程需要的所有 cpp 文件
#   GLOB_RECURSE 会递归访问目录，是一种粗粒度的写法
#   如果想要精细控制，应该在部分目录 该用 GLOB 
#   请把所有 .cpp 文件写入 src 目录，然后就不用管了
FILE(GLOB_RECURSE PIXEL_FILES   
                        src/*.cpp
                        )

#---------------------------------------------------#
#                   emptyApp
#---------------------------------------------------#

if( ${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.16 )
    set ( CMAKE_UNITY_BUILD_BATCH_SIZE 16 ) # 10 ～ 20
endif()


add_executable( emptyApp ${PIXEL_FILES} )


#-- set libs/dlls output-name --> "emptyApp.xxx"
set_target_properties(emptyApp PROPERTIES PREFIX "")
set_target_properties(emptyApp PROPERTIES OUTPUT_NAME "emptyApp")


if( ${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.16 )
    target_precompile_headers( emptyApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/_pch_/pch.h ) # PCH
    set_target_properties( emptyApp PROPERTIES UNITY_BUILD ON) # UNITY
endif()


#---------------------------------------------------#
#                   include
#---------------------------------------------------#
# 很粗鲁的写法
# 每新增一个 include 目录，就要手动添加进这个列表中
target_include_directories ( emptyApp PUBLIC

    # === 第三方库 ===
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/rapidjson
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/fmt-6.1.2/include

    # === 项目代码 ===
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/_pch_

    ${CMAKE_CURRENT_SOURCE_DIR}/src/main
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debug
    ${CMAKE_CURRENT_SOURCE_DIR}/src/classA
    # 请在此处 添加更多需要 include 的目录
    # ...
    

    ${EXECUTABLE_OUTPUT_PATH}/sysconfig # vals from camke file
    )


#-- 防止 第三方库h文件 报 warnings --
target_include_directories ( emptyApp SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/deps
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm.9.9.5
    )


#---------------------------------------------------#
#             子目录 CMakeLists.txt
#---------------------------------------------------#
#-- 子 CMakeLists.txt 执行的 中间产物，将分别放在 
#      build/src  build/libhello  目录中。
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/fmt-6.1.2 EXCLUDE_FROM_ALL)


#---------------------------------------------------#
#             target_link_libraries
#---------------------------------------------------#
if ( UNIX )
    target_link_libraries( emptyApp 
                            fmt
                            )

else()
    target_link_libraries( emptyApp
                            fmt
                            )
endif( UNIX )


# 编译选项，可以自行增删
target_compile_options( emptyApp
                        PRIVATE 
                        -Wall -Wextra
                        -Wno-c++98-compat
                        -Wno-c++98-compat-pedantic
                        -Wno-language-extension-token      #- glad
						-Wno-nonportable-system-include-path
						-Wno-reserved-id-macro
						-Wno-global-constructors            #++ need ++
                        -Wno-exit-time-destructors          #++ need ++
                        -Wno-covered-switch-default         #++ need ++
                        -Wno-switch-enum                    #++ need ++
                        -Wno-unused-parameter               #++ need ++
                        -Wno-unused-member-function         #++ need ++
                        -Wno-missing-variable-declarations  #++ need ++
                        -Wno-missing-prototypes

                        -Wno-old-style-cast   #---- tmp ---- 
                        -Wno-unused-variable #----- tmp ----
                        -Wno-unused-private-field #----- tmp ----

                        )


#=========== 优化设置（非正式） ============
# 不喜欢这组设置，可以将它彻底删除掉
# 整体上只做了一次改动：
#   release 模式，仍然允许 assert 宏起效

#-------- UNIX ----------
if( UNIX )
    set ( CMAKE_C_FLAGS                  "-O0"              CACHE STRING "regular mode: no optimize" FORCE )
    set ( CMAKE_C_FLAGS_DEBUG            "-O0 -g"           CACHE STRING "debug mode: no optimize" FORCE )
    set ( CMAKE_C_FLAGS_MINSIZEREL       "-O0 -DNDEBUG"     CACHE STRING "minSizeRel mode: no optimize" FORCE )
    set ( CMAKE_C_FLAGS_RELEASE          "-O2 -DNDEBUG"     CACHE STRING "release mode: no optimize" FORCE )
    set ( CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g -DNDEBUG"  CACHE STRING "relWithDebugInfo mode: no optimize" FORCE )

    set ( CMAKE_CXX_FLAGS                 "-O0"             CACHE STRING "regular mode: no optimize" FORCE )
    set ( CMAKE_CXX_FLAGS_DEBUG           "-O0 -g"          CACHE STRING "debug mode: no optimize" FORCE )
    set ( CMAKE_CXX_FLAGS_MINSIZEREL      "-O0 -DNDEBUG"    CACHE STRING "minSizeRel mode: no optimize" FORCE )
    set ( CMAKE_CXX_FLAGS_RELEASE         "-O2 -DNDEBUG"    CACHE STRING "release mode: no optimize" FORCE )
    set ( CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG" CACHE STRING "relWithDebugInfo mode: no optimize" FORCE )

#-------- WIN ----------
else()
    # do not have CMAKE_C_FLAGS;
    set ( CMAKE_C_FLAGS_DEBUG            "/MDd /Zi /Ob0 /Od /RTC1"   CACHE STRING "debug mode: no optimize" FORCE )
    set ( CMAKE_C_FLAGS_MINSIZEREL       "/MD /O0 /Ob1 /DNDEBUG"     CACHE STRING "minSizeRel mode: no optimize" FORCE )
    set ( CMAKE_C_FLAGS_RELEASE          "/MD /O2 /Ob1 /DNDEBUG"     CACHE STRING "release mode: no optimize" FORCE )
    set ( CMAKE_C_FLAGS_RELWITHDEBINFO   "/MD /Zi /O2 /Ob1 /DNDEBUG" CACHE STRING "relWithDebugInfo mode: no optimize" FORCE )

    # do not have CMAKE_CXX_FLAGS;
    set ( CMAKE_CXX_FLAGS_DEBUG            "/MDd /Zi /Ob0 /Od /RTC1"   CACHE STRING "debug mode: no optimize" FORCE )
    set ( CMAKE_CXX_FLAGS_MINSIZEREL       "/MD /O0 /Ob1 /DNDEBUG"     CACHE STRING "minSizeRel mode: no optimize" FORCE )
    set ( CMAKE_CXX_FLAGS_RELEASE          "/MD /O2 /Ob1 /DNDEBUG"     CACHE STRING "release mode: no optimize" FORCE )
    set ( CMAKE_CXX_FLAGS_RELWITHDEBINFO   "/MD /Zi /O2 /Ob1 /DNDEBUG" CACHE STRING "relWithDebugInfo mode: no optimize" FORCE )


endif( UNIX )




