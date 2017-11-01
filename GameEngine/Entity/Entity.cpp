 #include "Entity.h"
namespace EntityM
{
	Entity::Entity()
	{

	}

	Entity::Entity(ModelM::Model* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
		: _model(model), _position(position), _rx(rx), _ry(ry), _rz(rz), _scale(scale)
	{


	}

	Entity::~Entity()
	{
	}
}