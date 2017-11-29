/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <win32/Win32Window.h>
#include <core/Ref.h>
#include <OGL/OGLGraphicsSystem.h>
#include <TestApplication.h>
#include <core/ElapsedTimer.h>
#include <stdio.h>
#include <stdlib.h>
#include <core/Log.h>

int main(int argc, char* argv[]) {
	//fclose(stdout);
	int w = 640;
	int h = 480;
	LOGI("Application create window (%d, %d)\n", w, h );
	//fopen(stdout);

	engine::Ref<engine::Win32Window> window = new engine::Win32Window( w, h, L"Engine test application" );	// create window

	engine::Ref<engine::OGLGraphicsSystem> graphics = new engine::OGLGraphicsSystem(window); // create graphics
	window->setGraphics(graphics);															 // Set graphics for window
	
	engine::Ref<engine::InputManager> inputManager = new engine::InputManager();			 // create inputManager
	window->setInputManager(inputManager);													// Set the input manager for window
	
	engine::Ref<engine::GraphicsApplication> application = new engine::TestApplication(window, graphics, inputManager);
	window->setApplication(application); // Set application for window

	
	engine::ElapsedTimer frameTimer;
	frameTimer.reset();
	while (window->updateMessages())
	{
		// updateMessages palautta true. Päivitä peliä.
		float deltaTime = frameTimer.getTime();
		frameTimer.reset();
		application->update(deltaTime);
	}

	LOGI("Application done!\n");
	
	return 0;
}





