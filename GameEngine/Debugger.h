#pragma once
#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Utility\common.hpp"

namespace GameEngine 
{
	namespace Debugger
	{
		class Debugger
		{
		private:

		public:
			static Debugger & getInstance()
			{
				static Debugger _inst_{} ;
				return _inst_;
			}
			void GetFirstNMessages(GLuint numMsgs);
			Debugger(Debugger&) = delete;
			void operator=(Debugger&) = delete;
			~Debugger();

			void ClearError()
			{
				while (glGetError() != GL_NO_ERROR);
			}

			bool checkErrors()
			{
				GLenum err;
				static bool hasError = false;
				while ((err = glGetError()) != GL_NO_ERROR) {
					hasError = true;
					std::cerr << err << nl;
					return err;
				}
				
				return hasError;
			}

			static void APIENTRY DebugMessageCB(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, const void* userParam​);

		private:
			Debugger() 
			{
#ifdef DEBUG
				GLDEBUGPROC MessageCB = &(Debugger::DebugMessageCB);
				if (glDebugMessageCallback) {
					cout << "Register OpenGL debug callback " << endl;
					glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
					glDebugMessageCallback(MessageCB, nullptr);
					GLuint unusedIds = 0;
					glDebugMessageControl(GL_DONT_CARE,
						GL_DONT_CARE,
						GL_DONT_CARE,
						0,
						&unusedIds,
						true);
				}
				else
					cout << "glDebugMessageCallback not available" << endl;
#endif
			}
		};
		static Debugger& debug = Debugger::getInstance();
	}
}
#endif /* DEBUGGER_H */