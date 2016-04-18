#pragma once

#include <commctrl.h>

void CreateMenu(HWND hwnd) {
	
	HMENU hMenubar;
	HMENU hMenu;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, MENU_01, L"&Lines");
	AppendMenuW(hMenu, MF_STRING, MENU_02, L"&Ellipses");
	AppendMenuW(hMenu, MF_STRING, MENU_03, L"&Rectangles");
	AppendMenuW(hMenu, MF_STRING, MENU_04, L"&Bezier");
	AppendMenuW(hMenu, MF_STRING, MENU_05, L"&Object");
	AppendMenuW(hMenu, MF_STRING, MENU_06, L"&BitMap");
	
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Drawnings");
	SetMenu(hwnd, hMenubar);

}

void draw_lines(HWND hwnd, HDC hdc, RECT rec) {

	for (int i = 1; i <= 5; i++) {
		GetClientRect(hwnd, &rec);
		HPEN hLinePen;
		COLORREF qLineColor;
		HPEN hPenOld;
		qLineColor = RGB(rand() % 255, rand() % 255, rand() % 255);
		hLinePen = CreatePen(PS_SOLID, rand() % 15, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		MoveToEx(hdc, 200, 20 * i, NULL);
		LineTo(hdc, 400, 20 * i);

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);
		DeleteObject(hPenOld);
		DeleteObject(hLinePen);
	}

}

void draw_objects(HDC hdc) {
	POINT Pt[7];
	Pt[0].x = 320;
	Pt[0].y = 50;
	Pt[1].x = 480;
	Pt[1].y = 50;
	Pt[2].x = 480;
	Pt[2].y = 20;
	Pt[3].x = 530;
	Pt[3].y = 70;
	Pt[4].x = 480;
	Pt[4].y = 120;
	Pt[5].x = 480;
	Pt[5].y = 90;
	Pt[6].x = 320;
	Pt[6].y = 90;


	HPEN hLinePen;
	COLORREF qLineColor;
	HPEN hPenOld;
	qLineColor = RGB(rand() % 255, rand() % 255, rand() % 255);
	hLinePen = CreatePen(PS_SOLID, rand() % 15, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);
	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, hBrush);

	Pie(hdc, 240, 220, 426, 344, 355, 52, 402, 315);
	Polygon(hdc, Pt, 7);

	SelectObject(hdc, hPenOld);
	DeleteObject(hLinePen);
	DeleteObject(hBrush);
	DeleteObject(hLinePen);

	//Polygon(hdc, Pt, 7);

}

void DrawBezier(HDC hdc, POINT apt[]) {
	PolyBezier(hdc, apt, 4);
	MoveToEx(hdc, apt[0].x, apt[0].y, NULL);
	LineTo(hdc, apt[1].x, apt[1].y);
	MoveToEx(hdc, apt[2].x, apt[2].y, NULL);
	LineTo(hdc, apt[3].x, apt[3].y);
}

void Erase_BK(HWND hwnd) {
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
	RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME);
}