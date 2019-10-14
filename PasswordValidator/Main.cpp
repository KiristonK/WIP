#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, UINT, LONG);

class Password
{
public:
	Password() {
		setPassword();
	}
private:
	std::string password;
	struct rules
	{
		bool lenght = false;
		bool num = false;
		bool specialChar = false;
		bool spaces = true;
	}rule;
public : 
	void setPassword() {
		//cout << "Enter password to validate : ";
		rule = { 0 };
		password = "";
		int n = 0;
		char passw[255] = { 0 };
		//getline(cin, password);
		while ((passw[n] = _getch()) != '\r' && (n = n + 1)) {
			printf("%c", '*');
		}
		for (size_t i = 0; passw[i] != 0 &&  i < 255; i++){
			password += passw[i];
		}
	}
	std::string getPassword() {
		return password;
	}
	bool passwordCorrect() {
		system("cls");
		//cout << "Password : ";
		for (int i = 0; i < password.length(); i++)
			//cout << "*";
		//cout << "\n";
		for (int i = 0; i < password.length(); i++) {
			if (password[i] >= 48 && password[i] <= 57)
				rule.num = true;
			if (password[i] >= 33 && password[i] <= 47 || password[i] >= 58 && password[i] <= 64)
				rule.specialChar = true;
			if (password[i] == 32)
				rule.spaces = false;
		}
		if (password.length() >= 5 && password.length() <= 15)
			rule.lenght = true;
		if (rule.lenght == false) {
			//if (password.length() < 5)
				//cout << " - Password is too short !\n";
			//else
				//cout << " - Password is too long !\n";
			//cout << "Password minimum length is 5\nPassword maximum length is 15\n";
		}
		if (rule.num == false)
			//cout << "Password should contain at least one number !\n";
		if (rule.spaces == false)
			//cout << "Password should not contain spaces !\n";
		if (rule.specialChar == false)
			//cout << "Password should contain at least one special charakter (such as !,@,#,$,%,^,&,*,+,- etc)\n";
		
		if (rule.lenght == true && rule.num == true && rule.spaces == true && rule.specialChar == true) 
			return true;
		else
			return false;
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	WNDCLASS	WndClass;
	MSG			Msg;
	HWND		hWnd = NULL;
	LPCSTR		szClassName = "PasswordValidator";

	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;
	WndClass.hInstance		= hInstance;
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszClassName	= szClassName;
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	WndClass.lpszMenuName	= NULL;
	WndClass.cbClsExtra		= 0;
	WndClass.cbWndExtra		= 0;


	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, (LPCSTR)L"Cannot register class", (LPCSTR)L"Error", MB_OK);
		return 0;
	}

	hWnd = CreateWindowEx(WS_EX_TOPMOST, szClassName, (LPCSTR)L"Game",
		WS_OVERLAPPEDWINDOW | WS_BORDER,
		100,
		100,
		640,
		480,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		MessageBox(NULL, (LPCSTR)L"Cannot create window", (LPCSTR)L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hWnd, 3);
	UpdateWindow(hWnd);

	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	ExitProcess(0);
}

LRESULT CALLBACK WndProc(HWND funcHWND, UINT Message, UINT wParam, LONG lParam) {

	switch (Message)
	{
	case WM_DESTROY: {
		
	}break;
	case WM_PAINT:
		break;
	
	default: return DefWindowProc(funcHWND, Message, wParam, lParam);
	}
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	WinMain(hInstance, hPrevInstance, lpszCmdParam, nCmdShow);
	Password passwordToValidate;
	bool check = false;
	try {
		while (!check)
		{
			if (!passwordToValidate.passwordCorrect()) {
				passwordToValidate.setPassword();
			}
			else
				check = true;
		}
	}
	catch (std::exception) {
		//cout << "Error !\n";
		return 1;
	}
	//cout << "\nPassword correct!\n\nDo you want to see your password ? Y/N : ";
	try {
		if (_getch() == 'y' || _getch() == 'Y') {
			//cout << passwordToValidate.getPassword();
		}
		else
			if (_getch() == 'n' || _getch() == 'N')
				return 0;
			else
				throw 10;
	}
	catch (int i) {
		if (i == 10)
			//cout << "\n\nUsed default value : no !\n";
		system("pause");
		return 0;
	}
	system("pause");
	return 0;
}
