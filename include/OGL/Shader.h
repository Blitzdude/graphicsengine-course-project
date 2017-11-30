#ifndef _SHADER_H_
#define _SHADER_H_

#include <core/Object.h>
#include <GLES2/gl2.h>
#include <core/Ref.h>
#include <EGL/egl.h>
#include <string>


namespace engine {

	class Shader : public Object
	{
	public:

		
		Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath, void* manager);

		~Shader();
		void CreateShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath, void* manager);

		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);
		void compileShader(const char* source, const std::string& name, GLuint id);
		void linkShaders();

		void use();

		void unUse();

		void addAttribute(const std::string& attributeName);
		
		GLuint getUniformLocation(const char* const uniformName);

		void dispose();
		
		// public members
	private:
		GLuint m_vertexShaderId;
		GLuint m_fragmentShaderId;

		GLuint m_programId;
		int m_numAttributes;

	};

}

#endif // !_SHADER_H_
