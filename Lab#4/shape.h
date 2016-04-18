#pragma once
class shape {
	private:
		int x, y;
		int width, height;
		int dx, dy;
		bool circle = false;
		int XY;
		int R, G, B;
		int speed;
		
	public:
		shape();
		~shape();
		shape(float, float, int, int); //initialize the the object;
		void setCircle(bool circle); //function for setting the object type circle;
		void setDimension(int, int);
		void setCoordinates(int, int);
		void setDirection(int);
		int getDirection() { return XY; }
		void setColor(int, int, int);
		int getR();
		int getG();
		int getB();
		int getX() { return x; }
		int getY() { return y; }
		int getWidth() { return width; }
		int getHeight() { return height; }
		bool ifCircle() { return this->circle; }
		void setSpeed(int speed) { this->speed = speed; }
		int getSpeed() { return speed; }
		void reach_the_wall(int, int);
		bool objInteract(float, float);
		
		
		

};

