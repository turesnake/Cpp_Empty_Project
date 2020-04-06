/*
 * =========================== A.h ==========================
 *                                        CREATE --
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#ifndef CLASS_A_H
#define CLASS_A_H

#include "innDebug.h"


// 示例
class A{
public:
    A( int data_ ): data(data_){
        debug::log( "class A: Constructor" );
    }

    ~A(){
        debug::log( "class A: Destructor" );
    }

    inline int get_data()const noexcept{
        return this->data;
    } 

private:
    int data;
};

// 示例
void print_A_data( const A &a_ );

#endif
