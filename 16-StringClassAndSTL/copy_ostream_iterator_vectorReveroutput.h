//
// Created by Cookie on 2017/11/26.
//

#ifndef CPPGRAMMER_COPY_OSTREAM_ITERATOR_VECTORREVEROUTPUT_H
#define CPPGRAMMER_COPY_OSTREAM_ITERATOR_VECTORREVEROUTPUT_H
// copyit.cpp -- copy() and iterators
#include <iostream>
#include <iterator>
#include <vector>

void copyTest(){
    using namespace std;

    /// copy 函数功能1：能将数组复制到vector.
    int casts[10] = {6, 7, 2, 9 ,4 , 11, 8, 7, 10, 5};
    vector<int> dice(10);
    // copy from array to vector
    /// 第一个参数是src_begin,第二参数：src_end, 第三个参数：destination_begin
    copy(casts, casts + 10, dice.begin());
    cout << "Let the dice be cast!\n";
    // create an ostream iterator

    /// copy 函数功能2：创建输出流，把要输出向量的起止范围复制到输出流完成输出
    ostream_iterator<int, char> out_iter(cout, " ");
    // copy from vector to output
    copy(dice.begin(), dice.end(), out_iter);
    cout << endl;

    /// 隐式的逆序输出（利用copy 函数）
    cout <<"Implicit use of reverse iterator.\n";
    copy(dice.rbegin(), dice.rend(), out_iter);
    cout << endl;

    /// 显示的逆序输出(vector的iterator)
    cout <<"Explicit use of reverse iterator.\n";
    // vector<int>::reverse_iterator ri;  // use if auto doesn't work
    for (auto ri = dice.rbegin(); ri != dice.rend(); ++ri)
        cout << *ri << ' ';
    cout << endl;
}


#endif //CPPGRAMMER_COPY_OSTREAM_ITERATOR_VECTORREVEROUTPUT_H
