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
		// shader 0 = textured shader
		m_shaders.push_back(new Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag"));

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

		m_textures.push_back(new Texture2D(2, 2, 3, pixels));
		m_textures.push_back(new Texture2D(4, 3, 3, finnishPixels));
	}

	bool TestApplication::update(float deltaTime)
	{
		m_totalTime += deltaTime;
		return true;
	}


	void TestApplication::render(Window* window, GraphicsSystem* graphics)
	{
		float xVal = cosf(2.0f*m_totalTime) / 3.0f;
		float yVal = sinf(2.0f*m_totalTime) / 3.0f;

		// Triangles vertex coordinates;
		float size = 1.0f;
		float dx = -0.5f + xVal;
		float dy = -0.5f + yVal;
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
		graphics->clearScreen(val, val * 1.5f, val * 2.0f, true);


		// set OpenGL drawing window display to entire window.
		glViewport(0, 0, window->getWidth(), window->getHeight());
	
		graphics->drawTriangles(m_shaders[0], m_textures[1], quad, textureCoordinates, 6);

		// switch secondary buffer to be displayed on screen. 
		graphics->swapBuffers();
	}

}