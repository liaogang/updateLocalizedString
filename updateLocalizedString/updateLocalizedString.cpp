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
#include <vector>
using namespace std;


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


bool parseLine(char *s,int len,vector<string> &ret)
{
    if (s==NULL)
        return false;
    
    char *curr=s;
    char *last=NULL;
    for (;curr <= s + len;curr++)
    {
        if (curr[0]=='"')
        {
            if (last==NULL)
            {
                last=curr;
            }
            else
            {
                ret.push_back(string(last+1,curr));
                last=NULL;
            }
        }
    }
    
    return last==NULL;
}


bool getLine(FILE *file,string &line)
{
    const int bufLen=1000;
    char buff[bufLen];
    char buff2[1]={'\0'};
    
    fread(buff, sizeof(char), bufLen  , file);
    
    char *p = strchr(buff, '\n');
    if (p)
    {
        line=string(buff,p);
        
        //point the next new line.
        p++;
        
        fseek(file, buff+ bufLen - p, SEEK_CUR);
        
        return true;
    }
    else
    {
        return false;
    }
    
    return  false;
}



/**
 @usage: exec [parent path of localized string files] [path of file where updated localized string stores]
*/
int main(int argc, const char * argv[])
{
    char *wd = (char*)argv[1];
    
    ///change current working directory.
    if(chdir(wd) == -1)
    {
       printf("error: change direcoty: %s\n",wd);
       printf("error number: %d\n", errno);
       return errno;
    }
    
    
    
   int arrayLanguageOrder[folderNum];
    vector<vector<string>> vecLocalizedStrings;
    
    
    
    
   char *filePathUpdate = (char*)argv[2];
    FILE *fileUpdate=fopen(filePathUpdate, "r");
    if (fileUpdate)
    {
        long fileSize=ftell(fileUpdate);
       
        
        ///parse language order
        string stringLanguageOrder;
        getLine(fileUpdate, stringLanguageOrder);
       
        char *languageOrder = (char*) stringLanguageOrder.c_str();
        
        char *beg=languageOrder;
        char *end;
        
        
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
        
        
        
        
        
        string line;
        while( !feof(fileUpdate) )
        {
            if( getLine(fileUpdate,line) )
                ///valid line?
                if (line.size()>10)
                {
                    cout<<line<<endl;
                    
                    
                    ///key "en" "fr" "zh-hans" ...
                    char *localizedStrings=(char*) line.c_str();
                    
                    char toFind = '"';
                    len = line.length();
                    beg = localizedStrings;
                    int numFind=0;

                    vector<string> vecLocalizedString;
                    
                    
                    if(!  parseLine(localizedStrings,len,vecLocalizedString) )
                    {
                        printf("can not parse string: %s\n",localizedStrings);
                    }

                    
                    
                }
        }
        
        
        fclose(fileUpdate);
    }
    
    
    
    
    
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
            
            
            
            fclose(file);
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
