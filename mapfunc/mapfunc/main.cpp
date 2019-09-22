//
//  main.cpp
//  mapfunc
//
//  Created by 慕寒 on 2019/9/22.
//  Copyright © 2019 慕寒. All rights reserved.
//

// 将函数指针缓存在map里

#include <iostream>
#include <map>

using namespace std;

void* helloFuncOne()
{
    cout << "Hello, World!\n";
    return NULL;
}

long helloFuncTwo(long x, long y)
{
    long ret = 0;
    ret = x + y;
    cout << "x + y = "<< ret <<endl;
    return ret;
}

int main(int argc, const char * argv[]) {

    // 缓存函数名，函数指针在map里
    map<string, long> func_name_ptr;
    
    //将函数指针缓存到map里
    func_name_ptr["func1"] = (long)&helloFuncOne;
    func_name_ptr["func2"] = (long)&helloFuncTwo;

    //调用函数指针func1
    typedef void* (*FUNC)();
    long fptr_one = func_name_ptr["func1"];
    if(fptr_one != 0)
    {
        cout << "fptr_one \n";
        //调用函数func1
        ((FUNC)fptr_one)();
    }
    
    //调用函数指针func2
    typedef long (*FUNCTWO)(long, long);
    long fptr_two = func_name_ptr["func2"];
    if(fptr_two != 0)
    {
        cout << "fptr_two \n";
        //调用函数func2
        long two_ret = ((FUNCTWO)fptr_two)(3, 7);
        cout << "two_ret = "<<two_ret <<endl;
    }
    
    return 0;
}

//PS: map的第二个参数为什么用了long型，而不是int型
//由于在XCode编译报错 Cast from pointer to smaller type 'int' loses information
//报错原因是：由于使用了强转将void*转为int，而在XCode上使用的为x64的编译，X64下的void*地址为8字节，而int为4字节，强转时会导致越界，故出现此错误。

