#include "WindowCreator.h"



WindowCreator::WindowCreator()
{
	_monitor = glfwGetPrimaryMonitor();
}

WindowCreator::WindowCreator(std::string name, Size3D size, Coord2D position, int monitor, bool fullScreeen, bool visable)
{
	createWindow(name, size, position, monitor, fullScreeen, visable);
}


WindowCreator::~WindowCreator()
{}

int WindowCreator::createWindow(std::string name, Size3D size, Coord2D position, int monitor, bool fullScreeen, bool visable)
{
	int monCount;
	GLFWmonitor** mons = glfwGetMonitors(&monCount);


	if(monCount > monitor)
		_monitor = mons[_info->monitor = monitor];
	else
		_monitor = glfwGetPrimaryMonitor();

	_info->size = &size;
	_info->position = &position;


	_window = glfwCreateWindow(size.width, size.height, (*(_info->title) = name).c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(_window); //gives opengl the window it renders to
	
	setFullScreen(fullScreeen);
	setVisable(visable);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	return _window != nullptr ? WINDOW_CREATED : WINDOW_FAILED;
}

void WindowCreator::setVisable(bool viz)
{
	if(viz)
		glfwShowWindow(_window);
	else
		glfwHideWindow(_window);
}

void WindowCreator::setFullScreen(bool full)
{
	if(_full == full)	
		return;//Return if the window is fullscreen
	

	int w, h;
	double x, y;
	if(full)
	{

		glfwGetWindowSize(_window, &w, &h);
		_info->size = new Size3D {float(w), float(h)};
		glfwGetWindowPos(_window, &w, &h);
		_info->position = new Coord2D {float(w), float(h)};


		glfwGetCursorPos(_window,&x,&y);

		// get reolution of monitor
		int tmp;
		const GLFWvidmode * mode = glfwGetVideoMode(glfwGetMonitors(&tmp)[_info->monitor]);

		// switch to full screen
		glfwGetFramebufferSize(_window, &w, &h);
		glViewport(0, 0, w, h);
		glfwSetWindowMonitor(_window, _monitor, 0, 0, mode->width, mode->height, 0);

		glfwSetCursorPos(_window,x,y);
	} else
	{
		glfwGetCursorPos(_window, &x, &y);
		glfwGetFramebufferSize(_window, &w, &h);
		glViewport(0, 0, w, h);
		glfwSetWindowMonitor(_window, nullptr, _info->position->x, _info->position->y, _info->size->width, _info->size->height, 0);
		glfwSetCursorPos(_window, x, y);
	//	_monitor = nullptr;
	}

	_full = full;
}

GLFWwindow* WindowCreator::getWindow()
{
	return _window;
}

std::string & WindowCreator::getTitle()
{
	return *_info->title;
}

Size3D& WindowCreator::getScreenSize()
{
	return *_info->size;
}

int& WindowCreator::getScreenWidth()
{
	int w, h;
	glfwGetFramebufferSize(_window, &w, &h);
	return w;
}

int& WindowCreator::getScreenHeight()
{
	int w, h;
	glfwGetFramebufferSize(_window, &w, &h);
	return h;
}
