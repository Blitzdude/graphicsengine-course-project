/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_GRAPHICSSYSTEM_H_
#define _ENGINE_GRAPHICSSYSTEM_H_

#include <core/Object.h>
#include <stdint.h>
#include <string>
#include <fstream>
#include <GLES2/gl2.h>
#include <OGL/Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
	class GraphicsSystem :
		public Object
	{

	public:
		GraphicsSystem();
		~GraphicsSystem();

		// Clears the screen using given color
		virtual void clearScreen(float red, float green, float blue, bool setViewport) = 0;

		// Method for swapping backbuffer to screen.
		virtual void swapBuffers() = 0;

		virtual void createNewShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath, void* manager) = 0;
		
		virtual Shader* getShader(int index) = 0;
	
	};
}

#endif

