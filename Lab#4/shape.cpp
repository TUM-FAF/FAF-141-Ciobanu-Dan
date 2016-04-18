#include "shape.h"
#include <iostream>


shape::shape() {
}


shape::~shape() {
}

shape::shape(float x, float y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void shape::setCircle(bool circle) {
	this->circle = circle;
}

void shape::setCoordinates(int x, int y) {
	
	this->x = x;
	this->y = y;
}

void shape::setDimension(int width, int height) {
	this->width = width;
	this->height = height;
}

void shape::setDirection(int XY) {
	this->XY = XY;
}

void shape::setColor(int R, int G, int B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

int shape::getB() { return B; }
int shape::getR() { return R; }
int shape::getG() { return G; }

void shape::reach_the_wall(int xClientRect, int yClientRect) {

	if (x - width < 0) {
		setDirection(0);
	}
	if (y - height < 0) {
		
		setDirection(1);
	}

	if (x + width > xClientRect) {
		
		setDirection(2);
	}
	if (y + height > yClientRect) {
		
		setDirection(3);
	}
}


bool shape::objInteract(float X, float Y) {
	
	if (y <= Y + height && y > Y && x <= X + width && x >= X) {
		return true;
	}

	return false;
}