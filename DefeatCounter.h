//=============================================================================
//
// jvν [DefeatCounter.h]
// Author : vFθΑ
//
//=============================================================================
#ifndef _DEFEATCOUNTER_INCLUDE_H_
#define _DEFEATCOUNTER_INCLUDE_H_

//*****************************************************************************
// NXθ`
//*****************************************************************************
class DefeatCounter
{
private:
	int count;
	
public:
	DefeatCounter();

	void CountUp(void);
	int GetCount(void);
	void SetCount(int value);

};

//*****************************************************************************
// vg^CvιΎ
//*****************************************************************************
DefeatCounter *GetDefeatCounter(int no);
void InitDefeatCounter(void);
int GetAllDefeat(void);

#endif