#include <windows.h>

#define err_ex(a) MessageBox(NULL,a,NULL,NULL),ExitProcess(NULL);

void SetMyText(HWND a,DWORD b) {
	static char buf1[20];
	wsprintf (buf1, "%d", (DWORD)b);
	SetWindowText (a, &buf1[0]);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK windowProc (HWND, UINT, WPARAM, LPARAM);

HINSTANCE hinstMain=GetModuleHandle(NULL);
HWND hwndMain=NULL;
HDC winDC, //�������� ����
		cwinDC, //�������� � ������ (����� ����) - ��������� ����� ���������� ����������� � ����� - �� ��� ����� �������� ��
		fonDC, //�������� � ������� ��������
		samDC; //�������� � ���������
RECT rClient, //������������� � ���������� ������
			rWindow, //������������� ����� ����
			rFon, //������������� � ����� (����� ��������������, ���� ��������� ����� ������ ����� ����, � �� ����)
			rSam, //������������� � ���������
			rcurSam; //������� ������������� (���� �� ������ �������)
HANDLE hThread; //����� ������
HBITMAP bmpFon, //����� ��� �������� ��������-����
				bmpSam, //�������
				bmpMask, //�����
				bmpMem, //������, � ������� ����� ��������� ����� ���������� �������
				bmpTemp; //��������� �����

////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc (LPVOID A) {
	//���������� �������� (����������� ��� �������� ������� ��������������)
	static int x = 500;
	static int y = 300;
	static int w = 160; //������ �������� 
	static int h = 120; //������

	HDC tempDC = GetDC (hwndMain); //����������� �������� ���� (����� ������� �� ��� ����� ��� ����)
	cwinDC = CreateCompatibleDC (tempDC); //��������-��������� ����� ���������� ����������� � �����
	fonDC = CreateCompatibleDC (tempDC); //��������� �������� ��� �������� ����������� ����
	samDC = CreateCompatibleDC (tempDC); //��������� �������� ��� �������� ��������
	
	//��������� ��� ��������
	bmpFon = (HBITMAP)LoadImage (NULL, "fon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpSam = (HBITMAP)LoadImage (NULL, "samolet.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpMask = (HBITMAP)LoadImage (NULL, "maska.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//������� ������ ������ ��� �������� ���� ������� (�.�. ��� �������� ��� �� ������)
	//������ � ���� ������� �� ����� ��������
	bmpMem = CreateCompatibleBitmap (tempDC, 800, 600);
	
	ReleaseDC (hwndMain, tempDC); //��������� �������� ����
	
	bmpTemp = (HBITMAP)SelectObject (fonDC, bmpFon); //������������ ������ � ���������
	if (bmpTemp) DeleteObject (bmpTemp);
	
	bmpTemp = (HBITMAP)SelectObject (cwinDC, bmpMem);
	if (bmpTemp) DeleteObject (bmpTemp);
	
	bmpTemp = (HBITMAP)SelectObject (samDC, bmpSam);
	if (bmpTemp) DeleteObject (bmpTemp);
	
	//��������� ����������� ���� ��� ���������
	while (true) {
		//��������� �������������, ������� ����� ��������������� 
		//����� � ��������� �� ���� �������, ����� �������� ��� �������� � ������ ������� ������� �� �� ������� �������, 
		//� �� ����, ��� ���������� ���
		rcurSam.left = 0;
		rcurSam.top = 0;
		rcurSam.right = 800;
		rcurSam.bottom = 600;
		
		//�������� � ��� �������� ��������
		if (x < -300) {
			x = 900;
		} else {
			x -= 3;
		}
		

		//������� ��������� ��� (����� ��������� ������ ��������� ��������, ����� �� ���������� ���� ���, � ��������� ������
		//���� �������)
		StretchBlt (cwinDC, 0, 0, rWindow.right, rWindow.bottom, fonDC, 0, 0, 1920, 1080, SRCCOPY);

		//�������� �� ��������� ����������� �������� ����� �����
		MaskBlt(cwinDC, x, y, 160, 120, samDC, 0, 0, bmpMask, 0, 0, 0xaacc0020);
		//��� ���� ���������
		MaskBlt(cwinDC, x + 150, y - 100, 160, 120, samDC, 0, 0, bmpMask, 0, 0, 0xaacc0020);
		MaskBlt(cwinDC, x + 150, y + 100, 160, 120, samDC, 0, 0, bmpMask, 0, 0, 0xaacc0020);
		
		//�������� ��������� WM_PAINT � ������������ ��������� ������� ��������������, ����� �� ����������� ���
		//�������� ���� � �� ���� ��������
		InvalidateRect (hwndMain, &rcurSam, false);
		
		Sleep (60); //�������� ����� �� 60 ��
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WinMain (HINSTANCE funcH1, HINSTANCE funcH2, LPSTR funcStr, int funcShow) {
	MSG msgMain;
	WNDCLASS winClass;
	//��������� ��������� ��� �������� ����
	winClass.style			= CS_HREDRAW|CS_VREDRAW ;
	winClass.lpfnWndProc	= (WNDPROC)windowProc;
	winClass.hInstance		= hinstMain;
	winClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	winClass.lpszClassName	= "osdufoasdf";
	winClass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	winClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
	winClass.lpszMenuName	= NULL;
	winClass.cbClsExtra		= 0;
	winClass.cbWndExtra		= 0;
	
	//������� ������������� ���������� �����
	//rClient.left = 0;
	//rClient.top = 0;
	//rClient.bottom = 1000;
	//rClient.right = 1920;
	//rWindow = rClient;
	//AdjustWindowRectEx (&rWindow, WS_OVERLAPPEDWINDOW, false, 0); //������������� �������������� ����

	//������������ ����� � ������� ����
	if (!RegisterClass (&winClass)) err_ex ("no class");
	hwndMain=CreateWindow (
		winClass.lpszClassName,
		"������� �������...",
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinstMain,
		NULL
	);

	GetClientRect(hwndMain, &rClient);
	rWindow = rClient;
	AdjustWindowRectEx(&rWindow, WS_OVERLAPPEDWINDOW, false, 0);

	//�������� ������� ������ (������� ThreadProc), ������� ����� ���������� ������� 
	//(� ���� ��� ������� ��� ����������� �������)
	hThread = CreateThread (NULL, 0, ThreadProc, NULL, NULL, NULL); 
	
	ShowWindow (hwndMain, SW_SHOW);
	UpdateWindow (hwndMain);
	
//SetMyText (hwndMain, rWindow.bottom - rWindow.top);
	while (GetMessage (&msgMain, NULL, 0, 0)) {
			DispatchMessage (&msgMain);
			TranslateMessage (&msgMain);
	}
	
	ExitProcess (0);
}
LRESULT CALLBACK windowProc (HWND funcHWND,UINT funcMSG, WPARAM funcWP, LPARAM funcLP) {
	static PAINTSTRUCT paintStruct;
	switch (funcMSG) {
		case  WM_DESTROY: {
			//������� ����� � ����������� ������, ������� ������ ���������
			if (hThread) {
				TerminateThread (hThread, 0);	
				if (bmpFon) DeleteObject (bmpFon);
				if (bmpSam) DeleteObject (bmpSam);
				if (bmpMask) DeleteObject (bmpMask);
				if (bmpMem) DeleteObject (bmpMem);
				if (cwinDC) DeleteDC (cwinDC);
				if (fonDC) DeleteDC (fonDC);
				if (samDC) DeleteDC (samDC);
			}
			ExitProcess (0);
		} break;
		case WM_PAINT: {
			//����������� �� ���� �� ��������� � ������ (������)
			//����� ������������ ��������� ��� �������� ������� ���������� (��� ������� � ��� ��� �������� ���� ���)
			winDC = BeginPaint (hwndMain, &paintStruct);
			StretchBlt (
				winDC, 
				paintStruct.rcPaint.left, 
				paintStruct.rcPaint.top, 
				paintStruct.rcPaint.right, 
				paintStruct.rcPaint.bottom, 
				cwinDC, 
				paintStruct.rcPaint.left, 
				paintStruct.rcPaint.top, 
				paintStruct.rcPaint.right, 
				paintStruct.rcPaint.bottom,
				SRCCOPY
			);
			EndPaint (hwndMain, &paintStruct);
		}break;
		default: return DefWindowProc (funcHWND, funcMSG, funcWP, funcLP);
		}
}
int main(HINSTANCE hInstance, HINSTANCE hPrewInstance,
	LPSTR lpszCmdParam, int nCmdShow) {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	WinMain(hInstance, hPrewInstance,
		lpszCmdParam, nCmdShow);
	return 0;
}