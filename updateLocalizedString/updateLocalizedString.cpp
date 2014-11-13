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

const int fileBuffLen = 500000;
char fileBuff[fileBuffLen];

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
                ret.push_back(string(last,curr+1));
                last=NULL;
            }
        }
    }
    
    return last==NULL;
}

long findKey(FILE *file,string key);
bool getLine(FILE *file,string &line)
{
    const int bufLen=2000;
    char buff[bufLen];
    
    int readed = fread(buff, sizeof(char), bufLen - 2  , file);
    if (readed == 0)
        return false;
    
    buff[readed+1]='\n';
    buff[readed+2]='\0';
    
    char *p = strchr(buff, '\n');
    if (p)
    {
        line=string(buff,p);
        
        
        //point the next new line.
        while (p[0]=='\n')
            p++;
        
        fseek(file,  (p - buff) - readed , SEEK_CUR);
        
        return true;
    }
    
    return  true;
}


///return where new line begins.
char* getLine(char *strFileBuf , string &line)
{
    char *p = strchr(strFileBuf, '\n');
    if (p)
    {
        line=string(strFileBuf,p);
        
        //point the next new line.
        p++;
    }

    return p;
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
    
    
    
    ///parse the file where updated localized string stores
    char *filePathUpdate = (char*)argv[2];
    FILE *fileUpdate=fopen(filePathUpdate, "r");
    if (fileUpdate)
    {
        ///parse language order
        string stringLanguageOrder;
        getLine(fileUpdate, stringLanguageOrder);
       
        char *languageOrder = (char*) stringLanguageOrder.c_str();
        
        char *beg=languageOrder;
        char *end = NULL;
        
        
        memset(arrayLanguageOrder, -1, sizeof(arrayLanguageOrder[0])*folderNum);
        
        int len = strlen(languageOrder);
        int wordIndex=0;
        while (end <= languageOrder + len && beg <= languageOrder + len)
        {
            while (!isLetter(beg[0]))
                beg++;
            
            
            end=beg;
            while (isLetter(end[0]))
                end++;
            
            
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
        


        
        string line;
        while( !feof(fileUpdate) )
        {
            if( getLine(fileUpdate,line) )
            {
                //printf("%s\n",line.c_str());
                
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
                    
                    vecLocalizedStrings.push_back(vecLocalizedString);
                }}
        }
        
        
        fclose(fileUpdate);
    }
    
    
    
    
    
    ///parse file xx.lproj/Localizable.strings .
    
    ///ignore the notes in code.
    
    FILE **fileArrays=new FILE*[folderNum];
    
    for (int i =0 ; i < folderNum; i++)
    {
        char folderName[MAXPATHLEN];
        strcat( strcpy(folderName, arrFolderName[arrayLanguageOrder[i] ] ) ,".lproj/Localizable.strings");

        FILE *file=fopen( folderName , "r");
        if (file)
        {
            fileArrays[i]=file;
            printf("success: open file: %s\n",folderName);
            
            fseek(file, 0, SEEK_END);
            long fileSize = ftell(file);
            fseek(file, 0L, SEEK_SET);
            
            if (fileSize > fileBuffLen ) {
                printf("file is too large: %s\n",folderName);
            }
            
            bool isDirty = false;
            int readed = fread(fileBuff, sizeof(char), fileBuffLen , file);
            int ll = vecLocalizedStrings.size();
            for (int j = 0; j < ll; j++)
            {
                vector<string> veckeyValues = vecLocalizedStrings[j];
                
                string key=veckeyValues[0];
                string value = veckeyValues[i+1];
                
                
                
                int keyLen=key.length();
               int valueLen = value.length();
                string line;
                int lines=1;
                
                ///add a empty line in file end.
                if (fileBuff[fileSize]!='\n')
                    fileBuff[fileSize+1]='\n';
                /*
                char *lineBeg=fileBuff;
                char *lineEnd=NULL;
                
                lineEnd = strchr(lineBeg, '\n');
                while(lineEnd[0] =='\n')
                {
                    lineEnd++;
                    lines++;
                }
                */
                
                printf("~~~%s~~~\n",key.c_str());
                char *keyBeg= strstr(fileBuff, key.c_str());
                if ( keyBeg )
                {
                    char *lineBeg = strrchr(keyBeg, '\n');
                    char *noteBeg = strstr(lineBeg, "//");
                    char *noteBeg2 =strstr(lineBeg, "/*");
                    
                    if ( (noteBeg && noteBeg < keyBeg ) ||
                        ( noteBeg2 && noteBeg2 < keyBeg ) )
                    {
                        //
                    }
                    
                    char *valueBeg= strchr(keyBeg+keyLen+2, '"' );
                    if (valueBeg )
                    {
                        char *valueEnd = strchr(valueBeg + 1 , '"');
                        if (valueEnd )
                        {
                            //value beg ~ valueEnd == value ?
                            if (strncmp(valueBeg, value.c_str(), valueLen) != 0)
                            {
                                valueEnd++;
                                
                                ///replace  (valueBeg,valueEnd)  with value
                                memmove( valueBeg + valueLen , valueEnd, fileBuff + fileSize - valueEnd);
                                memcpy(valueBeg, value.c_str() , valueLen );
                                fileSize += valueLen - (valueEnd - valueBeg);
                                isDirty=true;
                                string temp(keyBeg,valueEnd);
                                printf("replace %s with %s \n",temp.c_str(),value.c_str() );
                            }
                        }
                    }
                    
                    
                }
                else
                {
                    ///add to end then.
                    memcpy(fileBuff + fileSize , key.c_str() , keyLen );
                    fileSize+= keyLen;
                    
                    memcpy(fileBuff + fileSize , "=" , 1);
                    fileSize++;
                    
                    memcpy(fileBuff + fileSize , value.c_str() , valueLen);
                    fileSize+=valueLen;
                    
                    fileBuff[fileSize+1]='\n';
                    fileSize++;
                    
                    isDirty = true;
                    
                    printf("add line:  %s = %s \n", key.c_str(), value.c_str() );
                }
            }
            
            fclose(file);
            
            //write back if data is changed.
            if (isDirty)
            {
                FILE *file2=fopen( folderName , "w");
                if (file2)
                {
                    fwrite(fileBuff, sizeof(char), fileSize , file2);
                    printf("write data back to file: %s\n",folderName);
                    fclose(file2);
                }
            }
            
            
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

