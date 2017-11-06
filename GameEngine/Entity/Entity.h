#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "..\Utility\common.hpp"
#include "..\Model\Model.h"

namespace GameEngine
{
	using namespace ModelM;

	namespace EntityM
	{
		class Entity
		{
		private:
			Model* _model;
			vec3 _position;
			GLfloat _rx;
			GLfloat _ry;
			GLfloat _rz;
			GLfloat _scale;

		protected:
			void model(Model *model) { _model = model; }
			void position(vec3 val) { _position = val; }
			void rx(GLfloat val) { _rx = val; }
			void ry(GLfloat val) { _ry = val; }
			void rz(GLfloat val) { _rz = val; }
			void scale(GLfloat val) { _scale = val; }


		public:
			Entity();
			Entity(Model* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale);
			~Entity();

			// Getters
			Model* model() { return _model; }
			vec3 position() { return _position; }
			GLfloat scale() { return _scale; }
			GLfloat rx() { return _rx; }
			GLfloat ry() { return _ry; }
			GLfloat rz() { return _rz; }


			// Mutators
			virtual void increasePosition(GLfloat dx, GLfloat dy, GLfloat dz)
			{
				_position.x += dx;
				_position.y += dy;
				_position.z += dz;
			}

			virtual void increaseRotation(GLfloat dx, GLfloat dy, GLfloat dz)
			{
				_rx += dx;
				_ry += dy;
				_rz += dz;
			}
		};
	}
}
#endif /* ENTITY_H*/