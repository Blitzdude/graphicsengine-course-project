/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <TestApplication.h>

#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include <math.h>


namespace engine
{

	TestApplication::TestApplication(Window* window, GraphicsSystem* graphics)
		: GraphicsApplication(window, graphics)
		, m_totalTime(0.0f)
	{
		init();
	}


	TestApplication::~TestApplication()
	{
	}

	void TestApplication::init()
	{
		m_shader.CreateShaderProgram("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
	}

	bool TestApplication::update(float deltaTime)
	{
		m_totalTime += deltaTime;
		return true;
	}


	void TestApplication::render(Window* window, GraphicsSystem* graphics)
	{
		// Triangles vertex coordinates;
		float size = 1.0f;
		float dx = -0.5f;
		float dy = -0.5f;
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
		graphics->clearScreen(val, val, 0.0f, true);


		// set OpenGL drawing widnow display to entire window.
		glViewport(0, 0, window->getWidth(), window->getHeight());
	
		graphics->drawTriangles(&m_shader, quad, textureCoordinates, 6);

		// switch secondary buffer to be displayed on screen. 
		graphics->swapBuffers();
	}

}