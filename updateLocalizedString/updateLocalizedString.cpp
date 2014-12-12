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

enum enum_language
{
    language_English,
    language_German,
    language_Swedish,
    language_French,
    language_Dutch,
    language_Italian,
    language_Spanish,
    language_Danish,
    language_Finnish,
    language_Norwegian,
    language_Greek,
    language_Portuguese,
    language_Russian,
    language_Polish,
    language_Hungarian,
    language_Czech,
    language_Slovenian,
    language_Slovak,
    language_Romanian,
    language_Simple_Chinese,
    language_Korean,
    language_Japanese,
    language_Arabic,
    language_Turkish
};


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

/// return　'"' 是否是偶数个.
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
        for (unsigned char c = p[0];
             p[0]=='\n' || isspace(c) || iscntrl(c) ;
             p++,c=p[0]);
        
        
        return p;
    }
    
    return NULL;
}






/**
 @usage: exec [parent path of localized string files] [update]  [path of file where updated localized string stores]
 @usage: exec [parent path of localized string files] [delete] [string1,string2,...]
*/
void Usage()
{
    printf("usage: exec [directory] update [sourcefile]\n");
    printf("            [directory] delete [key1,key2,...]\n");
    
    printf("directory: parent path of `xx.lproj` folders\n");
    printf("sourcefile: file where updated localized string stores\n");
    printf("sourcefile example:\n\n\
          English   German     Swedish    French     Traditional Chinese\n\
\"fooKey\" \"fooEn\"   \"fooGer\"   \"fooSwd\"   \"fooFrh\"   \"照片..\"\n\
\"barKey\" \"barEn\"   \"barGer\"   \"barSwd\"   \"barFrh\"   \"图片..\"\n");

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
            bool bUpdateFileError = false;
            char *filePathUpdate = (char*)argv[3];
            FILE *fileUpdate=fopen(filePathUpdate, "r");
            if (fileUpdate)
            {
                printf("success open file: %s\n\n",filePathUpdate);
               
                size_t fileSize = fread( fileBuff, sizeof(char), fileBuffLen, fileUpdate);
                
                /// add a line break and a zero terminal in file buffer's end.
                if (fileBuff[fileSize-1]!='\n')
                    fileBuff[fileSize] ='\n';
                else
                    fileBuff[fileSize] ='\0';
                
                fileBuff[fileSize+1] ='\0';
                
                
                ///parse language order
                string stringLanguageOrder;
                
                char *lineBegins = getLine( fileBuff, stringLanguageOrder) ;
                
                char *languageOrder = (char*) stringLanguageOrder.c_str();
                
                char *beg=languageOrder;
                char *end = NULL;
                
                
                memset(arrayLanguageOrder, -1, sizeof(arrayLanguageOrder[0])*folderNum);
                
                int len = strlen(languageOrder);
                int languageCountInfile = 0;
                while (end <= languageOrder + len && beg <= languageOrder + len)
                {
                    while (!isLetter(beg[0]))
                        beg++;
                    
                    
                    end=beg;
                    while (isLetter(end[0]))
                        end++;
                    
                    
                    //int l = folderNum;
                    for (int i = 0; i < folderNum ; i++)
                    {
                        if(strncmp(language[i], beg , end - beg)==0)
                        {
                            languageCountInfile++;
                            printf("%d: %s\n", languageCountInfile ,language[i]);
                            arrayLanguageOrder[languageCountInfile-1]=i;
                            break;
                        }
                    }
                    
                    beg=end+1;
                }
               
                
                printf("\n~~~~~~total %d language finded.~~~~~\n\n", languageCountInfile);
                
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
                        //int numFind=0;
                        
                        vector<string> vecLocalizedString;
                        if( parseLine(localizedStrings,len,vecLocalizedString) )
                        {
                            int  sz = vecLocalizedString.size();
                            if ( sz != languageCountInfile + 1 ) //values + key.
                            {
                                printf("line error , strings number: %d not equal to : %d + 1\n",sz , languageCountInfile + 1 );
                                bUpdateFileError = true;
                            }
                            else
                            {
                                printf("new row added.\n");
                                
                                vecLocalizedStrings.push_back(vecLocalizedString);
                            }
                        }
                        else
                        {
                            printf("can not parse this row: %s\n",localizedStrings);
                            bUpdateFileError = true;
                        }
                        
                        
                    }
                }
                
                
                fclose(fileUpdate);
            }
            
            printf("%lu rows in update file.\n",vecLocalizedStrings.size());
            
            
            if (!bUpdateFileError && vecLocalizedStrings.size() > 0)
            {
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
                            //int lines=1;
                            
                            /// begin find the key and write the value.
                            bool keyValueWrited = false;
                            bool keyValueExist = false;
                            printf("~~~%s~~~\n",key.c_str());
                            char *keyBeg = fileBuff;
                            
                            while ( !keyValueExist && !keyValueWrited && (keyBeg = strstr(keyBeg, key.c_str()))  )
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
                                            if (strncmp(valueBeg, value.c_str(), valueLen) == 0)
                                            {
                                                printf("key value exist,skip this.\n");
                                                keyValueExist = true;
                                            }
                                            else
                                            {
                                                valueEnd++;
                                                
                                                ///replace  (valueBeg,valueEnd)  with value
                                                memmove( valueBeg + valueLen , valueEnd , fileBuff + fileSize - valueEnd);
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
                            
                            if ( !keyValueExist && !keyValueWrited )
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
        }
        else
        {
            ///user choose a command 'delete'.
            
            
            
        }
    }
    
    
    return 0;
}

