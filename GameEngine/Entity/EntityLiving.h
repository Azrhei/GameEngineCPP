#pragma once
#include "Entity.h"
class EntityLiving :
	public Entity
{
private:
	typedef enum {
		CHILD,
		ADULT
	}AGE;

	GLuint _health;
	GLuint _hunger;
	GLuint _satiation;
	AGE _age;

protected:
	void doDamage(GLint damage) { _health -= damage; }
	void doHeal(GLint heal) { _health += heal; }
	void setHealth(GLuint h) { _health = h; }
	void feed(GLint f) { _hunger -= f; }
	void growUp() { if (_age == CHILD) _age = AGE::ADULT; }

public:
	EntityLiving();
	EntityLiving(Model* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
		: Entity(model, position, rx, ry, rz, scale) {}
	~EntityLiving();
};

