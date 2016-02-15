#include "Init_GLFW.h"
using namespace Core;
using namespace Core::Init;


//Core::IListener* Init_GLFW::listener = NULL;
//Core::WindowInfo Init_GLFW::windowInformation;
GLFWwindow* window = NULL;
/*
Errors callback
*/

Init_GLFW::Init_GLFW()
{

}

Init_GLFW::~Init_GLFW()
{

}

void error_callback(int error, const char* description)
{
	throw std::runtime_error(description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{

	}

}

void Init_GLFW::Init(const Core::WindowInfo&  windowInfo,
	const Core::ContextInfo& contextInfo)
{
	windowInformation = windowInfo;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()){
		throw std::runtime_error("glfwInit failed");
	}

	// open a window with GLFW
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(windowInfo.width, windowInfo.height, windowInfo.name.c_str(), NULL, NULL);

	if (!window){
		glfwTerminate();
		throw std::runtime_error("failed to create window");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	Core::Init::Init_GLEW::Init();

	// print out some info about the graphics drivers
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	glfwSetKeyCallback(window, key_callback);
}

void Init_GLFW::Run()
{
	std::cout << "GLFW:\t Start Running  " << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		DisplayCallback();

		// Poll for and process events 
		glfwPollEvents();
	}

	glfwTerminate();
}
void Init_GLFW::DisplayCallback()
{
	//if (listener)
	//{

	//	listener->NotifyBeginFrame();
	//	listener->NotifyDisplayFrame();

	//	glfwSwapBuffers(window);

	//	listener->NotifyEndFrame();
	//}
	for (auto iter = m_listeners.begin(); iter != m_listeners.end(); iter++)
	{
		(*iter)->NotifyBeginFrame();
	}
	for (auto iter = m_listeners.begin(); iter != m_listeners.end(); iter++)
	{
		(*iter)->NotifyDisplayFrame();
	}
	glfwSwapBuffers(window);
	for (auto iter = m_listeners.begin(); iter != m_listeners.end(); iter++)
	{
		(*iter)->NotifyEndFrame();
	}
}

//void Init_GLFW::SetListener(Core::IListener*& iListener)
//{
//	listener = iListener;
//}

void Init_GLFW::AddListener(Core::IListener* listener)
{
	m_listeners.push_back(listener);
}