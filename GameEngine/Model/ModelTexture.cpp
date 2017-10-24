#include "ModelTexture.h"

ModelTexture::ModelTexture()
:_textureId(0), _shineDamper(0), _reflectivity(0), _hasTransparency(false), _useFakeLighting(false)
{

}

ModelTexture::ModelTexture(GLint id) : _textureId(id), _shineDamper(0), _reflectivity(0), _hasTransparency(false), _useFakeLighting(false)
{
}

ModelTexture::~ModelTexture()
{
}
