#ifndef LAYER_H
#define LAYER_H

#include <string>

using namespace std;

class Layer {
public:
	Layer();
	Layer(int idParam, int zIndexParam, string imagePathParam);

private:
	int id;
	int zIndex;
	string imagePath;
};

#endif