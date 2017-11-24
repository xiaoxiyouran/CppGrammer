#include <iostream>
#include "17-InputOutputFile/inputOutputFile.h"
int main() {
    using namespace std;
    std::cout << "Hello, World!" << std::endl;
    inputoutputfile::Output output;
    std::vector<char *> res;
    output.tmpFileName(res,10);
    for(auto x:res) cout<< string(x)<< endl;

    inputoutputfile::Input input;
    cout << "好的";

    return 0;
}