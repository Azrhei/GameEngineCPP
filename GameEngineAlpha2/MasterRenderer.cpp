#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
: shader(new StaticShader), terrain_shader(new TerrainShader)
{
	this->entities = new map<TexturedModel*, vector<Entity*>>;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	createProjectionMatrix();

	entity_renderer = new EntityRenderer{ shader, projectionMatrix };
	terrain_renderer = new TerrainRenderer{ terrain_shader, projectionMatrix };
}


MasterRenderer::~MasterRenderer()
{
	delete entity_renderer;
	delete terrain_renderer;
	entities->clear();
	delete entities;

}

void MasterRenderer::render(Light* sun, ICamera* cam)
{
	assert(cam != NULL);
	assert(sun != NULL);
	assert(this->shader != NULL);
	assert(this->entity_renderer != NULL);

	prepare();

	if (!entities && !entities->empty())
	{
		shader->start();

		shader->loadLight(sun);
		shader->loadViewMatrix(cam);

		entity_renderer->render(entities);

		shader->stop();
		entities->clear();
	}

	if (terrains != NULL && !terrains->empty())
	{
		terrain_shader->start();

		terrain_shader->loadLight(sun);
		terrain_shader->loadViewMatrix(cam);

		terrain_renderer->render(terrains);

		terrain_shader->stop();
		terrains->clear();
	}

}

// Add an entity to be rendered during render cycle.
void MasterRenderer::processEntity(Entity* entity)
{
	assert(entity != NULL);
	/* 
	is entity null ? break;
    is entities empty?
		construct vector
		insert entity into vector
		create pair with model and new vector
		insert into entities.
	else we need to find if key/model already exists
		if it does, 
			go to it and access it's vector (which should be empty)
			add entity to vector (should update if we use pointers corretly)
		if it does not
			we need to construct new vector
			add entity to vector
			make pair with key/model and new vector
			insert pair into entities.

	if using point to vector then we also need to make certain to allocate the vector when creating the vector
	*/
	
	TexturedModel* model = entity->getModel();
	if (entities->empty())
	{
		vector<Entity*>* t = new vector<Entity*>();
		t->push_back(entity);
		entities->insert(make_pair(model, *t));
	}
	else{
		auto it = entities->find(model);
		if (it != entities->end())
		{
			(it->second).push_back(entity);
		}
		else
		{
			vector<Entity*>* t = new vector<Entity*>();
			t->push_back(entity);
			entities->insert(make_pair(model, *t));
		}
	}
}

glm::mat4* MasterRenderer::createProjectionMatrix()
{
	//glm can do this for us, see glm::frustrum
	// Generate a Frustum matrix for converting from orthogonal space
	GLfloat aspectRatio = (GLfloat)::display->getWidth() / (GLfloat)::display->getHeight();
	GLfloat y_scale = (1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustrum_length = F_Plane - N_Plane;

	glm::mat4* matrix = new glm::mat4{ 1 };
	(*matrix)[0][0] = x_scale;
	(*matrix)[1][1] = y_scale;
	(*matrix)[2][2] = -((F_Plane + N_Plane) / frustrum_length);
	(*matrix)[2][3] = -1;
	(*matrix)[3][2] = -((2 * N_Plane * F_Plane) / frustrum_length);
	(*matrix)[3][3] = 0;

	this->projectionMatrix = matrix;

	return matrix;
}

void MasterRenderer::prepare()
{
	// Enable Depth testing
	glEnable(GL_DEPTH_TEST);

	// Clear color buffer and depth buffer for next frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear screen and set color before drawing frame
	glClearColor(0.49f, .89f, 0.98f, 1);
}