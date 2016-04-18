#include <Windows.h>
#include "Header.h"
#include "shape.h"
#include "functions.h"
PAINTSTRUCT ps;
#define ID_TIMER 1

bool mouse = false;
shape *shp;
LPCWSTR ClassName = L"mainClass";
LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	
	switch (Msg) {

		case WM_SIZE:
			return 0; 
		case WM_CREATE:
		{
			GetMapMode(hdc);
			SetMapMode(hdc, MM_LOENGLISH);
			GetClientRect(hwnd, &rectangle);

			int time = SetTimer(hwnd, ID_TIMER, 5, NULL);
			if (time == 0)
				MessageBox(hwnd, TEXT("Could not SetTimer()!"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);

			newShapes();
		}
			return 0;
		case WM_TIMER:
			InvalidateRect(hwnd, &rectangle, FALSE);
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			Paint(hwnd);
			EndPaint(hwnd, &ps);

			return 0;


		case WM_RBUTTONDOWN:
			// Create a new shape and extending the vector for proccessing all the objects
			shp = new shape(rand() % rectangle.right, rand() % rectangle.bottom, 50, 50);
			shp->setColor(rand() % 255, rand() % 255, rand() % 255);
			shp->setDirection(rand() % 4);
			shp->setSpeed(rand() % 2 + 1);
			shp->setCircle(true);
			vec.push_back(*shp);
			v_size ++;

			break;
		case WM_LBUTTONDOWN:
			v_size --;
			if (v_size < 0) {
				v_size = 0;
			}
			break;
		case WM_MOUSEWHEEL:
			if ((short)HIWORD(wParam) < 0) {
				boost -= 1;
				if (boost == 0) { mouse = true; }
			} else {
				boost += 1;
				mouse = false;
			}
			if (mouse) {
				boost = 0;
			}
			
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			KillTimer(hwnd, ID_TIMER);
			PostQuitMessage(0);
			return 0;

		
	}
	return DefWindowProc(hwnd, Msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASSEX wc;
	MSG msg;
	HWND hwnd;

	ZeroMemory(&wc, sizeof(wc));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIconSm = LoadIcon(NULL, IDC_ICON);
	wc.hIcon = LoadIcon(NULL, IDC_ICON);
	wc.hbrBackground = CreateSolidBrush(COLOR_WINDOW);
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;

	if (!RegisterClassEx(&wc)) {
		LPCWSTR Error01 = L"Could not register class";
		LPCWSTR Error10_Caption = L"Error";
		MessageBox(NULL, Error01, Error10_Caption, MB_OK | MB_ICONERROR);
	}

	LPCWSTR WindowTitle = L"LAB 4";

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, ClassName, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		850, 600, NULL, NULL, hInstance, NULL);

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