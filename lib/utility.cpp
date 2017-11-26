//
// Created by Cookie on 2017/11/25.
//

#include "../include/utility.h"

namespace converter_BB{

    unsigned long
    string2ulong(std::string src)
    // convert binary string to unsigned integer.
    // i.e. src = "1101", return 1101(binary) = 13(decimal)
    {
        std::bitset<64> buf(src);
        return buf.to_ulong();
    }

    unsigned long
    string2ulong_r(std::string src)
    // reversely convert binary string to unsigned integer.
    // i.e. src = "1101", return 1011(binary) = 11(decimal)
    {
        std::string temp = src;
        reverse(temp.begin(), temp.end());

        std::bitset<64> buf(temp);
        return buf.to_ulong();
    }

    int
    string2int(std::string src)
    // convert binary string (twos complement) to signed integer.
    // i.e. src = "1101", return 1101(binary) = -3(decimal)
    {
        std::bitset<64> buf(src);
        unsigned int length = src.length();
        if(buf.test(length-1))
        {
            for(unsigned int i=0 ; i < length ; i++)
                buf.flip(i);
            return 0 - ((int)buf.to_ulong() + 1);
        }
        else
            return (int)buf.to_ulong();
    }

    int
    string2int_r(std::string src)
    // reversely convert binary string (twos complement) to signed integer.
    // i.e. src = "1101", return 1011(binary) = -5(decimal)
    {
        std::string temp = src;
        reverse(temp.begin(), temp.end());
        unsigned int length = src.length();
        std::bitset<64> buf(temp);
        if(buf.test(length-1))
        {
            for(unsigned int i=0 ; i < length ; i++)
                buf.flip(i);
            return 0 - ((int)buf.to_ulong() + 1);
        }
        else
            return (int)buf.to_ulong();
    }


    std::string
    convertDecToBase(int source, NumberBase base){
        std::stringstream buffer;
        if(base ==kBinary )
            buffer<<(std::bitset<32>)source;
        else if (base == kDecimal)
            buffer<<source;
        else if(base == kHexidecimal)
            buffer<<"0x"<<std::hex<<source;
       else
            std::cerr << "not known base." << std::endl;
        return buffer.str();
    }


    int
    convertBaseToDec(std::string source, NumberBase base){
        return (int)std::stoll(source,0,base);
    }

    std::string
    int2string(int integer, int length){
        std::string buffer_s;
        std::bitset<32> buffer_b(integer);
        buffer_s = buffer_b.to_string();
        return buffer_s.substr(buffer_s.length()-length, length);
    }

    std::string
    uint2string(unsigned integer, int length){
        std::string buffer_s;
        std::bitset<32> buffer_b(integer);
        buffer_s = buffer_b.to_string();
        return buffer_s.substr(buffer_s.length() - length, length);
    }


}

namespace converter_SN{

        /// "123"    --> 123
        /// "123.3"  --> 123.3
        /// "+123.3" --> 123.3
        /// "-123.3" --> -123.3
        /// "123e2"  --> 12300
        /// "-1.2e2" --> -130
        /// "0x12"   --> 0x12
        /// "011"    --> 011,int c=5;std::bitset<sizeof(int)*8> a(c);
        void dataScope(char * in, int &fir, int &sec,int &pos){
            if( isdigit(in[pos])){
                sec = pos;
                pos ++;
                dataScope(in,fir,sec,pos);
            }else
                return;
        }

        void dataFormart(int &src, int base, int &res,int &pos){
            int ge = src % 10;
            src = src /10;
            res += ge * pow(base,pos);
            if ( src !=0 ){
                pos ++;
                dataFormart(src,base,res,pos);
            }
            else
                return;
        }


}

namespace info{
    bool isNumber(std::string str){
        int cnt = 0;
        int len = str.length();
        for(int j=0; j < len; j++ ){
            if( isdigit(str[j]) )
                cnt++;
        }
        return cnt == len;
    }

    bool isNumber(char * str){
        int cnt = 0;
        int len = strlen(str);
        for(int j=0; j < len; j++ ){
            if( isdigit(str[j]) )
                cnt++;
        }
        return cnt == len;
    }
}