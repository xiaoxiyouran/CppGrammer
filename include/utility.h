//
// Created by Cookie on 2017/11/25.
//

#ifndef CPPGRAMMER_UTILITY_H
#define CPPGRAMMER_UTILITY_H

#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "define.h"

/// converter string("11011")binary to the given base,such as(2,10,16)radix.
namespace converter_BB{
    unsigned long
    string2ulong(std::string src);
    // convert binary string to unsigned integer.
    // i.e. src = "1101", return 1101(binary) = 13(decimal)

    unsigned long
    string2ulong_r(std::string src);
    // reversely convert binary string to unsigned integer.
    // i.e. src = "1101", return 1011(binary) = 11(decimal)

    int
    string2int(std::string src);
    // convert binary string (twos complement) to signed integer.
    // i.e. src = "1101", return 1101(binary) = -3(decimal)

    int
    string2int_r(std::string src);
    // reversely convert binary string (twos complement) to signed integer.
    // i.e. src = "1101", return 1011(binary) = -5(decimal)

    std::string
    int2string(int integer, int length);

    std::string
    uint2string(unsigned integer, int length);

    std::string
    convertDecToBase(int source, NumberBase base);

    int convertBaseToDec(std::string source, NumberBase base);

}

/// converter  between string word("123") and a number(int(123))
namespace converter_SN{

    /// "123"    --> 123
    /// "123.3"  --> 123.3
    /// "+123.3" --> 123.3
    /// "-123.3" --> -123.3
    /// "123e2"  --> 12300
    /// "-1.2e2" --> -130
    /// "0x12"   --> 0x12
    /// "011"    --> 011,int c=5;std::bitset<sizeof(int)*8> a(c);
    // recurrence to get the edge of the digit .
    void dataScope(char * in, int &fir, int &sec,int &pos);

    void dataFormart(int &src, int base, int &res,int &pos);

    template<typename dataType>
    bool convertStringToNumber(char * in_str,dataType &data){
//        char * in_str;
//        if(typeid(in) == typeid(std::string) )
//            in_str = in.c_str(); // print typeid(char*).name()
//        else
//            in_str = in;

        bool symbol = 0;
        NumberBase base = kDecimal; // default is 10
        bool dot = false; // no dot, an integer.
        bool exp = false; // no exponential.
        int next = 1;

        if(in_str && *in_str !='\0' ){  /// if not empty
            if( in_str[0]=='+' )
                ;
            else if( in_str[0]=='-' )
                symbol = 1;
            else if( in_str[0] =='0' ){
                if( in_str[1] == 'x' ){
                    base = kHexidecimal;
                    next = 2;
                }
                else
                    base = kOctonary;
            }else if( isdigit(in_str[0]) )
                next = 0;
            else
                std::cerr << "the first char in[0] is not a ligeal char" << std::endl;

            int fir,sec,pos;
            int pre_dot;
            if( isdigit(in_str[next]) ) {     // next char must be number.
                fir = next;
                sec = next;
                pos = next;
                dataScope(in_str,fir,sec,pos);
                pre_dot = std::atoi(std::string(in_str).substr(fir,sec-fir+1).c_str());
            }

            // next char.
            next = sec +1;
            int post_dot = 0;
            int post_exp = 0;
            if( in_str[next] =='\0' ){ // end
                int res = 0;
                int pos = 0;
                if( base ==kOctonary ){
                    dataFormart(pre_dot, base, res,pos);
                    //if(~symbol)
                        data = res;     // octonary no negative nunber.
                    //else
                    //    data = 0-res;
                    return true;
                }else if (base ==kHexidecimal ){
                    dataFormart(pre_dot, base, res,pos);
                    data = res;
                    return true;
                }else if (base ==kDecimal ){
                    data = pre_dot;
                    return true;
                }
            }else if( in_str[next]=='.' ){  // -1.2 or -1.2e2 or -1.2e+2
                dot = true;
                next++;
                fir = next;
                sec = next;
                pos = next;
                dataScope(in_str,fir,sec,pos);
                post_dot = std::atoi(std::string(in_str).substr(fir,sec-fir+1).c_str());
                int dot_bit = sec -fir +1;

                double  result_tmp = pre_dot + post_dot/(pow(10,dot_bit));
                if(symbol) // neg
                    result_tmp = 0-result_tmp;

                // next char
                next = sec + 1;
                //std::cout << in_str[next] << std::endl; // if -1. not known for in_str[4] �

                if( in_str[next] == '\0' ){ // -0.11
                    data = result_tmp;
                    return true;
                }else if( in_str[next++] == 'e' ){    // -1.2e2 or -1.2e+2
                    if( in_str[next] == '+' )
                        next++;

                    exp = true;
                    fir = next;
                    sec = next;
                    pos = next;
                    dataScope(in_str,fir,sec,pos);
                    post_exp = std::atoi(std::string(in_str).substr(fir,sec-fir+1).c_str());
                    //int exp_bit = sec -fir +1;
                    result_tmp *=pow(10,post_exp);
                    data = result_tmp;
                    return true;

                }else { // -1. ==> -1
                    //std::cerr << "cann't resolve not like -1.2e2 or -1.2e+2." << std::endl;
                    data = result_tmp;
                    return true;
                }

            } else if( in_str[next++]=='e'){    // -12e3 or -12e+2
                if( in_str[next] == '+' )
                    next++;

                exp = true;
                fir = next;
                sec = next;
                pos = next;
                dataScope(in_str,fir,sec,pos);
                post_exp = std::atoi(std::string(in_str).substr(fir,sec-fir+1).c_str());
                //int exp_bit = sec -fir +1;
                int result_tmp = pre_dot;
                if(symbol) // neg
                    result_tmp = 0-result_tmp;
                result_tmp *=pow(10,post_exp);
                data = result_tmp;
                return true;

            }else
                std::cerr << "after -12 but not end,cann't  recognize char " << std::endl;

        }else{
            std::cerr<<"you must input a unempty number!";
        }

    };


}

namespace info{
    /// judge whether a word is a number
    /// such as ,"123" true
    ///          "Z123" false
    ///          "123Z" false
    //    bool isNumber(std::string str){       ///error!
    //        int cnt = 0;
    //        int len = str.length();
    //        for(int j=0; j < len; j++ ){
    //            if( isdigit(str[j]) )
    //                cnt++;
    //        }
    //        return cnt == len;
    //    }
    bool isNumber(std::string str); // global function must defined in another .cpp file.or will occur duplicate redefine.
    bool isNumber(char * str);

}


#endif //CPPGRAMMER_UTILITY_H
