//
// Created by Cookie on 2017/11/26.
//

#ifndef CPPGRAMMER_AUTO_PTR_H
#define CPPGRAMMER_AUTO_PTR_H
// fowl.cpp  -- auto_ptr a poor choice
#include <iostream>
#include <string>
#include <memory>       /// 使用智能指针，是为了在代码块内用new关键字创建的内存，当离开时，不用记住手动delete or delete[] 删除new创建的内存，而是由程序自动完成
///
/// 例如：





void auto_ptrTest(){
    using namespace std;
    auto_ptr<string> films[5] =
            {
                    auto_ptr<string> (new string("Fowl Balls")),
                    auto_ptr<string> (new string("Duck Walks")),
                    auto_ptr<string> (new string("Chicken Runs")),
                    auto_ptr<string> (new string("Turkey Errors")),
                    auto_ptr<string> (new string("Goose Eggs"))
            };

    /// auto_ptr<> 指针具有唯一性，会把原来的指针给剥夺，如果再次访问原来位置，会不安全，异常退出。
    /// auto_ptr<> 不要使用。
    auto_ptr<string> pwin;
    pwin = films[2];   // films[2] loses ownership

    cout << "The nominees for best avian baseball film are\n";
    for (int i = 0; i < 5; i++)
        cout << *films[i] << endl;
    cout << "The winner is " << *pwin << "!\n";
    // cin.get();

}


#endif //CPPGRAMMER_AUTO_PTR_H
