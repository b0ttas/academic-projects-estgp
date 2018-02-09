#pragma once
class Point
{
public:
	Point();
	~Point();

	void SetX(int);	
	void SetY(int);
	int GetX();
	int GetY();

	Point(int, int);

protected:
		int x;
		int y;
};

