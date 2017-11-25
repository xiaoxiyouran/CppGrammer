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
#include <fstream>      // for ofstream
#include <string>       // for ofstream?
#include <map>          // for multimap, many keys the same allowed.

// ios_base
// |
// ios(general stream attribute,a pointer to steambuf obj)  ---> steambuf(manage the buffer memory of i/o)
// |        |
// ostream  istream
// |
// iostream


namespace inputoutputfile{

///---------------------------------------------------------------------------------------------------------------------
    /// cin
    class Input{
    public:
        /// empty constructor, main usage is the funciton, one kit helper cls.
        Input(){}

        /// Using cin to get in a string, and store in array, please provided width.
        /// such as:
        // char arr[20];        // !! cannot using char * arr, this will create a runtime error.
        // input.cinGet(arr,10);
        void cinGet(char * store,int width = 20){ std::cin.get(store,width).get();}

        /// this function to test cin and cin.get()
        /// cin will ignore blank space,table or Enter
        /// cin.get() can read Enter and other blank char.
        void testCin();

        void testCin2(){
            int sum {0};
            int input;
            while( std::cin >>input )   // 1 2 3 Z "Z" is not valid for input type,will return 0,and get out of loop. failbit is set.
                sum += input;
            std::cout << sum << std::endl;
        }

        /// using istream to read each word from a long string, such as :"I love you", and it return "I","love","you"
        void readFromString(const std::string input, std::vector<std::string> & output);

        /// strean state
        /// eofbit(file end),badbit(file is destroyed),failbit(not read expect char or write expect char),goodbit(0)
        /// good(): if all bit is cleared,return true.
        /// eof(): if eofbit is set, return true.
        /// bad(): if badbit is set, return true.
        /// fail(): if badbit/failbit is set, return true.
        /// rdstate(): return the state of stream.
        /// exceptions(): return bit mask to indicate which mask trigger exception. 3bits:eofbit_failbit_badbit,default =0, no exception.
        /// exceptions(iostate ex): if ex = eofbit, and if eofbit is set, clear will throw a exception.
        /// clear(iostate s): set the state of stream. default s = 0(goodbit).
        ///                   if ( rdstate()&exceptions() )!=0,[thus there is 1bit not the same] throw exception basic_ios::failure --> std::exception class.ows a what() function.
        /// setstate(iostate s): call func: clear(rdstate()|s), set the state fo s

        // clear(); // clear 3 state of eofbit,badbit and failbit.
        // clear(eofbit); // eofbit is set, other two bits are cleared.
        // setstate(eofbit); // only set eofbit, others not care.

        /// set a exception may occur, to indicate whether there is an exception capture.
        void cinExceptionTest();

        /// cin.get() each rean one char, and read blank char, space,"\t","\n"
        void cinGetTest();

        /// cin ignore space.
        void cinTest();

        /// char ch = cin.get(void) ,use ruturn value.
        /// but prototype is : int get(void), cann't using cin.get().get()
        void cinGetVoidTest();

        ///// chosing from cin,get(char &),get(void)
        /// cin: If you want to skip space
        /// get(char &) to get each char
        /// cin.get(void)   >>> to replace getchar()
        /// cout.put(ch)    >>> to replace putchar(ch)

        ///--------------------------
        /// input for string, get(),getline(),ignore()

        /// cin.get(),cin.getline(),cin . get input a string
        void cinGetForStringTest();

        /// cin.peeker() to look ahead the next char whether is your want.
        void peekerTest();

        /// to truncate rest of one line if not arrive at the '\n'
        void truncateTest();

    };

///---------------------------------------------------------------------------------------------------------------------
    /// cout
    class Output{

    public:
        enum Base{Dec,Hex,Oct};     // in public scope, so that outer can use.

    public:
        /// Display the width of the value,right align default. only next word is valid
        /// what's more, cpp never truncation data.
        void setWidth(std::ostream & os,int width = 15){
            os << std::setw(width);         // or cout.width(width);
        }

        /// chose a base to display the data.
        void setDisplayBase(std::ostream &os,Base base = Dec);

        /// set retain decimal(xiao shu) bits
        void setPrecision(std::ostream & os, int width = 2){
            os<< std::setprecision(width);  // or cout.precision(width); apart from dot, total bits.
        }

        /// this used with cout.width(),for fill remaining char.
        void setFill(std::ostream &os,char ch){
            os.fill(ch);    // such as cout.fill('*');  or cout << setfill('*')  //from <iomanip>
        }

        /// Decimal, base is None
        /// Hex,base is 0x
        /// Octal, base is 0
        void showbase(std::ostream & os){
            os.setf(std::ios::showbase);
            //os.unsetf(std::ios_base::showbase);   // restore or cout << noshowbase;
        }

        /// print the end of 0 and dot. such as : 20.4000
        void showpoint(std::ostream &os){
            os.setf(std::ios::showpoint);
            //os.unsetf(std::ios_base::showpoint); // if you want to restore it or cout << noshowpoint;
        }

        /// enable to show true or false,otherwise 1 or 0.
        void showbollapha(std::ostream & os){
            os.setf(std::ios_base::boolalpha);
            //os.unsetf(std::ios_base::boolalpha); // restore it . or cout << noboolalpha
        }

        /// add "+" ahead in a positive number, such as +10, only when base is 10.
        void showpos(std::ostream & os){
            os.setf(std::ios_base::showpos);
            //os.unsetf(std::ios_base::showpos);                    // restore. ir cout << noshowpos
        }

        /// floatfiels can be select from fixed / scientific
        void showfixed(std::ostream &os){
            //os.setf(std::ios::fixed,std::ios::floatfield);        // or
            //os << std::fixed;                                     // or os << std::scientific;
            // recommend in this way.
            std::ios_base::fmtflags old = os.setf(std::ios_base::fixed,std::ios_base::floatfield);  // this will store the old formart. and we call retore it later.
            //os.setf(old,std::ios_base::floatfield);                                               // restore.
        }      // first is the set value, second param is the category.

        /// right align
        void rightalign(std::ostream &os){
            os.setf(std::ios::right,std::ios::adjustfield);         // or cout << right
        }    // first is the set value, second param is the category.

        /// left align
        void leftalign(std::ostream &os){
            os.setf(std::ios::left,std::ios::adjustfield);          // or cout << left;
        }                                                           // first is the set value, second param is the category.

        /// internal align
        void internalalign(std::ostream &os){
            os.setf(std::ios::internal,std::ios::adjustfield);      // or cout << internal;
        }                                                           // first is the set value, second param is the category.


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
            //setPrecision(outstr,2);     //
            outstr<<std::fixed;
            outstr<< data;
            return outstr.str();        // return a string. and you cann't add it.
        }

        /// If you want to generate temporal file, and this function will generate the number different filename in current directory.
        void tmpFileName(std::vector<char *> &res ,int number = 10);

        /// cout << overload ostream & operator << (int/double/..)

        /// retur the length of char * str = "abcd"
        int getLengthOfCharPtr(const char * str){ return std::strlen(str); }

        /// cout.put(),fuc prototype: ostream & put(char)
        /// output a single char
        void coutPutTest();

        /// cout.write() test.
        /// fucn prototype: basic_ostream<charT,traits>& write(const char_type *s,streamsize n)
        /// this function will write the giving address, and giving the number of character you want to display.
        void coutWriteTest();

        /// flush the buffer,512 bytes X
        void coutFlush(std::ostream & os){
            os << std::flush; // or cout << flush or flush(cout)
            /// << endl === flush + "\n"
        }



    };

///---------------------------------------------------------------------------------------------------------------------
    ///
    class FileOutput{
    private:
        const char * filename;
        std::ofstream fout;
    public:
        /// set filename and create file stream
        FileOutput(){}
        FileOutput(std::string filename):filename(filename.c_str()){
            fout.open(filename);            /// or std::ofstream fout(filename)
        }
        FileOutput(char* filename):filename(filename){
            fout.open(filename);
        }

        void setFilename(char * filename){ this->filename = filename; }
        void setFilename(std::string filename) {this->filename = filename.c_str();}

        void openFile(){
            fout.open(filename);
        }

        /// write into file. The input maybe string(generated by stringstream, consist of data and string and also owns the formart you want)
        /// each time, write one line.
        template <typename T>
        bool writeOut(std::vector<T> data){
            for(auto in : data )
                fout<< in << std::endl;
            return true;
        }

        bool closeFile(){
            fout.close();
            return true;
        }



    };

    class FileInput{
    private:
        const char * filename;
        std::ifstream fin;
    public:
        /// set filename and create file stream
        FileInput(){}
        FileInput(std::string filename):filename(filename.c_str()){
            fin.open(filename);            /// or std::ifstream fin(filename)
        }
        FileInput(char* filename):filename(filename){
            fin.open(filename);
        }

        void setFilename(char * filename){ this->filename = filename; }
        void setFilename(std::string filename) {this->filename = filename.c_str();}

        void openFile(){
            fin.open(filename);
        }

        /// This function read in one line from the file,but you must give the length of one line ahead, or you will get truncation.
         bool readin(std::vector<std::string> &vec,const int line_length = 255 ){   // default line length is 255 bytes.
             char one_line[line_length];
             while( fin.get(one_line,sizeof(one_line),'\n') ){ // param 3 can be omit,default be '\n' split.
                 is_lineend(this->fin);
                 vec.push_back(std::string(one_line));
             }
             return true;
        };

        /// to judge whether get the end of the line. if not, abandon the rest of the line.
        inline bool is_lineend(std::ifstream & fin){
            char ch;
            fin.get(ch);
            if( ch!='\n' ){
                while (fin.get() != '\n') continue;     // abandon rest of the line.
                std::cerr << "your line_length is too short, the rest of the line is abandoned";
                return false;
            }
            return true;
        }

        /// This function will read onle without know the length of one line,and each word is split by separator.but
        /// it maybe slow,because it is get one by one.
        bool readrandom(std::vector<std::string> &vec, char separator = 0){
            using namespace std;
            stringstream instr;
            char ch;
            while (fin.get(ch)){    // will get each char(include space,'\t','\n'),untill get end of the file.
                //cout << "--"<<ch;
                if( ch!='\n' )
                    instr.put(ch);  // put each char in stringstream(include space,'\t','\n')
                else{   // get end of the line
                    string str = instr.str();
                    //cout <<"++" <<str << endl;
                    //instr.clear();  // clear last line tmp. However, this is clear the state of stringstream,such as error bit.
                    instr.str("");
                    if( str != "" )
                        vec.push_back(str);
                    else
                        cerr<<"read in one empty line."<<endl;
                }
            }
            return true;

        }

        /// if you input the data(consist of lines), we will parse it into each word with right format(string or number)
        bool parseLines(const std::vector<std::string> &vec,
                        std::multimap< int,std::vector<std::string> > & lines){ // first one is the line number.
            Input input_helper;
            int line_no = 0;
            for(std::string one_line:vec){
                line_no++;
                parseLine(input_helper,one_line,line_no,lines);

            }
            return true;

        }

        /// parse each line
        bool parseLine(Input & input_helper,std::string & oneline, const int & line_no,std::multimap<int, std::vector<std::string>> & res){
            std::vector<std::string> line_words;    // line contains words in each line.
            input_helper.readFromString(oneline,line_words);
            res.insert(std::make_pair(line_no,line_words));
            return true;
        }


        /// close file.
        bool closeFile(){
            fin.close();
            return true;
        }

        /// clear the buffer.
        bool clearBuffer(){
            fin.clear();
            return true;
        }



    };

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /// One global function to test class FileInput and class FileOutput.
    void FileOutput_FileInput_Test();


}

#endif //CPPGRAMMER_INPUTOUTPUTFILE_H
