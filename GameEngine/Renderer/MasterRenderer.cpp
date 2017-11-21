#include "MasterRenderer.h"
#include "..\Display\Display.h"
#include "..\Debugger.h"

namespace GameEngine
{
	using namespace DisplayM;
	using namespace EntityM;
	using namespace ModelM;
	using namespace Debugger;
	namespace RenderM
	{
		MasterRenderer::MasterRenderer()
			: _entity_shader(new StaticShader), _terrain_shader(new TerrainShader), _terrains(new vector<Terrain>{})
		{
			_entities = new map<Model*, vector<Entity>>;

			enableCulling();

			glCullFace(GL_BACK);

			createProjectionMatrix();

			_entity_renderer = new EntityRenderer{ _entity_shader, projectionMatrix };
			_terrain_renderer = new TerrainRenderer{ _terrain_shader, projectionMatrix };
		}

		void MasterRenderer::enableCulling()
		{
			glEnable(GL_CULL_FACE);
		}

		void MasterRenderer::disableCulling()
		{
			glDisable(GL_CULL_FACE);
		}

		MasterRenderer::~MasterRenderer()
		{
			delete _entity_renderer;
			delete _terrain_renderer;
			_entities->clear();
			delete _entities;
			_terrains->clear();
			delete _terrains;
		}

		void MasterRenderer::processTerrain(Terrain terrain)
		{
			_terrains->push_back(terrain);
		}

		void MasterRenderer::render(Light& sun, Camera& cam)
		{
			prepare();

			if (!(_terrains->empty()))
			{
				_terrain_shader->start();
				_terrain_shader->loadSkyColor(RED, GREEN, BLUE);
				_terrain_shader->loadLight(sun);
				_terrain_shader->loadViewMatrix(cam);

				_terrain_renderer->render(_terrains);

				_terrain_shader->stop();
				_terrains->clear();
			}

			if (!(_entities->empty()))
			{
				_entity_shader->start();
				_entity_shader->loadSkyColor(RED, GREEN, BLUE);
				_entity_shader->loadLight(sun);
				_entity_shader->loadViewMatrix(cam);

				_entity_renderer->render(_entities);

				_entity_shader->stop();
				_entities->clear();
			}
		}

		// Add an entity to be rendered during render cycle.
		void MasterRenderer::processEntity(Entity& entity)
		{
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


			// It should be noted that having more than 1 entity makes this fail....still.
			Model* model = entity.model();
			if (_entities->empty())
			{
				vector<Entity>* t = new vector<Entity>();
				t->push_back(entity);
				_entities->insert(make_pair(model, *t));
			}
			else {
				auto it = _entities->find(model);
				if (it != _entities->end())
				{
					(it->second).push_back(entity);
				}
				else
				{
					vector<Entity>* t = new vector<Entity>();
					t->push_back(entity);
					_entities->insert(make_pair(model, *t));
				}
			}
		}

		mat4* MasterRenderer::createProjectionMatrix()
		{
			//glm can do this for us, see glm::frustrum
			// Generate a Frustum matrix for converting from orthogonal space
			GLfloat aspectRatio = (GLfloat)display.width() / (GLfloat)display.height();
			GLfloat y_scale = (1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio;
			GLfloat x_scale = y_scale / aspectRatio;
			GLfloat frustrum_length = F_Plane - N_Plane;

			mat4* matrix = new mat4{ 1 };
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
			// Clear screen and set color before drawing frame
			glClearColor(RED, GREEN, BLUE, 1);
			
			// Clear color buffer and depth buffer for next frame
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Enable Depth testing
			glEnable(GL_DEPTH_TEST);
		}
	}
}