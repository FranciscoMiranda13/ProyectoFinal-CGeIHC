/*
Entrega de los modelos y casillas 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;

//Casillas
Model Casilla28;
Model Casilla29;
Model Casilla30;
Model Casilla31;
Model Casilla32;
Model Casilla33;
Model Casilla34;
Model Casilla35;
Model Casilla36;
Model Casilla37;
Model Casilla38;
Model Casilla39;
Model Casilla40;

//Modelos de las casillas 
Model ModeloCasilla28;
Model ModeloCasilla29;
Model ModeloCasilla30;
Model ModeloCasilla31;
Model ModeloCasilla32;
Model ModeloCasilla33;
Model ModeloCasilla34;
Model ModeloCasilla35;
Model ModeloCasilla36;
Model ModeloCasilla37;
Model ModeloCasilla38;
Model ModeloCasilla39;
Model ModeloCasilla40;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();


	//Casillas
	Casilla28 = Model();
	Casilla28.LoadModel("Models/casilla28.obj");
	Casilla29 = Model();
	Casilla29.LoadModel("Models/casilla29.obj");
	Casilla30 = Model();
	Casilla30.LoadModel("Models/casilla30.obj");
	Casilla31 = Model();
	Casilla31.LoadModel("Models/casilla31.obj");
	Casilla32 = Model();
	Casilla32.LoadModel("Models/casilla32.obj");
	Casilla33 = Model();
	Casilla33.LoadModel("Models/casilla33.obj");
	Casilla34 = Model();
	Casilla34.LoadModel("Models/casilla34.obj");
	Casilla35 = Model();
	Casilla35.LoadModel("Models/casilla35.obj");
	Casilla36 = Model();
	Casilla36.LoadModel("Models/casilla36.obj");
	Casilla37 = Model();
	Casilla37.LoadModel("Models/casilla37.obj");
	Casilla38 = Model();
	Casilla38.LoadModel("Models/casilla38.obj");
	Casilla39 = Model();
	Casilla39.LoadModel("Models/casilla39.obj");
	Casilla40 = Model();
	Casilla40.LoadModel("Models/casilla40.obj");


	// Modelos de las casillas
	ModeloCasilla28 = Model();
	ModeloCasilla28.LoadModel("Models/brianCasilla28.obj");
	ModeloCasilla29 = Model();
	ModeloCasilla29.LoadModel("Models/ernieCasilla29.obj");
	ModeloCasilla30 = Model();
	ModeloCasilla30.LoadModel("Models/loisCasilla30.obj");
	ModeloCasilla31 = Model();
	ModeloCasilla31.LoadModel("Models/megCasilla31.obj");
	ModeloCasilla32 = Model();
	ModeloCasilla32.LoadModel("Models/peterCasilla32.obj");
	ModeloCasilla33 = Model();
	ModeloCasilla33.LoadModel("Models/joeCasilla33.obj");
	ModeloCasilla34 = Model();
	ModeloCasilla34.LoadModel("Models/chrisCasilla34.obj");
	ModeloCasilla35 = Model();
	ModeloCasilla35.LoadModel("Models/drunkenCasilla35.obj");
	ModeloCasilla36 = Model();
	ModeloCasilla36.LoadModel("Models/treeCasilla36.obj");
	ModeloCasilla37 = Model();
	ModeloCasilla37.LoadModel("Models/ChristmasTreeCasilla37.obj");
	ModeloCasilla38 = Model();
	ModeloCasilla38.LoadModel("Models/vinnyCasilla38.obj");
	ModeloCasilla39 = Model();
	ModeloCasilla39.LoadModel("Models/flowersCasilla39.obj");
	ModeloCasilla40 = Model();
	ModeloCasilla40.LoadModel("Models/carterCasilla40.obj");
	

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.3f,
		0.0f, 0.0f, -1.0f);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	unsigned int spotLightCount = 0;

	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);


	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelauxCasillas(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//CASILLAS
		//Casilla28
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 5.0f, 40.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla28.RenderModel();

		model = modelauxCasillas;
	
		//Casilla29
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla29.RenderModel();

		model = modelauxCasillas; 

		//Casilla30
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla30.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		//Casilla31
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla31.RenderModel();

		model = modelauxCasillas;

		//Casilla32
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla32.RenderModel();

		model = modelauxCasillas;

		//Casilla33
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla33.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		//Casilla34
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla34.RenderModel();

		model = modelauxCasillas;

		//Casilla35
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla35.RenderModel();

		model = modelauxCasillas;

		//Casilla36
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla36.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		//Casilla37
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla37.RenderModel();

		model = modelauxCasillas;

		//Casilla38
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla38.RenderModel();

		model = modelauxCasillas;

		//Casilla39
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla39.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		//Casilla40
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla40.RenderModel();


		//MODELOS DE LAS CASILLAS
		//Brian - Casilla28
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 7.5f, 60.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla28.RenderModel();

		//Ernie - Casilla29
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 9.5f, 60.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla29.RenderModel();

		//Lois - Casilla30
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, 9.5f, 60.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla30.RenderModel();

		//Meg - Casilla31
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 9.0f, 60.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla31.RenderModel();

		//Peter - Casilla32
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 9.0f, 20.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla32.RenderModel();

		//Joe - Casilla33
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 9.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla33.RenderModel();

		//Chris - Casilla34
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f,-1.0f, -20.0));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla34.RenderModel();

		//Drunken - Casilla35
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 4.5f, -40.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla35.RenderModel();

		//Arbol - Casilla36
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 9.5f, -60.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla36.RenderModel();

		//Arbol Navidad - Casilla37
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 7.0f, -80.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla37.RenderModel();

		//Vinny - Casilla38
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 7.5f, -100.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla38.RenderModel();

		//Flores - Casilla39
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 7.0f, -120.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla39.RenderModel();

		//Carter - Casilla40
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 9.6f, -140.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla40.RenderModel();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
