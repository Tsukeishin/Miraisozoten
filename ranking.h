//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : �����ޕ�
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "workHagiwara.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_CSV		_T("data/EXCEL_DATA/ranking.csv")	// �T���v���p�摜
#define RANKING_MAX			(6)								// �X�R�A�̍ő�l
#define BUFC_MAX			(1024)							// �X�R�A�̍ő�l
#define NAME_MAX			(5)								// ���O�̍ő�l

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RANKING
{
public:
	int			id;
	int			rank;
	int			score;
	long long	name[NAME_MAX][2];//���O���͂�(��������,�q��,�ꉹ)
};

//*****************************************************************************
// �񋓌^
//*****************************************************************************

enum
{
	RANKING_CSV_ID = 0,		// ID
	RANKING_CSV_RANK,		// ����
	RANKING_CSV_SCORE,		// �X�R�A
	RANKING_CSV_NAME,		//���O
	RANKING_CSV_MAX,
};

enum
{	// ����
	FIRST = 0,		//1��
	SECOND,			//2��
	THIRD,			//3��
	FOURTH,			//4��
	FIFTH,			//5��
	SIXTH,			//6��
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
RANKING *GetRanking(int no);
int GetRankingCnt(void);
void WriteRankingCsv(void);
void LoadRankingCsv(void);
void Ranking(void);
void DebugRank(void);

#endif