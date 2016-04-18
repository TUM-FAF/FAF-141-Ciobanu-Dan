#pragma once

#include<iostream>
#include "shape.h"
#include <vector>

using namespace std;
vector<shape> vec;
int v_size = 5;
static RECT rectangle;
HDC hdc;
HBRUSH hBrush;
int x, y;
int boost = 0;
POINT Pt[3];


void newShapes() {
	shape *shp;
	for (int i = 0; i < v_size; i++) {
		shp = new shape(rand() % rectangle.right, rand() % rectangle.bottom, 50, 50);
		shp->setColor(rand() % 255, rand() % 255, rand() % 255);
		shp->setDirection(rand() % 4);
		shp->setSpeed(rand() % 2 + 1);
		shp->setCircle(true);
		vec.push_back(*shp);
	}

}

static void Paint(HWND hwnd) {

	
	GetClientRect(hwnd, &rectangle);
	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rectangle.right, rectangle.bottom);
	HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

	for (int i = 0; i < v_size; i++) {
		x = vec[i].getX();
		y = vec[i].getY();
		
		hBrush = CreateSolidBrush(RGB(vec[i].getR(), vec[i].getG(), vec[i].getB()));
		SelectObject(hdcBuffer, hBrush);

		for (int j = 0; j < v_size; j++) {
			if (vec[i].objInteract(vec[j].getX(), vec[j].getY())) {
				vec[i].setColor(rand() % 255, rand() % 255, rand() % 255);
				vec[i].setDirection(rand() % 4);
				//vec[i].setCircle(false);
				vec[j].setColor(rand() % 250, rand() % 250, rand() % 250);
				vec[j].setDirection(rand() % 4);
				//vec[j].setCircle(false);
			}
		}

		vec[i].reach_the_wall(rectangle.right, rectangle.bottom);
		switch (vec[i].getDirection()) {
			case 0:
				x += vec[i].getSpeed() + boost;
				y -= vec[i].getSpeed() + boost;
				break;
			case 1:
				x += vec[i].getSpeed() + boost;
				y += vec[i].getSpeed() + boost;
				break;
			case 2:
				x -= vec[i].getSpeed() + boost;
				y += vec[i].getSpeed() + boost;
				break;
			case 3:
				x -= vec[i].getSpeed() + boost;
				y -= vec[i].getSpeed() + boost;
				break;

			
		}

		vec[i].setCoordinates(x, y);
		if (vec[i].ifCircle()) {
			Ellipse(hdcBuffer, vec[i].getX(), vec[i].getY(), vec[i].getX() - vec[i].getWidth(), vec[i].getY() - vec[i].getHeight());
		} else {
			Pt[0].x = vec[i].getX();
			Pt[0].y = vec[i].getY();
			Pt[1].x = vec[i].getX() + vec[i].getWidth();
			Pt[1].y = vec[i].getY() + vec[i].getHeight();
			Pt[2].x = vec[i].getX() - vec[i].getWidth();
			Pt[2].y = vec[i].getY() - vec[i].getHeight();
			Polygon(hdcBuffer, Pt, 3);

		}


		

	}
	
	BitBlt(hdc, 0, 0, rectangle.right, rectangle.bottom, hdcBuffer, 0, 0, SRCCOPY);
	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteObject(hbmBuffer);
	DeleteDC(hdcBuffer);
}


