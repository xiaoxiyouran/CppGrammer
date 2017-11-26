#智能指针
##1.为什么要用智能指针  
&nbsp;&nbsp;&nbsp;&nbsp;使用智能指针，主要是为了针对new关键字创建的内存，当程序离开代码块的时候，无论是自己忘了delete 释放内存还是由于异常中间退出而没有释放堆里的内存而造成的内存泄漏问题。

```cpp
void remodel(std:: string & str){
    std::string * ps(new std::string(str));    // 里面创建一个对象，然后返回
    ...
    if (weird_thing) // 如果有异常发生，将会造成内存泄漏
        throw exception;
    str = *ps;
    delete ps;
    return;
}

void remodel(std:: string & str){
    std::auto_ptr<std::string> ps(new std::string(str));    // 里面创建一个对象，然后返回
    ...
    if (weird_thing) // 如果有异常发生，将会造成内存泄漏
        throw exception;
    str = *ps;
    //delete ps;
    return;
}
```
##2.智能指针的使用方法  
&nbsp;&nbsp;&nbsp;&nbsp;所有智能指针类都有一个显示的构造函数,该构造函数用指针作参数。  
	
```cpp
	/// 赋值的方式
	share_ptr<double> pd;
	double *p_reg = new double;
	pd = shared_ptr<double>(p_reg);	//allowd,explicit conversion	pd = p_reg;							// not allowed,implicit conversion
	
	/// 用构造函数 
	shared_ptr<double> pshared = p_reg //not allowd,implicit conversion
	shared_ptr<double> pshared(p_reg) //allowd,explicit conversion
	*pshared 				 	     	 	// 解除引用
	ps - > 结构成员
	赋给指向相同类型的常规指针
	赋给另一个同类型的智能指针对象 	
	
```

程序要特别注意的是，智能指针只能用于指向堆内存创建的对象(new创建的)
如果是非堆内存会引起delete错误的（delete只能用于堆内存）
例如  
 
```cpp
string va("haha");
shared_ptr<string> ps(&va);		// illegal.
```

shared_ptr 是创建一个引用能赋新值，更安全，

 

