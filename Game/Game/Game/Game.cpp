// Game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Game.h"

#include <WIndows.h>
#include <thread>
#include "time.h"
#include <timeapi.h>
#include <ctime>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

#define err_ex(a) MessageBox(NULL,a,NULL,NULL),ExitProcess(NULL);


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // current instance
WCHAR szTitle[MAX_LOADSTRING]; // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name


wchar_t enemyName[] = L"res/rEn/0.bmp";

HINSTANCE mainHinstace; //Main instance
HWND hWnd = nullptr, hwndMenu = nullptr; //Handlers
//All needed descriptors
HDC winDC,
    fonDC,
    cwinDC,
    steveDC,
    steveRDC,
    groundDC,
    treeDC,
    stoneDC,
    houseDC,
    houseWallDC,
    houseFloorDC,
    enemyDC[5],
    hitDC,
    hpDC,
    fireBallDC;
//Ractengles
RECT rClient,
     rWindow,
     rFon;
//Handles for threads
HANDLE hThread, hEnemyThread;
//Bitmaps for objects to draw
HBITMAP hBitmap,
        hSteve,
        hSteveR,
        bmpFon,
        bmpMem,
        bmpTemp,
        bmpTree,
        bmpStone,
        bmpHouse,
        bmpHouseWall,
        bmpFloor,
        bmpEnemy[5],
        bmpHit,
        bmpHpBar,
        bmpFireBall;
//Player and ene,y positions and health
INT xPl = 1, yPl = 32 * 3;
INT xEn = 500, yEn = 32 * 3;
INT plHP = 100, enHP = 150;
//Level
INT lvl = 0;

//Logic variables
BOOL jump = FALSE, onGround = TRUE, menu = FALSE, attack = FALSE;
BOOL mRight = TRUE, mLeft = FALSE, inFight = FALSE;
BOOL levels[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, inHouse = FALSE;
BOOL enemyAlive = TRUE;
//Fonts
HFONT hfont;
LOGFONT font;

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI threadDraw(LPVOID);
VOID EnemyDraw(BOOL,  int, int, int, int, BITMAP, BITMAP, BITMAP);
VOID DrawHouse(int, int, BITMAP, BITMAP, BITMAP, BITMAP);
VOID Attack(BITMAP, BITMAP, BITMAP);
VOID BgDraw(int,  int,  int , BITMAP , BITMAP , BITMAP , BITMAP );
VOID ClearRAM();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);

	WNDCLASS wnd_class;
	MSG msg;
	const wchar_t szClassName[] = L"Game";
	//Window class registering
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;
	wnd_class.lpfnWndProc = WndProc; //Main process
	wnd_class.hInstance = hInstance; //Instance
	wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); //Default brush for background
	wnd_class.lpszClassName = szClassName; //Class name
	wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW); //Default cursor
	wnd_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION); //Icon
	wnd_class.lpszMenuName = nullptr; //Window menu name
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;


	if (!RegisterClass(&wnd_class))
	{
		MessageBox(nullptr, L"Cannot register class", L"Error", MB_OK);
		return 0;
	}

	hWnd = CreateWindowEx(WS_EX_TOPMOST, szClassName, L"Game",
	                      WS_MAXIMIZE | WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX | WS_BORDER,
	                      CW_USEDEFAULT,
	                      CW_USEDEFAULT,
	                      CW_USEDEFAULT,
	                      CW_USEDEFAULT,
	                      nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		MessageBox(nullptr, L"Cannot create window", L"Error", MB_OK);
		return 0;
	}

	GetClientRect(hWnd, &rClient);
	rWindow = rClient;
	AdjustWindowRectEx(&rWindow, WS_OVERLAPPED | WS_MAXIMIZE | WS_EX_STATICEDGE, FALSE, 0);

	mainHinstace = hInstance;
	hThread = CreateThread(nullptr, 0, threadDraw, nullptr, NULL, nullptr);

	font.lfHeight = 10; // Height of symbol
	font.lfWidth = 0; // Width of symbol
	font.lfEscapement = 0; 
	font.lfOrientation = 0; 
	font.lfWeight = 800; // Thickness (0 - 1000)
	font.lfItalic = 0; 
	font.lfUnderline = 0; 
	font.lfStrikeOut = 0; 
	font.lfCharSet = RUSSIAN_CHARSET; //Charracter set
	font.lfOutPrecision = 0; // Output precision
	font.lfClipPrecision = 0; 
	font.lfQuality = 0; // Output quality
	font.lfPitchAndFamily = 0; // Width of symbols and family
	wsprintf(font.lfFaceName, L"VERDANA"); // Name of font

	hfont = ::CreateFontIndirect(&font);

	ShowWindow(hWnd, 3);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(0);
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	const auto hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	                          CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PaintStruct;
	BITMAP bm;

	GetObject(hBitmap, sizeof(bm), &bm);
	switch (message)
	{
	case WM_DESTROY: //Close window
		{
			if (hThread)
			{
				ClearRAM();
				ExitProcess(0);
			}
		}
		break;
	case WM_PAINT: //Draw window
		GetClientRect(hWnd, &rWindow); //Getting Window dimensions
		winDC = BeginPaint(hWnd, &PaintStruct); //Start paint procedure
		StretchBlt( //Copy in-memory painted window to opened window
			winDC,
			rWindow.left,
			rWindow.top,
			rWindow.right,
			rWindow.bottom,
			cwinDC,
			rWindow.left,
			rWindow.top,
			rWindow.right,
			rWindow.bottom,
			SRCCOPY
		);
		EndPaint(hWnd, &PaintStruct); //End paint procedure
		return 0;
		break;
	case WM_KEYDOWN: //If key pressed
		if (GetAsyncKeyState(VK_UP) < 0 && onGround == TRUE || GetKeyState(VK_SPACE) && onGround == TRUE || //If W or w or Arrow Up or Space Bar and player is on the ground then jump
			LOWORD(wParam) == 'w' && onGround == TRUE || LOWORD(wParam) == 'W' && onGround == TRUE)
		{
			jump = TRUE;
			onGround = FALSE;
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0 || LOWORD(wParam) == 'd' || LOWORD(wParam) == 'D') //If Arrow Right or d then move right
		{
			!inHouse //If not in house
				? (xPl + 64 >= rWindow.right) //If right border of player is outside of window rectangle
					  ? xPl = rWindow.right - 64 //Set player position to maximum right
					  : xPl += 10 //Increase position by 10 (Move right)
				: (xPl + 190 >= rWindow.right) //If in house player position is outside of window rectangle
				? xPl = rWindow.right - 190 //Set player position to maximum right
				: xPl += 10; //Increase by 10 (Move right)
			mRight = TRUE;
			mLeft = FALSE;
		}
		if (GetAsyncKeyState(VK_LEFT) < 0 || LOWORD(wParam) == 'a' || LOWORD(wParam) == 'A') //If Arrow Left or a then move left
		{
			!inHouse //If not is house
				? (xPl - 24 <= rWindow.left) //If left border of player is outside of window rectangle
					  ? xPl = rWindow.left //Set player position to maximum left
					  : xPl -= 10 //Decrease player position by 10 (Move left)
				: (xPl + 190 <= rWindow.left) //If in house left border of player is outside of window rectangle
				? xPl = rWindow.left - 190 //Set player position to maximum left
				: xPl -= 10; //Decrease by 10 (Move left)
			mRight = FALSE;
			mLeft = TRUE;
		}
		if (LOWORD(wParam) == 'f' || LOWORD(wParam) == 'F') //If F or f then attack
		{
			attack = TRUE;
		}

		if (LOWORD(wParam) == 'r' || LOWORD(wParam) == 'R') //IF R or r then restart game
		{
			const auto msg_result = MessageBox(hWnd, L"Do you really want restart game ?", L"Caution, game restart !",
			                                  MB_YESNO);
			if (msg_result == 6)
			{
				xPl = 0;
				yPl = 32 * 3;
				if (inFight) inFight = FALSE;
				if (inHouse)
				{
					inHouse = FALSE;
					lvl--;
					levels[lvl] = TRUE;
				}
				enHP = 150;
			}
		}

		if (GetKeyState(VK_ESCAPE) < 0) //If escape show menu 
		{
			MessageBox(hWnd, L"Menu body", L"Main menu", NULL);
		}

		return 0;
		break;
	case WM_KEYUP: //If F or f key is up (released) then stop attack
		if (LOWORD(wParam) == 'f' || LOWORD(wParam) == 'F')
		{
			attack = FALSE;
		}
		return 0;
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

/*
 * LoadResource
 * Desc: Function to load all needed resources from files in project
 * After all resources has been loaded, temporary objects are deleted
 */
VOID LoadResuorce()
{
	const auto tempDC = GetDC(hWnd);

	cwinDC = CreateCompatibleDC(tempDC);
	groundDC = CreateCompatibleDC(tempDC);
	steveDC = CreateCompatibleDC(tempDC);
	steveRDC = CreateCompatibleDC(tempDC);
	fonDC = CreateCompatibleDC(tempDC);
	treeDC = CreateCompatibleDC(tempDC);
	stoneDC = CreateCompatibleDC(tempDC);
	houseDC = CreateCompatibleDC(tempDC);
	houseWallDC = CreateCompatibleDC(tempDC);
	houseFloorDC = CreateCompatibleDC(tempDC);
	hitDC = CreateCompatibleDC(tempDC);
	hpDC = CreateCompatibleDC(tempDC);
	fireBallDC = CreateCompatibleDC(tempDC);

	for (auto& i : enemyDC)
	{
		i = CreateCompatibleDC(tempDC);
	}

	bmpFon = static_cast<HBITMAP>(LoadImage(nullptr, L"res/fon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	hBitmap = static_cast<HBITMAP>(LoadImage(nullptr, L"res/Grass.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	hSteve = static_cast<HBITMAP>(LoadImage(nullptr, L"res/Steve.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	hSteveR = static_cast<HBITMAP>(LoadImage(nullptr, L"res/SteveR.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpTree = static_cast<HBITMAP>(LoadImage(nullptr, L"res/TreeBig.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpStone = static_cast<HBITMAP>(LoadImage(nullptr, L"res/stoneGrassed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpHouse = static_cast<HBITMAP>(LoadImage(nullptr, L"res/House.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpHouseWall = static_cast<HBITMAP>(LoadImage(nullptr, L"res/houseWall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpHit = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hit.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpFloor = static_cast<HBITMAP>(LoadImage(nullptr, L"res/floor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpHpBar = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hpBar.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	bmpFireBall = static_cast<HBITMAP>(LoadImage(nullptr, L"res/fireBallDark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)
	);

	for (auto i = 0; i < 5; i++)
	{
		wsprintf(enemyName, L"%s%d%s", L"res/rEn/", i, L".bmp");
		bmpEnemy[i] = static_cast<HBITMAP>(LoadImage(nullptr, enemyName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	}

	bmpMem = CreateCompatibleBitmap(tempDC, rClient.right, rClient.bottom);

	ReleaseDC(hWnd, tempDC);

	bmpTemp = static_cast<HBITMAP>(SelectObject(fonDC, bmpFon));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(groundDC, hBitmap));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(steveDC, hSteve));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(steveRDC, hSteveR));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(treeDC, bmpTree));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(houseDC, bmpHouse));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(stoneDC, bmpStone));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(houseWallDC, bmpHouseWall));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(houseFloorDC, bmpFloor));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(hitDC, bmpHit));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(hpDC, bmpHpBar));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(fireBallDC, bmpFireBall));
	if (bmpTemp) DeleteObject(bmpTemp);

	bmpTemp = static_cast<HBITMAP>(SelectObject(cwinDC, bmpMem));
	if (bmpTemp) DeleteObject(bmpTemp);

	for (auto i = 0; i < 5; i++)
	{
		bmpTemp = static_cast<HBITMAP>(SelectObject(enemyDC[i], bmpEnemy[i]));
		if (bmpTemp) DeleteObject(bmpTemp);
	}
}


/*
 * threadDraw
 * Desc: Thread function to draw main player hero and all other stuff on screen to in-memory window descriptor
 */
DWORD WINAPI threadDraw(LPVOID A)
{
	static auto w = 64, h = 64;
	srand(time(nullptr));

	BITMAP bm, bmSteve, bmBg, bmTree, bmStone,
	       bmHouse, bmHouseWall, bmHouseFloor, bmHpBar,
	       bmFireBall;

	BITMAP bmEnemy, bmHit;
	RECT rSteveUp;

	LoadResuorce();

	GetObject(hBitmap, sizeof(BITMAP), &bm);
	GetObject(hSteve, sizeof(BITMAP), &bmSteve);
	GetObject(bmpFon, sizeof(BITMAP), &bmBg);
	GetObject(bmpTree, sizeof(BITMAP), &bmTree);
	GetObject(bmpStone, sizeof(BITMAP), &bmStone);
	GetObject(bmpHouse, sizeof(BITMAP), &bmHouse);
	GetObject(bmpHouseWall, sizeof(BITMAP), &bmHouseWall);
	GetObject(bmpEnemy[0], sizeof(BITMAP), &bmEnemy);
	GetObject(bmpHit, sizeof(BITMAP), &bmHit);
	GetObject(bmpFloor, sizeof(BITMAP), &bmHouseFloor);
	GetObject(bmpHpBar, sizeof(BITMAP), &bmHpBar);
	GetObject(bmpFireBall, sizeof(BITMAP), &bmFireBall);

	wchar_t buff[256];

	auto treePos = 400, treePos1 = treePos - 200;
	int t = timeGetTime(), t1 = t;
	auto enF = 0;
	auto maxHpPl = 100, maxHpEn = 150;
	auto enR = TRUE, hitDraw = FALSE;
	xEn = treePos + 50;

	while (true)
	{
		float fx = -50, fy = -50;

		if (plHP <= 0)
		{
			MessageBox(hWnd, L"Game over !", L"", MB_OK);
			ExitProcess(0);
		}
		
		if (jump == FALSE && onGround != TRUE)
		{
			if (rWindow.bottom - yPl <= rWindow.bottom - (bm.bmHeight * 3))
			{
				yPl = bm.bmHeight * 3;
				onGround = TRUE;
			}
			else
				yPl -= 10;
		}
		if (jump == TRUE)
		{
			if (rWindow.bottom - yPl <= (rWindow.bottom - (bm.bmHeight * 3)) - 60)
			{
				onGround = FALSE;
				jump = FALSE;
			}
			else
			{
				yPl += 20;
			}
		}

		if (levels[lvl])
		{
			fx += xPl / 40;
			fy -= yPl / 100;
			auto x = 0;
			if (xPl >= xEn - 50 && xPl <= xEn + 50)
			{
				inFight = TRUE;
			}
			if (!inFight)
			{
				if (timeGetTime() - t >= 500)
				{
					if (xEn >= treePos1 - bmTree.bmWidth && xEn <= treePos + bmTree.bmWidth)
						enR = rand() % 2;
					else
					{
						if (xEn <= treePos + bmTree.bmWidth)
							enR = rand() % 2;
					}
					t = timeGetTime();
				}
				if (!enR)
				{
					if (xEn - 10 <= treePos1)
						xEn = treePos1;
					else
						xEn -= 10;
				}
				else
				{
					if (xEn + 10 >= treePos + bmTree.bmWidth)
						xEn = treePos + bmTree.bmWidth;
					else
						xEn += 10;
				}
			}
			else
			{
				if (xEn <= xPl - 25)
				{
					enR = TRUE;
					xEn += 10;
				}
				else if (xEn >= xPl + 45)
				{
					enR = FALSE;
					xEn -= 10;
				}
			}

			BgDraw(fx, fy, treePos, bm, bmStone, bmTree, bmHouse);
			if (xPl >= rWindow.right - bmHouse.bmWidth * 1.5)
			{
				xPl = rWindow.right - bmHouse.bmWidth * 1.5;
				xPl = 0;
				inHouse = TRUE;
				levels[lvl] = FALSE;
				lvl++;
			}
			if (mRight)
				TransparentBlt(cwinDC, rWindow.left + xPl, (rWindow.bottom - bm.bmHeight * 2) - (yPl - 12),
				               bmSteve.bmWidth, bmSteve.bmHeight, steveDC, 0, 0, bmSteve.bmWidth, bmSteve.bmHeight,
				               RGB(255, 255, 255));
			if (mLeft)
				TransparentBlt(cwinDC, rWindow.left + xPl, (rWindow.bottom - bm.bmHeight * 2) - (yPl - 12),
				               bmSteve.bmWidth, bmSteve.bmHeight, steveRDC, 0, 0, bmSteve.bmWidth, bmSteve.bmHeight,
				               RGB(255, 255, 255));

			TransparentBlt(cwinDC, treePos1, (rWindow.bottom - bm.bmHeight * 3) - (bmTree.bmHeight - 20),
			               bmTree.bmWidth, bmTree.bmHeight, treeDC, 0, 0, bmTree.bmWidth, bmTree.bmHeight,
			               RGB(255, 255, 255));

			if (enemyAlive == TRUE)
			{
				EnemyDraw(enR, enF, t, t1, maxHpEn, bmHpBar, bmEnemy, bm);
				enF += enF < 4 ? 1 : -enF;
 			}
			if (attack)
			{
				Attack(bmHit, bmSteve, bm);
				hitDraw = TRUE;
				rSteveUp.bottom = rWindow.bottom - bm.bmHeight * 3;
				rSteveUp.left = xPl;
				rSteveUp.right = rWindow.right - (xPl + bmSteve.bmWidth);
				rSteveUp.top = rWindow.top + (yPl - bmSteve.bmHeight);
			}
			else if (hitDraw == TRUE && timeGetTime() - t >= 120)
			{
				InvalidateRect(hWnd, &rSteveUp, FALSE);
				t = timeGetTime();
				hitDraw = FALSE;
			}

			TransparentBlt(cwinDC, rWindow.left + 10, rWindow.top + 10, bmHpBar.bmWidth * 4, bmHpBar.bmHeight * 2,
			               static_cast<HDC>(hpDC), 0, 0, bmHpBar.bmWidth, bmHpBar.bmHeight, RGB(255, 255, 255));
			auto c = wsprintf(buff, L"%d%s%d", plHP, L" / ", maxHpPl);
			SetBkMode(cwinDC, TRANSPARENT);
			hfont = CreateFont(0, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, nullptr);
			SelectObject(cwinDC, hfont);
			TextOut(cwinDC, rWindow.left + bmHpBar.bmWidth * 2 - 20, rWindow.top + bmHpBar.bmHeight, buff, c);
		}
		if (inHouse)
		{
			fx += xPl / 20;
			fy -= yPl / 50;
			DrawHouse(fx, fy, bmHouseWall, bmHouseFloor, bmSteve, bm);
		}

		InvalidateRect(hWnd, &rWindow, FALSE);
		Sleep(60);
	}
}

VOID BgDraw(int fx, int fy, int treePos,BITMAP bm, BITMAP bmStone, BITMAP bmTree, BITMAP bmHouse)
{
	auto x = 0;
	StretchBlt(cwinDC, fx, fy, rWindow.right + 100, rWindow.bottom + 80, fonDC, 0, 0, 1920, 1080, SRCCOPY);
	while (x <= rWindow.right)
	{
		StretchBlt(cwinDC, x, rWindow.bottom - bm.bmHeight * 3,
			bm.bmWidth * 3, bm.bmHeight * 3, groundDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		x += bm.bmWidth * 3;
	}
	TransparentBlt(cwinDC, treePos, (rWindow.bottom - bm.bmHeight * 3) - (bmTree.bmHeight - 8), bmTree.bmWidth,
		bmTree.bmHeight, treeDC, 0, 0, bmTree.bmWidth, bmTree.bmHeight, RGB(255, 255, 255));
	TransparentBlt(cwinDC, treePos - 20, (rWindow.bottom - bm.bmHeight * 3) - (bmStone.bmHeight - 10),
		bmStone.bmWidth, bmStone.bmHeight, stoneDC, 0, 0, bmStone.bmWidth, bmStone.bmHeight,
		RGB(255, 255, 255));
	//house
	TransparentBlt(cwinDC, rWindow.right - (bmHouse.bmWidth * 1.5),
		(rWindow.bottom - bm.bmHeight * 3) - (bmHouse.bmHeight * 1.5 - 20), bmHouse.bmWidth * 1.5,
		bmHouse.bmHeight * 1.5, houseDC, 0, 0, bmHouse.bmWidth, bmHouse.bmHeight,
		RGB(255, 255, 255));
}

VOID EnemyDraw(BOOL enR, int enF, int t, int t1, int maxHpEn, BITMAP bmHpBar, BITMAP bmEnemy,
               BITMAP bm)
{
	wchar_t buff[256];
	if (enHP <= 0) enemyAlive = FALSE;
	if (enR)
	{
		wsprintf(enemyName, L"%s%d%s", L"res/rEn/", enF, L".bmp");
		bmpEnemy[enF] = static_cast<HBITMAP>(LoadImage(nullptr, enemyName, IMAGE_BITMAP, 0, 0,
		                                               LR_LOADFROMFILE));
		bmpTemp = static_cast<HBITMAP>(SelectObject(enemyDC[enF], bmpEnemy[enF]));
		if (bmpTemp) DeleteObject(bmpTemp);
		TransparentBlt(cwinDC, xEn, (rWindow.bottom - bm.bmHeight * 2) - yEn, bmEnemy.bmWidth / 10,
		               bmEnemy.bmHeight / 10, static_cast<HDC>(enemyDC[enF]), 0, 0, bmEnemy.bmWidth,
		               bmEnemy.bmHeight, RGB(255, 255, 255));
		if (xPl >= xEn && xPl <= xEn + 100)
		{
			if (timeGetTime() - t > 1000)
			{
				plHP -= 10;
				t = timeGetTime();
			}
		}
	}
	if (!enR)
	{
		wsprintf(enemyName, L"%s%d%s", L"res/lEn/", enF, L".bmp");
		bmpEnemy[enF] = static_cast<HBITMAP>(LoadImage(nullptr, enemyName, IMAGE_BITMAP, 0, 0,
		                                               LR_LOADFROMFILE));
		bmpTemp = static_cast<HBITMAP>(SelectObject(enemyDC[enF], bmpEnemy[enF]));
		if (bmpTemp) DeleteObject(bmpTemp);
		TransparentBlt(cwinDC, xEn, (rWindow.bottom - bm.bmHeight * 2) - yEn, bmEnemy.bmWidth / 10,
		               bmEnemy.bmHeight / 10, static_cast<HDC>(enemyDC[enF]), 0, 0, bmEnemy.bmWidth,
		               bmEnemy.bmHeight, RGB(255, 255, 255));
		if (xPl >= xEn - 100 && xPl <= xEn)
		{
			if (timeGetTime() - t > 1000)
			{
				plHP -= 10;
				t = timeGetTime();
			}
		}
	}
	if (timeGetTime() - t1 > 100)
	{
		enF++;
		t1 = timeGetTime();
	}
	if (enF == 5)
		enF = 0;
	TransparentBlt(cwinDC, rWindow.left + xEn,
	               (rWindow.bottom - bm.bmHeight * 2) - (bmEnemy.bmHeight / 10) - yEn / 2, bmHpBar.bmWidth,
	               bmHpBar.bmHeight,
	               static_cast<HDC>(hpDC), 0, 0, bmHpBar.bmWidth, bmHpBar.bmHeight, RGB(255, 255, 255));
	auto c = wsprintf(buff, L"%d%s%d", enHP, L" / ", maxHpEn);
	SetBkMode(cwinDC, TRANSPARENT);
	hfont = ::CreateFontIndirect(&font);
	SelectObject(cwinDC, hfont);
	TextOut(cwinDC, rWindow.left + xEn + bmHpBar.bmWidth / 2 - 25,
	        (rWindow.bottom - bm.bmHeight * 2) - (bmEnemy.bmHeight / 10) - yEn / 2 + bmHpBar.bmHeight / 3,
	        buff, c);
}

VOID DrawHouse(int fx, int fy, BITMAP bmHouseWall, BITMAP bmHouseFloor, BITMAP bmSteve, BITMAP bm)
{
	StretchBlt(cwinDC, fx, fy, rWindow.right + 100, rWindow.bottom + 80, fonDC, 0, 0, 1920, 1080, SRCCOPY);
	TransparentBlt(cwinDC, -20, -20, rWindow.right + 50, rWindow.bottom - 200, houseWallDC, 0, 0,
	               bmHouseWall.bmWidth, bmHouseWall.bmHeight, RGB(255, 255, 255));
	TransparentBlt(cwinDC, -20, rWindow.bottom - 240, rWindow.right + 50, rWindow.bottom, houseFloorDC, 0, 0,
	               bmHouseFloor.bmWidth, bmHouseFloor.bmHeight, RGB(255, 255, 255));

	if (mRight)
		TransparentBlt(cwinDC, rWindow.left + xPl, (rWindow.bottom - bm.bmHeight * 20) - (yPl - 12),
		               bmSteve.bmWidth * 10, bmSteve.bmHeight * 10, steveDC, 0, 0, bmSteve.bmWidth,
		               bmSteve.bmHeight, RGB(255, 255, 255));
	if (mLeft)
		TransparentBlt(cwinDC, rWindow.left + xPl, (rWindow.bottom - bm.bmHeight * 20) - (yPl - 12),
		               bmSteve.bmWidth * 10, bmSteve.bmHeight * 10, steveRDC, 0, 0, bmSteve.bmWidth,
		               bmSteve.bmHeight, RGB(255, 255, 255));
}

VOID Attack(BITMAP bmHit, BITMAP bmSteve, BITMAP bm)
{
	if (mRight)
	{
		bmpHit = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hit.bmp", IMAGE_BITMAP, 0, 0,
		                                        LR_LOADFROMFILE));
		bmpTemp = static_cast<HBITMAP>(SelectObject(hitDC, bmpHit));
		if (bmpTemp) DeleteObject(bmpTemp);
		TransparentBlt(cwinDC, xPl + bmSteve.bmWidth - 30, (rWindow.bottom - bm.bmHeight * 3) - 50,
		               bmHit.bmWidth / 2, bmHit.bmHeight / 2, hitDC, 0, 0, bmHit.bmWidth, bmHit.bmHeight,
		               RGB(255, 255, 255) | RGB(255, 0, 0));
		if (xEn >= xPl && xEn <= xPl + bmSteve.bmWidth + bmHit.bmWidth)
		{
			enHP -= 5;
		}
	}
	if (mLeft)
	{
		bmpHit = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hitL.bmp", IMAGE_BITMAP, 0, 0,
		                                        LR_LOADFROMFILE));
		bmpTemp = static_cast<HBITMAP>(SelectObject(hitDC, bmpHit));
		if (bmpTemp) DeleteObject(bmpTemp);
		TransparentBlt(cwinDC, xPl, (rWindow.bottom - bm.bmHeight * 3) - 50, bmHit.bmWidth / 2,
		               bmHit.bmHeight / 2, hitDC, 0, 0, bmHit.bmWidth, bmHit.bmHeight,
		               RGB(255, 255, 255) | RGB(255, 0, 0));
		if (xEn >= xPl - bmHit.bmWidth && xEn <= xPl)
		{
			enHP -= 5;
		}
	}
}

VOID ClearRAM()
{
	TerminateThread(hThread, 0);
	if (hBitmap) DeleteObject(hBitmap);
	if (hSteve) DeleteObject(hSteve);
	if (bmpMem) DeleteObject(bmpMem);
	if (bmpTree) DeleteObject(bmpTree);
	if (bmpStone) DeleteObject(bmpStone);
	if (bmpFon) DeleteObject(bmpFon);
	if (bmpHpBar) DeleteObject(bmpHpBar);
	if (bmpFireBall) DeleteObject(bmpFireBall);
	for (auto& i : bmpEnemy)
		if (i) DeleteObject(i);

	if (cwinDC) DeleteDC(cwinDC);
	if (groundDC) DeleteDC(groundDC);
	if (steveDC) DeleteDC(steveDC);
	if (treeDC) DeleteDC(treeDC);
	if (stoneDC) DeleteDC(stoneDC);
	if (fonDC) DeleteDC(fonDC);
	if (hpDC) DeleteDC(hpDC);
	if (fireBallDC) DeleteDC(fireBallDC);
	for (auto& i : enemyDC)
		if (i) DeleteDC(i);
}