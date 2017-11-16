#pragma once
#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Utility\common.hpp"

namespace GameEngine 
{
	namespace DEBUGGER
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

		private:
			Debugger() {};
		};
		static Debugger& debug = Debugger::getInstance();
	}
}
#endif /* DEBUGGER_H */