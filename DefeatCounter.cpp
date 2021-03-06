//=============================================================================
//
// jvν [DefeatCounter.cpp]
// Author : vFθΑ
//
//=============================================================================
#include "DefeatCounter.h"

#include "enemyRE.h"

//*****************************************************************************
// NXθ`
//*****************************************************************************
DefeatCounter::DefeatCounter()
{
	this->count = 0;
}

void DefeatCounter::CountUp(void)
{
	this->count++;
}

int DefeatCounter::GetCount(void)
{
	return this->count;
}

void DefeatCounter::SetCount(int value)
{
	this->count = value;
}

//*****************************************************************************
// O[oΟ
//*****************************************************************************
DefeatCounter DefeatCounterWk[E_TYPE_MAX];

//=============================================================================
// ϊ»
//=============================================================================
void InitDefeatCounter(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);

	for (int i = 0; i < E_TYPE_MAX; i++)
	{
		(DefeatCounter + i)->SetCount(0);
	}
}

//=============================================================================
// ζΎ
//=============================================================================
DefeatCounter *GetDefeatCounter(int no)
{
	return &DefeatCounterWk[no];
}

//=============================================================================
// ζΎijaj
//=============================================================================
int GetAllDefeat(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);
	int value = 0;
	for (int i = 0; i < E_TYPE_MAX; i++)
	{
		value += (DefeatCounter + i)->GetCount();
	}
	
	return value;
}