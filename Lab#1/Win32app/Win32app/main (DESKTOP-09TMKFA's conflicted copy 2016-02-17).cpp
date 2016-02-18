#include<windows.h>

LPCWSTR g_szClassName = L"mainClass";

#define BUTTON_01 1
#define BUTTON_02 2


LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	HDC ContextHandle;
	PAINTSTRUCT PaintStructure;
	RECT ClientRectangle;
	int window;
	LPCWSTR MyText = L"Done with Pride and Prejudice by me!";
	switch (Msg)
	{
		case WM_CREATE:
			{
				LPCWSTR button01_ID = L"BUTTON";
				LPCWSTR button01_text = L"DEFAULT";
				HWND button01 = CreateWindowEx(WS_EX_WINDOWEDGE, button01_ID, button01_text, BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_CHILD, 5, 5, 85, 25, hwnd, (HMENU)BUTTON_01, NULL, NULL);
	
				LPCWSTR button02_ID = L"BUTTON";
				LPCWSTR button02_text = L"CUSTOM";
				HWND button02 = CreateWindowEx(NULL, button02_ID, button02_text, BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_CHILD, 5, 35, 85, 25, hwnd, (HMENU)BUTTON_02, NULL, NULL);
	
			}
			break;
		case WM_PAINT:
			ContextHandle = BeginPaint(hwnd, &PaintStructure);
			GetClientRect(hwnd, &ClientRectangle);
			DrawText(ContextHandle, MyText, -1,
				&ClientRectangle, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			
			EndPaint(hwnd, &PaintStructure);

			return 0;
		case WM_COMMAND:
			
			{
				switch (wParam) {
			
					case BUTTON_01:
					
						break;
					case BUTTON_02:
					
						break;
				}	
			}
			break;
		
		case WM_CLOSE:
			{
				if (MessageBox(hwnd, L"Do you want to exit?", L"Exit", MB_OKCANCEL) == IDOK)
					DestroyWindow(hwnd);
			}
			
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASSEX wc;
	MSG msg;
	HWND hwnd;

	ZeroMemory(&wc, sizeof(wc));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
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

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, WindowTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100,
		500, 300, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		LPCWSTR Error02 = L"Could not create window!";
		LPCWSTR Error02_Caption = L"Error";
		MessageBox(NULL, Error02, Error02_Caption, MB_OK | MB_ICONERROR);
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}