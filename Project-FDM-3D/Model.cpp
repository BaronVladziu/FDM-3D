#include "Model.h"
#include "RenderTriangle.h"
#include "RenderRectangle.h"

void Model::updateRotation() {
	while (_rotation > 360.f) {
		_rotation -= 360.f;
	}
	while (_rotation < -360.f) {
		_rotation += 360.f;
	}
}
ModelPoint * Model::findModelPoint(unsigned int id) const {
	if (id >= _points.size()) {
		std::cout << "Error: Attepted to access non-existing point" << std::endl;
		return nullptr;
	}
	std::list<ModelPoint *>::const_iterator it = _points.begin();
	for (unsigned int actID = 0; actID < id; actID++) {
		it++;
	}
	return *it;
}

Model::Model()
	: _rotationAxis(0.f, 1.f, 0.f), _scale(1.f, 1.f, 1.f), _ifAutoscaled(false)
{}
const ModelPoint * Model::addPoint(const Vector3f & position) {
	ModelPoint * ptr = new ModelPoint(position);
	_points.push_back(ptr);
	return ptr;
}
void Model::setPoint(ModelPoint * point, const Vector3f & position) {
	point->setPosition(position);
}
const std::list<ModelPoint *> & Model::getPoints() const {
	return _points;
}
std::list<ModelPoint *>::iterator Model::getPointsBegin() {
	return _points.begin();
}
std::list<ModelPoint *>::iterator Model::getPointsEnd() {
	return _points.end();
}
int Model::getNumberOFPoints() const {
	return _points.size();
}
const std::list<Renderable*> & Model::getPlanes() const {
	return _rectangles;
}
std::list<Renderable *>::iterator Model::getPlanesBegin() {
	return _rectangles.begin();
}
std::list<Renderable *>::iterator Model::getPlanesEnd() {
	return _rectangles.end();
}
int Model::getNumberOFPlanes() const {
	return _rectangles.size();
}
void Model::addTriangle(ModelPoint * a, ModelPoint * b, ModelPoint * c, E_TextureID texID) {
	_rectangles.push_front(new RenderTriangle(a, b, c, texID));
}
void Model::addTriangle(int a, int b, int c, E_TextureID texID) {
	_rectangles.push_front(new RenderTriangle(findModelPoint(a), findModelPoint(b), findModelPoint(c), texID)); //TODO: can be quickened
}
void Model::addRectangle(ModelPoint * a, ModelPoint * b, ModelPoint * c, ModelPoint * d, E_TextureID texID) {
	_rectangles.push_front(new RenderRectangle(a, b, c, d, texID));
}
void Model::addRectangle(int a, int b, int c, int d, E_TextureID texID) {
	_rectangles.push_front(new RenderRectangle(findModelPoint(a), findModelPoint(b), findModelPoint(c), findModelPoint(d), texID)); //TODO: can be quickened
}
void Model::saveModelToFile(const std::string & fileName) const {
	std::ofstream outfile(fileName + ".bvm");
	outfile << "P:" << std::endl;
	for (ModelPoint * point : _points) {
		outfile << point->getPosition().x << " " << point->getPosition().y << " " << point->getPosition().z << std::endl;
	}
	outfile << "R:" << std::endl;
	for (Renderable * rectangle : _rectangles) {
		const Tab<ModelPoint *> & rectPoints = rectangle->getVertices();
		outfile << rectPoints.getSize() << " " << int(rectangle->getTextureID()) << " ";
		for (int i = 0; i < rectPoints.getSize(); i++) {
			outfile << rectPoints[i] << " ";
		}
		outfile << std::endl;
	}
	outfile.close();
}
void Model::loadModelFromFile(const std::string & fileName) {
	std::ifstream infile(fileName + ".bvm");
	std::string line;
	std::string word;
	float x, y, z;
	int q, w, i;
	int * intTab;
	char state = 'P';
	while (std::getline(infile, line)) {
		if (line != "") {
			std::istringstream issLine(line);
			issLine >> word;
			if (word == "P:" || word == "R:") {
				state = word[0];
			}
			else {
				switch (state) {
				case 'P': //points
					x = std::stof(word);
					issLine >> y >> z;
					_points.push_back(new ModelPoint(Vector3f(x, y, z)));
					break;
				case 'R': //rectangles
					q = std::stoi(word);
					intTab = new int[q + 1];
					i = 0;
					while (issLine >> w) {
						intTab[i] = w;
						i++;
					}
					switch (q) {
					case 3:
						addTriangle(intTab[1], intTab[2], intTab[3], E_TextureID(intTab[0]));
						break;
					case 4:
						addRectangle(intTab[1], intTab[2], intTab[3], intTab[4], E_TextureID(intTab[0]));
						break;
					default:
						std::cout << "Loading rectangles failed - Unsupported polygon type" << std::endl;
						break;
					}
					delete[] intTab;
					break;
				default:
					std::cout << "Error: Unsupported data state!" << std::endl;
					break;
				}
			}
		}
	}
	infile.close();
}
const Vector3f & Model::getPosition() const {
	return _position;
}
void Model::setPosition(const Vector3f & position) {
	_position = position;
}
void Model::move(const Vector3f & position) {
	_position += position;
}
bool Model::isAutorotated() const {
	return _ifAutorotated;
}
void Model::setIfAutorotated(bool autorotate) {
	_ifAutorotated = autorotate;
}
const float Model::getRotation() const {
	return _rotation;
}
void Model::setRotation(float rotation) {
	_rotation = rotation;
	updateRotation();
}
void Model::rotate(float rotation) {
	_rotation += rotation;
	updateRotation();
}
const Vector3f & Model::getRotationAxis() const {
	return _rotationAxis;
}
void Model::setRotationAxis(const Vector3f & rotationAxis) {
	_rotationAxis = rotationAxis;
}
bool Model::isAutoscaled() const {
	return _ifAutoscaled;
}
void Model::setIfAutoscaled(bool autoscale) {
	_ifAutoscaled = autoscale;
}
const Vector3f & Model::getScale() const {
	return _scale;
}
void Model::setScale(const Vector3f & scale) {
	_scale = scale;
}
E_TextureID Model::getTextureID(std::list<Renderable *>::iterator plane) const {
	return (*plane)->getTextureID();
}
void Model::setTextureID(std::list<Renderable *>::iterator plane, E_TextureID texID) {
	(*plane)->setTextureID(texID);
}
void Model::setTextureIDForAllPlanes(E_TextureID texID) {
	for (Renderable * plane : _rectangles) {
		plane->setTextureID(texID);
	}
}
Model::~Model() {
	for (ModelPoint * point : _points) {
		delete point;
	}
	for (Renderable * rectangle : _rectangles) {
		delete rectangle;
	}
}