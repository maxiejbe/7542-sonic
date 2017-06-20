#ifndef RECTANGLE2_H
#define RECTANGLE2_H

class Rectangle2 {
public:
	Rectangle2(double x0, double x1, double y0, double y1);
	bool collisionsWith(double x0, double x1, double y0, double y1);
	bool collisionsWithX(double x0, double x1);
	bool collisionsWithY(double y0, double y1);
private:
	double x0, x1, y0, y1;
};

#endif // !RECTANGLE2_H
