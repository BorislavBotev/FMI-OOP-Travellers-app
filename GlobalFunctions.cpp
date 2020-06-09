#include "GlobalFunctions.hpp"
void createString(char*&des,const char*src)
{
    des=new char[strlen(src)+1];
    strcpy(des,src);
}

int extractNumberFromString(const char*arr,int& startingIndex)
{
    int number=0;
    while(arr[startingIndex]>='0' && arr[startingIndex<='9'])
    {
        number*=10;
        number+=(arr[startingIndex]-'0');
        startingIndex++;
    }
    return number;
}
void extractWordFromInput(char*&text,const char*input,int&startingIndex)
{
    int start=startingIndex;
    if(!input)
    {
        return;
    }
    while(input[startingIndex]>='a' && input[startingIndex]<='z')
    {
        startingIndex++;
    }
    createSubString(text,input,start,(startingIndex-1));
}
void createSubString(char*&name,const char*input,int start,int finish)
{
    int length=finish-start+1;
    name=new char[length+1];
    int i=0;
    for(; i<length; i++)
    {
        name[i]=input[start++];
    }
    name[i]='\0';
}

char* createFileNameFromUsername(const char*name)
{
    if(!name)
    {
        return NULL;
    }
    int s=strlen(name)+4;
    char*fName=new char[s];
    //fName[0]='"';
    //fName[1]='\0';
    fName=strcat(fName,name);
    fName=strcat(fName,".db");
    //fName[s-2]='"';
   // fName[s-1]='\0';
    return fName;
}
