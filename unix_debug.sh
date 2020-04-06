#!/bin/bash

#------------- prepare dirs ---------------
# 将 根目录下的一些 资料目录（比如 "shaders","jsons" ）
# 复制进 <root>/build/publish/ 目录下

DIR_base="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR_out=${DIR_base}/build/publish/

DIR_src_shaders=${DIR_base}/shaders/
DIR_src_jsons=${DIR_base}/jsons/


DIR_dst_shaders=${DIR_out}/shaders/
DIR_dst_jsons=${DIR_out}/jsons/


echo -e "------------"
echo -e "DIR_base: ${DIR_base} "
echo -e "DIR_out: ${DIR_out} "
echo -e "------------"


if [ ! -d "${DIR_out}" ]; then
    mkdir -p ${DIR_out}
fi

if [ ! -d "${DIR_dst_shaders}" ]; then
    mkdir -p ${DIR_dst_shaders}
fi

if [ ! -d "${DIR_dst_jsons}" ]; then
    mkdir -p ${DIR_dst_jsons}
fi


# Access Permission
chmod -R ug=rwx ${DIR_out}

#-----------------------#
# cp -R "dir1"/. "dir2" 
# copy files in "dir1", not copy "dir1" self 
#:
cp -R ${DIR_src_shaders}.   ${DIR_dst_shaders} 
cp -R ${DIR_src_jsons}.     ${DIR_dst_jsons} 

#------------- build cpp/c# ----------------
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# 多线程加速编译，可自行改写线程数，比如：-j8
make -j4
cd ..

