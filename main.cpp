#include <iostream>
#include <sstream>
#include <vector>
#include "include/utility.h"
#include "17-InputOutputFile/inputOutputFile.h"

int main() {
    using namespace std;
    using namespace inputoutputfile;
    std::cout << "Hello, World!" << std::endl;
    inputoutputfile::Output output;

    inputoutputfile::Input input;

    using namespace converter_SN;
    double res;
    convertStringToNumber("-12e+3",res);
    cout << "结果是:" << res << endl;








    return 0;
}



