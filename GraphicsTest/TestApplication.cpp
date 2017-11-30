/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include <math.h>
#include <core/IOManager.h>
#include <glm/glm.hpp>

#include "TestApplication.h"

namespace engine
{
	TestApplication::TestApplication( Window * window, GraphicsSystem * graphics, InputManager* inputMgr, void * manager /* = nullptr */)
            : GraphicsApplication(window, graphics)
			, m_inputManager(inputMgr)
			, m_assetManager(manager)
            , m_totalTime(0.0f)
	{
		LOGI("Starting UP...\n");

		init();
	}

	TestApplication::~TestApplication()
	{
	}

	void TestApplication::init()
	{
		
		m_shaders.push_back(new Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag", m_assetManager));

		// Create 2x2 image, 3 bytes per pixel (R, G, B)
		GLubyte pixels[4 * 3] = 
		{
			255, 0, 0,		// Red
			0, 255, 0,		// Green
			0, 0, 255,		// Blue
			255, 255, 0		// Yellow
		};

		GLubyte finnishPixels[12 * 3] =
		{
			255, 255, 255,	// white
			0, 0, 255,		// blue
			255, 255, 255,	// white
			255, 255, 255,	// white
			
			0, 0, 255,		// blue
			0, 0, 255,		// blue
			0, 0, 255,		// blue
			0, 0, 255,		// blue

			255, 255, 255,	// white
			0, 0, 255,		// blue
			255, 255, 255,	// white
			255, 255, 255	// white
		};


		m_textures.push_back(new Texture2D(2, 2, 3, pixels));			            // 0
		m_textures.push_back(new Texture2D(4, 3, 3, finnishPixels));	            // 1
		m_textures.push_back(new Texture2D(4, 3, 4, "test.png", m_assetManager));	// 2
        m_textures.push_back(new Texture2D(1, 3, 4, "mr_t.png",m_assetManager));    // 3

		// create camera and initilize it
		m_camera = new Camera2D();
		m_camera->init(getWindow()->getWidth(), getWindow()->getHeight());


	}

	bool TestApplication::update(float deltaTime)
	{
		m_totalTime += deltaTime;
		processInput(getWindow());

		m_camera->update();
		
		return true;
	}


	void TestApplication::render(Window* window, GraphicsSystem* graphics)
	{
        // this comment was done in visual studio
		float xVal, yVal;
		xVal = (m_inputManager->getMouseX() / window->getWidth()) - 1.0f;
		
		yVal = (m_inputManager->getMouseY() / window->getHeight()) - 1.0f;

		// Triangles vertex coordinates;
		float size = 1.0f;
		float dx = xVal;
		float dy = yVal;
		float depth = 0.0f;

		GLfloat quad[] = {
			dx + 0.0f, dy + size, depth, //vertex 0
			dx + 0.0f, dy + 0.0f, depth, //vertex 1
			dx + size, dy + 0.0f, depth, //vertex 2

			dx + size, dy + size, depth, //vertex 3
			dx + size, dy + 0.0f, depth, //vertex 4
			dx + 0.0f, dy + size, depth  //vertex 5
		};

		// Texture coordinates, whose origin (0,0) is top-left corner
		GLfloat textureCoordinates[] = {
			0,0, //vertex 0
			0,1, //vertex 1
			1,1, //vertex 2
			1,0, //vertex 3
			1,1, //vertex 4
			0,0  //vertex 5
		};
		
		(void)window;	
		
		float val = fabsf(sinf(2.0f*m_totalTime));
		// Clear screen with pulsating yellow
		graphics->clearScreen(val, val * 1.5f, val * 0.5f, true);


		// set OpenGL drawing window display to entire window.
		glViewport(0, 0, window->getWidth(), window->getHeight());

		

		// switch secondary buffer to be displayed on screen. 
		graphics->swapBuffers();
	}

	void TestApplication::processInput(Window* window)
	{
		
		float mX = m_inputManager->getMouseX();
		float mY = m_inputManager->getMouseY();

		if ((mX < window->getWidth() && mX > 0) &&
			(mY < window->getHeight() && mY > 0))
		{
			LOGI("MouseX: %f MouseY: %f \r", mX, mY);
		}
	}

}