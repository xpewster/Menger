#include "menger.h"

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

Menger::Menger()
{
	// Add additional initialization if you like
}

Menger::~Menger()
{
}

void
Menger::set_nesting_level(int level)
{
	nesting_level_ = level;
	dirty_ = true;
}

bool
Menger::is_dirty() const
{
	return dirty_;
}

void
Menger::set_clean()
{
	dirty_ = false;
}

// FIXME generate Menger sponge geometry
void
Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& obj_faces) const
{
	int k = 0;
	std::vector<cube> cubes;
	cube base;
	base.position = glm::vec3(0.0, 0.0, 0.0);
	base.width = 1.0;
	generate_subcube(base.vertices, base.faces, base.position, base.width);
	cubes.push_back(base);
	while(k < nesting_level_){
		std::vector<cube> cubes2;
		for (cube c : cubes){
			glm::vec3 pos = c.position;
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					for(int h = 0; h < 3; h++){
						if (!((i == j && i == 1) || (j == h && j == 1) || (i == h && h == 1))){
							cube sub;
							float third = c.width/3.0;
							glm::vec3 newPos = {pos.x-1.5*third+(i*third), pos.y-1.5*third+(j*third), pos.z-1.5*third+(h*third)};
							generate_subcube(sub.vertices, sub.faces, newPos, third);
							sub.position = newPos;
							sub.width = third;
							cubes2.push_back(sub);
						}
					}
				}
			}
		}
		cubes = cubes2;
		k++;
	}
	CreateMenger(obj_vertices, obj_faces, cubes);
}

void
Menger::CreateMenger(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& obj_faces, std::vector<cube> cubes) const
{
	obj_vertices.clear();
	obj_faces.clear();
	for(cube c : cubes){
		int index = obj_vertices.size();
		obj_vertices.insert(obj_vertices.end(), c.vertices.begin(), c.vertices.end());
		for(size_t i = 0; i < c.faces.size(); i++){
			glm::uvec3 face = c.faces[i];
			face.x += index;
			face.y += index;
			face.z += index;
			obj_faces.push_back(face);
		}
	}
}


void
Menger::generate_subcube(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& obj_faces, glm::vec3 center, float width) const
{
	uint16_t index = obj_vertices.size();
	obj_vertices.push_back(glm::vec4(center.x-width/2.0, center.y-width/2.0, center.z-width/2, 1.0f));
	obj_vertices.push_back(glm::vec4(center.x+width/2.0, center.y-width/2.0, center.z-width/2, 1.0f));
	obj_vertices.push_back(glm::vec4(center.x+width/2.0, center.y+width/2.0, center.z-width/2, 1.0f));
	obj_vertices.push_back(glm::vec4(center.x-width/2.0, center.y+width/2.0, center.z-width/2, 1.0f));
	obj_vertices.push_back(glm::vec4(center.x-width/2.0, center.y+width/2.0, center.z+width/2, 1.0f));
	obj_vertices.push_back(glm::vec4(center.x-width/2.0, center.y-width/2.0, center.z+width/2, 1.0f));
	obj_vertices.push_back(glm::vec4(center.x+width/2.0, center.y-width/2.0, center.z+width/2, 1.0f));
	obj_vertices.push_back(glm::vec4(center.x+width/2.0, center.y+width/2.0, center.z+width/2, 1.0f));

	obj_faces.push_back(glm::uvec3(index, index+1, index+2));
	obj_faces.push_back(glm::uvec3(index, index+2, index+3));

	obj_faces.push_back(glm::uvec3(index+1, index+2, index+7));
	obj_faces.push_back(glm::uvec3(index+1, index+6, index+7));

	obj_faces.push_back(glm::uvec3(index, index+6, index+1));
	obj_faces.push_back(glm::uvec3(index, index+5, index+6));

	obj_faces.push_back(glm::uvec3(index, index+3, index+5));
	obj_faces.push_back(glm::uvec3(index+3, index+4, index+5));

	obj_faces.push_back(glm::uvec3(index+4, index+6, index+5));
	obj_faces.push_back(glm::uvec3(index+4, index+7, index+6));

	obj_faces.push_back(glm::uvec3(index+2, index+4, index+3));
	obj_faces.push_back(glm::uvec3(index+2, index+7, index+4));
}
