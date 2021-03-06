#include "voicetank.h"
#include "Library\Input.h"
#include "Library\/DebugProcess.h"
#include "MicTest.h"
#include "UIBonus.h"

#define VTG_MAX (1000)
#define VTG_ARG (30)

static Vector2 vtPosi   = Vector2(95, 550);
static float   vtScale  = 0.8f;
static float   vtValue  = 0.0f;
static int     vtVolume = 0;
static int     vtArg[VTG_ARG] = { 0 };

static Vector2 vtsBack = Vector2(70, 160);
static Vector2 vtsTank = Vector2(100, 200);

int VoiceTankUI::GetVoiceVolume()
{
	return vtVolume;
}

void VoiceTankUI::Init()
{
	CEnergyTankUI::Initialize();
	MicTestInit();
	this->CEnergyTankUI::Init(95 * SCREEN_SCALE, 550 * SCREEN_SCALE, 8 * SCREEN_SCALE, 8 * SCREEN_SCALE, 1000);
}

void VoiceTankUI::Update()
{
	if (GetKeyboardTrigger(DIK_V))
	{
		if (GetKeyboardPress(DIK_LSHIFT))
		{
			MicReStart();
		}
	}

	int sum = 0;
	vtArg[VTG_ARG - 1] = (int)Absolute(MicTest()) / 10;	// 10 = 値の調整 (音量値60〜3000間)
	if (vtArg[VTG_ARG - 1] < VoiceVolumeMIN)
	{
		vtArg[VTG_ARG - 1] = 0;
	}
	else if (GetFiver())
	{// フィーバー中発声時->MAX
		vtArg[VTG_ARG - 1] = 3000;
	}

	for (int i = 0; i < VTG_ARG - 1; i++)
	{
		vtArg[i] = vtArg[i + 1];
		sum += vtArg[i];
	}
	vtVolume = sum / VTG_ARG;

#ifdef _DEBUG
	if (IsMouseLeftPressed()) vtVolume += (int)GetMouseY();
	if (IsMouseCenterPressed()) vtPosi += Vector2((float)GetMouseX(), (float)GetMouseY());
	vtScale += (float)GetMouseZ() / 1200.0f;
#endif // _DEBUG

	if (vtVolume <       0) vtVolume =       0;
	if (vtVolume > VTG_MAX) vtVolume = VTG_MAX;

	this->SetValue((float)vtVolume);
	PrintDebugProcess("声のヴァリュー : %d\n", vtVolume);
}

void VoiceTankUI::Uninit()
{
	MicTestUninit();
	CEnergyTankUI::Uninitialize();
}


