#include "camera.h"

namespace {
	float pan_speed = 0.1f;
	float roll_speed = 0.1f;
	float rotation_speed = 0.05f;
	float zoom_speed = 0.1f;
};

// FIXME: Calculate the view matrix
glm::mat4 Camera::get_view_matrix() const
{
	return lookAt(center_);
}

glm::mat4 Camera::lookAt(glm::vec3 at) const
{
	glm::vec3 forward = glm::normalize(eye_-at); // z
	glm::vec3 right = glm::normalize(glm::cross(up_, forward)); // x
	glm::vec3 up = glm::normalize(glm::cross(forward, right)); // y

	glm::mat4 lookMat = glm::mat4(1.0);
	lookMat[0][0] = right.x;
	lookMat[1][0] = right.y;
	lookMat[2][0] = right.z;
	lookMat[0][1] = up.x;
	lookMat[1][1] = up.y;
	lookMat[2][1] = up.z;
	lookMat[0][2] = forward.x;
	lookMat[1][2] = forward.y;
	lookMat[2][2] = forward.z;

	lookMat[3][0] = -glm::dot(right, eye_);
	lookMat[3][1] = -glm::dot(up, eye_);
	lookMat[3][2] = -glm::dot(forward, eye_);

	return lookMat;
}

void Camera::rotate(glm::dvec2 mouse_direction) {
	float dx = (float)mouse_direction.x;
	float dy = (float)mouse_direction.y;

	glm::vec3 axis = glm::cross(glm::vec3(look_.x, 0.0, look_.z), dx * tangent_ + dy * up_);

	look_ = glm::normalize(glm::rotate(look_, -rotation_speed, axis));
	up_ = glm::normalize(glm::rotate(up_, -rotation_speed, axis));
	tangent_ = glm::normalize(glm::cross(up_, look_));

	if (fps_mode)
		center_ = eye_ + camera_distance_ * look_;
	else
		eye_ = center_ - camera_distance_ * look_;
}

void Camera::zoom(glm::dvec2 mouse_direction) {
	float dy = (float)mouse_direction.y;
	if (dy < 0)
		eye_ += look_ * zoom_speed;
	else if (dy > 0)
		eye_ -= look_ * zoom_speed;
	camera_distance_ = glm::length(eye_ - center_);
}

void Camera::zoom(float zoom_direction) {
	if (zoom_direction < 0){
		eye_ += look_ * zoom_speed;
		if (fps_mode)
			center_ += look_ * zoom_speed;
	}
	else if (zoom_direction > 0){
		eye_ -= look_ * zoom_speed;
		if (fps_mode)
			center_ -= look_ * zoom_speed;
	}
}

void Camera::pan(glm::dvec2 pan_direction) {
	if (fps_mode){
		eye_ += tangent_ * (float)pan_direction.x * pan_speed;
		eye_ += up_ * (float)pan_direction.y * pan_speed;
	}
	center_ += tangent_ * (float)pan_direction.x * pan_speed;
	center_ += up_ * (float)pan_direction.y * pan_speed;
}

void Camera::roll(float roll_direction) {
	if (roll_direction > 0)
		up_ = glm::normalize(glm::rotate(up_, -roll_speed, look_));
	else if (roll_direction < 0)
		up_ = glm::normalize(glm::rotate(up_, roll_speed, look_));
	tangent_ = glm::normalize(glm::cross(up_, look_));
}

void Camera::toggleFPS() {fps_mode = !fps_mode;}

bool Camera::mode() const {return fps_mode;}