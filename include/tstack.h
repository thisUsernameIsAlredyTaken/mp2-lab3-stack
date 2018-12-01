#ifndef __STACK_H__
#define __STACK_H__

#include "tdataroot.h"

class TStack :public TDataRoot
{
private:
	int top; 
public:
    TStack(int Size = DefMemSize);
    ~TStack() {};
	void Put(const TData &Val); 
	TData Get();
	virtual TData TopElem() const; 

	int IsValid();
    void Print();
};

#endif