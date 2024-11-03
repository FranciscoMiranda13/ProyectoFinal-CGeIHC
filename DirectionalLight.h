

#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	//CAMBIAMOS LA DIRECCION
	glm::vec3 GetDirection() const;
	void SetDirection(const glm::vec3& newDirection);
	void SetIntensity(GLfloat newIntensity);          // Ajustar la intensidad difusa
	void SetAmbientIntensity(GLfloat newAmbient);     // Ajustar la intensidad ambiental
	void SetDiffuseIntensity(GLfloat newDiffuse);      // Ajustar la intensidad difusa
	~DirectionalLight();

private:
	glm::vec3 direction;
};
