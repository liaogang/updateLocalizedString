//
//  main.cpp
//  updateLocalizedString
//
//  Created by liaogang on 14/11/11.
//  Copyright (c) 2014年 gang.liao. All rights reserved.
//

#include <iostream>
#include <sys/param.h>//MAXPATHLEN
 #include <unistd.h> //chdir



const char *language[]=
{
    "English",	"German",           "Swedish",              "French",
    "Dutch",	"Italian",          "Spanish",              "Danish",
    "Finnish",	"Norwegian",        "Greek",                "Portuguese",
    "Russian",	"Polish",           "Hungarian",            "Czech",
    "Slovenian","Slovak",           "Romanian",             "Simple Chinese",
    "Korean",   "Japanese",         "Arabic",	            "Turkish"
    /*"Traditional Chinese"*/
    /*"Croatian",*/
    /*"Bulgarian",*/
};

const char *arrFolderName[] =
{
    "en","de","sv","fr",
    "nl","it","es","da",
    "fi","nb","el","pt",
    "ru","pl","hu","cs",
    "sl","sk","ro","zh-Hans",
    "ko","ja","ar","tr"
};

const int folderNum = sizeof(arrFolderName)/sizeof(arrFolderName[0]);

///是否是字母
bool isLetter(char c)
{
    return (c >= 'a' && c <= 'z' ) ||
           (c >= 'A' && c <= 'Z' ) ;
}

int main(int argc, const char * argv[])
{
    char *wd = (char*)argv[1];
    
    wd = (char*) "/Users/liaogang/GenieForIOS-NEWDLNA2/GenieForiOS2014_6_4/GenieForiOS-NewDLNA/GenieforiOS_2.0.45/1.0/GenieiPad/GenieiPad/GenieiPad";
    
    ///change current working directory.
    if(chdir(wd) == -1)
    {
       printf("error: change direcoty: %s\n",wd);
       printf("error number: %d\n", errno);
       return errno;
    }
    
    
    
    ///parse language order
    char *languageOrder = (char*)
     " 	English	German	Swedish	French	Dutch	Italian	Spanish	Danish	Finnish	Norwegian	Greek	Portuguese	Russian	Polish	Hungarian	Czech	Slovenian	Slovak	Romanian	Bulgarian	Croatian	Simple Chinese	Korean	Japanese	Arabic	Turkish	Traditional Chinese"
    ;
    
    char *beg=languageOrder;
    char *end;
   
    int arrayLanguageOrder[folderNum];
    memset(arrayLanguageOrder, -1, sizeof(arrayLanguageOrder[0])*folderNum);
    
    int len = strlen(languageOrder);
    int wordIndex=0;
    while (end <= languageOrder + len && beg <= languageOrder + len)
    {
        while (!isLetter(beg[0])) {
            beg++;
        }
        
        end=beg;
        while (isLetter(end[0])) {
            end++;
        }
        
        int l = folderNum;
        for (int i = 0; i < folderNum ; i++)
        {
            if(strncmp(language[i], beg , end - beg)==0)
            {
                printf("%d: %s\n", wordIndex ,language[i]);
                arrayLanguageOrder[wordIndex]=i;
                wordIndex++;
                break;
            }
        }
        
        beg=end+1;
    }
    
    
    ///print it.
//    for (int i = 0; i < folderNum ; i++)
//    {
//        if (arrayLanguageOrder[i]==-1)
//            continue;
//        
//        printf("%d: language: %s\n", i ,language[arrayLanguageOrder[i]]);
//    }
    
    
    
    
    
    
    ///parse file
    
    ///ignore the notes in code.
    
    FILE **fileArrays=new FILE*[folderNum];
    
    for (int i =0 ; i < folderNum; i++)
    {
        char folderName[MAXPATHLEN];
        strcat( strcpy(folderName, arrFolderName[i]) ,".lproj/Localizable.strings");

        FILE *file=fopen( folderName , "w");
        if (file)
        {
            fileArrays[i]=file;
            printf("success: open file: %s\n",folderName);
            
            
        }
        else
        {
            printf("failed: open file: %s\n",folderName);
            printf("error number: %d\n", errno);
            return errno;
        }
    }
    
    
    
    
    return 0;
}
