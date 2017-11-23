#include "OGL/Shader.h"
#include <core/Log.h>
#include <core/IOManager.h>
#include <fstream>


namespace engine {
	Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath, void* manager) 
	{
		CreateShaderProgram(vertexShaderFilePath, fragmentShaderFilePath, manager);
	}

	Shader::~Shader()
	{
		glDeleteProgram(programId);
	}

	void Shader::CreateShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath, void* manager)
	{

		std::string vertSource;
		std::string fragSource;


        LOGI("Loading vertex shader\n");
        if (!IOManager::readFileToBuffer(vertexShaderFilePath, vertSource, manager)) {
			LOGE("Failed to load vertex shader file\n");
		}

		LOGI("%s\n\n\n\n", vertSource.c_str());

        LOGI("Loading fragment shader\n");
		if (!IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource, manager)) {
			LOGE("Failed to load fragment shader file\n");
		}

		LOGI("%s\n\n\n\n", fragSource.c_str());

		compileShadersFromSource(vertSource.c_str(), fragSource.c_str());

		// link the shaders to the program then detach them
		linkShaders();
	}

	void Shader::compileShadersFromSource(const char * vertexSource, const char * fragmentSource)
	{
		//Get a program object.
		programId = glCreateProgram();

		//Create the vertex shader object, and store its ID
		vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

		//Create the fragment shader object, and store its ID
		fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		//Compile each shader
		compileShader(vertexSource, "Vertex Shader", vertexShaderId);
		compileShader(fragmentSource, "Fragment Shader", fragmentShaderId);

	}

	void Shader::compileShader(const char * source, const std::string & name, GLuint id)
	{

		//tell opengl that we want to use fileContents as the contents of the shader file
		glShaderSource(id, 1, &source, nullptr);

		//compile the shader
		glCompileShader(id);

		//check for errors
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) //error checking
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			GLchar errorLog[128];
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Exit with failure.
			glDeleteShader(id); //Don't leak the shader.

			LOGI("Shader %s failed to compile: %s\n", name.c_str(), &(errorLog[0]));
		}
	}

	void Shader::linkShaders()
	{
		//Attach our shaders to our program
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);

		// binds the attributes TODO: create separate method. 
		glBindAttribLocation(programId, 0, "vPosition");

		//Link our program
		glLinkProgram(programId);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			GLchar errorLog[128];
			glGetProgramInfoLog(programId, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(programId);
			//Don't leak shaders either.
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);

			//print the error log and quit
			LOGI("Shaders failed to link! %s\n", &(errorLog[0]));
		}

		//Always detach shaders after a successful link.
		glDetachShader(programId, vertexShaderId);
		glDetachShader(programId, fragmentShaderId);
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}

	void Shader::use()
	{
		glUseProgram(programId);
		// todo bind attributes
	}

	void Shader::unUse()
	{
		glUseProgram(0);
		// todo unbind attributes
	}
	GLuint Shader::getUniformLocation(const char * const uniformName)
	{
		return (GLuint)glGetUniformLocation(programId, uniformName);
	}
}


