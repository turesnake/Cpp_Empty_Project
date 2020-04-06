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



int main( int argc, char* argv[] ){

    
    //===== debug::log 示例：
    debug::log(
        "\n\n" \
        " This is a Empty projetc. \n" \
        " print some vals:\n" \
        "    int    = {0}\n" \
        "    double = {1}\n" \
        "    str    = {2}\n\n",
        77, 
        0.134, 
        std::string{"koko"}
    );



    //===== class 示例：
    //A a { 12345 };
    //print_A_data( a );


    return(0);
}


