#pragma once
#include <glm/glm.hpp>
#include "common.hpp"

using namespace glm;

namespace GameEngine
{
	class ICamera
	{
	private:

		vec3 _position = { 0,0,0 };
		GLfloat _pitch = 20;
		GLfloat _yaw = 0;
		GLfloat _roll = 0;
	protected:
		/*
		void roll(GLfloat val) { _roll = val; }
		void drx(GLfloat val);
		void dry(GLfloat val);
		void drz(GLfloat val);
		void drot(vec3 val);
		void drot(GLfloat pitch, GLfloat yaw, GLfloat roll);
		*/

	public:
		ICamera();
		~ICamera();

		vec3 position() { return _position; }
		GLfloat pitch() { return _pitch; }
		GLfloat yaw() { return _yaw; }
		GLfloat roll() { return _roll; }

		void position(vec3 val) { _position = val; }
		void position(GLfloat nx, GLfloat ny, GLfloat nz) { _position = { nx, ny, nz }; }
		void pitch(GLfloat val) { _pitch = val; }
		void yaw(GLfloat val) { _yaw = val; }
		void roll(GLfloat val) { _roll = val; }

		virtual void move(double delta) = 0;
		//virtual void move(double delta, vec3 npos, vec3 nrot) = 0;
		//virtual void move(double delta, vec3 npos, GLfloat drx, GLfloat dry, GLfloat drz) = 0;
		//virtual void move(double delta, GLfloat dx, GLfloat dy, GLfloat dz) = 0;
		//virtual void move(double delta, vec3 npos) = 0;
	};

}
