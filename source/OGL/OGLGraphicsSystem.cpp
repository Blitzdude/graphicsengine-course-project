/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <OGL/OGLGraphicsSystem.h>
#include <graphics/Window.h>
#include <initializer_list>
#include <OGL/OGL.h>
#include <fstream>
#include <core/Log.h>
#include <string>

namespace engine
{
	OGLGraphicsSystem::OGLGraphicsSystem(Window* window)
		: GraphicsSystem()
		, m_window(window)
		, m_active(false)
	{
		assert(window != 0);
		
		// Here specify the attributes of the desired configuration.
		// Below, we select an EGLConfig with at least 8 bits per color
		// component compatible with on-screen windows
		const EGLint attribs[] = {
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_ALPHA_SIZE, 8,
				EGL_DEPTH_SIZE, 16,
				EGL_NONE
		};
		EGLint w, h, format;
		EGLint numConfigs;
		EGLConfig config;
		m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		eglInitialize(m_eglDisplay, 0, 0);

		// Here, the application chooses the configuration it desires.
        // find the best match if possible, otherwise use the very first one
		eglChooseConfig(m_eglDisplay, attribs, nullptr, 0, &numConfigs);
		EGLConfig* supportedConfigs = new EGLConfig[numConfigs];
		assert(supportedConfigs);
		eglChooseConfig(m_eglDisplay, attribs, supportedConfigs, numConfigs, &numConfigs);
		assert(numConfigs);
		int i = 0;
		for (; i < numConfigs; i++)
		{
			EGLConfig& cfg = supportedConfigs[i];
			EGLint a;
		//	LOGI("EGL_CONFIG[%d]:", i);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_RED_SIZE, &a);
		//	LOGI("  EGL_RED_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_GREEN_SIZE, &a);
		//	LOGI("  EGL_GREEN_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_BLUE_SIZE, &a);
		//	LOGI("  EGL_BLUE_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_ALPHA_SIZE, &a);
		//	LOGI("  EGL_ALPHA_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_DEPTH_SIZE, &a);
		//	LOGI("  EGL_DEPTH_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_STENCIL_SIZE, &a);
		//	LOGI("  EGL_STENCIL_SIZE: %d", a);
			eglGetConfigAttrib(m_eglDisplay, cfg, EGL_SAMPLE_BUFFERS, &a);
		//	LOGI("  EGL_SAMPLE_BUFFERS: %d", a);
		}

		config = supportedConfigs[0];
		for (; i < numConfigs; i++)
		{
			EGLint r, g, b, d;
			EGLConfig& cfg = supportedConfigs[i];
			if (eglGetConfigAttrib(m_eglDisplay, cfg, EGL_RED_SIZE, &r) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_GREEN_SIZE, &g) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_BLUE_SIZE, &b) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_DEPTH_SIZE, &d) &&
				r == 8 && g == 8 && b == 8 && d == 0 ) {

				config = supportedConfigs[i];
				break;
			}
		}
	
		// EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
        // guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
        // As soon as we picked a EGLConfig, we can safely reconfigure the
        // ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
		eglGetConfigAttrib(m_eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, config, window->getNativeWindow(), NULL);
		EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
		m_eglContext = eglCreateContext(m_eglDisplay, config, NULL, contextAttribs);

		if (eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext) == EGL_FALSE) {
			assert(0);//LOGW("Unable to eglMakeCurrent");
		}

		// Get size of the surface
		eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &w);
		eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &h);
		window->setSize(w,h);

		LOGI("OpenGL information:\n");
		LOGI("  GL_VENDOR: %s\n", glGetString(GL_VENDOR));
		LOGI("  GL_RENDERER: %s\n", glGetString(GL_RENDERER));
		LOGI("  GL_VERSION: %s\n", glGetString(GL_VERSION));
		LOGI("  GL_EXTENSIONS: %s\n", glGetString(GL_EXTENSIONS));
		LOGI("Surface size: %dx%d\n", w, h);
		
		// initialize shaders and such
		
		m_active = true;
	}

	OGLGraphicsSystem::~OGLGraphicsSystem()
	{
		
	}

	void OGLGraphicsSystem::clearScreen(float red, float green, float blue, bool setViewport)
	{
		// Sets wiewport and clears the screen by given color.
		if (setViewport)
			glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
		glClearColor(red, green, blue, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	
	void OGLGraphicsSystem::swapBuffers()
	{
		eglSwapBuffers(m_eglDisplay, m_eglSurface);
	}

	
	void OGLGraphicsSystem::drawTriangles(	Shader* shader,
											float vertices[],
											float textureCoordinates[],
											int numVertices)
	{
		// bind program to be used
		shader->use();

		// set position of the vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Set texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
		glEnableVertexAttribArray(1);

		// draw the vertex array as triangle
		glDrawArrays(GL_TRIANGLES, 0, numVertices);

		// dont forget to unuse !
		shader->unUse();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	}

	void OGLGraphicsSystem::drawTriangles(Shader * shader, Texture2D * texture, float vertices[], float textureCoordinates[], int numVertices)
	{
		// Bind shader
		shader->use();

		// Set positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// set texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
		glEnableVertexAttribArray(1);

		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureId());

		// set the sampler texture unit to 0
		glUniform1i(shader->getUniformLocation("texture"), 0);

		// draw vertex arrays as triangle
		glDrawArrays(GL_TRIANGLES, 0, numVertices);

		// don't forget to unUse!
		shader->unUse();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}