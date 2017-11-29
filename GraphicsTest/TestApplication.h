/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_TEST_APPLICATION_H_
#define _ENGINE_TEST_APPLICATION_H_

#include <graphics/GraphicsApplication.h>
#include <core/Log.h>
#include <GLES2/gl2.h>
#include <OGL/Shader.h>
#include <OGL/Texture2D.h>
#include <core/InputManager.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace engine
{
	class Window;
	class GraphicsSystem;


	class TestApplication :
		public GraphicsApplication
	{
	public:
		TestApplication(Window* window, GraphicsSystem* graphics, InputManager* inputMgr, void* manager = nullptr);

		~TestApplication();

		void init();

		/// Updates application. Returns true, if application is running.
		virtual bool update(float deltaTime);
		
		/// Renders application.
		virtual void render(Window* window, GraphicsSystem* graphics);

		virtual void processInput(Window* window);

	private:
		

		float						m_totalTime;
		std::vector<Shader*>		m_shaders;
		std::vector<Texture2D*>		m_textures;
		void* 						m_assetManager;
		InputManager*				m_inputManager;

		// matrix calculation test
		glm::mat4					m_view;
		glm::mat4					m_projection;
		glm::mat4					m_model;
	};

}

#endif

