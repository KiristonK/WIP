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
HDC winDC, //контекст окна
		cwinDC, //контекст в памяти (копия окна) - прослойка между ресурсными контекстами и окном - на нем будем рисовать всё
		fonDC, //контекст с фоновым рисунком
		samDC; //контекст с самолетом
RECT rClient, //прямоугольник с клиентской частью
			rWindow, //прямоугольник всего окна
			rFon, //прямоугольник с фоном (будет использоваться, если обновлять будем только часть фона, а не весь)
			rSam, //прямоугольник с самолетом
			rcurSam; //текущий прямоугольник (куда мы рисуем самолет)
HANDLE hThread; //хэндл потока
HBITMAP bmpFon, //хэндл для хранения картинки-фона
				bmpSam, //самолет
				bmpMask, //маска
				bmpMem, //битмап, в котором будет храниться копия клиентской области
				bmpTemp; //временный хэндл

////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc (LPVOID A) {
	//Координаты самолета (потребуются при создании области перекрашивания)
	static int x = 500;
	static int y = 300;
	static int w = 160; //Ширина самолета 
	static int h = 120; //Высота

	HDC tempDC = GetDC (hwndMain); //Захватываем контекст окна (чтобы создать всё что нужно для него)
	cwinDC = CreateCompatibleDC (tempDC); //Контекст-прослойка между ресурсными контекстами и окном
	fonDC = CreateCompatibleDC (tempDC); //ресурсный контекст для хранения нетронутого фона
	samDC = CreateCompatibleDC (tempDC); //ресурсный контекст для хранения самолета
	
	//Загружаем все картинки
	bmpFon = (HBITMAP)LoadImage (NULL, "fon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpSam = (HBITMAP)LoadImage (NULL, "samolet.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpMask = (HBITMAP)LoadImage (NULL, "maska.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//Создаем пустой битмап для хранения всей картины (т.к. сам контекст это не хранит)
	//Именно в этом битмапе мы будем рисовать
	bmpMem = CreateCompatibleBitmap (tempDC, 800, 600);
	
	ReleaseDC (hwndMain, tempDC); //Отпускаем контекст окна
	
	bmpTemp = (HBITMAP)SelectObject (fonDC, bmpFon); //Прикручиваем битмап к контексту
	if (bmpTemp) DeleteObject (bmpTemp);
	
	bmpTemp = (HBITMAP)SelectObject (cwinDC, bmpMem);
	if (bmpTemp) DeleteObject (bmpTemp);
	
	bmpTemp = (HBITMAP)SelectObject (samDC, bmpSam);
	if (bmpTemp) DeleteObject (bmpTemp);
	
	//Запускаем бесконечный цикл для рисования
	while (true) {
		//Заполняем прямоугольник, который будет перекрашиваться 
		//Здесь я использую всё окно целиком, чтобы показать что мерцание в первую очередь зависит не от размера области, 
		//а от того, как вызывается оно
		rcurSam.left = 0;
		rcurSam.top = 0;
		rcurSam.right = 800;
		rcurSam.bottom = 600;
		
		//Изменяем Х для создания движения
		if (x < -300) {
			x = 900;
		} else {
			x -= 3;
		}
		

		//Сначала обновляем фон (можно сохранять старое положение самолета, чтобы не копировать весь фон, а обновлять только
		//этот участок)
		StretchBlt (cwinDC, 0, 0, rWindow.right, rWindow.bottom, fonDC, 0, 0, 1920, 1080, SRCCOPY);

		//Копируем на прослойку изображение самолета через маску
		MaskBlt(cwinDC, x, y, 160, 120, samDC, 0, 0, bmpMask, 0, 0, 0xaacc0020);
		//Еще пару самолетов
		MaskBlt(cwinDC, x + 150, y - 100, 160, 120, samDC, 0, 0, bmpMask, 0, 0, 0xaacc0020);
		MaskBlt(cwinDC, x + 150, y + 100, 160, 120, samDC, 0, 0, bmpMask, 0, 0, 0xaacc0020);
		
		//Посылаем сообщение WM_PAINT с обязательным указанием области перекрашивания, чтобы не обновлялись все
		//элементы окна и не было мерцания
		InvalidateRect (hwndMain, &rcurSam, false);
		
		Sleep (60); //Усыпляем потом на 60 мс
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WinMain (HINSTANCE funcH1, HINSTANCE funcH2, LPSTR funcStr, int funcShow) {
	MSG msgMain;
	WNDCLASS winClass;
	//Заполняем структуру для создания окна
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
	
	//Создаем прямоугольник клиентской части
	//rClient.left = 0;
	//rClient.top = 0;
	//rClient.bottom = 1000;
	//rClient.right = 1920;
	//rWindow = rClient;
	//AdjustWindowRectEx (&rWindow, WS_OVERLAPPEDWINDOW, false, 0); //Корректировка прямоугольника окна

	//Регистрируем класс и создаем окно
	if (!RegisterClass (&winClass)) err_ex ("no class");
	hwndMain=CreateWindow (
		winClass.lpszClassName,
		"Процесс запущен...",
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

	//Создание второго потока (функция ThreadProc), который будет перемещать самолет 
	//(и плюс еще создаст все необходимые ресурсы)
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
			//Убиваем поток и освобождаем память, которую заняли ресурсами
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
			//Копирование на окно из прослойки в памяти (буфера)
			//Здесь используется структура для указания области обновления (для примера у нас она занимает весь фон)
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