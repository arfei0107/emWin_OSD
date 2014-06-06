#ifndef __GammaFormula_H__
#define __GammaFormula_H__

typedef short WORD;
typedef unsigned char  BYTE;

int SetGammaPoint(int x, int value);
int GetGammaPoint(int x);
const WORD* GetGammaTable(int *TableSize);
int GetGammaPointX_byIndex(int Index);

#endif


