#ifndef MENGER_H
#define MENGER_H

#include <glm/glm.hpp>
#include <vector>

struct cube{
	std::vector<glm::vec4> vertices;
	std::vector<glm::uvec3> faces;
	glm::vec3 position;
	float width;
};

class Menger {
public:
	Menger();
	~Menger();
	void set_nesting_level(int);
	bool is_dirty() const;
	void set_clean();
	void generate_geometry(std::vector<glm::vec4>& obj_vertices,
	                       std::vector<glm::uvec3>& obj_faces) const;
	void CreateMenger(std::vector<glm::vec4>& obj_vertices,
	                       std::vector<glm::uvec3>& obj_faces,  std::vector<cube> cubes) const;
	void generate_subcube(std::vector<glm::vec4>& obj_vertices,
	                       std::vector<glm::uvec3>& obj_faces, glm::vec3 center, float width) const;
private:
	int nesting_level_ = 0;
	bool dirty_ = false;
};

#endif
