#pragma once
#include "Core\Init\Init_GLFW.h"
#include "Core\Init\WindowInfo.h"
#include "Managers\SceneManager.h"

using namespace Core;
using namespace Init;


int main(int argc, char *argv[])
{
	WindowInfo window(std::string("Whiskey engine test"), 400, 200, 800, 600, true);
	Core::ContextInfo context(4, 5, true);

	try{
		Core::Init::Init_GLFW::Init(window,context);
		IListener* scene = new Managers::SceneManager();
		Init_GLFW::SetListener(scene);

		Init_GLFW::Run();

		delete scene;
	}
	catch (const std::exception& e){
		//log here
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}