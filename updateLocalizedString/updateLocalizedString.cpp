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
    return isalpha(c);
}

///从后开始往前找
char *strrchr(char *beg,char *end,char c)
{
    char tmp=end[1];
    end[1]='\0';
    
    char *find = strrchr( beg , c);
    
    end[1]=tmp;
    
    return find;
}

char *strrchr(char *s,int sLen,char c)
{
    return strrchr(s , s + sLen , c);
}

///从后开始往前找
char *strrstr(char *beg, char *end,const char *find)
{
    char tmp=end[1];
    end[1]='\0';
    
    char *ret = strstr( beg, find);
    
    end[1]=tmp;
    
    return ret;
}

char *strrstr(char *s, int sLen,const char *find)
{
    return strrstr(s, s + sLen , find);
}





bool isInAnnoate(char * begin ,char *test , int testLen)
{
    char *lineBeg = strrchr( begin , test , '\n');
    
    char *lineAnnoate = strstr(lineBeg, "//");
    if ( lineAnnoate && lineAnnoate < test )
    {
        return true;
    }
    else
    {
        char *annoateBeg =strrstr(fileBuff , test, "/*");
        if (annoateBeg)
        {
            char *annoateEnd = strstr(annoateBeg ,"*/");
            if(  annoateEnd > test + testLen )
            {
                return true;
            }
        }
    }
    
    return false;
}











bool parseLine(char *s,int len,vector<string> &ret)
{
    if (s==NULL)
        return false;
    
    char *curr=s;
    char *last=NULL;
    
    char *annoate = strstr(s, "//");
    if (annoate && annoate < s + len) {
        len = annoate - s;
    }
    
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


/// return new line begins.
char * getLine(char *filebufPoint,string &line)
{
    char *p = strchr(filebufPoint, '\n');
    if (p)
    {
        line=string(filebufPoint,p);
        
        
        //point the next new line.
        while (p[0]=='\n')
            p++;
        
        
        return p;
    }
    
    return NULL;
}

/*
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
*/

///return where new line begins.
//char* getLine(char *strFileBuf , string &line)
//{
//    char *p = strchr(strFileBuf, '\n');
//    if (p)
//    {
//        line=string(strFileBuf,p);
//        
//        //point the next new line.
//        p++;
//    }
//
//    return p;
//}





/**
 @usage: exec [parent path of localized string files] [update]  [path of file where updated localized string stores]
 @usage: exec [parent path of localized string files] [delete] [string1,string2,...]
*/
void Usage()
{
    printf("usage: exec [directory] update [file]\n");
    printf("            [directory] delete [key1,key2,...]\n");
    
    printf("directory: parent path of `xx.lproj` folders\n");
    printf("file: file where updated localized string stores\n");
}

int main(int argc, const char * argv[])
{
    if (argc < 4)
    {
        Usage();
        return 0;
    }
    
    bool bUsageUpdate= (strcmp( "update", argv[2] ) == 0 );
    bool bUsageDelete= (strcmp( "delete", argv[2] ) == 0 );
    if ( !bUsageUpdate && !bUsageDelete )
    {
        Usage();
    }
    else
    {
        ///change current working directory.
        char *wd = (char*)argv[1];
        if(chdir(wd) == -1)
        {
            printf("error: change direcoty: %s\n",wd);
            printf("error number: %d\n", errno);
            return errno;
        }
        
        ///user choose a command 'update'.
        if (bUsageUpdate)
        {
            int arrayLanguageOrder[folderNum];
            vector<vector<string>> vecLocalizedStrings;
            
            
            
            ///parse the file where updated localized string stores
            char *filePathUpdate = (char*)argv[3];
            FILE *fileUpdate=fopen(filePathUpdate, "r");
            if (fileUpdate)
            {
                printf("success open file: %s\n",filePathUpdate);
               
                size_t fileSize = fread( fileBuff, sizeof(char), fileBuffLen, fileUpdate);
                
                ///parse language order
                string stringLanguageOrder;
                
                char *lineBegins = getLine( fileBuff, stringLanguageOrder) ;
                
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
                
                printf("\n");
                
                string line;
                while( ( lineBegins = getLine( lineBegins, line) ) )
                {
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
                        else
                        {
                            if (vecLocalizedString.size() != wordIndex + 1 +1 )
                                printf("line error");
                            else
                                printf("new row added.\n");
                        }
                        
                        vecLocalizedStrings.push_back(vecLocalizedString);
                    }
                }
                
                
                fclose(fileUpdate);
            }
            
            printf("%lu rows in update file.\n",vecLocalizedStrings.size());
            
            
            
            ///parse file xx.lproj/Localizable.strings .
            
            ///ignore the notes in code.
            
            FILE **fileArrays=new FILE*[folderNum];
            
            for (int i =0 ; i < folderNum; i++)
            {
                char folderName[MAXPATHLEN];
                strcat( strcpy(folderName, arrFolderName[arrayLanguageOrder[i] ] ) ,".lproj/Localizable.strings");
                
               printf("\n");
                
                FILE *file=fopen( folderName , "r");
                if (file)
                {
#ifdef DEBUG
                    memset(fileBuff, 0 , fileBuffLen);
#endif
                    
                    fileArrays[i]=file;
                    printf("success open file: %s\n",folderName);
                    printf("parse language: %s\n", language[arrayLanguageOrder[i]]);
                    
                    fseek(file, 0, SEEK_END);
                    long fileSize = ftell(file);
                    fseek(file, 0L, SEEK_SET);
                    
                    if (fileSize + 600 > fileBuffLen ) {
                        printf("file is too large: %s\n",folderName);
                    }
                   
                    int readed = fread(fileBuff, sizeof(char), fileBuffLen , file);
                    
                    bool isDirty = false;
                    
                    /// add two empty line in file end.
                    int lineWillAdd = 2;
                    if(fileBuff[fileSize -1 ] =='\n')
                        lineWillAdd--;
                    if(fileBuff[fileSize -2 ] =='\n')
                        lineWillAdd--;
                    
                    while(lineWillAdd>0)
                    {
                        fileBuff[fileSize]='\n';
                        fileSize++;
                        isDirty = true;
                        lineWillAdd--;
                    }
                    
                    /// add a zero terminal in file buffer's end.
                    fileBuff[fileSize ]='\0';
                    

                    
                    
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
                        
                        /// begin find the key and write the value.
                        bool keyValueWrited = false;
                        printf("~~~%s~~~\n",key.c_str());
                        char *keyBeg = fileBuff;
                        
                        while ( (keyBeg = strstr(keyBeg, key.c_str()))  )
                        {
                            ///@todo: make sure the finded key is not a value...
                            bool isKeyAValue = false;
                            
                            /// the finded key is in a annotate?
                            bool isKeyInAnnoate = isInAnnoate(fileBuff,keyBeg,keyLen);
                            
                            if (isKeyInAnnoate || isKeyAValue )
                            {
                                keyBeg+=keyLen;
                                continue;
                            }
                            else
                            {
                                char *valueBeg= strchr(keyBeg+keyLen+1, '"' );
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
                                            memmove( valueBeg + valueLen +1 , valueEnd , fileBuff + fileSize - valueEnd);
                                            memcpy(valueBeg, value.c_str() , valueLen );
                                            fileSize += valueLen - (valueEnd - valueBeg);
                                            isDirty=true;
                                            keyValueWrited = true;
                                            string temp(keyBeg,valueEnd);
                                            printf("replace %s with %s \n",temp.c_str(),value.c_str() );
                                        }
                                    }
                                }
                            }
                            
                            keyBeg += keyLen;
                        }
                        
                        if ( !keyValueWrited )
                        {
                            ///add to end then.
                            memcpy(fileBuff + fileSize , key.c_str() , keyLen );
                            fileSize+= keyLen;
                           
                            fileBuff[fileSize]='=';
                            fileSize++;
                            
                            memcpy(fileBuff + fileSize , value.c_str() , valueLen);
                            fileSize+=valueLen;
                            
                            fileBuff[fileSize]=';';
                            fileBuff[fileSize+1]='\n';
                            fileSize+=2;
                            
                            ///add a zero terminal so the c-str function work correctly.
                            fileBuff[fileSize]='\0';
                            
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
        }
        else
        {
            ///user choose a command 'delete'.
            
            
            
        }
    }
    
    
    return 0;
}

