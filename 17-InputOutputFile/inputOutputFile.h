//
// Created by xiaoxi on 2017/11/23.
//

#ifndef CPPGRAMMER_INPUTOUTPUTFILE_H
#define CPPGRAMMER_INPUTOUTPUTFILE_H

#include <iostream>
#include <iomanip>      // for setw()
// ostream                                  istream
// |                                        |
// ostringstream/wostringstream             istringstream/wistringstream
#include <sstream>      // for incore(kernal) formatting.

#include <vector>

#include <cstdio>       // for tmpnam()

namespace inputoutputfile{

///---------------------------------------------------------------------------------------------------------------------
    /// cin
    class Input{
    public:
        /// Using cin to get in a string, and store in array, please provided width.
        /// such as:
        // char arr[20];        // !! cannot using char * arr, this will create a runtime error.
        // input.cinGet(arr,10);
        void cinGet(char * store,int width = 20){ std::cin.get(store,width).get();}

        /// this function to test cin and cin.get()
        /// cin will ignore blank space,table or Enter
        /// cin.get() can read Enter and other blank char.
        void testCin();

        /// using istream to read each word from a long string, such as :"I love you", and it return "I","love","you"
        void readFromString(const std::string input, std::vector<std::string> & output);
    };

///---------------------------------------------------------------------------------------------------------------------
    /// cout
    class Output{

    public:
        enum Base{Dec,Hex,Oct};     // in public scope, so that outer can use.

    public:
        /// Display the width of the value,right align default. only next word is valid
        void setWidth(std::ostream & os,int width = 15){  os << std::setw(width); }

        /// chose a base to display the data.
        void setDisplayBase(std::ostream &os,Base base = Dec);

        /// set retain decimal(xiao shu) bits
        void setPrecision(std::ostream & os, int width = 2){ os<< std::setprecision(width);}

        /// Decimal, base is None
        /// Hex,base is 0x
        /// Octal, base is 0
        void showbase(std::ostream & os){ os.setf(std::ios::showbase); }

        ///
        void showpoint(std::ostream &os){ os.setf(std::ios::showpoint);}

        /// floatfiels can be select from fixed / scientific
        void showfixed(std::ostream &os){ os.setf(std::ios::fixed,std::ios::floatfield);        // or
//        os << std::fixed;
        }      // first is the set value, second param is the category.

        /// right align
        void rightalign(std::ostream &os){ os.setf(std::ios::right,std::ios::adjustfield); }    // first is the set value, second param is the category.

        /// left align
        void leftalign(std::ostream &os){ os.setf(std::ios::left,std::ios::adjustfield); }    // first is the set value, second param is the category.


        ///**************************************
        /// ostringstream to save different word segment to a integral string and return it .
        /// this is only a case
        /// we must note two:
        /// 1. template must defined in .h file,because it is member function, and the instance will look for the context.
        /// 2. if you use like: param cann't use T &str,because it is temporal.
        //std::cout<< output.writeToString<std::string,double>( "haha",10.09) << std::endl;
        //std::cout<< output.writeToString( "haha",10.09) << std::endl;
        template <typename T,typename U>
        std::string writeToString(T str,U data) {
        std::stringstream outstr;   // manages a string stream

        outstr << str;
        outstr.precision(2);        // or it is inherit from ostream
//        setPrecision(outstr,2);     //
        outstr<<std::fixed;
        outstr<< data;
        return outstr.str();        // return a string. and you cann't add it.
    }

        /// If you want to generate temporal file, and this function will generate the number different filename in current directory.
        void tmpFileName(std::vector<char *> &res ,int number = 10);

    };

///---------------------------------------------------------------------------------------------------------------------
    ///
    class File{
    public:
    };
}

#endif //CPPGRAMMER_INPUTOUTPUTFILE_H
