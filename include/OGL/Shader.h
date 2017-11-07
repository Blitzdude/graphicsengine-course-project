#pragma once
#include <core/Object.h>
#include <GLES2\gl2.h>
#include <core\Ref.h>
#include <EGL\egl.h>
#include <string>


namespace engine {

	class Shader : public Object
	{
	public:

		Shader();

		~Shader();

		void CreateShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void readFileToBuffer(std::string filePath, std::string& buffer);
		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

		void compileShader(const char* source, const std::string& name, GLuint id);

		void linkShaders();

		void use();

		void unUse();

		// public members
		GLuint vertexShaderId;
		GLuint fragmentShaderId;

		GLuint programId;

	};

}

