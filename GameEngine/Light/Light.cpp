#include "Light.h"

Light::Light(vec3 pos, vec3 col, GLfloat inten)
: _position(pos), _color(col), _intensity(inten)
{

}

Light::Light()
{
}


Light::~Light()
{
}
