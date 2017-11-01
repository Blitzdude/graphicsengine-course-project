/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_OGLGRAPHICSSYSTEM_H_
#define _ENGINE_OGLGRAPHICSSYSTEM_H_

#include <graphics/GraphicsSystem.h>
#include <core/Ref.h>
#include <EGL/egl.h>

namespace engine
{
	// Forward declare Window-class
	class Window;

	class OGLGraphicsSystem :
		public GraphicsSystem
	{
	public:

		// Creates new OpenGL ES 2.0 Graphics System binded to given window.
		OGLGraphicsSystem(Window* window);
		~OGLGraphicsSystem();

		virtual void clearScreen(float red, float green, float blue, bool setViewport);

		virtual void swapBuffers();

	private:
		engine::Ref<Window> m_window;	// Window where graphics is binded
		bool m_active;					// True-flag if all is okay.

		// Embedded OpenGLES member variables
		EGLDisplay m_eglDisplay; // Display object
		EGLContext m_eglContext; // Context object
		EGLSurface m_eglSurface; // Surface object
	};

}

#endif


