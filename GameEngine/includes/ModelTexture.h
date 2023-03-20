#pragma once
#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#include "common.hpp"

namespace GameEngine
{
	class ModelTexture
	{
	private:
		GLint _textureId;
		GLfloat _shineDamper;
		GLfloat  _reflectivity;
		bool _hasTransparency;
		bool _useFakeLighting;

	public:
		ModelTexture();
		ModelTexture(GLint id);
		~ModelTexture();
		bool hasTransparency() { return _hasTransparency; }
		void hasTransparency(bool newVal) { _hasTransparency = newVal; }

		GLint id() { return _textureId; }
		GLfloat shineDampener() { return _shineDamper; }
		GLfloat reflectivity() { return _reflectivity; }

		bool useFakeLighting() { return _useFakeLighting; }
		void useFakeLighting(bool newVal) { _useFakeLighting = newVal; }

		void transparency(bool newVal) { _hasTransparency = newVal; }
		void shineDampener(GLfloat newValue) { _shineDamper = newValue; }
		void reflectivity(GLfloat newValue) { _reflectivity = newValue; }
	};
}
#endif /* MODEL_TEXTURE_H */