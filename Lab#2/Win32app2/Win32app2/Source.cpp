#include<windows.h>
#include<math.h>
#include "resource.h"

LPCWSTR ClassName = L"mainClass";

HWND TextBox;
HWND hWndSizeBox;
HINSTANCE hInstance;


LRESULT CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

	case WM_CREATE:
		CreateWindowW(L"button", L"Ok",
			WS_VISIBLE | WS_CHILD,
			100, 100, 80, 25, hwnd, (HMENU)1, NULL, NULL);
		break;

	case WM_COMMAND:
		DestroyWindow(hwnd);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	}

	return (DefWindowProcW(hwnd, msg, wParam, lParam));
}


void CreateDialogBox(HWND hwnd) {

	CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, TEXT("DialogClass"), L"Dialog Box",
		WS_VISIBLE | WS_SYSMENU | WS_CAPTION, 0, 0, 350, 250,
		NULL, NULL, hInstance, NULL);
}


void RegisterDialogClass(HWND hwnd) {
	WNDCLASSEXW wndc = { 0 };
	BOOL  CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);
	
	wndc.cbSize = sizeof(WNDCLASSEXW);
	wndc.lpfnWndProc = (WNDPROC)DialogProc;
	wndc.hInstance = hInstance;
	wndc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wndc.lpszClassName = TEXT("DialogClass");
	RegisterClassExW(&wndc);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	HDC ContextHandle;
	PAINTSTRUCT PaintStructure;
	RECT ClientRectangle;
	LPCWSTR MyText = L"Done with Pride and Prejudice by Danny!";
	int cxClient, cyClient;



	switch (Msg)
	{
	////////////////////////////////////
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	////////////////////////////////////
	case WM_CREATE:
	{

		RegisterDialogClass(hwnd);
		HMENU menu =  GetSystemMenu(hwnd, TRUE);
		LPCWSTR button01_ID = L"BUTTON";
		LPCWSTR button01_text = L"FONT";
		HWND button01 = CreateWindowEx(WS_EX_WINDOWEDGE, button01_ID, button01_text, BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_CHILD, 5, 5, 105, 25, hwnd, (HMENU)BUTTON_01, NULL, NULL);

		LPCWSTR button02_ID = L"BUTTON";
		LPCWSTR button02_text = L"DIALOG BOX";
		HWND button02 = CreateWindowEx(NULL, button02_ID, button02_text, BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_CHILD, 5, 35, 105, 25, hwnd, (HMENU)BUTTON_02, NULL, NULL);

		hWndSizeBox = CreateWindowEx(NULL, TEXT("Scrollbar"), 0, WS_CHILD | WSF_VISIBLE | WS_VISIBLE | SBS_SIZEBOXTOPLEFTALIGN, 50, 100, 0, NULL, hwnd, (HMENU)NULL, NULL, NULL);
		

	}
	break;
	//////////////////////////////////
	case WM_PAINT:
		ContextHandle = BeginPaint(hwnd, &PaintStructure);
		GetClientRect(hwnd, &ClientRectangle);
		/*DrawText(ContextHandle, MyText, -1,
			&ClientRectangle, DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/

		EndPaint(hwnd, &PaintStructure);

		return 0;
	//////////////////////////////////
	case WM_COMMAND:

	{
		switch (LOWORD(wParam)) {

		
		case BUTTON_01: {
			
			HFONT Font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Times New Roman"));
			SendMessage(TextBox, WM_SETFONT, (WPARAM)Font, TRUE);
			break; }
		case BUTTON_02: {
			
			CreateDialogBox(hwnd);
			
			break; }
		}
	}

	break;

	//////////////////////////////
	case WM_KEYDOWN:   // keyboard input
	{
		switch (wParam)
		{
		case KEY_C: {  // LeftSHIFT + E
			if (GetAsyncKeyState(VK_LSHIFT)) {
				if (MessageBox(hwnd, L"Do you want to exit?", L"Exit", MB_OKCANCEL) == IDOK)
					DestroyWindow(hwnd);
			}
			break;
		}
		case KEY_SPACE:
			if (GetAsyncKeyState(VK_LCONTROL)) {
				HBRUSH brush = CreateSolidBrush(RGB(100, 23, 31));

				SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
				RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME);
				MessageBox(NULL, L"Background color changed", L"ATENTION", NULL);
			}
			break;
		}
	}
	/////////////////////////////
	case WM_SYSCOMMAND:
		switch (LOWORD(wParam)) {
		case IDM_SYS_CHANGE: {
			HBRUSH brush1 = (HBRUSH)GetStockObject(WHITE_BRUSH);
			SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush1);
			RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME);
			break;
		}
		case IDM_SYS_ABOUT: {
			MessageBox(NULL, L"Done by FaF sTudent!", L"ATENTION", NULL);
		}
							return 0;
		case IDM_SYS_HELP: {
			TextBox = CreateWindowEx((DWORD)NULL, TEXT("EDIT"), TEXT("DEFAULT FONT"), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | DT_VCENTER,

			5, 65, 200, 25, hwnd, (HMENU)NULL, NULL, NULL);
			RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME);
			
			break;
		}
		}
		break;
	/////////////////////////////
	case WM_CLOSE:
	{
		if (MessageBox(hwnd, L"Do you want to exit?", L"Exit", MB_OKCANCEL) == IDOK)
			DestroyWindow(hwnd);
	}

	break;
	/////////////////////////////
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, Msg, wParam, lParam);
}



//\\\\\\\\\\\     WINMAIN FUNCTION \\\\\\\\\\\\/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASSEX wc;
	MSG msg;
	HWND hwnd;
	HMENU hMenu;
	ZeroMemory(&wc, sizeof(wc));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIconSm = LoadIcon(NULL, IDC_ICON);
	wc.hIcon = LoadIcon(NULL, IDC_ICON);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;

	if (!RegisterClassEx(&wc)) {
		LPCWSTR Error01 = L"Could not register class";
		LPCWSTR Error10_Caption = L"Error";
		MessageBox(NULL, Error01, Error10_Caption, MB_OK | MB_ICONERROR);
	}

	LPCWSTR WindowTitle = L"LAB 1";
	
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, ClassName, WindowTitle, WS_OVERLAPPEDWINDOW , CW_USEDEFAULT, CW_USEDEFAULT,
		500, 300, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		LPCWSTR Error02 = L"Could not create window!";
		LPCWSTR Error02_Caption = L"Error";
		MessageBox(NULL, Error02, Error02_Caption, MB_OK | MB_ICONERROR);
	}

	hMenu = GetSystemMenu(hwnd, FALSE);

	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hMenu, MF_STRING, IDM_SYS_ABOUT, TEXT("ABOUT"));
	AppendMenu(hMenu, MF_STRING, IDM_SYS_HELP, TEXT("TXT BOX"));
	AppendMenu(hMenu, MF_STRING, IDM_SYS_CHANGE, TEXT("CHANGE"));

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, 0, 0, 0)) {
	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	return msg.wParam;
}

