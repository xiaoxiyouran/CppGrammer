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

    void Input::cinExceptionTest() {
        using namespace std;
        //cin.exceptions(std::ios_base::badbit);
        //cin.exceptions(ios_base::badbit | ios_base::eofbit); // throw a exception
        cin.exceptions(ios_base::failbit);
        cout << "Enter numbers: ";
        int sum = 0;
        int input;
        try {
            while (cin >> input)
            {
                sum += input;
            }
        } catch(ios_base::failure & bf)
        {
            cout << bf.what() << endl;
            cout << "O! the horror!\n";
        }

        if( cin.fail() && !cin.eof() )  // read failed because of mismatched input ,not at the end of file.
        {
            cin.clear(); // reset stream state
            while( !isspace(cin.get()) )    // isspace is a cctype func.  get rid of the left char, until meet a space.
                continue;                   //  abandon a word.

            //while ( cin.get()!='\n' )
            //    continue;                   // abandon the rest of one line.

        }else{
            exit(1);                           // arrive in eof of file or hardware problem.
        }

        cout << "Last value entered = " << input << endl;
        cout << "Sum = " << sum << endl;
    }

    void Input::cinGetTest() {
        using namespace std;
        int t = cin.get();  // input converts to int
        cin.clear();

        char ch;
        int ct{0};
        //cin.get(ch);    // 1<Enter> get is Enter.
        cin >> ch;        // ignore <Enter>
        while( ch!='\n' ){
            cout << ch << endl;
            ct++;
            cin.get(ch);    // getin next char.
        }

        cout << ct << endl;

        char ch1,ch2,c3;
        cin.get(ch1).get(ch2) >> c3;    // c3 is not a space.

        /// read from file.
        char ch4;
        while( cin.get(ch4) ){  // if get eof, will return false.
            ///.. processing
        }
    }

    void Input::cinTest() {
        using namespace std;
        char ch;
        cin >> ch;
        while( ch!='\n' )   // cin will ignore space,so never stop
            cin >> ch;
    }

    void Input::cinGetVoidTest() {
        using namespace std;
        char ch;
        ch = cin.get();
        while( ch!='\n' ){
            cout << ch;
            ch = cin.get();
        }

        char c1,c2,c3;
        //cin.get().get()>>c3;  // not valid,ret is int, cann't followed by extract operator
        cin.get(c1).get();      // skip the<Enter>

        /// when for reading from a file.
        while ( (c2 = cin.get())!= EOF ){
            /// processing...
        }

    }

    void Input::cinGetForStringTest() {
        using std::cout;
        using std::cin;
        using std::endl;
        using std::string;
        const int Limit = 255;

        char input[Limit];

        cout << "Enter a string for getline() processing:\n";
        cin.getline(input, Limit, '#');     // min{Limit-1(last is '\0'),'#'}; default is get '\n' and abandon it  ,,,me a #3 melon!
        cout << "Here is your input:\n";
        cout << input << "\nDone with phase 1\n";               // me a

        char ch;
        cin.get(ch);
        cout << "The next input character is " << ch << endl;   // 3

        if (ch != '\n')
            cin.ignore(Limit, '\n');                            // discard rest of line,abandon  min{Limit,'\n'}
                                                                // also,cin.ignore(Limit, '\n').ignore(Limit, '\n');

        cout << "Enter a string for get() processing:\n";
        cin.get(input, Limit, '#');                             // min{(Limit-1),'#'},but not get '#'
        cout << "Here is your input:\n";
        cout << input << "\nDone with phase 2\n";

        cin.get(ch);
        cout << "The next input character is " << ch << endl;   // '#


        char temp[80];
        while( cin.get(temp,80)&&temp[0]!='\n' ){   // if input is an empty line,terminate.
            //
        }


        //------------------------------------
        // cin >> string
        string filename;
        cin >> filename;

    }

    void Input::peekerTest() {
        using std::cout;
        using std::cin;
        using std::endl;

        //  read and echo input up to a # character
        char ch;

        while(cin.get(ch)){   // terminates on EOF
            if (ch != '#')
                cout << ch;
            else{
                cin.putback(ch);    // reinsert character
                break;
            }
        }

        if (!cin.eof()){
            cin.get(ch);
            cout << endl << ch << " is next input character.\n";
        }else{
            cout << "End of file reached.\n";
            std::exit(0);
        }

        while(cin.peek() != '#'){   // look ahead,but not get in.
            cin.get(ch);
            cout << ch;
        }

        if (!cin.eof()){
            cin.get(ch);
            cout << endl << ch << " is next input character.\n";
        }else
            cout << "End of file reached.\n";
    }

    void Input::truncateTest() {
        using std::cin;
        using std::cout;
        using std::endl;
        const int SLEN = 10;

        char name[SLEN];
        char title[SLEN];
        cout << "Enter your name: ";
        cin.get(name,SLEN);
        if (cin.peek() != '\n')
            cout << "Sorry, we only have enough room for "
                 << name << endl;
        while (std::cin.get() != '\n') continue;            /// eatline()
        cout << "Dear " << name << ", enter your title: \n";
        cin.get(title,SLEN);
        if (cin.peek() != '\n')
            cout << "We were forced to truncate your title.\n";
        while (std::cin.get() != '\n') continue;            /// eatline()
        cout << " Name: " << name
             << "\nTitle: " << title << endl;
    }

///---------------------------------------------------------------------------------------------------------------------
    /// cout
    void Output::setDisplayBase(std::ostream &os,Base base){
        switch (base){
            case Dec: os<<std::dec;       // switch can only use single char or number. or dec(cout)
                // or
                //os.setf(std::ios_base::dec/hex/oct,std::ios_base::basefield);
                break;
            case Hex: os<<std::hex;
                os.setf(std::ios_base::uppercase);  // oxA   , restore cout << nouppercase;
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


    void Output::coutPutTest() {
        std::cout.put('W');
        std::cout.put('I').put('t');    // because return ostream &
        std::cout.put(66.3);            // maybe B char.
    }

    void Output::coutWriteTest() {
        using std::cout;
        using std::endl;
        const char * state1 = "Florida";
        const char * state2 = "Kansas";
        const char * state3 = "Euphoria";
        int len = std::strlen(state2);
        cout << "Increasing loop index:\n";
        int i;
        for (i = 1; i <= len; i++){
            cout.write(state2,i);
            cout << endl;
        }

        // concatenate output
        cout << "Decreasing loop index:\n";
        for (i = len; i > 0; i--)
            cout.write(state2,i) << endl;       // return is ostream &

        // exceed string length
        cout << "Exceeding string length:\n";
        cout.write(state2, len + 5) << endl;        // also valid.

        /// also used to transform the stored bit in memory.
        //long val = 560031841;
        //cout.write((char *)val, sizeof(long));      // display 4 bytes in memory.
    }


///---------------------------------------------------------------------------------------------------------------------
    ///


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void FileOutput_FileInput_Test(){
        using namespace std;

        /// write out
        FileOutput fileout("out.txt");

        stringstream outstr;
        outstr << setw(10) << "Student Id" << setw(5) << 10 << '\n' << '\n' <<setw(10)<< "10"<< setw(5)<<20 ;
        vector<string> vec_out;
        vec_out.push_back(outstr.str());    // convert to string and push back

        fileout.writeOut(vec_out);
        fileout.closeFile();

        /// read in
        FileInput filein("out.txt");
        vector<string> vec_in;
        //filein.readin(vec_in,20);
        filein.readrandom(vec_in);
        filein.clearBuffer();
        filein.closeFile();

        for(auto it:vec_in) cout << it << endl;

        multimap< int,std::vector<std::string> > lines;
        filein.parseLines(vec_in,lines);

        for(multimap<int,vector<std::string>>::iterator it = lines.begin(); it != lines.end();it++ ){
            cout << "line no:" << it->first;
            for(string word:it->second)
                cout << " "<< word;     // get each word of the line.
            cout << endl;
        }
    }


}

