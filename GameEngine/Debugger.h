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

		private:
			Debugger() {};
		};
		static Debugger& debug = Debugger::getInstance();
	}
}
#endif /* DEBUGGER_H */