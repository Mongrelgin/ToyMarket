#if !defined _MSTRING_
  #define _MSTRING_
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
//#include <conio.h>
//#include <iostream.h>
using namespace std;
class MString
{
    private:
  char * str;
  int len;
    public:
  MString(void);
  MString(const char * s);
  MString(const MString &s);
  ~MString(void);
  MString operator +(const MString &s2);
  MString operator =(const MString &s2);
  int operator >(const MString &s2)const;
  int operator <(const MString &s2)const;
  int operator >=(const MString &s2)const;
  int operator <=(const MString &s2)const;
  int operator ==(const MString &s2)const;
  int operator !=(const MString &s2)const;
  char* RetStr(void);
  const char* RetPntr(void);
  friend std::ostream & operator<<(std::ostream &s, const MString &x);
};

MString::MString(void)
{
  len=0;
  str=new char[1];
  str[0]='\0';
}

MString::MString(const char * s)
{
  len=strlen(s);
  str=new char[len+1];
  strcpy(str, s);
}

MString::MString(const MString &s)
{
  len=s.len;
  str=new char[len+1];
  strcpy(str, s.str);
}

MString::~MString(void)
{
  delete[] str;
}

MString MString::operator +(const MString &s2)
{
  MString s;
  delete[] s.str;
  s.len=len+s2.len;
  s.str=new char[s.len+1];
  strcpy(s.str, str);
  strcat(s.str, s2.str);
  return s;
}

MString MString::operator =(const MString &s2)
{
  len=s2.len;
  delete[] str;
  str=new char[len+1];
  strcpy(str, s2.str);
  return *this;
}

int MString::operator >(const MString &s2)const
{
  if(strcmp(str,s2.str)>0)
    return 1;
  return 0;
}

int MString::operator <(const MString &s2)const
{
  if(strcmp(str,s2.str)<0)
    return 1;
  return 0;
}

int MString::operator >=(const MString &s2)const
{
  if(strcmp(str,s2.str)>=0)
    return 1;
  return 0;
}

int MString::operator <=(const MString &s2)const
{
  if(strcmp(str,s2.str)<=0)
    return 1;
  return 0;
}

int MString::operator ==(const MString &s2)const
{
  return !strcmp(str,s2.str);
}

int MString::operator !=(const MString &s2)const
{
  return strcmp(str,s2.str);
}

std::ostream & operator<<(std::ostream & s, const MString & x)
{
	return s << x.str;
}

char* MString::RetStr(void)
{
  char* s=new char[len+1];
  if(s)
    strcpy(s,str);
  return s;
}

const char* MString::RetPntr(void)
{
  return str;
}

#endif
