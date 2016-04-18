#include <windows.h>
#include <windowsx.h>
#include "Header.h"
#include "functions.h"


LPCWSTR ClassName = L"mainClass";
HINSTANCE hInstance;
static POINTS ptsBegin, ptsPrevEnd, ptsEnd;
int setState;
HMENU hMenu;
HDC hdc;
bool draw = false, draw_circle = false, draw_rect = false, draw_bezier = false, 
draw_obj = false, bitMap = false;
int xMouse, yMouse;
RECT eRect;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	//HDC hdc;
	static PAINTSTRUCT PaintStructure;
	static RECT ClientRectangle;
	static POINT Line;
	POINT Pt[4] = { { 320, 120 },{ 88, 246 },{ 364, 122 }, {123, 64} };
	POINT Pt1[4] = { { 745, 413 },{ 434, 356 },{ 434, 256 },{ 670, 164 } };
	static POINT apt[4];
	int cxClient, cyClient;
	static HDC Memhdc;
	static BITMAP bitmap;
	static HBITMAP hbmpimage;

	switch (Msg) {
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			apt[0].x = cxClient / 4;
			apt[0].y = cyClient / 2;
			apt[1].x = cxClient / 2;
			apt[1].y = cyClient / 4;
			apt[2].x = cxClient / 2;
			apt[2].y = 3 * cyClient / 4;
			apt[3].x = 3 * cxClient / 4;
			apt[3].y = cyClient / 2;

			return 0;
		case WM_CREATE:
		{
			CreateMenu(hwnd);
			 RegisterHotKey(hwnd, CONTROL_C, MOD_CONTROL, VK_C);
			 RegisterHotKey(hwnd, CONTROL_X, MOD_CONTROL, VK_X);
			 RegisterHotKey(hwnd, ALT_R, MOD_ALT, VK_R);

			 hbmpimage = (HBITMAP)LoadImage(hInstance, TEXT("tux-288.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			 GetObject(hbmpimage, sizeof(bitmap), &bitmap);

		}
		break;

		case WM_HOTKEY:
			switch (wParam) {
				case CONTROL_C:
					setState = 2;
					break;
				case ALT_R:
					setState = 3;
					break;
				case CONTROL_X:
					Erase_BK(hwnd);
					break;
			}

			break;
					
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case MENU_01:
					setState = 1;
					draw = true;
					break;
				case MENU_02:
					setState = 2;
					break;
				case MENU_03:
					setState = 3;
					break;
				case MENU_04:
					setState = 4;
					draw_bezier = true;
					break;
				case MENU_05:
					setState = 5;
					draw_obj = true;
					break;
				case MENU_06:
					setState = 6;
					bitMap = true;
					break;
			}
		
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &PaintStructure);
			GetClientRect(hwnd, &ClientRectangle);
			
			EndPaint(hwnd, &PaintStructure);
		}
			return 0;
		case WM_RBUTTONDOWN:
			
			break;
		case WM_LBUTTONDOWN:
		{

			if (setState != 6 && bitMap == true) {
				bitMap = false;
			}

			if (draw == true && setState != 1) {
				draw = false;
			}

			if (setState != 4 && draw_bezier == true) {
				draw_bezier = false;
			}

			if (setState != 5 && draw_obj == true) {
				draw_obj = false;
			}

			if (setState == 1) {
				hdc = GetDC(hwnd);
				draw_lines(hwnd, hdc, ClientRectangle);
				ReleaseDC(hwnd, hdc);
			}
			
			if (setState == 2) {

				hdc = GetDC(hwnd);
				draw_circle = true;
				ptsBegin.x = LOWORD(lParam);
				ptsBegin.y = HIWORD(lParam);

				ptsEnd.x = LOWORD(lParam);
				ptsEnd.y = HIWORD(lParam);

				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
				ReleaseDC(hwnd, hdc);
			}

			if (setState == 3) {
				hdc = GetDC(hwnd);
				draw_rect = true;
				ptsBegin.x = LOWORD(lParam);
				ptsBegin.y = HIWORD(lParam);

				ptsEnd.x = LOWORD(lParam);
				ptsEnd.y = HIWORD(lParam);

				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Rectangle(hdc, ptsBegin.x, ptsBegin.y, LOWORD(lParam), HIWORD(lParam));
				ReleaseDC(hwnd, hdc);
			}
			
			
			
			if (draw_obj) {
				hdc = GetDC(hwnd);
				GetClientRect(hwnd, &ClientRectangle);
				draw_objects(hdc);
				SendMessage(hwnd, WM_PAINT, 0, 0);
				DrawBezier(hdc, Pt);
				DrawBezier(hdc, Pt1);
				ReleaseDC(hwnd, hdc);
			}

			
		
			if (bitMap) {
				hdc = GetDC(hwnd);
				Memhdc = CreateCompatibleDC(hdc);
				SelectObject(Memhdc, hbmpimage);
				BitBlt(hdc, 250, 40, 280, 600, Memhdc, 0, 0, SRCCOPY);
				DeleteDC(Memhdc);
				ReleaseDC(hwnd, hdc);
			}
			
		}
			break;

		case WM_LBUTTONUP:
		{
			

			if (draw_circle) {
				hdc = GetDC(hwnd);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
				ReleaseDC(hwnd, hdc);
			}

			draw_circle = false;

			if (draw_rect) {
				
				hdc = GetDC(hwnd);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Rectangle(hdc, ptsBegin.x, ptsBegin.y, LOWORD(lParam), HIWORD(lParam));
				ReleaseDC(hwnd, hdc);
				
			}
			draw_rect = false;

			
			
		}
		
			return 0;
		case WM_MOUSEMOVE:
		{

			if (draw_circle) {
				GetClientRect(hwnd, &ClientRectangle);
				hdc = GetDC(hwnd);
				SetROP2(hdc, R2_NOTXORPEN);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);

				ptsEnd.x = LOWORD(lParam);
				ptsEnd.y = HIWORD(lParam);

				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
				ReleaseDC(hwnd, hdc);
			}
		
			
			if (draw_rect) {
				GetClientRect(hwnd, &ClientRectangle);
				hdc = GetDC(hwnd);

				SetROP2(hdc, R2_NOTXORPEN);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Rectangle(hdc, ptsBegin.x, ptsBegin.y, LOWORD(lParam), HIWORD(lParam));

				ptsEnd.x = LOWORD(lParam);
				ptsEnd.y = HIWORD(lParam);

				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
				Rectangle(hdc, ptsBegin.x, ptsBegin.y, LOWORD(lParam), HIWORD(lParam));
				ReleaseDC(hwnd, hdc);
			}

			if (draw_bezier) {
				if (wParam & MK_LBUTTON || wParam & MK_RBUTTON) {
					hdc = GetDC(hwnd);
					SelectObject(hdc, GetStockObject(WHITE_PEN));

					DrawBezier(hdc, apt);
					if (wParam & MK_LBUTTON) {
						apt[1].x = LOWORD(lParam);
						apt[1].y = HIWORD(lParam);
					}
					if (wParam & MK_RBUTTON) {
						apt[2].x = LOWORD(lParam);
						apt[2].y = HIWORD(lParam);
					}
					SelectObject(hdc, GetStockObject(BLACK_PEN));
					DrawBezier(hdc, apt);
					ReleaseDC(hwnd, hdc);
				}

			}
			
		}
			return 0;
	
		case WM_CLOSE:
		{
				DestroyWindow(hwnd);
		}

		break;

		case WM_DESTROY:
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;

	if (!RegisterClassEx(&wc)) {
		LPCWSTR Error01 = L"Could not register class";
		LPCWSTR Error10_Caption = L"Error";
		MessageBox(NULL, Error01, Error10_Caption, MB_OK | MB_ICONERROR);
	}

	LPCWSTR WindowTitle = L"LAB 1";

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, ClassName, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		800, 500, NULL, NULL, hInstance, NULL);

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
