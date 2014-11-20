//
//  main.cpp
//  test
//
//  Created by liaogang on 14/11/20.
//  Copyright (c) 2014年 gang.liao. All rights reserved.
//

#include <iostream>
#include "uncTable.h"

void testUncTableFunc()
{
//    const char *test="حدث خطأ غير متوقع.";
    const char *test="حدثخطأغيرمتوقع\t邓紫棋Δενυπάρχειαρκετόςχώροςαποθήκευσης";
    int len = sizeof(test)/sizeof(test[0]);
    
    
    uncTableConvert(test,len);
}




int main(int argc, const char * argv[])
{
    testUncTableFunc();
    
    
    return 0;
}
