#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera {
public:
	glm::mat4 get_view_matrix() const;
	// FIXME: add functions to manipulate camera objects.
	glm::mat4 lookAt(glm::vec3 at) const;
	void rotate(glm::dvec2 mouse_direction);
	void zoom(glm::dvec2 mouse_direction);
	void zoom(float zoom_direction);
	void pan(glm::dvec2 pan_direction);
	void roll(float roll_direction);
	void toggleFPS();
	bool mode() const;
	
private:
	float camera_distance_ = 3.0;
	glm::vec3 look_ = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up_ = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 eye_ = glm::vec3(0.0f, 0.0f, camera_distance_);
	// Note: you may need additional member variables
	glm::vec3 center_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 tangent_ = glm::cross(up_, look_);
	bool fps_mode = true;
};

#endif
