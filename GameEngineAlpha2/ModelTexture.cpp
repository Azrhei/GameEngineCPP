#include "ModelTexture.h"

ModelTexture::ModelTexture()
:textureId(0), shineDamper(0), reflectivity(0) 
{

}

ModelTexture::ModelTexture(GLint id) : textureId(id), shineDamper(0), reflectivity(0)
{
}

ModelTexture::~ModelTexture()
{
}
