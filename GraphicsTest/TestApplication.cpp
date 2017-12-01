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
#include <core/ResourceManager.h>
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
		
		initShaders();
		// create camera and initilize it
		m_camera = new Camera2D();
		m_camera->init(getWindow()->getWidth(), getWindow()->getHeight());
		//create textures
		ResourceManager::createTexture("mr_t.png", 50, 50, 4, m_assetManager);
		// create Spritebatch and initialize it
		m_spriteBatch = new SpriteBatch();
		m_spriteBatch->init();
	}

	void TestApplication::initShaders()
	{
		getGraphicsSystem()->createNewShader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag", m_assetManager); // indexed at 0
		auto shaderPtr = getGraphicsSystem()->getShader(0);

		shaderPtr->addAttribute("vPosition");
		shaderPtr->addAttribute("vTexCoord");

		shaderPtr->linkShaders();

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
		float xVal, yVal;
		xVal = m_inputManager->getMouseX();
		
		yVal = (m_inputManager->getMouseY()) * -1.0f;


		
		(void)window;	
		
		float val = fabsf(sinf(2.0f*m_totalTime));
		// Clear screen with pulsating yellow
		graphics->clearScreen(val, val * 1.5f, val * 0.5f, true);

		auto shaderProg = graphics->getShader(0);

		shaderProg->use();

		//setCamera matrix
		GLint pLocation = shaderProg->getUniformLocation("MVP");
		glm::mat4 cameraMatrix = m_camera->getCameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		m_spriteBatch->begin();

		glm::vec4 position(xVal, yVal, 50.0f, 50.0f);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		
		Texture2D fooTexture = ResourceManager::getTexture("mr_t.png");

		m_spriteBatch->draw(position, uv, fooTexture.id, 0.0f, ColorRGBA8(255, 255, 255, 255));

		m_spriteBatch->end();

		m_spriteBatch->renderBatch();

		shaderProg->unUse();
		
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