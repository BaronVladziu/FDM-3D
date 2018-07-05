#include "Model.h"
#include "RenderRectangle.h"

Model::Model() {}
const std::list<Renderable*> & Model::getRenderables() {
	return _rectangles;
}
const ModelPoint * Model::addPoint(const Vector3f & position) {
	ModelPoint * ptr = new ModelPoint(position);
	_points.push_back(ptr);
	return ptr;
}
void Model::setPoint(ModelPoint * point, const Vector3f & position) {
	point->setPosition(position);
}
void Model::setRectangle(int a, int b, int c, int d) {
	_rectangles.push_front(new RenderRectangle(_points, a, b, c, d));
}
void Model::saveModelToFile(const std::string & fileName) const
{
	std::ofstream outfile(fileName + ".bvm");
	outfile << "P:" << std::endl;
	for (ModelPoint * point : _points) {
		outfile << point->getPosition().x << " " << point->getPosition().y << " " << point->getPosition().z << std::endl;
	}
	outfile << "E:" << std::endl;
	for (int emptyPoint : _emptyPoints) {
		outfile << emptyPoint << std::endl;
	}
	outfile << "R:" << std::endl;
	for (Renderable * rectangle : _rectangles) {
		const Tab<int> & rectPoints = rectangle->getVerticeIDs();
		outfile << rectPoints.getSize() << " ";
		for (int i = 0; i < rectPoints.getSize(); i++) {
			outfile << rectPoints[i] << " ";
		}
		outfile << std::endl;
	}
	outfile.close();
}
void Model::loadModelFromFile(const std::string & fileName)
{
	std::ifstream infile(fileName + ".bvm");
	std::string line;
	std::string word;
	float x, y, z;
	int q, w, i;
	int * intTab;
	char state = 'P';
	while (std::getline(infile, line)) {
		std::cout << line << std::endl;
		if (line != "") {
			std::istringstream issLine(line);
			issLine >> word;
			if (word == "P:" || word == "E:" || word == "R:") {
				state = word[0];
			}
			else {
				switch (state) {
				case 'P': //points
					x = std::stof(word);
					issLine >> y >> z;
					_points.push_back(new ModelPoint(Vector3f(x, y, z)));
					break;
				case 'E': //empty points
					_emptyPoints.push_back(std::stoi(word));
					break;
				case 'R': //rectangles
					q = std::stoi(word);
					intTab = new int[q];
					i = 0;
					while (issLine >> w) {
						intTab[i] = w;
						i++;
					}
					switch (q) {
					case 4:
						_rectangles.push_back(new RenderRectangle(_points, intTab[0], intTab[1], intTab[2], intTab[3]));
						break;
					default:
						std::cout << "Loading rectangles failed - Unsupported polygon type" << std::endl;
						break;
					}
					delete[] intTab;
					break;
				}
			}
		}
	}
	infile.close();
}
Model::~Model() {
	for (ModelPoint * point : _points) {
		delete point;
	}
	for (Renderable * rectangle : _rectangles) {
		delete rectangle;
	}
}