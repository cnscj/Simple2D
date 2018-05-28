/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-07 18:21:51 
 * @Brief: 字符串链
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-19 12:13:39
 * @Last Modified log: 
 */
#ifndef _SSTRINGLIST_H_
#define _SSTRINGLIST_H_
#include <iostream>
#include <list>
#include "SString.h"
class SStringList 
{
	friend ostream& operator <<(ostream&, SStringList&);
	friend istream& operator >>(istream&, SStringList&);
public:
	SStringList();
	SStringList(char ch);
	SStringList(SString &&str);
	SStringList(const SStringList &strlist);

	//
	SStringList &operator &= (const SStringList &stl);
    SStringList &operator |= (const SStringList &stl);
    SStringList operator & (const SStringList &stl) const;
    SStringList operator | (const SStringList &stl)const;
    SStringList &operator -= (const SStringList &stl);
    SStringList operator - (const SStringList &stl)const;
    SStringList &operator += (const SStringList &stl);
    SStringList operator + (const SStringList &stl)const;
    SStringList &operator =(const SStringList &strlist);
    bool operator == (const SStringList &stl)const;

	///
    SStringList &operator <<(const SString &&str);
    SStringList &operator <<(const SStringList &stl);


	int Find(SString str, int start = 0) const;

	SStringList Sublist(int start, int length = -1) const;

	SString &At(int index)const ;
	SString At(int index, SString defaultstr)const;

	SStringList &Distinct();

	SString ToString() const;

private:
    std::list<SString>     m_strList;
};

#endif