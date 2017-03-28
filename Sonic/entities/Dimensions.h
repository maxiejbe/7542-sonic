#ifndef DIMENSIONS_H
#define DIMENSIONS_H

class Dimensions {
public:
	Dimensions();
	Dimensions(int widthParam, int heightParam, int radioParam);

	int GetWidth();
	int GetHeight();
private:
	int width;
	int height;
	int radio;
};

#endif