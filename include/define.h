//
// Created by Cookie on 2017/11/25.
//

#ifndef CPPGRAMMER_DEFINE_H
#define CPPGRAMMER_DEFINE_H

#include <cstdlib>
//#include <map>
//#include <string>

#define VERSION 2017-11-25

///----------------------------------------------------------------------------------------------------------------------
/// Debug mode enable.
//#define DEBUG_


///----------------------------------------------------------------------------------------------------------------------
/// global typedef
//typedef std::map<std::string, std::string> Config;

///----------------------------------------------------------------------------------------------------------------------
/// global static variable.
//const int kConfigMemDepth = 32;
//const int kPERegFileDepth = 16;
//const int kSMBankNum = 16;
//const int kSMBankIndexWidth = 4;
//const int kSMBankDepth = 256;
//const int kSMBankAddrWidth = 8; // log2(kSMBankDepth)
//const int kUninitialized32Bit = 0xDEADBEAF;
//const int kUninitialized1Bit = 0;
//const int kPENumberHorizontal = 4;
//const int kPENumberVertical = 4;
//const int kPENumberTotal = kPENumberHorizontal * kPENumberVertical;
//const int kGlobalRegNum = 16;

///----------------------------------------------------------------------------------------------------------------------
/// global variable, which can be change by one and another.
extern int global_var;


///----------------------------------------------------------------------------------------------------------------------
/// global define function
// torus style routing
#define ROUTER(index,x,y) ((index/kPENumberHorizontal+kPENumberVertical-(y))%kPENumberVertical*kPENumberHorizontal+(index%kPENumberHorizontal+kPENumberHorizontal+(x))%kPENumberHorizontal)

///----------------------------------------------------------------------------------------------------------------------
/// global function
template<typename T>
inline T maxValue(T in1, T in2){
    return (in1 > in2) ? in1 : in2;
}

///----------------------------------------------------------------------------------------------------------------------
/// data type define.
#if 1      // the C99 format
    /// 不管32位还是64位，都是固定字节数
    typedef int8_t char8;       // 1 bytes int/char  -2^7~2^7-1
    typedef uint8_t uchar8;

    typedef int16_t int16;      // <==> short int
    typedef uint16_t uint16;    // 2 bytes int

    typedef int32_t int32;      // 4 bytes int
    typedef uint32_t uint32;

    typedef int64_t int64;      // 8 bytes int  <===>long int, if in 32bit machine,long long int
    typedef uint64_t uint64;

    #if __WORDSIZE == 64
    //typedef long int   int64_t; // 64 位机器就用这个
    //#else
    //__extension__
    //        typedef long long int      int64_t;
    #endif

    /// Optional,字长由机器来定
    #if __WORDSIZE == 64
    typedef long int                intptr_t;   // 64 位机器 8字节
    #else
    typedef int                        intptr_t; // 32 位机器 4字节
    #endif

    //    另外还有ssize_t和size_t分别是sign size_t和unsigned signed size of computer word size。它们也是表示计算机的字长，
    //    在32位机器上是int型，在64位机器上long型，从某种意义上来说它们等同于intptr_t和 uintptr_t。
    //    它们在stddef.h里面定义。需要注意的是socket的accept函数在有些操作系统上使用size_t是不正确的，
    //    因为 accept接收的int*类型，而size_t可能是long int 类型。后来BSD使用sock_t来替代它。


#elif 0   // the BSD format
    typedef int32_t int32;
    typedef u_int32_t uint32;
    typedef int64_t int64;
    typedef u_int64_t uint64;
#elif 0     // the windows (vc7) format
    typedef __int32 int32;
    typedef unsigned __int32 uint32;
    typedef __int64 int64;
    typedef unsigned __int64 uint64;
#else
    #error Do not know how to define a 32-bit integer quantity on your system
#endif

///----------------------------------------------------------------------------------------------------------------------
/// global identifier:Numberbase
enum NumberBase{
    // indicate which number representation (10=decimal, 2=binary, 16=hexadecimal) is the user interface
    kBinary = 2,
    kOctonary = 8,
    kDecimal = 10,
    kHexidecimal = 16,

};


///----------------------------------------------------------------------------------------------------------------------
/// global identifier:ErrorType


enum ErrorType
{
    kReservoirUninitialized = -1,
    kReservoirCrossBoundary = -2,
};


///----------------------------------------------------------------------------------------------------------------------
/// not allowed operation
//namespace ReSim
//{
//// disallow copy and operator=
//#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
//            TypeName(const TypeName&); \
//            void operator=(const TypeName&)
//}




#endif //CPPGRAMMER_DEFINE_H
