#include "Photo.hpp"
Photo::~Photo()
{
    delete[]name;
}
Photo::Photo(const char*n):name(NULL)
{
    if(!isValidFileName(n))
    {
        throw MyException("Only letters and '_' with no space, only jpeg and png extensions");
    }
    createString(name,n);
}
bool Photo::isValidFileName(const char*name)
{
    if(!name)
    {
        return false;
    }
    int len=strlen(name);
    if(len==0)
    {
        return false;
    }
    int i=0;
    while(name[i]!='\0' && name[i]!='.')
    {
        if(!isPhotoFileLetter(name[i++]))
        {
            return false;
        }
    }
    if(name[i++]!='.')
    {

        return false;
    }
    char*fExtentsion=NULL;
    extractWordFromInput(fExtentsion,name,i);
    if(fExtentsion==NULL || name[i]!='\0')
    {

        return false;
    }
    for(int index=0; index<FILE_EXTENSIONS_COUNT; index++)
    {
        if(strcmp(FILE_EXTENSIONS[index],fExtentsion)==0)
        {
            return true;
        }
    }
    return false;
}

bool Photo::isPhotoFileLetter(char l)
{
    return (l>='a' && l<='z') || (l>='A' && l<='Z') || l=='_';
}
const char* Photo::getName() const
{
    return name;
}
std::ostream& operator<<(std::ostream& os, Photo const& p)
{
    return os<<p.getName()<<std::endl;
}

