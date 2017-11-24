//
// Created by xiaoxi on 2017/11/23.
//
#include "inputOutputFile.h"
namespace inputoutputfile{
///---------------------------------------------------------------------------------------------------------------------
    /// cin
    void Input::testCin() {
        using namespace std;
        char ch;
        int ct1 = 0;

        cin >> ch;              // each time read only one char, and ignore blank space.
        while( ch != 'q' ){
            ct1++;
            cin >> ch;
        }

        int ct2 = 0;
        cin.get(ch);            // begin read at <Enter>
        while( ch != 'q' ){
            ct2++;
            cin.get(ch);
        }

        cout<< "ct1 = " << ct1 << " ; " << "ct2 = " << ct2 << endl;
    }
//    I see a q<Enter>
//    I see a q<Enter>
//    ct1 = 5 ; ct2 = 9

    void Input::readFromString(const std::string input, std::vector<std::string> & output) {
        std::istringstream instr(input);    // use buf for input
        std::string word;
        while (instr >> word)              // read a word a time
            output.push_back(word);
    }
    //std::string lit = "It was a dark and stormy day, and "
    //        " the full moon glowed brilliantly. ";

///---------------------------------------------------------------------------------------------------------------------
    /// cout
    void Output::setDisplayBase(std::ostream &os,Base base){
        switch (base){
            case Dec: os<<std::dec;       // switch can only use single char or number.
                break;
            case Hex: os<<std::hex;
                break;
            case Oct: os<<std::oct;
                break;
            default:
                break;
        }
    }

//    template <typename T,typename U>
//    std::string Output::writeToString(T &str, U &data) {
//        std::stringstream outstr;   // manages a string stream
//
//        outstr << str;
//        outstr.precision(2);        // or it is inherit from ostream
////        setPrecision(outstr,2);     //
//        outstr<<std::fixed;
//        outstr<< data;
//        return outstr.str();        // return a string.
//    }

    void Output::tmpFileName(std::vector<char *> &res,int number) {
        char pszNmae[L_tmpnam] = {'\0'};                // one filename is 16bit.
        for(int i=0;i<number && i < TMP_MAX;i++){       // max number is 32767
            tmpnam(pszNmae);                            // char * tmpnam(char * pszNmae)
            res.push_back(pszNmae);
        }

    }
///---------------------------------------------------------------------------------------------------------------------
    ///
}

