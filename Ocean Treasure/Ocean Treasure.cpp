#include "framework.h"
#include "Ocean Treasure.h"
#include <mmsystem.h>
#include <d2d1.h>
#include <dwrite.h>
#include "D2BMPLOADER.h"
#include "gifresizer.h"
#include "ErrH.h"
#include "FCheck.h"
#include "Ocean.h"
#include <chrono>
#include <clocale>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2bmploader.lib")
#pragma comment(lib, "gifresizer.lib")
#pragma comment(lib, "errh.lib")
#pragma comment(lib, "fcheck.lib")
#pragma comment(lib, "ocean.lib")

constexpr wchar_t bWinClassName[]{ L"PIRATEs" };
constexpr char tmp_file[]{ ".\\res\\data\\temp.dat" };
constexpr wchar_t Ltmp_file[]{ L".\\res\\data\\temp.dat" };
constexpr wchar_t sound_file[]{ L".\\res\\snd\\main.wav" };
constexpr wchar_t help_file[]{ L".\\res\\data\\help.dat" };
constexpr wchar_t record_file[]{ L".\\res\\data\\record.dat" };
constexpr wchar_t save_file[]{ L".\\res\\data\\save.dat" };

constexpr int mNew{ 1001 };
constexpr int mSpeed{ 1002 };
constexpr int mExit{ 1003 };
constexpr int mSave{ 1004 };
constexpr int mLoad{ 1005 };
constexpr int mHoF{ 1006 };

constexpr int first_record{ 2001 };
constexpr int no_record{ 2002 };
constexpr int record{ 2003 };

WNDCLASS bWinClass{};
HINSTANCE bIns{ nullptr };
HICON bIcon{ nullptr };
HCURSOR bCursor{ nullptr };
HCURSOR outCursor{ nullptr };
HMENU bBar{ nullptr };
HMENU bMain{ nullptr };
HMENU bStore{ nullptr };
HWND bHwnd{ nullptr };
HDC PaintDC{ nullptr };
PAINTSTRUCT bPaint{};
POINT cur_pos{};
MSG bMsg{};
BOOL bRet{ 0 };

D2D1_RECT_F b1Rect(50.0f, 10.0f, scr_width / 3.0f - 50.0f, 40.0f);
D2D1_RECT_F b2Rect(scr_width / 3.0f, 10.0f, scr_width * 2.0f / 3.0f - 50.0f, 40.0f);
D2D1_RECT_F b3Rect(scr_width * 2.0f / 3.0f, 10.0f, scr_width - 50.0f, 40.0f);

D2D1_RECT_F b1TxtRect(80.0f, 15.0f, scr_width / 3.0f - 50.0f, 40.0f);
D2D1_RECT_F b2TxtRect(scr_width / 3.0f + 30.0f, 15.0f, scr_width * 2.0f / 3.0f - 50.0f, 40.0f);
D2D1_RECT_F b3TxtRect(scr_width * 2.0f / 3.0f + 20.0f, 15.0f, scr_width - 50.0f, 40.0f);

int speed = 1;
int score = 0;

float scale_x{ 0 };
float scale_y{ 0 };

bool pause = false;
bool show_help = false;
bool sound = true;
bool in_client = true;
bool b1Hglt = false;
bool b2Hglt = false;
bool b3Hglt = false;
bool name_set = false;

wchar_t current_player[16]{ L"TARLYO" };

dll::RANDIT RandIt{};

ID2D1Factory* iFactory{ nullptr };
ID2D1HwndRenderTarget* Draw{ nullptr };

ID2D1RadialGradientBrush* b1BckgBrush{ nullptr };
ID2D1RadialGradientBrush* b2BckgBrush{ nullptr };
ID2D1RadialGradientBrush* b3BckgBrush{ nullptr };

ID2D1SolidColorBrush* statBrush{ nullptr };
ID2D1SolidColorBrush* txtBrush{ nullptr };
ID2D1SolidColorBrush* hgltBrush{ nullptr };
ID2D1SolidColorBrush* inactBrush{ nullptr };

IDWriteFactory* iWriteFactory{ nullptr };
IDWriteTextFormat* nrmFormat{ nullptr };
IDWriteTextFormat* midFormat{ nullptr };
IDWriteTextFormat* bigFormat{ nullptr };

ID2D1Bitmap* bmpArmor{ nullptr };
ID2D1Bitmap* bmpLogo{ nullptr };
ID2D1Bitmap* bmpGold{ nullptr };
ID2D1Bitmap* bmpGun{ nullptr };
ID2D1Bitmap* bmpIsland{ nullptr };
ID2D1Bitmap* bmpLoose{ nullptr };
ID2D1Bitmap* bmpPort{ nullptr };
ID2D1Bitmap* bmpRecord{ nullptr };
ID2D1Bitmap* bmpRock1{ nullptr };
ID2D1Bitmap* bmpRock2{ nullptr };
ID2D1Bitmap* bmpRock3{ nullptr };
ID2D1Bitmap* bmpTreasure{ nullptr };
ID2D1Bitmap* bmpWin{ nullptr };
ID2D1Bitmap* bmpCannonBall{ nullptr };
ID2D1Bitmap* bmpShipWreck{ nullptr };

ID2D1Bitmap* bmpBoatD{ nullptr };
ID2D1Bitmap* bmpBoatU{ nullptr };
ID2D1Bitmap* bmpBoatL{ nullptr };
ID2D1Bitmap* bmpBoatR{ nullptr };

ID2D1Bitmap* bmpBoatDR{ nullptr };
ID2D1Bitmap* bmpBoatDL{ nullptr };
ID2D1Bitmap* bmpBoatUR{ nullptr };
ID2D1Bitmap* bmpBoatUL{ nullptr };

ID2D1Bitmap* bmpIntro[7]{ nullptr };
ID2D1Bitmap* bmpOcean[5]{ nullptr };
ID2D1Bitmap* bmpSwirl[12]{ nullptr };

ID2D1Bitmap* bmpEvil1UL[6]{ nullptr };
ID2D1Bitmap* bmpEvil1UR[6]{ nullptr };
ID2D1Bitmap* bmpEvil1DL[6]{ nullptr };
ID2D1Bitmap* bmpEvil1DR[6]{ nullptr };

ID2D1Bitmap* bmpEvil2UL[7]{ nullptr };
ID2D1Bitmap* bmpEvil2UR[7]{ nullptr };
ID2D1Bitmap* bmpEvil2DL[7]{ nullptr };
ID2D1Bitmap* bmpEvil2DR[7]{ nullptr };

ID2D1Bitmap* bmpEvil3UL[3]{ nullptr };
ID2D1Bitmap* bmpEvil3UR[3]{ nullptr };
ID2D1Bitmap* bmpEvil3DL[3]{ nullptr };
ID2D1Bitmap* bmpEvil3DR[3]{ nullptr };

ID2D1Bitmap* bmpEvil4UL[5]{ nullptr };
ID2D1Bitmap* bmpEvil4UR[5]{ nullptr };
ID2D1Bitmap* bmpEvil4DL[5]{ nullptr };
ID2D1Bitmap* bmpEvil4DR[5]{ nullptr };

ID2D1Bitmap* bmpHeroUL[7]{ nullptr };
ID2D1Bitmap* bmpHeroUR[7]{ nullptr };
ID2D1Bitmap* bmpHeroDL[7]{ nullptr };
ID2D1Bitmap* bmpHeroDR[7]{ nullptr };

ID2D1Bitmap* bmpExplosion[24]{ nullptr };

//////////////////////////////////////////////////////////

dll::FIELD* Field{ nullptr };

dll::HERO* Hero{ nullptr };



std::vector<EXPLOSION>vExplosions;

//////////////////////////////////////////////////////////

template<typename T>concept HasRelease = requires(T check)
{
	check.Release();
};
template<HasRelease T>bool FreeMem(T** var)
{
	if ((*var))
	{
		(*var)->Release();
		(*var) = nullptr;
		return true;
	}

	return false;
};
void LogErr(const wchar_t* what)
{
	std::wofstream err{ L".\\res\\data\\error.log" };
	err << what << L" time stamp: " << std::chrono::system_clock::now() << std::endl;
	err.close();
}
int IntroFrame()
{
	static int frame{ 0 };
	static int frame_delay{ 7 };

	--frame_delay;

	if (frame_delay <= 0)
	{
		frame_delay = 7;
		++frame;
		if (frame > 6)frame = 0;
	}

	return frame;
}
int OceanFrame()
{
	static int frame{ 0 };
	static int frame_delay{ 10 };

	--frame_delay;

	if (frame_delay <= 0)
	{
		frame_delay = 10;
		++frame;
		if (frame > 4)frame = 0;
	}

	return frame;
}
void ClearResources()
{
	if (!FreeMem(&iFactory))LogErr(L"Error releasing iFactory !");
	if (!FreeMem(&Draw))LogErr(L"Error releasing Draw !");
	if (!FreeMem(&b1BckgBrush))LogErr(L"Error releasing b1BckgBrush !");
	if (!FreeMem(&b2BckgBrush))LogErr(L"Error releasing b2BckgBrush !");
	if (!FreeMem(&b3BckgBrush))LogErr(L"Error releasing b3BckgBrush !");
	if (!FreeMem(&statBrush))LogErr(L"Error releasing statBrush !");
	if (!FreeMem(&txtBrush))LogErr(L"Error releasing txtBrush !");
	if (!FreeMem(&hgltBrush))LogErr(L"Error releasing hgltBrush !");
	if (!FreeMem(&inactBrush))LogErr(L"Error releasing inactBrush !");
	if (!FreeMem(&iWriteFactory))LogErr(L"Error releasing iWriteFactory !");
	if (!FreeMem(&nrmFormat))LogErr(L"Error releasing nrmFormat !");
	if (!FreeMem(&midFormat))LogErr(L"Error releasing midFormat !");
	if (!FreeMem(&bigFormat))LogErr(L"Error releasing bigFormat !");

	if (!FreeMem(&bmpArmor))LogErr(L"Error releasing bmpArmor !");
	if (!FreeMem(&bmpLogo))LogErr(L"Error releasing bmpLogo !");
	if (!FreeMem(&bmpGold))LogErr(L"Error releasing bmpGold !");
	if (!FreeMem(&bmpGun))LogErr(L"Error releasing bmpGun !");
	if (!FreeMem(&bmpIsland))LogErr(L"Error releasing bmpIsland !");
	if (!FreeMem(&bmpLoose))LogErr(L"Error releasing bmpLoose !");
	if (!FreeMem(&bmpPort))LogErr(L"Error releasing bmpPort !");
	if (!FreeMem(&bmpRecord))LogErr(L"Error releasing bmpRecord !");
	if (!FreeMem(&bmpRock1))LogErr(L"Error releasing bmpRock1 !");
	if (!FreeMem(&bmpRock2))LogErr(L"Error releasing bmpRock2 !");
	if (!FreeMem(&bmpRock3))LogErr(L"Error releasing bmpRock3 !");
	if (!FreeMem(&bmpTreasure))LogErr(L"Error releasing bmpTreasure !");
	if (!FreeMem(&bmpWin))LogErr(L"Error releasing bmpWin !");
	if (!FreeMem(&bmpCannonBall))LogErr(L"Error releasing bmpCannonBall !");

	if (!FreeMem(&bmpShipWreck))LogErr(L"Error releasing bmpShipWreck !");

	if (!FreeMem(&bmpBoatD))LogErr(L"Error releasing bmpBoatD !");
	if (!FreeMem(&bmpBoatU))LogErr(L"Error releasing bmpBoatU !");
	if (!FreeMem(&bmpBoatL))LogErr(L"Error releasing bmpBoatL !");
	if (!FreeMem(&bmpBoatR))LogErr(L"Error releasing bmpBoatR !");

	if (!FreeMem(&bmpBoatUL))LogErr(L"Error releasing bmpBoatUL !");
	if (!FreeMem(&bmpBoatUR))LogErr(L"Error releasing bmpBoatUR !");
	if (!FreeMem(&bmpBoatDL))LogErr(L"Error releasing bmpBoatDL !");
	if (!FreeMem(&bmpBoatDR))LogErr(L"Error releasing bmpBoatDR !");

	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpIntro[i]))LogErr(L"Error releasing bmpIntro !");
	for (int i = 0; i < 5; ++i)if (!FreeMem(&bmpOcean[i]))LogErr(L"Error releasing bmpOcean !");
	for (int i = 0; i < 12; ++i)if (!FreeMem(&bmpSwirl[i]))LogErr(L"Error releasing bmpSwirl !");

	for (int i = 0; i < 6; ++i)if (!FreeMem(&bmpEvil1UL[i]))LogErr(L"Error releasing bmpEvil1UL !");
	for (int i = 0; i < 6; ++i)if (!FreeMem(&bmpEvil1UR[i]))LogErr(L"Error releasing bmpEvil1UR !");
	for (int i = 0; i < 6; ++i)if (!FreeMem(&bmpEvil1DL[i]))LogErr(L"Error releasing bmpEvil1DL !");
	for (int i = 0; i < 6; ++i)if (!FreeMem(&bmpEvil1DR[i]))LogErr(L"Error releasing bmpEvil1DR !");

	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpEvil2UL[i]))LogErr(L"Error releasing bmpEvil2UL !");
	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpEvil2UR[i]))LogErr(L"Error releasing bmpEvil2UR !");
	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpEvil2DL[i]))LogErr(L"Error releasing bmpEvil2DL !");
	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpEvil2DR[i]))LogErr(L"Error releasing bmpEvil2DR !");

	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpEvil3UL[i]))LogErr(L"Error releasing bmpEvil3UL !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpEvil3UR[i]))LogErr(L"Error releasing bmpEvil3UR !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpEvil3DL[i]))LogErr(L"Error releasing bmpEvil3DL !");
	for (int i = 0; i < 3; ++i)if (!FreeMem(&bmpEvil3DR[i]))LogErr(L"Error releasing bmpEvil3DR !");

	for (int i = 0; i < 5; ++i)if (!FreeMem(&bmpEvil4UL[i]))LogErr(L"Error releasing bmpEvil4UL !");
	for (int i = 0; i < 5; ++i)if (!FreeMem(&bmpEvil4UR[i]))LogErr(L"Error releasing bmpEvil4UR !");
	for (int i = 0; i < 5; ++i)if (!FreeMem(&bmpEvil4DL[i]))LogErr(L"Error releasing bmpEvil4DL !");
	for (int i = 0; i < 5; ++i)if (!FreeMem(&bmpEvil4DR[i]))LogErr(L"Error releasing bmpEvil4DR !");

	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpHeroUL[i]))LogErr(L"Error releasing bmpHeroUL !");
	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpHeroUR[i]))LogErr(L"Error releasing bmpHeroUR !");
	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpHeroDL[i]))LogErr(L"Error releasing bmpHeroDL !");
	for (int i = 0; i < 7; ++i)if (!FreeMem(&bmpHeroDR[i]))LogErr(L"Error releasing bmpHeroDR !");

	for (int i = 0; i < 24; ++i)if (!FreeMem(&bmpExplosion[i]))LogErr(L"Error releasing bmpExplosion !");
}
void ErrExit(int what)
{
	MessageBeep(MB_ICONERROR);
	MessageBox(NULL, ErrHandle(what), L"Критична грешка !", MB_OK | MB_APPLMODAL | MB_ICONERROR);

	std::remove(tmp_file);
	ClearResources();
	exit(1);
}

void GameOver()
{
	PlaySound(NULL, NULL, NULL);


	bMsg.message = WM_QUIT;
	bMsg.wParam = 0;
}
void InitGame()
{
	speed = 1;
	score = 0;

	wcscpy_s(current_player, L"TARLYO");
	name_set = false;

	if (Field)delete Field;
	Field = new dll::FIELD();

	FreeMem(&Hero);
	Hero = dll::HERO::create(RandIt(50.0f, scr_width - 100.0f), ground - 250.0f);


}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT ReceivedMsg, WPARAM wParam, LPARAM lParam)
{
	switch (ReceivedMsg)
	{
	case WM_INITDIALOG:
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)(bIcon));
		return true;

	case WM_CLOSE:
		EndDialog(hwnd, IDCANCEL);
		break;

	case WM_COMMAND:
		if (GetDlgItemText(hwnd, IDC_NAME, current_player, 16) < 1)
		{
			wcscpy_s(current_player, L"TARLYO");
			if (sound)mciSendString(L"play .\\res\\snd\\exclamation.wav", NULL, NULL, NULL);
			MessageBox(bHwnd, L"Ха, ха, ха ! Забрави си името !", L"Забраватор !", MB_OK | MB_APPLMODAL | MB_ICONEXCLAMATION);
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		EndDialog(hwnd, IDOK);
		break;
	}

	return (INT_PTR)(FALSE);
}
LRESULT CALLBACK WinProc(HWND hwnd, UINT ReceivedMsg, WPARAM wParam, LPARAM lParam)
{
	switch (ReceivedMsg)
	{
	case WM_CREATE:
		if (bIns)
		{
			bBar = CreateMenu();
			bMain = CreateMenu();
			bStore = CreateMenu();

			AppendMenu(bBar, MF_POPUP, (UINT_PTR)(bMain), L"Основно меню");
			AppendMenu(bBar, MF_POPUP, (UINT_PTR)(bStore), L"Меню за данни");

			AppendMenu(bMain, MF_STRING, mNew, L"Нова игра");
			AppendMenu(bMain, MF_STRING, mSpeed, L"Увеличи скоростта");
			AppendMenu(bMain, MF_SEPARATOR, NULL, NULL);
			AppendMenu(bMain, MF_STRING, mExit, L"Изход");

			AppendMenu(bStore, MF_STRING, mSave, L"Запази игра");
			AppendMenu(bStore, MF_STRING, mLoad, L"Зареди игра");
			AppendMenu(bStore, MF_SEPARATOR, NULL, NULL);
			AppendMenu(bStore, MF_STRING, mHoF, L"Зала на славата ");

			SetMenu(hwnd, bBar);
			InitGame();
		}
		break;

	case WM_CLOSE:
		pause = true;
		if (MessageBox(hwnd, L"Ако излезеш, ще изгубиш тази игра !\nНаистина ли излизаш ?", L"Изход",
			MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION) == IDNO)
		{
			pause = false;
			break;
		}
		GameOver();
		break;

	case WM_PAINT:
		PaintDC = BeginPaint(hwnd, &bPaint);
		FillRect(PaintDC, &bPaint.rcPaint, CreateSolidBrush(RGB(10, 10, 10)));
		EndPaint(hwnd, &bPaint);
		break;

	case WM_SETCURSOR:
		GetCursorPos(&cur_pos);
		ScreenToClient(hwnd, &cur_pos);
		if (LOWORD(lParam) == HTCLIENT)
		{
			if (!in_client)
			{
				pause = false;
				in_client = true;
			}

			if (cur_pos.y * scale_y <= 50)
			{
				if (cur_pos.x * scale_x >= b1Rect.left && cur_pos.x * scale_x <= b1Rect.right)
				{
					if (!b1Hglt)
					{
						if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);

						b1Hglt = true;
						b2Hglt = false;
						b3Hglt = false;
					}
				}
				else if (cur_pos.x * scale_x >= b2Rect.left && cur_pos.x * scale_x <= b2Rect.right)
				{
					if (!b2Hglt)
					{
						if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);

						b1Hglt = false;
						b2Hglt = true;
						b3Hglt = false;
					}
				}
				else if (cur_pos.x * scale_x >= b3Rect.left && cur_pos.x * scale_x <= b3Rect.right)
				{
					if (!b3Hglt)
					{
						if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);

						b1Hglt = false;
						b2Hglt = false;
						b3Hglt = true;
					}
				}
				else
				{
					if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);

					b1Hglt = false;
					b2Hglt = false;
					b3Hglt = false;
				}

				SetCursor(outCursor);
				return true;
			}
			else if (b1Hglt || b2Hglt || b3Hglt)
			{
				if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);

				b1Hglt = false;
				b2Hglt = false;
				b3Hglt = false;
			}

			SetCursor(bCursor);

			return true;
		}
		else
		{
			if (in_client)
			{
				pause = true;
				in_client = false;
			}

			if (b1Hglt || b2Hglt || b3Hglt)
			{
				if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);

				b1Hglt = false;
				b2Hglt = false;
				b3Hglt = false;
			}

			SetCursor(LoadCursor(NULL, IDC_ARROW));

			return true;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case mNew:
			pause = true;
			if (MessageBox(hwnd, L"Ако рестартираш, ще изгубиш тази игра !\nНаистина ли рестартираш ?", L"Рестарт",
				MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION) == IDNO)
			{
				pause = false;
				break;
			}
			InitGame();
			break;

		case mSpeed:
			pause = true;
			if (MessageBox(hwnd, L"Готов ли си за по-висока скорост ?", L"Турбо",
				MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION) == IDNO)
			{
				pause = false;
				break;
			}
			++speed;
			break;

		case mExit:
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			break;

		}
		break;









	default: return DefWindowProc(hwnd, ReceivedMsg, wParam, lParam);
	}

	return (LRESULT)(FALSE);
}

void CreateResources()
{
	int result = 0;
	CheckFile(Ltmp_file, &result);
	if (result == FILE_EXIST)ErrExit(eStarted);
	else
	{
		std::wofstream start(Ltmp_file);
		start << L"Game started at: " << std::chrono::system_clock::now();
		start.close();
	}

	int win_x = (int)(GetSystemMetrics(SM_CXSCREEN) / 2 - (int)(scr_width / 2.0f));
	int win_y = 10;

	if (GetSystemMetrics(SM_CXSCREEN) < win_x + (int)(scr_width) || GetSystemMetrics(SM_CYSCREEN) < win_y + (int)(scr_height))
		ErrExit(eScreen);

	bIcon = (HICON)(LoadImage(NULL, L".\\res\\main.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE));
	if (!bIcon)ErrExit(eIcon);

	bCursor = LoadCursorFromFileW(L".\\res\\main.ani");
	outCursor = LoadCursorFromFileW(L".\\res\\out.ani");

	if (!bCursor || !outCursor)ErrExit(eCursor);

	bWinClass.lpszClassName = bWinClassName;
	bWinClass.hInstance = bIns;
	bWinClass.lpfnWndProc = &WinProc;
	bWinClass.hbrBackground = CreateSolidBrush(RGB(10, 10, 10));
	bWinClass.hIcon = bIcon;
	bWinClass.hCursor = bCursor;
	bWinClass.style = CS_DROPSHADOW;

	if (!RegisterClass(&bWinClass))ErrExit(eClass);

	bHwnd = CreateWindow(bWinClassName, L"ПИРАТСКО СЪКРОВИЩЕ", WS_SYSMENU | WS_CAPTION, win_x, win_y,
		(int)(scr_width), (int)(scr_height), NULL, NULL, bIns, NULL);
	if (!bHwnd)ErrExit(eWindow);
	else
	{
		ShowWindow(bHwnd, SW_SHOWDEFAULT);

		HRESULT  hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &iFactory);
		if (hr != S_OK)LogErr(L"Error creating D2D1Factory !");
		if (iFactory)
			iFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(bHwnd,
				D2D1::SizeU((UINT32)(scr_width), (UINT32)(scr_height))), &Draw);
		if (hr != S_OK)LogErr(L"Error creating D2D1HwndRenderTarget !");
		if (Draw)
		{
			RECT ClR{};
			GetClientRect(bHwnd, &ClR);
			D2D1_SIZE_F D2D1R{ Draw->GetSize() };

			scale_x = D2D1R.width / (ClR.right - ClR.left);
			scale_y = D2D1R.height / (ClR.bottom - ClR.top);

			D2D1_GRADIENT_STOP gStops[2]{};
			ID2D1GradientStopCollection* gColl{ nullptr };
			gStops[0].position = 0;
			gStops[0].color = D2D1::ColorF(D2D1::ColorF::MediumSpringGreen);
			gStops[1].position = 1.0f;
			gStops[1].color = D2D1::ColorF(D2D1::ColorF::Maroon);

			hr = Draw->CreateGradientStopCollection(gStops, 2, &gColl);
			if (hr != S_OK)LogErr(L"Error creating D2D1GradientStopCollection !");
			if (gColl)
			{
				hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(b1Rect.left +
					(b1Rect.right - b1Rect.left) / 2.0f), D2D1::Point2F(0, 0), (b1Rect.right - b1Rect.left) / 2.0f, 15.0f),
					gColl, &b1BckgBrush);
				hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(b2Rect.left +
					(b2Rect.right - b2Rect.left) / 2.0f), D2D1::Point2F(0, 0), (b2Rect.right - b2Rect.left) / 2.0f, 15.0f),
					gColl, &b2BckgBrush);
				hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(b3Rect.left +
					(b3Rect.right - b3Rect.left) / 2.0f), D2D1::Point2F(0, 0), (b3Rect.right - b3Rect.left) / 2.0f, 15.0f),
					gColl, &b3BckgBrush);

				if (hr != S_OK)LogErr(L"Error creating D2D1 Button background brushes !");

				FreeMem(&gColl);
			}

			hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSeaGreen), &statBrush);
			hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Lime), &txtBrush);
			hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Tomato), &hgltBrush);
			hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &inactBrush);
			if (hr != S_OK)LogErr(L"Error creating D2D1 Text Brushes !");

			bmpArmor = Load(L".\\res\\img\\field\\armor.png", Draw);
			if (!bmpArmor)LogErr(L"Error creating .bmp for armor !");
			bmpLogo = Load(L".\\res\\img\\field\\Logo.png", Draw);
			if (!bmpLogo)LogErr(L"Error creating .bmp for Logo !");
			bmpGold = Load(L".\\res\\img\\field\\gold.png", Draw);
			if (!bmpGold)LogErr(L"Error creating .bmp for gold !");
			bmpGun = Load(L".\\res\\img\\field\\gun.png", Draw);
			if (!bmpGun)LogErr(L"Error creating .bmp for gun !");
			bmpIsland = Load(L".\\res\\img\\field\\island.png", Draw);
			if (!bmpIsland)LogErr(L"Error creating .bmp for island !");
			bmpLoose = Load(L".\\res\\img\\field\\loose.png", Draw);
			if (!bmpLoose)LogErr(L"Error creating .bmp for loose !");
			bmpPort = Load(L".\\res\\img\\field\\Port.png", Draw);
			if (!bmpPort)LogErr(L"Error creating .bmp for Port !");
			bmpRecord = Load(L".\\res\\img\\field\\Record.png", Draw);
			if (!bmpRecord)LogErr(L"Error creating .bmp for Record !");
			bmpRock1 = Load(L".\\res\\img\\field\\Rock1.png", Draw);
			if (!bmpRock1)LogErr(L"Error creating .bmp for Rock1 !");
			bmpRock2 = Load(L".\\res\\img\\field\\Rock2.png", Draw);
			if (!bmpRock2)LogErr(L"Error creating .bmp for Rock2 !");
			bmpRock3 = Load(L".\\res\\img\\field\\Rock3.png", Draw);
			if (!bmpRock3)LogErr(L"Error creating .bmp for Rock3 !");
			bmpTreasure = Load(L".\\res\\img\\field\\Treasure.png", Draw);
			if (!bmpTreasure)LogErr(L"Error creating .bmp for Treasure !");
			bmpWin = Load(L".\\res\\img\\field\\win.png", Draw);
			if (!bmpWin)LogErr(L"Error creating .bmp for Win !");
			bmpCannonBall = Load(L".\\res\\img\\CannonBall.png", Draw);
			if (!bmpCannonBall)LogErr(L"Error creating .bmp for CannonBall !");
			bmpShipWreck = Load(L".\\res\\img\\ShipWreck.png", Draw);
			if (!bmpShipWreck)LogErr(L"Error creating .bmp for ShipWreck !");

			bmpBoatD = Load(L".\\res\\img\\boat\\down.png", Draw);
			if (!bmpBoatD)LogErr(L"Error creating .bmp for BoatD !");
			bmpBoatU = Load(L".\\res\\img\\boat\\up.png", Draw);
			if (!bmpBoatU)LogErr(L"Error creating .bmp for BoatU !");
			bmpBoatL = Load(L".\\res\\img\\boat\\left.png", Draw);
			if (!bmpBoatL)LogErr(L"Error creating .bmp for BoatL !");
			bmpBoatR = Load(L".\\res\\img\\boat\\right.png", Draw);
			if (!bmpBoatR)LogErr(L"Error creating .bmp for BoatR !");
			bmpBoatUL = Load(L".\\res\\img\\boat\\up_left.png", Draw);
			if (!bmpBoatUL)LogErr(L"Error creating .bmp for BoatUL !");
			bmpBoatDL = Load(L".\\res\\img\\boat\\down_left.png", Draw);
			if (!bmpBoatDL)LogErr(L"Error creating .bmp for BoatDL !");
			bmpBoatUR = Load(L".\\res\\img\\boat\\up_right.png", Draw);
			if (!bmpBoatUR)LogErr(L"Error creating .bmp for BoatUR !");
			bmpBoatDR = Load(L".\\res\\img\\boat\\down_right.png", Draw);
			if (!bmpBoatDR)LogErr(L"Error creating .bmp for BoatDR !");

			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\field\\intro\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpIntro[i] = Load(name, Draw);
				if (!bmpIntro[i])LogErr(L"Error creating .bmp for Intro !");
			}
			for (int i = 0; i < 5; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\field\\ocean\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpOcean[i] = Load(name, Draw);
				if (!bmpOcean[i])LogErr(L"Error creating .bmp for Ocean !");
			}
			for (int i = 0; i < 12; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\field\\swirl\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpSwirl[i] = Load(name, Draw);
				if (!bmpSwirl[i])LogErr(L"Error creating .bmp for Swirl !");
			}
			for (int i = 0; i < 24; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\explosion\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpExplosion[i] = Load(name, Draw);
				if (!bmpExplosion[i])LogErr(L"Error creating .bmp for Explosion !");
			}

			for (int i = 0; i < 6; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship1\\up\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil1UL[i] = Load(name, Draw);
				if (!bmpEvil1UL[i])LogErr(L"Error creating .bmp for Evil1UL !");
			}
			for (int i = 0; i < 6; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship1\\up\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil1UR[i] = Load(name, Draw);
				if (!bmpEvil1UR[i])LogErr(L"Error creating .bmp for Evil1UR !");
			}
			for (int i = 0; i < 6; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship1\\down\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil1DR[i] = Load(name, Draw);
				if (!bmpEvil1DR[i])LogErr(L"Error creating .bmp for Evil1DR !");
			}
			for (int i = 0; i < 6; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship1\\down\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil1DL[i] = Load(name, Draw);
				if (!bmpEvil1DL[i])LogErr(L"Error creating .bmp for Evil1DL !");
			}

			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship2\\up\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil2UL[i] = Load(name, Draw);
				if (!bmpEvil2UL[i])LogErr(L"Error creating .bmp for Evil2UL !");
			}
			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship2\\up\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil2UR[i] = Load(name, Draw);
				if (!bmpEvil2UR[i])LogErr(L"Error creating .bmp for Evil2UR !");
			}
			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship2\\down\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil2DR[i] = Load(name, Draw);
				if (!bmpEvil2DR[i])LogErr(L"Error creating .bmp for Evil2DR !");
			}
			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship2\\down\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil2DL[i] = Load(name, Draw);
				if (!bmpEvil2DL[i])LogErr(L"Error creating .bmp for Evil2DL !");
			}

			for (int i = 0; i < 3; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship3\\up\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil3UL[i] = Load(name, Draw);
				if (!bmpEvil3UL[i])LogErr(L"Error creating .bmp for Evil3UL !");
			}
			for (int i = 0; i < 3; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship3\\up\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil3UR[i] = Load(name, Draw);
				if (!bmpEvil3UR[i])LogErr(L"Error creating .bmp for Evil3UR !");
			}
			for (int i = 0; i < 3; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship3\\down\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil3DR[i] = Load(name, Draw);
				if (!bmpEvil3DR[i])LogErr(L"Error creating .bmp for Evil3DR !");
			}
			for (int i = 0; i < 3; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship3\\down\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil3DL[i] = Load(name, Draw);
				if (!bmpEvil3DL[i])LogErr(L"Error creating .bmp for Evil3DL !");
			}

			for (int i = 0; i < 5; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship4\\up\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil4UL[i] = Load(name, Draw);
				if (!bmpEvil4UL[i])LogErr(L"Error creating .bmp for Evil4UL !");
			}
			for (int i = 0; i < 5; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship4\\up\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil4UR[i] = Load(name, Draw);
				if (!bmpEvil4UR[i])LogErr(L"Error creating .bmp for Evil4UR !");
			}
			for (int i = 0; i < 5; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship4\\down\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil4DR[i] = Load(name, Draw);
				if (!bmpEvil4DR[i])LogErr(L"Error creating .bmp for Evil4DR !");
			}
			for (int i = 0; i < 5; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\evils\\ship4\\down\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpEvil4DL[i] = Load(name, Draw);
				if (!bmpEvil4DL[i])LogErr(L"Error creating .bmp for Evil4DL !");
			}

			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\hero\\up\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpHeroUL[i] = Load(name, Draw);
				if (!bmpHeroUL[i])LogErr(L"Error creating .bmp for HeroUL !");
			}
			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\hero\\up\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpHeroUR[i] = Load(name, Draw);
				if (!bmpHeroUR[i])LogErr(L"Error creating .bmp for HeroUR !");
			}
			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\hero\\down\\r\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpHeroDR[i] = Load(name, Draw);
				if (!bmpHeroDR[i])LogErr(L"Error creating .bmp for HeroDR !");
			}
			for (int i = 0; i < 7; ++i)
			{
				wchar_t name[75]{ L".\\res\\img\\hero\\down\\l\\" };
				wchar_t add[5]{ L"\0" };

				wsprintf(add, L"%d", i);
				wcscat_s(name, add);
				wcscat_s(name, L".png");

				bmpHeroDL[i] = Load(name, Draw);
				if (!bmpHeroDL[i])LogErr(L"Error creating .bmp for HeroDL !");
			}
		}

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>
			(&iWriteFactory));
		if (hr != S_OK)LogErr(L"Error creating D2D1WriteFactory !");

		if (iWriteFactory)
		{
			hr = iWriteFactory->CreateTextFormat(L"Copperplate Gothic", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK,
				DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STRETCH_NORMAL, 16.0f, L"", &nrmFormat);
			hr = iWriteFactory->CreateTextFormat(L"Copperplate Gothic", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK,
				DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STRETCH_NORMAL, 32.0f, L"", &midFormat);
			hr = iWriteFactory->CreateTextFormat(L"Copperplate Gothic", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK,
				DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STRETCH_NORMAL, 72.0f, L"", &bigFormat);

			if (hr != S_OK)LogErr(L"Error creating D2D1WriteFactory text format !");
		}

		CheckFile(L".\\res\\data\\error.log", &result);
		if (result == FILE_EXIST)ErrExit(eD2D);
	}

	PlaySound(L".\\res\\snd\\wave.wav", NULL, SND_ASYNC);

	for (int i = 0; i < 180; ++i)
	{
		Draw->BeginDraw();
		Draw->DrawBitmap(bmpIntro[IntroFrame()], D2D1::RectF(0, 0, scr_width, scr_height));
		if (bigFormat && txtBrush)
			Draw->DrawTextW(L"PIRATE TREASURE !", 18, bigFormat, D2D1::RectF(100.0f, scr_height / 2.0f - 50.0f, scr_width,
				scr_height), txtBrush);
		Draw->EndDraw();
	}

	Draw->BeginDraw();
	Draw->DrawBitmap(bmpLogo, D2D1::RectF(0, 0, scr_width, scr_height));
	Draw->EndDraw();
	PlaySound(L".\\res\\snd\\intro.wav", NULL, SND_SYNC);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	_wsetlocale(LC_ALL, L"");

	bIns = hInstance;
	if (!bIns)
	{
		LogErr(L"Error obtaining hInstance from Windows !");
		ErrExit(eD2D);
	}

	CreateResources();



	while (bMsg.message != WM_QUIT)
	{
		if ((bRet = PeekMessage(&bMsg, nullptr, NULL, NULL, PM_REMOVE)) != 0)
		{
			if (bRet == -1)ErrExit(eMsg);
			TranslateMessage(&bMsg);
			DispatchMessage(&bMsg);
		}

		if (pause)
		{
			if (show_help)continue;
			Draw->BeginDraw();
			Draw->DrawBitmap(bmpIntro[IntroFrame()], D2D1::RectF(0, 0, scr_width, scr_height));
			if (txtBrush && bigFormat)
				Draw->DrawTextW(L"ПАУЗА", 6, bigFormat, D2D1::RectF(scr_width / 2.0f - 100.0f, scr_height / 2.0f - 50.0f,
					scr_width, scr_height), txtBrush);
			Draw->EndDraw();
			continue;
		}

		///////////////////////////////////////////////////////









		// DRAW THINGS *************************************
		
		Draw->BeginDraw();
		
		for (int rows = 0; rows < 3; ++rows)
		{
			for (int cols = 0; cols < 3; ++cols)
			{
				if (Field->in_view_port(Field->ocean_tiles[rows][cols]))
					Draw->DrawBitmap(bmpOcean[OceanFrame()], D2D1::RectF(Field->ocean_tiles[rows][cols].left,
						Field->ocean_tiles[rows][cols].up, Field->ocean_tiles[rows][cols].right,
						Field->ocean_tiles[rows][cols].down));
			}
		}
		
		if (Hero)
		{
			int aframe = Hero->get_frame();

			switch (Hero->dir)
			{
			case dirs::down:
				Draw->DrawBitmap(bmpHeroDL[aframe], Resizer(bmpHeroDL[aframe], Hero->start.x, Hero->start.y));
				break;

			case dirs::down_left:
				Draw->DrawBitmap(bmpHeroDL[aframe], Resizer(bmpHeroDL[aframe], Hero->start.x, Hero->start.y));
				break;

			case dirs::down_right:
				Draw->DrawBitmap(bmpHeroDR[aframe], Resizer(bmpHeroDR[aframe], Hero->start.x, Hero->start.y));
				break;

			case dirs::up:
				Draw->DrawBitmap(bmpHeroUR[aframe], Resizer(bmpHeroUR[aframe], Hero->start.x, Hero->start.y));
				break;

			case dirs::up_left:
				Draw->DrawBitmap(bmpHeroUL[aframe], Resizer(bmpHeroUL[aframe], Hero->start.x, Hero->start.y));
				break;

			case dirs::up_right:
				Draw->DrawBitmap(bmpHeroUR[aframe], Resizer(bmpHeroUR[aframe], Hero->start.x, Hero->start.y));
				break;

			case dirs::stop:
				Draw->DrawBitmap(bmpHeroUR[aframe], Resizer(bmpHeroUR[aframe], Hero->start.x, Hero->start.y));
				break;
			}
		}
		
		
		
		/////////////////////////////////////////////////////////////////////////
		
		if (statBrush && inactBrush && txtBrush && hgltBrush && b1BckgBrush && b2BckgBrush && b3BckgBrush && nrmFormat)
		{
			Draw->FillRectangle(D2D1::RectF(0, 0, scr_width, 50.0f), statBrush);
			Draw->FillRoundedRectangle(D2D1::RoundedRect(b1Rect, 20.0f, 10.0f), b1BckgBrush);
			Draw->FillRoundedRectangle(D2D1::RoundedRect(b2Rect, 20.0f, 10.0f), b2BckgBrush);
			Draw->FillRoundedRectangle(D2D1::RoundedRect(b3Rect, 20.0f, 10.0f), b3BckgBrush);

			if (name_set)Draw->DrawTextW(L"ИМЕ НА КАПИТАН", 15, nrmFormat, b1TxtRect, inactBrush);
			else
			{
				if (b1Hglt)Draw->DrawTextW(L"ИМЕ НА КАПИТАН", 15, nrmFormat, b1TxtRect, hgltBrush);
				else Draw->DrawTextW(L"ИМЕ НА КАПИТАН", 15, nrmFormat, b1TxtRect, txtBrush);
			}
			if (b2Hglt)Draw->DrawTextW(L"ЗВУЦИ ON / OFF", 15, nrmFormat, b2TxtRect, hgltBrush);
			else Draw->DrawTextW(L"ЗВУЦИ ON / OFF", 15, nrmFormat, b2TxtRect, txtBrush);
			if (b3Hglt)Draw->DrawTextW(L"ПОМОЩ ЗА ИГРАТА", 16, nrmFormat, b3TxtRect, hgltBrush);
			else Draw->DrawTextW(L"ПОМОЩ ЗА ИГРАТА", 16, nrmFormat, b3TxtRect, txtBrush);
		}
		
		//////////////////////////////////////////////
		
		Draw->EndDraw();

	}

	std::remove(tmp_file);
	ClearResources();

    return (int) bMsg.wParam;
}