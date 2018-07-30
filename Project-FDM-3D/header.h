#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <memory>

class Action;
class ActionManager;
class App;
class Axis;
class Camera;
class InputManager;
class Model;
class ModelPoint;
class Renderable;
class Renderer;
class RenderRectangle;
class RenderTriangle;
class RenderVertex;
class Scene;
class Shader;
class Vector3f;

template <class T>
class Tab;

/*
TODO:
- merge move actions
- ask before exit
- selecting textures
- GUI
- creating points
- deleting points
- creating rectangles
- deleting rectangles
- adding speakers

- converting models to grid
- computing acoustic pressure field

- displaying results
- saving and loading results
- fullscreen
- sorting transparent planes!
*/