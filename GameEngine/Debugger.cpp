//#include "Debugger.h"
#include <vector>
#include "common.hpp"
#include <string>

namespace GameEngine
{
	class Debugger {
		void DebugMessageCB(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, const void* userParam​);
		void GetFirstNMessages(GLuint numMsgs);
	};

	void Debugger::DebugMessageCB(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, const void* userParam​)
	{
		cerr << source​ << " : " << type​ << " : " << id​ << " : " << severity​ << " : ";
		cerr << message​ << endl;
	}

	void Debugger::GetFirstNMessages(GLuint numMsgs)
	{
		GLint maxMsgLen = 0;
		glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &maxMsgLen);
		if (maxMsgLen == 0)
		{
			cerr << "No debug messages...." << endl;
			return;
		}

		std::vector<GLchar> msgData(numMsgs * maxMsgLen);
		std::vector<GLenum> sources(numMsgs);
		std::vector<GLenum> types(numMsgs);
		std::vector<GLenum> severities(numMsgs);
		std::vector<GLuint> ids(numMsgs);
		std::vector<GLsizei> lengths(numMsgs);

		GLuint numFound = glGetDebugMessageLog(numMsgs, (GLsizei)msgData.size() * sizeof(vector<GLchar>), &sources[0], &types[0], &ids[0], &severities[0], &lengths[0], &msgData[0]);

		sources.resize(numFound);
		types.resize(numFound);
		severities.resize(numFound);
		ids.resize(numFound);
		lengths.resize(numFound);

		std::vector<std::string> messages;
		messages.reserve(numFound);

		std::vector<GLchar>::iterator currPos = msgData.begin();
		for (size_t msg = 0; msg < lengths.size(); ++msg)
		{
			messages.push_back(std::string(currPos, currPos + lengths[msg] - 1));
			currPos = currPos + lengths[msg];
		}

		for (string s : messages)
		{
			cerr << s << endl;
		}
	}
}