
// PROYECTO DE LABORATORIO

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
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminaci�n
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
Texture AgaveTexture;

// TEXTURAS EXTRAS
Texture colorBlanco;

// DADOS TEXTURAS
Texture dado4CarasT;
Texture dado8CarasT;

// CASILLAS TEXTURAS
Texture casilla01T;
Texture casilla02T;
Texture casilla03T;
Texture casilla04T;
Texture casilla05T;
Texture casilla06T;
Texture casilla07T;
Texture casilla08T;
Texture casilla09T;
Texture casilla10T;
Texture casilla11T;
Texture casilla12T;
Texture casilla13T;
Texture casilla14T;
Texture casilla15T;
Texture casilla16T;
Texture casilla17T;
Texture casilla18T;
Texture casilla19T;
Texture casilla20T;
Texture casilla21T;
Texture casilla22T;
Texture casilla23T;
Texture casilla24T;
Texture casilla25T;
Texture casilla26T;
Texture casilla27T;

// TEXTURAS DE LOS MODELOS DE LAS CASILLAS
Texture modeloCasilla01T01;
Texture modeloCasilla01T02;
Texture modeloCasilla02T01;
Texture modeloCasilla03T01;
Texture modeloCasilla03T02;
Texture modeloCasilla04T01;
Texture modeloCasilla04T02;
Texture modeloCasilla04T03;
Texture modeloCasilla04T04;
Texture modeloCasilla04T05;
Texture modeloCasilla04T06;

// DADOS MODELOS
Model dado4CarasM;
Model dado8CarasM;

// CASILLAS MODELOS
Model casillaM;
Model casilla01M;
Model casilla02M;
Model casilla03M;
Model casilla04M;
Model casilla05M;
Model casilla06M;
Model casilla07M;
Model casilla08M;
Model casilla09M;
Model casilla10M;
Model casilla11M;
Model casilla12M;
Model casilla13M;
Model casilla14M;
Model casilla15M;
Model casilla16M;
Model casilla17M;
Model casilla18M;
Model casilla19M;
Model casilla20M;
Model casilla21M;
Model casilla22M;
Model casilla23M;
Model casilla24M;
Model casilla25M;
Model casilla26M;
Model casilla27M;

// MODELOS DE LAS CASILLAS
Model modeloCasilla01M;
Model modeloCasilla02M;
Model modeloCasilla03M;
Model modeloCasilla04M;
Model modeloCasilla23M;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;


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


//funci�n de calculo de normales por promedio de v�rtices 
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

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


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

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

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
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();


	// DADOS MODELOS
	dado4CarasM = Model();
	dado4CarasM.LoadModel("Models/dado4Caras.obj");
	dado8CarasM = Model();
	dado8CarasM.LoadModel("Models/dado8Caras.obj");

	// CASILLAS MODELOS
	casillaM = Model();
	casillaM.LoadModel("Models/casilla.obj");
	casilla01M = Model();
	casilla01M.LoadModel("Models/casilla01.obj");
	casilla02M = Model();
	casilla02M.LoadModel("Models/casilla02.obj");
	casilla03M = Model();
	casilla03M.LoadModel("Models/casilla03.obj");
	casilla04M = Model();
	casilla04M.LoadModel("Models/casilla04.obj");
	casilla05M = Model();
	casilla05M.LoadModel("Models/casilla05.obj");
	casilla06M = Model();
	casilla06M.LoadModel("Models/casilla06.obj");
	casilla07M = Model();
	casilla07M.LoadModel("Models/casilla07.obj");
	casilla08M = Model();
	casilla08M.LoadModel("Models/casilla08.obj");
	casilla09M = Model();
	casilla09M.LoadModel("Models/casilla09.obj");
	casilla10M = Model();
	casilla10M.LoadModel("Models/casilla10.obj");
	casilla11M = Model();
	casilla11M.LoadModel("Models/casilla11.obj");
	casilla12M = Model();
	casilla12M.LoadModel("Models/casilla12.obj");
	casilla13M = Model();
	casilla13M.LoadModel("Models/casilla13.obj");
	casilla14M = Model();
	casilla14M.LoadModel("Models/casilla14.obj");
	casilla15M = Model();
	casilla15M.LoadModel("Models/casilla15.obj");
	casilla16M = Model();
	casilla16M.LoadModel("Models/casilla16.obj");
	casilla17M = Model();
	casilla17M.LoadModel("Models/casilla17.obj");
	casilla18M = Model();
	casilla18M.LoadModel("Models/casilla18.obj");
	casilla19M = Model();
	casilla19M.LoadModel("Models/casilla19.obj");
	casilla20M = Model();
	casilla20M.LoadModel("Models/casilla20.obj");
	casilla21M = Model();
	casilla21M.LoadModel("Models/casilla21.obj");
	casilla22M = Model();
	casilla22M.LoadModel("Models/casilla22.obj");
	casilla23M = Model();
	casilla23M.LoadModel("Models/casilla23.obj");
	casilla24M = Model();
	casilla24M.LoadModel("Models/casilla24.obj");
	casilla25M = Model();
	casilla25M.LoadModel("Models/casilla25.obj");
	casilla26M = Model();
	casilla26M.LoadModel("Models/casilla26.obj");
	casilla27M = Model();
	casilla27M.LoadModel("Models/casilla27.obj");

	// MODELOS DE LAS CASILLAS
	modeloCasilla01M = Model();
	modeloCasilla01M.LoadModel("Models/raidenCasilla01.obj");
	modeloCasilla02M = Model();
	modeloCasilla02M.LoadModel("Models/scorpionCasilla02.obj");
	modeloCasilla03M = Model();
	modeloCasilla03M.LoadModel("Models/shaoKahnCasilla03.obj");
	modeloCasilla04M = Model();
	modeloCasilla04M.LoadModel("Models/hellMountainsCasilla04.obj");
	modeloCasilla23M = Model();
	modeloCasilla23M.LoadModel("Models/babytCasilla23.obj");

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


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaraci�n de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	
	//se crean mas luces puntuales y spotlight 

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
		
		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		//sirve para que en tiempo de ejecuci�n (dentro del while) se cambien propiedades de la luz
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		
		// MATRIZ AUXILIAR PARA LAS CASILLAS
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


		// DADO DE 4 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 40.0f, 10.0));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dado4CarasM.RenderModel();

		// DADO DE 8 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 40.0f, -10.0));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dado8CarasM.RenderModel();

		// CASILLAS 
		model = glm::mat4(1.0);

		// 1
		model = glm::translate(model, glm::vec3(-100.0f, 0.3f, 100.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla01M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 2
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla02M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 3
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla03M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 4
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla04M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 5
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla05M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 6
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla06M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 7
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla07M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 8
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla08M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 9
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla09M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 10
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla10M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 11
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla11M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 12
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla12M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 13
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla13M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 14
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla14M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 15
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla15M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 16
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla16M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 17
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla17M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 18
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla18M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 19
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla19M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 20
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla20M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 21
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla21M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 22
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla22M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 23
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla23M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 24
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla24M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 25
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla25M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 26
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla26M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 27
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla27M.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 28
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 29
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 30
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 31
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 32
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 33
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 34
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 35
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 36
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 37
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 38
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 39
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 40
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();

		// MODELOS DE LAS CASILLAS

		// RAIDEN - CASILLA 01
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 11.1f, 80.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla01M.RenderModel();

		// SCORPION - CASILLA 02
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 11.3f, 60.0));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla02M.RenderModel();

		// SHAO KAHN - CASILLA 03
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 11.1f, 40.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla03M.RenderModel();

		// HELL MOUNTAIN - CASILLA 04
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 4.4f, 20.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla04M.RenderModel();

		// HELL MOUNTAIN - CASILLA 04
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 4.4f, 20.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla04M.RenderModel();



		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
