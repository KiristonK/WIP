#include <Windows.h>
#include <gdiplus.h>
#include <thread>
#include <ctime>

#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

#define err_ex(a) MessageBox(NULL,a,NULL,NULL),ExitProcess(NULL);

LRESULT CALLBACK GameWndProc(HWND, UINT, UINT, LONG);

HINSTANCE mainHinstace;
HWND hWnd = nullptr, hwndMenu = nullptr;

RECT rFon,
rSam,
rcurSam;
HANDLE hThread;
HANDLE hEnemyThread;


INT xPl = 1, yPl = 32 * 3;
INT xEn = 500, yEn = 32 * 3;


INT plHP = 100, enHP = 150;

BOOL jump = FALSE, onGround = TRUE, menu = FALSE, attack = FALSE;
BOOL mRight = TRUE, mLeft = FALSE, inFight = FALSE;
BOOL inHouse = FALSE;

HFONT hfont;
LOGFONT font;

wchar_t enemyName[] = L"res/rEn/0.bmp";

class game
{
	HWND hWnd{}, hWnd_Menu{};
	HDC fonDC,
		groundDC,
		treeDC,
		stoneDC,
		houseDC,
		houseWallDC,
		houseFloorDC,
		hitDC;
	HDC cwin_dc_, winDC;
	HBITMAP hBitmap,
		bmpFon,
		bmpMem,
		bmpTree,
		bmpStone,
		bmpHouse,
		bmpHouseWall,
		bmpFloor,
		bmpHpBar;
	RECT rClient, rWindow;
protected:
	BITMAP bm{};
	HDC hpDC;
private:
	BITMAP bmBg{}, bmSun{}, bmTree{}, bmStone{},
		bmHouse{}, bmHouseWall{}, bmHouseFloor{}, bmHpBar{};
	wchar_t buff[256];
	INT treePos = 400, treePos1 = 200;
	INT fx = -50, fy = -50;
	INT lvl = 0;
	BOOL levels_[10] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
public:
	HBITMAP bmpTemp;

	game()
	{
		GetWindowRect(hWnd, &rWindow);
		const HDC temp_dc = GetDC(hWnd);

		cwin_dc_ = CreateCompatibleDC(temp_dc);
		groundDC = CreateCompatibleDC(temp_dc);
		fonDC = CreateCompatibleDC(temp_dc);
		treeDC = CreateCompatibleDC(temp_dc);
		stoneDC = CreateCompatibleDC(temp_dc);
		houseDC = CreateCompatibleDC(temp_dc);
		houseWallDC = CreateCompatibleDC(temp_dc);
		houseFloorDC = CreateCompatibleDC(temp_dc);
		hitDC = CreateCompatibleDC(temp_dc);
		hpDC = CreateCompatibleDC(temp_dc);


		bmpFon = static_cast<HBITMAP>(LoadImage(nullptr, L"res/fon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hBitmap = static_cast<HBITMAP>(LoadImage(nullptr, L"res/Grass.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		bmpTree = static_cast<HBITMAP>(LoadImage(nullptr, L"res/TreeBig.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		bmpStone = static_cast<HBITMAP>(LoadImage(nullptr, L"res/stoneGrassed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)
			);
		bmpHouse = static_cast<HBITMAP>(LoadImage(nullptr, L"res/House.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		bmpHouseWall = static_cast<HBITMAP>(LoadImage(nullptr, L"res/houseWall.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE));
		bmpFloor = static_cast<HBITMAP>(LoadImage(nullptr, L"res/floor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		bmpHpBar = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hpBar.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

		bmpMem = CreateCompatibleBitmap(temp_dc, rClient.right, rClient.bottom);

		ReleaseDC(hWnd, temp_dc);

		bmpTemp = static_cast<HBITMAP>(SelectObject(fonDC, bmpFon));
		if (bmpTemp) DeleteObject(bmpTemp);

		bmpTemp = static_cast<HBITMAP>(SelectObject(groundDC, hBitmap));
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

		bmpTemp = static_cast<HBITMAP>(SelectObject(cwin_dc_, bmpMem));
		if (bmpTemp) DeleteObject(bmpTemp);

		GetObject(hBitmap, sizeof(BITMAP), &bm);
		GetObject(bmpFon, sizeof(BITMAP), &bmBg);
		GetObject(bmpTree, sizeof(BITMAP), &bmTree);
		GetObject(bmpStone, sizeof(BITMAP), &bmStone);
		GetObject(bmpHouse, sizeof(BITMAP), &bmHouse);
		GetObject(bmpHouseWall, sizeof(BITMAP), &bmHouseWall);
		GetObject(bmpFloor, sizeof(BITMAP), &bmHouseFloor);
		GetObject(bmpHpBar, sizeof(BITMAP), &bmHpBar);
	}

	~game()
	{
		if (hBitmap) DeleteObject(hBitmap);
		if (bmpMem) DeleteObject(bmpMem);
		if (bmpTree) DeleteObject(bmpTree);
		if (bmpStone) DeleteObject(bmpStone);
		if (bmpFon) DeleteObject(bmpFon);
		if (bmpHpBar) DeleteObject(bmpHpBar);

		if (cwin_dc_) DeleteDC(cwin_dc_);
		if (groundDC) DeleteDC(groundDC);
		if (treeDC) DeleteDC(treeDC);
		if (stoneDC) DeleteDC(stoneDC);
		if (fonDC) DeleteDC(fonDC);
		if (hpDC) DeleteDC(hpDC);
	}

	VOID lobbyEnter()
	{
		if (xPl >= rWindow.right - bmHouse.bmWidth * 1.5)
		{
			xPl = rWindow.right - bmHouse.bmWidth * 1.5;
			xPl = 0;
			inHouse = TRUE;
			setLevel(lvl, FALSE);
			lvl++;
		}
	}

	VOID setLevel(INT i, BOOL state)
	{
		levels_[i] = state;
	}

	INT getLevel() const
	{
		return lvl;
	}

	VOID bgDraw(int x)
	{
		fx += xPl / 40;
		fy -= yPl / 100;
		StretchBlt(cwin_dc_, fx, fy, rWindow.right + 100, rWindow.bottom + 80, fonDC, 0, 0, 1920, 1080, SRCCOPY);
		while (x <= rWindow.right)
		{
			StretchBlt(cwin_dc_, x, rWindow.bottom - bm.bmHeight * 3,
				bm.bmWidth * 3, bm.bmHeight * 3, groundDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
			x += bm.bmWidth * 3;
		}
		TransparentBlt(cwin_dc_, treePos, (rWindow.bottom - bm.bmHeight * 3) - (bmTree.bmHeight - 8), bmTree.bmWidth,
			bmTree.bmHeight, treeDC, 0, 0, bmTree.bmWidth, bmTree.bmHeight, RGB(255, 255, 255));
		TransparentBlt(cwin_dc_, treePos - 20, (rWindow.bottom - bm.bmHeight * 3) - (bmStone.bmHeight - 10),
			bmStone.bmWidth, bmStone.bmHeight, stoneDC, 0, 0, bmStone.bmWidth, bmStone.bmHeight,
			RGB(255, 255, 255));
		TransparentBlt(cwin_dc_, treePos1, (rWindow.bottom - bm.bmHeight * 3) - (bmTree.bmHeight - 20),
			bmTree.bmWidth, bmTree.bmHeight, treeDC, 0, 0, bmTree.bmWidth, bmTree.bmHeight,
			RGB(255, 255, 255));
		TransparentBlt(cwin_dc_, rWindow.right - (bmHouse.bmWidth * 1.5),
			(rWindow.bottom - bm.bmHeight * 3) - (bmHouse.bmHeight * 1.5 - 20), bmHouse.bmWidth * 1.5,
			bmHouse.bmHeight * 1.5, houseDC, 0, 0, bmHouse.bmWidth, bmHouse.bmHeight,
			RGB(255, 255, 255));
	}

	VOID houseDraw()
	{
		fx += xPl / 20;
		fy -= yPl / 50;
		StretchBlt(cwin_dc_, fx, fy, rWindow.right + 100, rWindow.bottom + 80, fonDC, 0, 0, 1920, 1080, SRCCOPY);
		TransparentBlt(cwin_dc_, -20, -20, rWindow.right + 50, rWindow.bottom - 200, houseWallDC, 0, 0,
			bmHouseWall.bmWidth, bmHouseWall.bmHeight, RGB(255, 255, 255));
		TransparentBlt(cwin_dc_, -20, rWindow.bottom - 240, rWindow.right + 50, rWindow.bottom, houseFloorDC, 0, 0,
			bmHouseFloor.bmWidth, bmHouseFloor.bmHeight, RGB(255, 255, 255));
	}

	VOID hpDraw(int maxHpPl)
	{
		TransparentBlt(cwin_dc_, rWindow.left + 10, rWindow.top + 10, bmHpBar.bmWidth * 4, bmHpBar.bmHeight * 2,
			static_cast<HDC>(hpDC), 0, 0, bmHpBar.bmWidth, bmHpBar.bmHeight, RGB(255, 255, 255));
		int c = wsprintf(buff, L"%d%s%d", plHP, L" / ", maxHpPl);
		SetBkMode(cwin_dc_, TRANSPARENT);
		hfont = CreateFont(0, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, nullptr);
		SelectObject(cwin_dc_, hfont);
		TextOut(cwin_dc_, rWindow.left + bmHpBar.bmWidth * 2 - 20, rWindow.top + bmHpBar.bmHeight, buff, c);
	}

	void restart()
	{
		xPl = 0;
		yPl = 32 * 3;
		if (inFight) inFight = FALSE;
		if (inHouse)
		{
			inHouse = FALSE;
			lvl--;
			levels_[lvl] = TRUE;
		}
		enHP = 150;
	}

	void GetClientRect(HWND hwnd)
	{
		::GetClientRect(hwnd, &rClient);
		rWindow = rClient;
		AdjustWindowRectEx(&rWindow, WS_OVERLAPPED | WS_MAXIMIZE | WS_EX_STATICEDGE, FALSE, 0);
	}

	HDC* setWinDC()
	{
		return &winDC;
	}

	VOID getDC(HDC* destHDC, int i)
	{
		i == 0 ? destHDC = &cwin_dc_ : destHDC = &hpDC;
	}

	int GetTreePos(int i) const
	{
		if (i == 0)
			return treePos;
		return treePos1;
	}

	BOOL getLevel()
	{
		return levels_[lvl];
	}

	RECT getWindowRECT() const
	{
		return rWindow;
	}


	BITMAP getBM() const
	{
		return bm;
	}

	BITMAP getBmTree() const
	{
		return bmTree;
	}

	HWND getHWND() const
	{
		return hWnd;
	}
} Game{};

class player : public game
{
private:
	BITMAP bm_{}, bm_tree_{}, bm_steve_{}, bmHit{};
	HBITMAP hSteve,
		hSteveR, bmpHit;
	HDC cwin_dc_{}, steveDC,
		steveRDC, hitDC, hpDC;
	RECT rSteveUp;
	RECT rWindow = getWindowRECT();
	BOOL hitDraw = FALSE;
	const int maxPlHp = 100;
public:
	player()
	{
		bm_tree_ = getBmTree();
		bm_ = getBM();
		getDC(&cwin_dc_, 0);
		getDC(&hpDC, 1);
		const HDC temp_dc = GetDC(getHWND()); // NOLINT(misc-misplaced-const)
		steveDC = CreateCompatibleDC(temp_dc);
		steveRDC = CreateCompatibleDC(temp_dc);
		hitDC = CreateCompatibleDC(temp_dc);

		hSteve = static_cast<HBITMAP>(LoadImage(nullptr, L"res/Steve.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hSteveR = static_cast<HBITMAP>(LoadImage(nullptr, L"res/SteveR.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

		bmpTemp = static_cast<HBITMAP>(SelectObject(steveDC, hSteve));
		if (bmpTemp) DeleteObject(bmpTemp);

		bmpTemp = static_cast<HBITMAP>(SelectObject(steveRDC, hSteveR));
		if (bmpTemp) DeleteObject(bmpTemp);

		bmpTemp = static_cast<HBITMAP>(SelectObject(hitDC, bmpHit));
		if (bmpTemp) DeleteObject(bmpTemp);

		GetObject(hSteve, sizeof(BITMAP), &bm_steve_);
	}

	~player()
	{
		if (hSteve) DeleteObject(hSteve);

		if (steveDC) DeleteDC(steveDC);

		if (hpDC) DeleteDC(hpDC);
	}

	void jumping() const
	{
		if (jump == FALSE && onGround != TRUE)
		{
			if (rWindow.bottom - yPl <= rWindow.bottom - 3 * bm_.bmHeight)
			{
				yPl = bm_.bmHeight * 3;
				onGround = TRUE;
			}
			else
				yPl -= 10;
		}
		if (jump == TRUE)
		{
			if (rWindow.bottom - yPl <= (rWindow.bottom - (bm_.bmHeight * 3)) - 60)
			{
				onGround = FALSE;
				jump = FALSE;
			}
			else
			{
				yPl += 20;
			}
		}
	}

	VOID playerDraw() const
	{
		if (mRight)
			TransparentBlt(cwin_dc_, rWindow.left + xPl, (rWindow.bottom - bm_.bmHeight * 2) - (yPl - 12),
				bm_steve_.bmWidth, bm_steve_.bmHeight, steveDC, 0, 0, bm_steve_.bmWidth, bm_steve_.bmHeight,
				RGB(255, 255, 255));
		if (mLeft)
			TransparentBlt(cwin_dc_, rWindow.left + xPl, (rWindow.bottom - bm_.bmHeight * 2) - (yPl - 12),
				bm_steve_.bmWidth, bm_steve_.bmHeight, steveRDC, 0, 0, bm_steve_.bmWidth, bm_steve_.bmHeight,
				RGB(255, 255, 255));
	}

	VOID inFight(int t, BOOL enR) const
	{
		if (timeGetTime() - t >= 500)
		{
			if (xEn >= GetTreePos(1) - bm_tree_.bmWidth && xEn <= GetTreePos(0) + bm_tree_.bmWidth)
				enR = rand() % 2;
			else
			{
				if (xEn <= GetTreePos(0) + bm_tree_.bmWidth)
					enR = rand() % 2;
			}
			t = timeGetTime();
		}
		if (!enR)
		{
			if (xEn - 10 <= GetTreePos(1))
				xEn = GetTreePos(1);
			else
				xEn -= 10;
		}
		else
		{
			if (xEn + 10 >= GetTreePos(0) + bm_tree_.bmWidth)
				xEn = GetTreePos(0) + bm_tree_.bmWidth;
			else
				xEn += 10;
		}
	}

	VOID attack()
	{
		if (mRight)
		{
			bmpHit = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hit.bmp", IMAGE_BITMAP, 0, 0,
				LR_LOADFROMFILE));
			bmpTemp = static_cast<HBITMAP>(SelectObject(hitDC, bmpHit));
			if (bmpTemp) DeleteObject(bmpTemp);
			TransparentBlt(cwin_dc_, xPl + bm_steve_.bmWidth - 30, (rWindow.bottom - bm.bmHeight * 3) - 50,
				bmHit.bmWidth / 2, bmHit.bmHeight / 2, hitDC, 0, 0, bmHit.bmWidth, bmHit.bmHeight,
				RGB(255, 255, 255) | RGB(255, 0, 0));
			if (xEn >= xPl && xEn <= xPl + bm_steve_.bmWidth + bmHit.bmWidth)
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
			TransparentBlt(cwin_dc_, xPl, (rWindow.bottom - bm.bmHeight * 3) - 50, bmHit.bmWidth / 2,
				bmHit.bmHeight / 2, hitDC, 0, 0, bmHit.bmWidth, bmHit.bmHeight,
				RGB(255, 255, 255) | RGB(255, 0, 0));
			if (xEn >= xPl - bmHit.bmWidth && xEn <= xPl)
			{
				enHP -= 5;
			}
		}
		hitDraw = TRUE;
		rSteveUp.bottom = rWindow.bottom - bm.bmHeight * 3;
		rSteveUp.left = xPl;
		rSteveUp.right = rWindow.right - (xPl + bm_steve_.bmWidth);
		rSteveUp.top = rWindow.top + (yPl - bm_steve_.bmHeight);
	}

	RECT getPlayerRect() const
	{
		return rSteveUp;
	}

	int getHP() const
	{
		return maxPlHp;
	}
} Player{};

class enemy : public game
{
	BOOL enemyAlive = TRUE, enR = TRUE;
	HDC cwin_dc_{}, hpDC, enemyDC[5]{};
	BITMAP bmEnemy{}, bmHpBar{};
	HBITMAP bmpEnemy[5]{};
	RECT rWindow = getWindowRECT();
	int enF;
	const int maxHpEn = 150;
	wchar_t buff[256]{};
public:
	enemy()
	{
		enF = 0;
		const HDC temp_dc = GetDC(getHWND()); // NOLINT(misc-misplaced-const)
		hpDC = CreateCompatibleDC(temp_dc);
		for (auto& i : enemyDC)
		{
			i = CreateCompatibleDC(temp_dc);
		}

		for (int i = 0; i < 5; i++)
		{
			wsprintf(enemyName, L"%s%d%s", L"res/rEn/", i, L".bmp");
			bmpEnemy[i] = static_cast<HBITMAP>(LoadImage(nullptr, enemyName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		}

		for (int i = 0; i < 5; i++)
		{
			bmpTemp = static_cast<HBITMAP>(SelectObject(enemyDC[i], bmpEnemy[i]));
			if (bmpTemp) DeleteObject(bmpTemp);
		}
	}

private:
	VOID enemyMoving(int t, int t1)
	{
		if (enemyAlive == TRUE)
		{
			if (enHP <= 0) enemyAlive = FALSE;
			if (enR)
			{
				wsprintf(enemyName, L"%s%d%s", L"res/rEn/", enF, L".bmp");
				bmpEnemy[enF] = static_cast<HBITMAP>(LoadImage(nullptr, enemyName, IMAGE_BITMAP, 0, 0,
					LR_LOADFROMFILE));
				bmpTemp = static_cast<HBITMAP>(SelectObject(enemyDC[enF], bmpEnemy[enF]));
				if (bmpTemp) DeleteObject(bmpTemp);
				TransparentBlt(cwin_dc_, xEn, (rWindow.bottom - bm.bmHeight * 2) - yEn, bmEnemy.bmWidth / 10,
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
				TransparentBlt(cwin_dc_, xEn, (rWindow.bottom - bm.bmHeight * 2) - yEn, bmEnemy.bmWidth / 10,
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

			int c = wsprintf(buff, L"%d%s%d", enHP, L" / ", maxHpEn);
			SetBkMode(cwin_dc_, TRANSPARENT);
			hfont = ::CreateFontIndirect(&font);
			SelectObject(cwin_dc_, hfont);
			TextOut(cwin_dc_, rWindow.left + xEn + bmHpBar.bmWidth / 2 - 25,
				(rWindow.bottom - bm.bmHeight * 2) - (bmEnemy.bmHeight / 10) - yEn / 2 + bmHpBar.bmHeight / 3,
				buff, c);
		}
	}

public:
	VOID enemyDraw() const
	{
		TransparentBlt(cwin_dc_, rWindow.left + xEn,
			(rWindow.bottom - bm.bmHeight * 2) - (bmEnemy.bmHeight / 10) - yEn / 2, bmHpBar.bmWidth,
			bmHpBar.bmHeight,
			static_cast<HDC>(hpDC), 0, 0, bmHpBar.bmWidth, bmHpBar.bmHeight, RGB(255, 255, 255));
	}
} Enemy{};

//
//VOID LoadResource()
//{
//	const HDC tempDC = GetDC(hWnd);
//
//	
//	hpDC = CreateCompatibleDC(tempDC);
//	fireBallDC = CreateCompatibleDC(tempDC);
//
//	
//
//	bmpFon = static_cast<HBITMAP>(LoadImage(nullptr, L"res/fon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	hBitmap = static_cast<HBITMAP>(LoadImage(nullptr, L"res/Grass.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpTree = static_cast<HBITMAP>(LoadImage(nullptr, L"res/TreeBig.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpStone = static_cast<HBITMAP>(LoadImage(nullptr, L"res/stoneGrassed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpHouse = static_cast<HBITMAP>(LoadImage(nullptr, L"res/House.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpHouseWall = static_cast<HBITMAP>(LoadImage(nullptr, L"res/houseWall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpHit = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hit.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpFloor = static_cast<HBITMAP>(LoadImage(nullptr, L"res/floor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpHpBar = static_cast<HBITMAP>(LoadImage(nullptr, L"res/hpBar.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
//	bmpFireBall = static_cast<HBITMAP>(LoadImage(nullptr, L"res/fireBallDark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)
//	);
//
//	
//
//	bmpMem = CreateCompatibleBitmap(tempDC, rClient.right, rClient.bottom);
//
//	ReleaseDC(hWnd, tempDC);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(fonDC, bmpFon));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(groundDC, hBitmap));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	
//	bmpTemp = static_cast<HBITMAP>(SelectObject(treeDC, bmpTree));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(houseDC, bmpHouse));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(stoneDC, bmpStone));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(houseWallDC, bmpHouseWall));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(houseFloorDC, bmpFloor));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(hpDC, bmpHpBar));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(fireBallDC, bmpFireBall));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	bmpTemp = static_cast<HBITMAP>(SelectObject(cwin_dc_, bmpMem));
//	if (bmpTemp) DeleteObject(bmpTemp);
//
//	
//}

DWORD WINAPI threadDraw(LPVOID a)
{
	static int w = 64, h = 64;
	srand(time(nullptr));

	BOOL enemyAlive = TRUE;


	int t = timeGetTime();
	BOOL enR = TRUE, hitDraw = FALSE;
	xEn = 450;

	while (true)
	{
		Player.jumping();

		if (Game.getLevel())
		{
			int x = 0;
			if (xPl >= xEn - 50 && xPl <= xEn + 50)
			{
				inFight = TRUE;
			}
			if (!inFight)
			{
				Player.inFight(t, enR);
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


			//house
			Game.bgDraw(x);
			Game.lobbyEnter();

			Enemy.enemyDraw();

			if (attack)
			{
				Player.attack();
			}
			else if (hitDraw == TRUE && timeGetTime() - t >= 120)
			{
				InvalidateRect(hWnd, &Player.getPlayerRect(), FALSE);
				t = timeGetTime();
				hitDraw = FALSE;
			}

			Game.hpDraw(Player.getHP());
		}
		if (inHouse)
		{
			Game.houseDraw();
			Player.playerDraw();
		}

		InvalidateRect(hWnd, &Game.getWindowRECT(), FALSE);
		Sleep(60);
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrewInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WNDCLASS WndClass;
	MSG Msg;
	const LPCWSTR szClassName = L"Game";

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = static_cast<WNDPROC>(GameWndProc);
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndClass.lpszClassName = szClassName;
	WndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WndClass.lpszMenuName = nullptr;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;


	if (!RegisterClass(&WndClass))
	{
		MessageBox(nullptr, static_cast<LPCWSTR>(L"Cannot register class"), static_cast<LPCWSTR>(L"Error"), MB_OK);
		return 0;
	}

	hWnd = CreateWindowEx(WS_EX_TOPMOST, szClassName, static_cast<LPCWSTR>(L"Game"),
		WS_MAXIMIZE | (WS_OVERLAPPEDWINDOW) & ~WS_MAXIMIZEBOX | WS_BORDER,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		MessageBox(nullptr, static_cast<LPCWSTR>(L"Cannot create window"), static_cast<LPCWSTR>(L"Error"), MB_OK);
		return 0;
	}

	Game.GetClientRect(hWnd);


	mainHinstace = hInstance;
	hThread = CreateThread(nullptr, 0, threadDraw, nullptr, NULL, nullptr);

	font.lfHeight = 10; // Устанавливает высоту шрифта или символа
	font.lfWidth = 0; // Устанавливает среднюю ширину символов в шрифте
	font.lfEscapement = 0; // Устанавливает угол, между вектором наклона и осью X устройства
	font.lfOrientation = 0; // Устанавливает угол, между основной линией каждого символа и осью X устройства
	font.lfWeight = 800; // Устанавливает толщину шрифта в диапазоне от 0 до 1000
	font.lfItalic = 0; // Устанавливает курсивный шрифт
	font.lfUnderline = 0; // Устанавливает подчеркнутый шрифт
	font.lfStrikeOut = 0; // Устанавливает зачеркнутый шрифт
	font.lfCharSet = RUSSIAN_CHARSET; // Устанавливает набор символов
	font.lfOutPrecision = 0; // Устанавливает точность вывода
	font.lfClipPrecision = 0; // Устанавливает точность отсечения
	font.lfQuality = 0; // Устанавливает качество вывода
	font.lfPitchAndFamily = 0; // Устанавливает ширину символов и семейство шрифта
	wsprintf(font.lfFaceName, L"VERDANA"); //  устанавливает название шрифта

	hfont = ::CreateFontIndirect(&font);

	ShowWindow(hWnd, 3);
	UpdateWindow(hWnd);

	while (GetMessage(&Msg, nullptr, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	ExitProcess(0);
}


LRESULT __stdcall GameWndProc(HWND funcHWND, UINT Message, UINT wParam, LONG lParam)
{
	PAINTSTRUCT PaintStruct;
	RECT rWindow = Game.getWindowRECT();
	HDC* cwinDC = nullptr;
	HDC* winDC;
	switch (Message)
	{
	case WM_DESTROY:
	{
		if (hThread)
		{
			TerminateThread(hThread, 0);

			ExitProcess(0);
		}
	}
	break;
	case WM_PAINT:
		rWindow = Game.getWindowRECT();
		winDC = Game.setWinDC();
		Game.getDC(cwinDC, 0);
		*winDC = BeginPaint(hWnd, &PaintStruct);
		StretchBlt(
			*winDC,
			rWindow.left,
			rWindow.top,
			rWindow.right,
			rWindow.bottom,
			*cwinDC,
			rWindow.left,
			rWindow.top,
			rWindow.right,
			rWindow.bottom,
			SRCCOPY
		);
		EndPaint(hWnd, &PaintStruct);
		return 0;
	case WM_KEYDOWN:
		if (GetAsyncKeyState(VK_UP) < 0 && onGround == TRUE || GetKeyState(VK_SPACE) && onGround == TRUE ||
			LOWORD(wParam) == 'w' && onGround == TRUE || LOWORD(wParam) == 'W' && onGround == TRUE)
		{
			jump = TRUE;
			onGround = FALSE;
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0 || LOWORD(wParam) == 'd' || LOWORD(wParam) == 'D')
		{
			!inHouse
				? (xPl + 64 >= rWindow.right)
				? xPl = rWindow.right - 64
				: xPl += 10
				: (xPl + 190 >= rWindow.right)
				? xPl = rWindow.right - 190
				: xPl += 10;
			mRight = TRUE;
			mLeft = FALSE;
		}
		if (GetAsyncKeyState(VK_LEFT) < 0 || LOWORD(wParam) == 'a' || LOWORD(wParam) == 'A')
		{
			!inHouse
				? (xPl - 24 <= rWindow.left)
				? xPl = rWindow.left
				: xPl -= 10
				: (xPl + 190 <= rWindow.left)
				? xPl = rWindow.left - 190
				: xPl -= 10;
			mRight = FALSE;
			mLeft = TRUE;
		}
		if (LOWORD(wParam) == 'f' || LOWORD(wParam) == 'F')
		{
			attack = TRUE;
		}

		if (LOWORD(wParam) == 'r' || LOWORD(wParam) == 'R')
		{
			const int msgResult = MessageBox(hWnd, L"Do you really want restart game ?", L"Caution, game restart !",
				MB_YESNO);
			if (msgResult == 6)
			{
				Game.restart();
			}
		}

		if (GetKeyState(VK_ESCAPE) < 0)
		{
			MessageBox(hWnd, L"Menu body", L"Main menu", NULL);
		}

		return 0;
	case WM_KEYUP:
		if (LOWORD(wParam) == 'f' || LOWORD(wParam) == 'F')
		{
			attack = FALSE;
		}
		return 0;
	default: return DefWindowProc(funcHWND, Message, wParam, lParam);
	}
	return 0;
}

int main(HINSTANCE hInstance, HINSTANCE hPrewInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	WinMain(hInstance, hPrewInstance,
		lpszCmdParam, nCmdShow);
	return 0;
}
