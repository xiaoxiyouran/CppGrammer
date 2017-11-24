//
// Created by xiaoxi on 2017/11/23.
//
#ifndef CPPGRAMMER_NEWC11STANDARD_H
#define CPPGRAMMER_NEWC11STANDARD_H

#include <iostream>
#include <array>            // for array
#include <initializer_list> // for std::initializer_list
#include <vector>           // for std::vector

namespace newstandard{
///--------------------------------------------------------------------------------------------------------------------------------------
/// 18.1.1 New type.
    /// new type added.
    /// long long , unsigned long long 64bit integer.
    /// char16_t,char32_t
    /// original string in chapter3.

///--------------------------------------------------------------------------------------------------------------------------------------
/// 18.1.2 Unified initialize.
    /// C11 used list to initialize
    /// Also avaliable to class initialize.
    class AnyCls{
    private:
        int a,b;
    public:
        AnyCls(int a,int b): a(a),b(b){}
    };

    void listInitialize(){
        int x{5}; // or x = {5}
        double y{1.2};
        short arr[5] {1,2,3,4,5};

//        char c1{1.57e27};     // compile error, not allowed to become narrow type, more safer.

        /// used in new expression
        int *ar = new int[4] {1,2,3,4};

        AnyCls ob1(1,2);    // cannot used AnyCls * obj; for initialize.
        AnyCls ob2{1,2};    // or ob2 = {1,2}
        AnyCls * ptr_obj1;
        ptr_obj1 = &ob1;    // valid
    }

    /// std::initialize_list for constructor or normal func.and this obj has begin() and end() member function.
    /// please remember the template.
    /// such as:
//    std::cout << newstandard::initializeList({1,2,3});
    double initializeList(std::initializer_list<int> lis){
        std::vector<int> a1(10);    // 10 elenments
        std::vector<int> a2{10};    // 1 element with value = 10
        std::vector<int> a3{4,6,1}; // in vector cls, there will be a constructor for std::initializer_list

        double tot = 0;
        for(auto p = lis.begin();p != lis.end();p++ )   tot+=*p;
        return tot;
    }

///--------------------------------------------------------------------------------------------------------------------------------------
/// 18.1.3 Declare.
    /// C11 used server ways to simplify the declare, especially for template.

    /// using auto
    void declareWithAuto(){
        auto maton = 112;
        auto pt = & maton;
        double fm(double ,int );
        auto pf = fm;   // double (*)(double,int), func pointer
        std::cout << pf(1,2) << std::endl;
    }
    double fm(double d,int d1) {return (d + d1);}   // must using {}

    /// decltype
    void delcareWithDecltype(){
        double x;
        int n;
        decltype(x*n) y;    // type of y is the same with the expression.
        decltype(&x) q;     // type of q is double *

        int j;
        const int &nn = j;
        decltype(nn) i1 = 0;     // const int &
//        decltype((j)) i2;       // rvalue of type int.  ???
    }

    /// decltype() function is very useful in template.
//    template <typename T,typename U>
//    auto ef(T t,U u) -> decltype( T*U ){      // ???
//        decltype(T*U) tu;
//        tu = t*u;
//        return tu;
//    };

    /// template alias.
    /// using  =
    typedef std::vector<std::string>::iterator itType;  // old usage.
    using itType2 = std::vector<std::string>;

    /// what's more, using can used template partial materialization.
    template <typename T>
    using arr12 = std::array<T,12>; // type is T, number of elements is 12.
    arr12 <double > a1;
    arr12 <std::string> a2;

    /// nullptr
    /// Previous, using 0 to stand for const pointer or integer.
    /// Now, recommend using nullptr,more safe, if you take 0 to a function(int) parameter.compiler will get the error ahead.
    /// But, both is valid still , nullptr == 0


///--------------------------------------------------------------------------------------------------------------------------------------
/// 18.1.4  Intelligent pointer.
    /// When new is used to allocate memory from heap(dui),when there is no need, it will auto delete to release memory.
    /// Previous, auto_ptr is available,abandoned now.
    /// NOw, unique_ptr,shared_ptr,weak_ptr

///--------------------------------------------------------------------------------------------------------------------------------------
/// 18.1.5  exception standard formula.
    class newExceptionStandard{
        /// Previous, Cpp used this way to denote these func will throw an exception,however it is abandoned now
        template <typename anyExceptionType>
        void willThrow(int) throw(anyExceptionType){};  // such as throw(bad_dog)
        void willThrow(long long)throw(){};

        /// Now, if there is no throw, please add noexcept key word to indicate.
        void noThrow() noexcept{};
    };

///--------------------------------------------------------------------------------------------------------------------------------------
/// 18.1.6  intra-area enum
    /// enum is used to define some constants.
    /// old form,enum belongs to its scope(inner cls, struct, or namespace,or even file),so there isnot two enum had the same name in the scope.
    /// c11 new add a kind of enum,defined by class or struct to overcome it .

    /// such as:
    //std::cout << newstandard::Old1::yes << std::endl;            // 0 converts to char,will be '',so used int
    //std::cout << (int)newstandard::New1::never << std::endl;    // if there no type converts,will be error,because there is no fucntion for operator<< func.
    //std::cout << (int)newstandard::New2::never << std::endl;
    enum Old1 {yes,no,maybe};   // old form.
    enum class New1 {never, sometimes,often,always};
    enum struct New2 {never,lever,sever};

///--------------------------------------------------------------------------------------------------------------------------------------
/// 18.1.7 Change for class.
    class newExplicitForConstructor{
    private:
        /// in-class initialize.
        int data = 0 ;
        double mem2{199.2}; // or double mem2 = {199.2}
        short mem3;

    public:

        newExplicitForConstructor(){};                  // default constructor for following init.
        newExplicitForConstructor(short s): mem3(s){};
        newExplicitForConstructor(int data, double mem2,short mem3) : data(data),mem2(mem2),mem3(mem3){};

        /// such as:
//        newstandard::newExplicitForConstructor a,b;
//        a = 5;              // implicit int to cls.
//        b = 0.5;            // not allowed.??? no error.
//        b = newstandard::newExplicitForConstructor(0.1);    // explicit double to cls
        newExplicitForConstructor(int){};               // implicit int to class
        explicit newExplicitForConstructor(double){}; // explicit double to class

        /// also in conversion function.
        /// such as:
//        int n = a;          // implicit conversion
//        double x = b;       // not allowed
//        x = double(b);      // explicit conversion
        operator int()const{
            return this->data;
        }
        explicit operator double()const{
            return this->data;
        }
    };


///--------------------------------------------------------------------------------------------------------------------------------------
 /// 18.1.8 模板和STL方面的修改

    class newFor{
    public:
        void newCharacteristic(){
            double prices[5] = {1,2,3,4,5};
            /// for loop based on scope, which can simplify the work for loop.
            for(double x: prices)    std::cout << x << std::endl;

            /// one more safe and simple way to deduce the type of var by auto.
            for( auto x: prices )    std::cout << x << std::endl;

            /// if you want to change the value. use &
            for( auto &x: prices )  x = std::rand();
        }
    };

    //// 新增的容器：forward_list(单向链表，只能沿一个方向遍历，比双向链表(list)简单，存储小)
    ////             unordered_map、unordered_multimap、unordered_set、unordered_multiset 都是使用哈希表实现的
    class newArray{
    public:
        void newCharacteristic(){
            /// new added template,fixed element type and numbers,but cannot change the size of container(no push_back func.) but there is begin,end func to realize althogrim based on scope.
            std::array<int,10> ar;  // array of 10 ints
//            for(auto &x: ar)
//                x = 1;
            for( std::array<int,10>::iterator it = ar.begin();it != ar.end();it++ ) // iterator can be replaced with auto.
                (*it) = 10;
            for( auto it = ar.begin();it !=ar.end();it++ )
                std::cout << *it << std::endl;
        }
    };


    /// 右值引用，为移动赋值做准备
    class RightValueRef{
    public:                     // must have,because default is private.
        /// 该函数主要是常见的几种引用的方式
        void generalReference(){
            int n;
            int &rn = n;        // 创建了一个n的引用

            int *pt = new int;
            int &rt = *pt;      // 为指针创建一个别名

            const  int b = 101; // b 不能再次赋值，但是可以创建b的引用
            const int & rb = b;
        }

        /// 以下是右值引用的一个例子
        /// 右值引用被存储到指定位置，可以获取该位置的地址
        inline double f(double tf) {return 5.0*(tf-32.0)/9.0;};
        void rightRef(){
            using namespace std;
            double tc = 21.5;
            double && rd1 = 7.07;
            double && rd2 = 1.8 * tc + 32.0;                                // 右值引用关联的是当前表达式计算的值，即使以后改变了tc的值，也不会影响到rd2
            double && rd3 = f(rd2);
            cout << " tc value and address: " << tc <<", " << &tc << endl;
            cout << "rd1 value and address: " << rd1 <<", " << &rd1 << endl;
            cout << "rd2 value and address: " << rd2 <<", " << &rd2 << endl;
            cout << "rd3 value and address: " << rd3 <<", " << &rd3 << endl;
            // cin.get();
        }
    };
}
#endif //CPPGRAMMER_NEWC11STANDARD_H
