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
#include <GLES2\gl2.h>


namespace engine
{

	TestApplication::TestApplication(Window* window, GraphicsSystem* graphics)
		: GraphicsApplication(window, graphics)
		, m_totalTime(0.0f)
	{
		// initialize the shaders and link them to a program.
		m_programId = graphics->CreateShaderProgram("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
		m_blueProgramId = graphics->CreateShaderProgram("Shaders/VertexShader.vert", "Shaders/BlueFragmentShader.frag");
	}


	TestApplication::~TestApplication()
	{
	}

	bool TestApplication::update(float deltaTime)
	{
		m_totalTime += deltaTime;
		return true;
	}


	void TestApplication::render(Window* window, GraphicsSystem* graphics)
	{
		// Triangles vertex coordinates;
		GLfloat vVertices1[] = {
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
		};

		// Triangles vertex coordinates;
		GLfloat vVertices2[] = {
			
			-0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};
		
		(void)window;	
		float val = fabsf(sinf(2.0f*m_totalTime));
		
		// Clear screen with pulsating yellow
		graphics->clearScreen(val, val, 0.0f, true);


		// set OpenGL drawing widnow display to entire window.
		glViewport(0, 0, window->getWidth(), window->getHeight());
		// Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use the shader program
		graphics->use(m_programId);

		// Load the vertex data to GPU
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices1);
		// Enable the first vertex attribute array ("attribute vec4 vPosition" in shader code)
			// done in graphics->use();

		// draw triangles in GL_triangle mode
		glDrawArrays(GL_TRIANGLES, 0, 3);

		graphics->use(m_blueProgramId);

		// Load the vertex data to GPU
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices2);
		// Enable the first vertex attribute array ("attribute vec4 vPosition" in shader code)
		// done in graphics->use();

		// draw triangles in GL_triangle mode
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		graphics->unUse();


		// switch secondary buffer to be displayed on screen. 
		graphics->swapBuffers();
	}

}