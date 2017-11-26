//
// Created by Cookie on 2017/11/26.
//

#ifndef CPPGRAMMER_SHARED_PTR_H
#define CPPGRAMMER_SHARED_PTR_H

// fowlsp.cpp  -- shared_ptr a good choice
#include <iostream>
#include <string>
#include <memory>

void shared_ptrTest(){
    using namespace std;
    shared_ptr<string> films[5] =
            {
                    shared_ptr<string> (new string("Fowl Balls")),
                    shared_ptr<string> (new string("Duck Walks")),
                    shared_ptr<string> (new string("Chicken Runs")),
                    shared_ptr<string> (new string("Turkey Errors")),
                    shared_ptr<string> (new string("Goose Eggs"))
            };

    /// 使用shared_ptr 是共享一个指针，两者都能访问，是比较安全的。
    shared_ptr<string> pwin;
    pwin = films[2];   // films[2], pwin both point to "Chicken Runs"

    cout << "The nominees for best avian baseball film are\n";
    for (int i = 0; i < 5; i++)
        cout << *films[i] << endl;
    cout << "The winner is " << *pwin << "!\n";
    // cin.get();
}

#endif //CPPGRAMMER_SHARED_PTR_H
