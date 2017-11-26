//
// Created by xiaoxi on 2017/11/23.
//
#include "inputOutputFile.h"
#include "../include/define.h"

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

    void Input::checkCinForValidInput(void){
        using namespace std;
        cout << "Enter numbers: ";

        int sum = 0;
        int input;
        while (cin >> input)
        {
            sum += input;
        }

        cout << "Last value entered = " << input << endl;
        cout << "Sum = " << sum << endl;
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

//    Increasing loop index:
//    K
//    Ka
//    Kan
//    Kans
//    Kansa
//    Kansas
//    Decreasing loop index:
//    Kansas
//    Kansa
//    Kans
//    Kan
//    Ka
//    K
//    Exceeding string length:
//            Kansas Euph

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
            cout.write(state2,i);   /// 从开头到这儿的字符
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

    void Output::coutIomanipTest(){
        using namespace std;
        // use new standard manipulators
        cout << fixed << right;

        // use iomanip manipulators
        cout << setw(6) << "N" << setw(14) << "square root"
             << setw(15) << "fourth root\n";

        double root;
        for (int n = 10; n <=100; n += 10)
        {
            root = sqrt(double(n));
            cout << setw(6) << setfill('.') << n << setfill(' ')
                 << setw(12) << setprecision(3) << root
                 << setw(14) << setprecision(4) << sqrt(root)
                 << endl;
        }
        // std::cin.get();
    }

///---------------------------------------------------------------------------------------------------------------------
    ///FileOutput

    /// output a vector, append at the end of the file.
    bool FileOutput::appendWords(std::vector<std::string> & vec_for_out) {
//        std::cout << "Enter guest names (enter a blank line to quit):\n";
//        std::string name;
//        while (getline(std::cin,name) && name.size() > 0)
//        {
//            fout << name << endl;
//        }

        for(auto word : vec_for_out)
           fout << word << std::endl;
#ifdef __DEBUG
        std::cout << filename << " has been append successfully." << std::endl;
#endif
    }

    /// Output a struct or class, and store it with binary format.
    /// Perhaps your constructor maybe, ofstream fout(file,ios_base::out | ios_base::app | ios_base::binary);
    /// for example the struct is :
    ///struct planet
    ///{
    ///    char name[20];      // name of planet
    ///    double population;  // its population
    ///    double g;           // its acceleration of gravity
    ///};
    //template <typename structType>
    bool FileOutput::writeStructClassTest(void ){
        struct planet
        {
            char name[20];      // name of planet
            double population;  // its population
            double g;           // its acceleration of gravity
        };

        const char * file = "planets.dat";
        using namespace std;
        planet pl;
        cout << fixed << right;

        // show initial contents
        ifstream fin;
        fin.open(file, ios_base::in |ios_base::binary);  // binary file
        //NOTE: some systems don't accept the ios_base::binary mode
        if (fin.is_open())
        {
            cout << "Here are the current contents of the "
                 << file << " file:\n";
            while (fin.read((char *) &pl, sizeof pl))
            {
                cout << setw(20) << pl.name << ": "
                     << setprecision(0) << setw(12) << pl.population
                     << setprecision(2) << setw(6) << pl.g << endl;
            }
            fin.close();
        }

        // add new data
        ofstream fout(file,
                      ios_base::out | ios_base::app | ios_base::binary);
        //NOTE: some systems don't accept the ios::binary mode
        if (!fout.is_open())
        {
            cerr << "Can't open " << file << " file for output:\n";
            exit(EXIT_FAILURE);
        }

        cout << "Enter planet name (enter a blank line to quit):\n";
        cin.get(pl.name, 20);
        while (pl.name[0] != '\0')
        {
            eatline();
            cout << "Enter planetary population: ";
            cin >> pl.population;
            cout << "Enter planet's acceleration of gravity: ";
            cin >> pl.g;
            eatline();
            fout.write((char *) &pl, sizeof pl);
            cout << "Enter planet name (enter a blank line "
                    "to quit):\n";
            cin.get(pl.name, 20);
        }
        fout.close();

        // show revised file
        fin.clear();    // not required for some implementations, but won't hurt
        fin.open(file, ios_base::in | ios_base::binary);
        if (fin.is_open())
        {
            cout << "Here are the new contents of the "
                 << file << " file:\n";
            while (fin.read((char *) &pl, sizeof pl))
            {
                cout << setw(20) << pl.name << ": "
                     << setprecision(0) << setw(12) << pl.population
                     << setprecision(2) << setw(6) << pl.g << endl;
            }
            fin.close();
        }
        cout << "Done.\n";

    }


    bool FileOutput::isOpen(){
        if(fout.is_open())
            return  true;
        else{
            std::cerr << "file cann't open correctly.function fin.is_open() failed,please checked it " << std::endl;
            exit(EXIT_FAILURE);
            return  false;
        }

    }

    bool FileOutput::closeFile(){
        fout.close();
        if(fout.fail()){
            std::cerr <<"fail or file is closed already!" <<std::endl;
            return false;
        }
        return true;
    }



///---------------------------------------------------------------------------------------------------------------------
    ///FileInput
    ///++++++++++++++++++++++++++++++++++++++++++++++++++++++
    bool FileInput::readin(std::vector<std::string> &vec,const int line_length ){   // default line length is 255 bytes.
        char one_line[line_length];
        while( fin.get(one_line,sizeof(one_line),'\n') ){ // param 3 can be omit,default be '\n' split.
            is_lineend(this->fin);
            vec.push_back(std::string(one_line));
        }
        return true;
    };

    /// to judge whether get the end of the line. if not, abandon the rest of the line.
    bool FileInput::is_lineend(std::ifstream & fin){
        char ch;
        fin.get(ch);
        if( ch!='\n' ){
            while (fin.get() != '\n') continue;     // abandon rest of the line.
            std::cerr << "your line_length is too short, the rest of the line is abandoned";
            return false;
        }
        return true;
    }

    bool FileInput::readrandom(std::vector<std::string> &vec, char separator){
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

    bool FileInput::parseLines(const std::vector<std::string> &vec,
                    std::multimap< int,std::vector<std::string> > & lines){ // first one is the line number.
        Input input_helper;
        int line_no = 0;
        for(std::string one_line:vec){
            line_no++;
            parseLine(input_helper,one_line,line_no,lines);

        }
        return true;

    }

    bool FileInput::parseLine(Input & input_helper,std::string & oneline, const int & line_no,std::multimap<int, std::vector<std::string>> & res){
        std::vector<std::string> line_words;    // line contains words in each line.
        input_helper.readFromString(oneline,line_words);
        res.insert(std::make_pair(line_no,line_words));
        return true;
    }

    void FileInput::readFileCommandLineTest(int argc, char * argv[]){
        using namespace std;
        if (argc == 1)          // quit if no arguments
        {
            cerr << "Usage: " << argv[0] << " filename[s]\n";
            exit(EXIT_FAILURE);
        }

        ifstream fin;              // open stream
        long count;
        long total = 0;
        char ch;

        for (int file = 1; file < argc; file++)
        {
            fin.open(argv[file]);  // connect stream to argv[file]
            if (!fin.is_open())
            {
                cerr << "Could not open " << argv[file] << endl;
                fin.clear();
                continue;
            }
            count = 0;
            while (fin.get(ch))
                count++;
            cout << count << " characters in " << argv[file] << endl;
            total += count;
            fin.clear();           // needed for some implementations
            fin.close();           // disconnect file
        }
        cout << total << " characters in all files\n";
    }


    ///++++++++++++++++++++++++++++++++++++++++++++++++++++++

    bool FileInput::isOpen(){
        if(fin.is_open())
            return  true;
        else{
            std::cerr << "file cann't open correctly.function fin.is_open() failed,please checked it " << std::endl;
            exit(EXIT_FAILURE);
            return  false;
        }

    }

    bool FileInput::closeFile(){
        fin.close();
        if(fin.fail()){
            std::cerr <<"fail or file is closed already!" <<std::endl;
            return false;
        }
        return true;
    }

    std::ostream & operator << (std::ostream & os,FileInput & fileInput ){
        using std::cout;
        char ch;
        if(fileInput.isOpen()){
            os << "Here are the current contents of the "
                 << fileInput.filename << " file:\n";
            while (fileInput.fin.get(ch))
                os << ch;
            //closeFile();
        }
        return os;

    }
///---------------------------------------------------------------------------------------------------------------------
    ///class FileInOut this class using fstream can read and write file at the same time.

    void FileInOut::finoutRandomReadWriteTest(){
        using namespace std;
        planet pl;
        cout << fixed;

// show initial contents
        fstream finout;     // read and write streams
        // can read and change file.
        finout.open(file,
                    ios_base::in | ios_base::out | ios_base::binary);
        //NOTE: Some Unix systems require omitting | ios::binary
        int ct = 0;
        if (finout.is_open())
        {
            finout.seekg(0);    // go to beginning
            cout << "Here are the current contents of the "
                 << file << " file:\n";
            while (finout.read((char *) &pl, sizeof pl))
            {
                cout << ct++ << ": " << setw(LIM) << pl.name << ": "
                     << setprecision(0) << setw(12) << pl.population
                     << setprecision(2) << setw(6) << pl.g << endl;
            }
            if (finout.eof())
                finout.clear(); // clear eof flag
            else
            {
                cerr << "Error in reading " << file << ".\n";
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cerr << file << " could not be opened -- bye.\n";
            exit(EXIT_FAILURE);
        }

// change a record
        cout << "Enter the record number you wish to change: ";
        long rec;
        cin >> rec;
        eatline();              // get rid of newline
        if (rec < 0 || rec >= ct)
        {
            cerr << "Invalid record number -- bye\n";
            exit(EXIT_FAILURE);
        }
        streampos place = rec * sizeof pl;  // convert to streampos type
        finout.seekg(place);    // random access
        if (finout.fail())
        {
            cerr << "Error on attempted seek\n";
            exit(EXIT_FAILURE);
        }

        finout.read((char *) &pl, sizeof pl);
        cout << "Your selection:\n";
        cout << rec << ": " << setw(LIM) << pl.name << ": "
             << setprecision(0) << setw(12) << pl.population
             << setprecision(2) << setw(6) << pl.g << endl;
        if (finout.eof())
            finout.clear();     // clear eof flag

        cout << "Enter planet name: ";
        cin.get(pl.name, LIM);
        eatline();
        cout << "Enter planetary population: ";
        cin >> pl.population;
        cout << "Enter planet's acceleration of gravity: ";
        cin >> pl.g;
        finout.seekp(place);    // go back
        finout.write((char *) &pl, sizeof pl) << flush;
        if (finout.fail())
        {
            cerr << "Error on attempted write\n";
            exit(EXIT_FAILURE);
        }

// show revised file
        ct = 0;
        finout.seekg(0);            // go to beginning of file
        cout << "Here are the new contents of the " << file
             << " file:\n";
        while (finout.read((char *) &pl, sizeof pl))
        {
            cout << ct++ << ": " << setw(LIM) << pl.name << ": "
                 << setprecision(0) << setw(12) << pl.population
                 << setprecision(2) << setw(6) << pl.g << endl;
        }
        finout.close();
        cout << "Done.\n";
    }

///---------------------------------------------------------------------------------------------------------------------
    ///global test function

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


//    Left Justification:
//    +1  |+1.000e+00  |
//    +11 |+3.317e+00  |
//    +21 |+4.583e+00  |
//    +31 |+5.568e+00  |
//    +41 |+6.403e+00  |
//    Internal Justification:
//    +  1|+       1.00|
//    + 11|+       3.32|
//    + 21|+       4.58|
//    + 31|+       5.57|
//    + 41|+       6.40|
//    Right Justification:
//    +1|      +1.000|
//    +11|      +3.317|
//    +21|      +4.583|
//    +31|      +5.568|
//    +41|      +6.403|
    void coutUsingSetfToControlOutputFormart(){
        using namespace std;
        // use left justification, show the plus sign, show trailing
        // zeros, with a precision of 3
        cout.setf(ios_base::left, ios_base::adjustfield);
        cout.setf(ios_base::showpos);
        cout.setf(ios_base::showpoint);
        cout.precision(3);
        // use e-notation and save old format setting
        ios_base::fmtflags old = cout.setf(ios_base::scientific,
                                           ios_base::floatfield);
        cout << "Left Justification:\n";
        long n;
        for (n = 1; n <= 41; n+= 10)
        {
            cout.width(4);
            cout << n << "|";
            cout.width(12);
            cout << sqrt(double(n)) << "|\n";
        }

        // change to internal justification
        cout.setf(ios_base::internal, ios_base::adjustfield);
        // restore default floating-point display style
        cout.setf(old, ios_base::floatfield);

        cout << "Internal Justification:\n";
        for (n = 1; n <= 41; n+= 10)
        {
            cout.width(4);
            cout << n << "|";
            cout.width(12);
            cout << sqrt(double(n)) << "|\n";
        }

        // use right justification, fixed notation
        cout.setf(ios_base::right, ios_base::adjustfield);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout << "Right Justification:\n";
        for (n = 1; n <= 41; n+= 10)
        {
            cout.width(4);
            cout << n << "|";
            cout.width(12);
            cout << sqrt(double(n)) << "|\n";
        }
    }


}

