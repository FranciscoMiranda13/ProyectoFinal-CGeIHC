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

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

// PARA ELEGIR LOS GRADOS DE MANERA RANDOM
#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

const float toRadians = 3.14159265f / 180.0f;

// VARIABLES PARA ANIMACION DEL DADO DE 8 CARAS
float subeBajaDado8 = 35.0f;
float subeBajaDadoOffset8 = 0.3f;
float rotaDadox8 = 0.0f;
float rotaDadoxOffset8 = 1.0f;
float rotaDadoy8 = 0.0f;
float rotaDadoyOffset8 = 1.0f;
float rotaDadoz8 = 0.0f;
float rotaDadozOffset8 = 1.0f;

// VARIABLES PARA ANIMACION DEL DADO DE 4 CARAS
float subeBajaDado4 = 35.0f;
float subeBajaDadoOffset4 = 0.3f;
float rotaDadox4 = 0.0f;
float rotaDadoxOffset4 = 1.0f;
float rotaDadoy4 = 0.0f;
float rotaDadoyOffset4 = 1.0f;

// RRESULTADO DEL DADO
int resultado4Caras = 0;
int resultado8Caras = 0;
int resultado = 0;

// VARIABLES PARA ANIAMCION DE RECORRIDO
float mueveAvatar01 = 0.0f;
float mueveAvatar01Offset = 0.3f;
float mueveAvatar01Base = 0.0f;
int resultadoAnterior01 = 0;

float mueveAvatar02 = 0.0f;
float mueveAvatar02Offset = 0.3f;
float mueveAvatar02Base = 0.0f;
int resultadoAnterior02 = 0;

float mueveAvatar03 = 0.0f;
float mueveAvatar03Offset = 0.3f;
float mueveAvatar03Base = 0.0f;
int resultadoAnterior03 = 0;

float mueveAvatar04 = 0.0f;
float mueveAvatar04Offset = 0.3f;
float mueveAvatar04Base = 0.0f;
int resultadoAnterior04 = 0;

float diferencia = 0.0f;
bool hayDiferencia = true;
int conta = 0;

float diferencia01 = 0.0f;
bool hayDiferencia01 = true;
int conta01 = 0;

float diferencia02 = 0.0f;
bool hayDiferencia02 = true;
int conta02 = 0;

// VARIABLES PARA LA ANIMACION DE LA VUELTA 
float rotaAvatar01 = 0.0f;
float rotaAvatar01Offset = 1.0;
float rotaAvatar02 = 0.0f;
float rotaAvatar02Offset = 1.0;
float rotaAvatar03 = 0.0f;
float rotaAvatar03Offset = 1.0;
float rotaAvatar04 = 0.0f;
float rotaAvatar04Offset = 1.0;

// VARIABLES PARA ANIMACIÓN DE LOS BRAZOS Y PIERNAS
float rotaBrazoD = 0.0f;
float rotaBrazoDOffset = 0.8f;
float rotaBrazoI = 0.0f;
float rotaBrazoIOffset = 0.8f;
float rotaPiernaD = 0.0f;
float rotaPiernaDOffset = 0.8;
float rotaPiernaI = 0.0f;
float rotaPiernaIOffset = 0.8;
bool subebaja = true;

// ANIMACIONES DE CASILLAS
// CASILLA 02
float raidenSubeBaja = -8.0f;
float raidenSubeBajaOffset = 0.1f;
float raidenRota = 0.0f;
float raidenRotaOffset = 2.0;
int raidenCont01 = 0;
int raidenCont02 = 0;
bool raiden = true;
float raidenTiempo = 0.0f;
// CASILLA 03
float scorpionSubeBaja = -8.0f;
float scorpionSubeBajaOffset = 0.1f;
float scorpionRota = 0.0f;
float scorpionRotaOffset = 2.0;
int scorpionCont01 = 0;
int scorpionCont02 = 0;
bool scorpion = true;
float scorpionTiempo = 0.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

// SUELO (PASTO)
Texture pasto;

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
Model casilla28M;
Model casilla29M;
Model casilla30M;
Model casilla31M;
Model casilla32M;
Model casilla33M;
Model casilla34M;
Model casilla35M;
Model casilla36M;
Model casilla37M;
Model casilla38M;
Model casilla39M;
Model casilla40M;

//CASILLA AMARILLA
Model casilla01A;
Model casilla02A;
Model casilla03A;
Model casilla04A;
Model casilla05A;
Model casilla06A;
Model casilla07A;
Model casilla08A;
Model casilla09A;
Model casilla10A;
Model casilla11A;
Model casilla12A;
Model casilla13A;
Model casilla14A;
Model casilla15A;
Model casilla16A;
Model casilla17A;
Model casilla18A;
Model casilla19A;
Model casilla20A;
Model casilla21A;
Model casilla22A;
Model casilla23A;
Model casilla24A;
Model casilla25A;
Model casilla26A;
Model casilla27A;
Model casilla28A;
Model casilla29A;
Model casilla30A;
Model casilla31A;
Model casilla32A;
Model casilla33A;
Model casilla34A;
Model casilla35A;
Model casilla36A;
Model casilla37A;
Model casilla38A;
Model casilla39A;
Model casilla40A;

//CASILLAS "ILUMINADA"
Model casilla01AR;
Model casilla01R;

// MODELOS DE LAS CASILLAS
Model modeloCasilla01M;
Model modeloCasilla02M;
Model modeloCasilla03M;
Model modeloCasilla04M;
Model modeloCasilla05M;
Model modeloCasilla06M;
Model modeloCasilla07M;
Model modeloCasilla08M;
Model modeloCasilla09M;
Model modeloCasilla11M;
Model modeloCasilla12M;
Model modeloCasilla13M;
Model modeloCasilla14M;
Model modeloCasilla15M;
Model modeloCasilla16M;
Model modeloCasilla17M;
Model modeloCasilla18M;
Model modeloCasilla19M;
Model modeloCasilla20M;
Model modeloCasilla21M;
Model modeloCasilla22M;
Model modeloCasilla23M;
Model modeloCasilla24M;
Model modeloCasilla25M;
Model modeloCasilla26M;
Model modeloCasilla27M;
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

// MODELO DEL AVATAR PARA EL RECORRIDO (SUBZERO)
Model torsoSubZero;
Model cinturaSubZero;
Model brazoDerechoSubZero;
Model brazoIzquieroSubZero;
Model piernaDerechaSubZero;
Model piernaIzquierdaSubZero;

// MODELOS AUXILIARES
Model esfera;

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

	// PISO (PASTO)
	unsigned int pisoPastoIndices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLfloat pisoPastoVertices[] = {
		// LA TEXTURA SE VERA REPETIDA 10 VECES
		-10.0f, 0.0f, 10.0f,	0.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, -10.0f,	0.0f, 20.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	20.0f, 20.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		20.0f, 0.0f,		0.0f, -1.0f, 0.0f,

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

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	// PISO (PASTO)
	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(pisoPastoVertices, pisoPastoIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
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

	// PISO (PASTO)
	pasto = Texture("Textures/pasto.png");
	pasto.LoadTextureA();

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
	casilla28M = Model();
	casilla28M.LoadModel("Models/casilla28.obj");
	casilla29M = Model();
	casilla29M.LoadModel("Models/casilla29.obj");
	casilla30M = Model();
	casilla30M.LoadModel("Models/casilla30.obj");
	casilla31M = Model();
	casilla31M.LoadModel("Models/casilla31.obj");
	casilla32M = Model();
	casilla32M.LoadModel("Models/casilla32.obj");
	casilla33M = Model();
	casilla33M.LoadModel("Models/casilla33.obj");
	casilla34M = Model();
	casilla34M.LoadModel("Models/casilla34.obj");
	casilla35M = Model();
	casilla35M.LoadModel("Models/casilla35.obj");
	casilla36M = Model();
	casilla36M.LoadModel("Models/casilla36.obj");
	casilla37M = Model();
	casilla37M.LoadModel("Models/casilla37.obj");
	casilla38M = Model();
	casilla38M.LoadModel("Models/casilla38.obj");
	casilla39M = Model();
	casilla39M.LoadModel("Models/casilla39.obj");
	casilla40M = Model();
	casilla40M.LoadModel("Models/casilla40.obj");

	//CASILLAS COLOR AMARILLO
	casilla01A = Model();
	casilla01A.LoadModel("Models/casilla01A.obj");
	casilla02A = Model();
	casilla02A.LoadModel("Models/casilla02A.obj");
	casilla03A = Model();
	casilla03A.LoadModel("Models/casilla03A.obj");
	casilla04A = Model();
	casilla04A.LoadModel("Models/casilla04A.obj");
	casilla05A = Model();
	casilla05A.LoadModel("Models/casilla05A.obj");
	casilla06A = Model();
	casilla06A.LoadModel("Models/casilla06A.obj");
	casilla07A = Model();
	casilla07A.LoadModel("Models/casilla07A.obj");
	casilla08A = Model();
	casilla08A.LoadModel("Models/casilla08A.obj");
	casilla09A = Model();
	casilla09A.LoadModel("Models/casilla09A.obj");
	casilla10A = Model();
	casilla10A.LoadModel("Models/casilla10A.obj");
	casilla11A = Model();
	casilla11A.LoadModel("Models/casilla11A.obj");
	casilla12A = Model();
	casilla12A.LoadModel("Models/casilla12A.obj");
	casilla13A = Model();
	casilla13A.LoadModel("Models/casilla13A.obj");
	casilla14A = Model();
	casilla14A.LoadModel("Models/casilla14A.obj");
	casilla15A = Model();
	casilla15A.LoadModel("Models/casilla15A.obj");
	casilla16A = Model();
	casilla16A.LoadModel("Models/casilla16A.obj");
	casilla17A = Model();
	casilla17A.LoadModel("Models/casilla17A.obj");
	casilla18A = Model();
	casilla18A.LoadModel("Models/casilla18A.obj");
	casilla19A = Model();
	casilla19A.LoadModel("Models/casilla19A.obj");
	casilla20A = Model();
	casilla20A.LoadModel("Models/casilla20A.obj");
	casilla21A = Model();
	casilla21A.LoadModel("Models/casilla21A.obj");
	casilla22A = Model();
	casilla22A.LoadModel("Models/casilla22A.obj");
	casilla23A = Model();
	casilla23A.LoadModel("Models/casilla23A.obj");
	casilla24A = Model();
	casilla24A.LoadModel("Models/casilla24A.obj");
	casilla25A = Model();
	casilla25A.LoadModel("Models/casilla25A.obj");
	casilla26A = Model();
	casilla26A.LoadModel("Models/casilla26A.obj");
	casilla27A = Model();
	casilla27A.LoadModel("Models/casilla27A.obj");
	casilla28A = Model();
	casilla28A.LoadModel("Models/casilla28A.obj");
	casilla29A = Model();
	casilla29A.LoadModel("Models/casilla29A.obj");
	casilla30A = Model();
	casilla30A.LoadModel("Models/casilla30A.obj");
	casilla31A = Model();
	casilla31A.LoadModel("Models/casilla31A.obj");
	casilla32A = Model();
	casilla32A.LoadModel("Models/casilla32A.obj");
	casilla33A = Model();
	casilla33A.LoadModel("Models/casilla33A.obj");
	casilla34A = Model();
	casilla34A.LoadModel("Models/casilla34A.obj");
	casilla35A = Model();
	casilla35A.LoadModel("Models/casilla35A.obj");
	casilla36A = Model();
	casilla36A.LoadModel("Models/casilla36A.obj");
	casilla37A = Model();
	casilla37A.LoadModel("Models/casilla37A.obj");
	casilla38A = Model();
	casilla38A.LoadModel("Models/casilla38A.obj");
	casilla39A = Model();
	casilla39A.LoadModel("Models/casilla39A.obj");
	casilla40A = Model();
	casilla40A.LoadModel("Models/casilla40A.obj");

	//CASILLAS COLOR "ILUMINADAS"
	//casilla01AR = Model();
	//casilla01AR.LoadModel("Models/casilla01AR.obj");
	//casilla01R = Model();
	//casilla01R.LoadModel("Models/casilla01R.obj");
	/*casilla02A = Model();
	casilla02A.LoadModel("Models/casilla02A.obj");
	casilla03A = Model();
	casilla03A.LoadModel("Models/casilla03A.obj");
	casilla04A = Model();
	casilla04A.LoadModel("Models/casilla04A.obj");
	casilla05A = Model();
	casilla05A.LoadModel("Models/casilla05A.obj");
	casilla06A = Model();
	casilla06A.LoadModel("Models/casilla06A.obj");
	casilla07A = Model();
	casilla07A.LoadModel("Models/casilla07A.obj");
	casilla08A = Model();
	casilla08A.LoadModel("Models/casilla08A.obj");
	casilla09A = Model();
	casilla09A.LoadModel("Models/casilla09A.obj");
	casilla10A = Model();
	casilla10A.LoadModel("Models/casilla10A.obj");
	casilla11A = Model();
	casilla11A.LoadModel("Models/casilla11A.obj");
	casilla12A = Model();
	casilla12A.LoadModel("Models/casilla12A.obj");
	casilla13A = Model();
	casilla13A.LoadModel("Models/casilla13A.obj");
	casilla14A = Model();
	casilla14A.LoadModel("Models/casilla14A.obj");
	casilla15A = Model();
	casilla15A.LoadModel("Models/casilla15A.obj");
	casilla16A = Model();
	casilla16A.LoadModel("Models/casilla16A.obj");
	casilla17A = Model();
	casilla17A.LoadModel("Models/casilla17A.obj");
	casilla18A = Model();
	casilla18A.LoadModel("Models/casilla18A.obj");
	casilla19A = Model();
	casilla19A.LoadModel("Models/casilla19A.obj");
	casilla20A = Model();
	casilla20A.LoadModel("Models/casilla20A.obj");
	casilla21A = Model();
	casilla21A.LoadModel("Models/casilla21A.obj");
	casilla22A = Model();
	casilla22A.LoadModel("Models/casilla22A.obj");
	casilla23A = Model();
	casilla23A.LoadModel("Models/casilla23A.obj");
	casilla24A = Model();
	casilla24A.LoadModel("Models/casilla24A.obj");
	casilla25A = Model();
	casilla25A.LoadModel("Models/casilla25A.obj");
	casilla26A = Model();
	casilla26A.LoadModel("Models/casilla26A.obj");
	casilla27A = Model();
	casilla27A.LoadModel("Models/casilla27A.obj");
	casilla28A = Model();
	casilla28A.LoadModel("Models/casilla28A.obj");
	casilla29A = Model();
	casilla29A.LoadModel("Models/casilla29A.obj");
	casilla30A = Model();
	casilla30A.LoadModel("Models/casilla30A.obj");
	casilla31A = Model();
	casilla31A.LoadModel("Models/casilla31A.obj");
	casilla32A = Model();
	casilla32A.LoadModel("Models/casilla32A.obj");
	casilla33A = Model();
	casilla33A.LoadModel("Models/casilla33A.obj");
	casilla34A = Model();
	casilla34A.LoadModel("Models/casilla34A.obj");
	casilla35A = Model();
	casilla35A.LoadModel("Models/casilla35A.obj");
	casilla36A = Model();
	casilla36A.LoadModel("Models/casilla36A.obj");
	casilla37A = Model();
	casilla37A.LoadModel("Models/casilla37A.obj");
	casilla38A = Model();
	casilla38A.LoadModel("Models/casilla38A.obj");
	casilla39A = Model();
	casilla39A.LoadModel("Models/casilla39A.obj");
	casilla40A = Model();
	casilla40A.LoadModel("Models/casilla40A.obj");*/

	// MODELOS DE LAS CASILLAS
	modeloCasilla01M = Model();
	modeloCasilla01M.LoadModel("Models/raidenCasilla01.obj");
	modeloCasilla02M = Model();
	modeloCasilla02M.LoadModel("Models/scorpionCasilla02.obj");
	modeloCasilla03M = Model();
	modeloCasilla03M.LoadModel("Models/shaoKahnCasilla03.obj");
	modeloCasilla04M = Model();
	modeloCasilla04M.LoadModel("Models/hellMountainsCasilla04.obj");
	modeloCasilla05M = Model();
	modeloCasilla05M.LoadModel("Models/viewerCasilla05.obj");
	modeloCasilla06M = Model();
	modeloCasilla06M.LoadModel("Models/treeStumpCasilla06.obj");
	modeloCasilla07M = Model();
	modeloCasilla07M.LoadModel("Models/pineTreeCasilla07.obj");
	modeloCasilla08M = Model();
	modeloCasilla08M.LoadModel("Models/fireDragonCasilla08.obj");
	modeloCasilla09M = Model();
	modeloCasilla09M.LoadModel("Models/scorpionCasilla09.obj");
	modeloCasilla11M = Model();
	modeloCasilla11M.LoadModel("Models/wolfCasilla11.obj");
	modeloCasilla12M = Model();
	modeloCasilla12M.LoadModel("Models/barakaCasilla12.obj");
	modeloCasilla13M = Model();
	modeloCasilla13M.LoadModel("Models/boCasilla13.obj");
	modeloCasilla14M = Model();
	modeloCasilla14M.LoadModel("Models/cassieCasilla14.obj");
	modeloCasilla15M = Model();
	modeloCasilla15M.LoadModel("Models/skullCasilla15.obj");
	modeloCasilla16M = Model();
	modeloCasilla16M.LoadModel("Models/rockyCasilla16.obj");
	modeloCasilla17M = Model();
	modeloCasilla17M.LoadModel("Models/neo_CortexCasilla17.obj");
	modeloCasilla18M = Model();
	modeloCasilla18M.LoadModel("Models/frogCasilla18.obj");
	modeloCasilla19M = Model();
	modeloCasilla19M.LoadModel("Models/polarCasilla19.obj");
	modeloCasilla20M = Model();
	modeloCasilla20M.LoadModel("Models/wizardCasilla20.obj");
	modeloCasilla21M = Model();
	modeloCasilla21M.LoadModel("Models/pinstripeCasilla21.obj");
	modeloCasilla22M = Model();
	modeloCasilla22M.LoadModel("Models/lionCasilla22.obj");
	modeloCasilla23M = Model();
	modeloCasilla23M.LoadModel("Models/babytCasilla23.obj");
	modeloCasilla24M = Model();
	modeloCasilla24M.LoadModel("Models/aku_akuCasilla24.obj");
	modeloCasilla25M = Model();
	modeloCasilla25M.LoadModel("Models/palm_treeCasilla25.obj");
	modeloCasilla26M = Model();
	modeloCasilla26M.LoadModel("Models/flowerCasilla26.obj");
	modeloCasilla27M = Model();
	modeloCasilla27M.LoadModel("Models/basic_treeCasilla27.obj");
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

	// MODELO DEL AVATAR PARA EL RECORRIDO (SUBZERO)
	torsoSubZero = Model();
	torsoSubZero.LoadModel("Models/avatarSubZeroCuerpo.obj");
	cinturaSubZero = Model();
	cinturaSubZero.LoadModel("Models/avatarSubZeroCintura.obj");
	brazoDerechoSubZero = Model();
	brazoDerechoSubZero.LoadModel("Models/avatarSubZeroBrazoDerecho.obj");
	brazoIzquieroSubZero = Model();
	brazoIzquieroSubZero.LoadModel("Models/avatarSubZeroBrazoIzquierdo.obj");
	piernaDerechaSubZero = Model();
	piernaDerechaSubZero.LoadModel("Models/avatarSubZeroPiernaDerecha.obj");
	piernaIzquierdaSubZero = Model();
	piernaIzquierdaSubZero.LoadModel("Models/avatarSubZeroPiernaIzquierda.obj");

	// MODELO AUXILIAR
	esfera = Model();
	esfera.LoadModel("Models/esfera.obj");

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
		0.9f, 0.3f, // ESTABA 0.3 Y 0.3
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
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

	// PARA CONTROLAR EL TIEMPO, AUN NO LO ESTOY OCUPANDO
	glfwSetTime(0);

	// GRADOS ALEATORIOS 
	// Inicializar la semilla solo una vez
	std::srand(static_cast<unsigned>(std::time(0)));

	// PARA GRADOS DE X DADO 8 CARAS
	std::vector<int> listaX = { 180, -180 };
	int gradosDeX = listaX[std::rand() % listaX.size()];

	// PARA GRADOS DE Y DADO 8 CARAS
	std::vector<int> listaY = { 45, 135, 225, 315, -45, -135, -225, -315 };
	int gradosDeY = listaY[std::rand() % listaY.size()];

	// PARA GRADOS DE Z DADO 8 CARAS
	std::vector<int> listaZ = { 25,-25 };
	int gradosDeZ = listaZ[std::rand() % listaZ.size()];

	// PARA GRADOS DE X_1 DADO DE 4 CARAS
	std::vector<int> listaX_1 = { 0, 115, 115 , 115 };
	int gradosDeX_1 = listaX_1[std::rand() % listaX_1.size()];

	// PARA GRADOS DE X_2 DADO DE 4 CARAS
	std::vector<int> listaX_2 = { 0, -115, -115 , -115 };
	int gradosDeX_2 = listaX_2[std::rand() % listaX_2.size()];

	// PARA GRADOS DE Y_1 DADO DE 4 CARAS
	std::vector<int> listaY_1 = { 60, 120, 180, 240, 300, 360, -60, -120, -180, -240, -300, -360 };
	int gradosDeY_1 = listaY_1[std::rand() % listaY_1.size()];

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		// PARA BAJAR
		// TECLA Y
		if (mainWindow.getsubeBajaDado() == true)
		{
			// HACER QUE EL DADO BAJE
			if (subeBajaDado8 > 7.0f)
			{
				subeBajaDado8 -= subeBajaDadoOffset8 * deltaTime;
			}
			// CUANDO LLEGUE AL FINAL
			else
			{
				// ROTAR EN X
				switch (gradosDeX)
				{
				case 180:
					if (rotaDadox8 < 180)
					{
						rotaDadox8 += rotaDadoxOffset8 * deltaTime;
					}
					else
					{
						// ROTAR EN Y
						switch (gradosDeY)
						{
						case 45:
							if (rotaDadoy8 < 45)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3; 
									break;
								}
							}
							break;
						case -45:
							if (rotaDadoy8 > -45)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2; 
									break;
								}
							}
							break;
						case 135:
							if (rotaDadoy8 < 135)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4; 
									break;
								}
							}
							break;
						case -135:
							if (rotaDadoy8 > -135)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1; 
									break;
								}
							}
							break;
						case 225:
							if (rotaDadoy8 < 225)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1; 
									break;
								}
							}
							break;
						case -225:
							if (rotaDadoy8 > -225)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4; 
									break;
								}
							}
							break;
						case 315:
							if (rotaDadoy8 < 315)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2; 
									break;
								}
							}
							break;
						case -315:
							if (rotaDadoy8 > -315)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3; 
									break;
								}
							}
							break;
						}
					}
					break;
				case -180:
					if (rotaDadox8 > -180)
					{
						rotaDadox8 -= rotaDadoxOffset8 * deltaTime;
					}
					else
					{
						// ROTAR EN Y
						switch (gradosDeY)
						{
						case 45:
							if (rotaDadoy8 < 45)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3; 
									break;
								}
							}
							break;
						case -45:
							if (rotaDadoy8 > -45)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2;
									break;
								}
							}
							break;
						case 135:
							if (rotaDadoy8 < 135)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4; 
									break;
								}
							}
							break;
						case -135:
							if (rotaDadoy8 > -135)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1; 
									break;
								}
							}
							break;
						case 225:
							if (rotaDadoy8 < 225)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1; 
									break;
								}
							}
							break;
						case -225:
							if (rotaDadoy8 > -225)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4; 
									break;
								}
							}
							break;
						case 315:
							if (rotaDadoy8 < 315)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2; 
									break;
								}
							}
							break;
						case -315:
							if (rotaDadoy8 > -315)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6; 
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3; 
									break;
								}
							}
							break;
						}
					}
					break;
				}
			} // AQUI TERMINA EL ELSE DEL DADO 8
		}
		
		// PARA BAJAR
		// TECLA Y
		if (mainWindow.getsubeBajaDado() == true)
		{
			// HACER QUE EL DADO BAJE
			if (subeBajaDado4 > 3.1f)
			{
				subeBajaDado4 -= subeBajaDadoOffset4 * deltaTime;
			}
			// CUANDO LLEGUE AL FINAL
			else
			{
				// ROTAR EN Y
				switch (gradosDeY_1)
				{
				case 60:
					if (rotaDadoy4 < 60)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case -60:
					if (rotaDadoy4 > -60)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case 120:
					if (rotaDadoy4 < 120)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case -120:
					if (rotaDadoy4 > -120)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case 180:
					if (rotaDadoy4 < 180)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				case -180:
					if (rotaDadoy4 > -180)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				case 240:
					if (rotaDadoy4 < 240)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case -240:
					if (rotaDadoy4 > -240)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case 300:
					if (rotaDadoy4 < 300)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case -300:
					if (rotaDadoy4 > -300)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case 360:
					if (rotaDadoy4 < 360)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				case -360:
					if (rotaDadoy4 > -360)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				}
			}
		}

		// RESULTADO DE LOS DADOS
		if (resultado8Caras != 0 && resultado4Caras != 0)
		{
			resultado = resultado4Caras + resultado8Caras;
			//printf("RESULTADO = %i", resultado);
		}

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior01) {
			mueveAvatar01Base = mueveAvatar01; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior01 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" MUEVEAVATAR01BASE = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar01Base, resultadoAnterior01);
		}

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior02) {
			mueveAvatar02Base = mueveAvatar02; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior02 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" EL SEGUNDOOOOOO = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar02Base, resultadoAnterior01);
		}

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior03) {
			mueveAvatar03Base = mueveAvatar03; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior03 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" EL SEGUNDOOOOOO = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar02Base, resultadoAnterior01);
		}

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior04) {
			mueveAvatar04Base = mueveAvatar04; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior04 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" EL SEGUNDOOOOOO = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar02Base, resultadoAnterior01);
		}

		// DIFERENCIA
		// DUDA SI ES BASE O ASI COMO ESTA EL MUEVEAVATAR01
		if (((mueveAvatar01 + (resultado * 20)) > 200))
		{
			diferencia = (mueveAvatar01Base + (resultado * 20)) - 200;
			diferencia = abs(diferencia);

			if (diferencia < 1)
			{
				conta += 1;
			}
		}
		if (conta > 0)
		{
			diferencia = 0.0f;
		}

		// DIFERENCIA
		// DUDA SI ES BASE O ASI COMO ESTA EL MUEVEAVATAR01
		if (((mueveAvatar02 + (resultado * 20)) > 200))
		{
			diferencia01 = (mueveAvatar02Base + (resultado * 20)) - 200;
			diferencia01 = abs(diferencia01);

			if (diferencia01 < 1)
			{
				conta01 += 1;
			}
		}
		if (conta01 > 0)
		{
			diferencia01 = 0.0f;
		}

		// DIFERENCIA
		// DUDA SI ES BASE O ASI COMO ESTA EL MUEVEAVATAR01
		if (((mueveAvatar03 + (resultado * 20)) > 200))
		{
			diferencia02 = (mueveAvatar03Base + (resultado * 20)) - 200;
			diferencia02 = abs(diferencia02);

			if (diferencia02 < 1)
			{
				conta02 += 1;
			}
		}
		if (conta02 > 0)
		{
			diferencia02 = 0.0f;
		}

		// DEBERIA ESTAR OTRA AQUI, PERO MEJOR REINICIO TODO AL FINAL

		// MOVIMIENTO AVATAR
		if (mueveAvatar01 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar01 < mueveAvatar01Base + (resultado * 20))
			{

				mueveAvatar01 += mueveAvatar01Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
		}
		else if (rotaAvatar01 > -90)
		{
			rotaAvatar01 -= rotaAvatar01Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
		}
		else if (diferencia > 0 && hayDiferencia)
		{
			// printf("RESULTADO = %f", diferencia);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar02 < diferencia)
			{

				mueveAvatar02 += mueveAvatar02Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
			else
			{
				hayDiferencia = !hayDiferencia;
			}
		}
		else if (mueveAvatar02 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar02 < mueveAvatar02Base + (resultado * 20))
			{

				mueveAvatar02 += mueveAvatar02Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}

			}
		}
		else if (rotaAvatar02 > -90)
		{
			rotaAvatar02 -= rotaAvatar02Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			}
		else if (diferencia01 > 0 && hayDiferencia01)
		{
			// printf("RESULTADO = %f", diferencia);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar03 < diferencia01)
			{

				mueveAvatar03 += mueveAvatar03Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
			else
			{
				hayDiferencia01 = !hayDiferencia01;
			}
		}
		else if (mueveAvatar03 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar03 < mueveAvatar03Base + (resultado * 20))
			{

				mueveAvatar03 += mueveAvatar03Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}

			}
		}
		else if (rotaAvatar03 > -90)
		{
			rotaAvatar03 -= rotaAvatar03Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			}
		else if (diferencia02 > 0 && hayDiferencia02)
		{
			// printf("RESULTADO = %f", diferencia);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar04 < diferencia02)
			{

				mueveAvatar04 += mueveAvatar04Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
			else
			{
				hayDiferencia02 = !hayDiferencia02;
			}
			}
		else if (mueveAvatar04 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar04 < mueveAvatar04Base + (resultado * 20))
			{

				mueveAvatar04 += mueveAvatar04Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}

			}
		}
		else if (rotaAvatar04 > -90)
		{
			rotaAvatar04 -= rotaAvatar04Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}

		}
		else
		{
			subeBajaDado8 = 35.0f;
			rotaDadox8 = 0.0f;
			rotaDadoy8 = 0.0f;
			rotaDadoz8 = 0.0f;

			subeBajaDado4 = 35.0f;
			rotaDadox4 = 0.0f;
			rotaDadoy4 = 0.0f;

			// RRESULTADO DEL DADO
			resultado4Caras = 0;
			resultado8Caras = 0;
			resultado = 0;

			// VARIABLES PARA ANIAMCION DE RECORRIDO
			mueveAvatar01 = 0.0f;
			mueveAvatar01Base = 0.0f;
			resultadoAnterior01 = 0;

			mueveAvatar02 = 0.0f;
			mueveAvatar02Base = 0.0f;
			resultadoAnterior02 = 0;

			mueveAvatar03 = 0.0f;
			mueveAvatar03Base = 0.0f;
			resultadoAnterior03 = 0;

			mueveAvatar04 = 0.0f;
			mueveAvatar04Base = 0.0f;
			resultadoAnterior04 = 0;

			diferencia = 0.0f;
			hayDiferencia = true;
			conta = 0;

			diferencia01 = 0.0f;
			hayDiferencia01 = true;
			conta01 = 0;

			diferencia02 = 0.0f;
			hayDiferencia02 = true;
			conta02 = 0;

			// VARIABLES PARA LA ANIMACION DE LA VUELTA 
			rotaAvatar01 = 0.0f;
			rotaAvatar02 = 0.0f;
			rotaAvatar03 = 0.0f;
			rotaAvatar04 = 0.0f;

			// VARIABLES PARA ANIMACIÓN DE LOS BRAZOS Y PIERNAS
			rotaBrazoD = 0.0f;
			rotaBrazoI = 0.0f;
			rotaPiernaD = 0.0f;
			rotaPiernaI = 0.0f;
			subebaja = true;
		}

		// ACTIVAR BANDERAS DE ANIMACION ESPECIAL
		if (mueveAvatar01 >= 20)
		{
			raidenCont01 += 1;
		}
		if (mueveAvatar01 >= 40)
		{
			scorpionCont01 += 1;
		}
		
		// PARA SUBIR
		// U
		if (mainWindow.getsubeBajaDado() == false)
		{
			if (subeBajaDado8 < 35.0f)
			{
				subeBajaDado8 += subeBajaDadoOffset8 * deltaTime;
			}
			else
			{
				// REGRESAR A SU ESTADO ORIGINAL Y REASIGNAR LOS VALORES DE LOS GRADOS
				gradosDeX = listaX[std::rand() % listaX.size()];
				rotaDadox8 = 0.0f;
				gradosDeY = listaY[std::rand() % listaY.size()];
				rotaDadoy8 = 0.0f;
				gradosDeZ = listaZ[std::rand() % listaZ.size()];
				rotaDadoz8 = 0.0f;
				resultado8Caras = 0;
			}
		}

		// PARA SUBIR
		// U
		if (mainWindow.getsubeBajaDado() == false)
		{
			if (subeBajaDado4 < 35.0f)
			{
				subeBajaDado4 += subeBajaDadoOffset4 * deltaTime;
			}
			else
			{
				// REGRESAR A SU ESTADO ORIGINAL Y REASIGNAR LOS VALORES DE LOS GRADOS

				gradosDeX_1 = listaX_1[std::rand() % listaX_1.size()];
				gradosDeX_2 = listaX_2[std::rand() % listaX_2.size()];
				rotaDadox4 = 0.0f;
				gradosDeY_1 = listaY_1[std::rand() % listaY_1.size()];
				rotaDadoy4 = 0.0f;
				resultado4Caras = 0;
			}
		}

		// INTERACCIINES ESPECIALES DE CASILLAS
		// RAIDEN
		if (raidenCont01 >= 1 && raidenCont02 < 1)
		{
			printf("ENTRO\n");
			if (raiden)
			{
				if (raidenSubeBaja < 9.9f)
				{
					raidenSubeBaja += raidenSubeBajaOffset * deltaTime;
					raidenRota += raidenRotaOffset * deltaTime;
					raidenTiempo = glfwGetTime();

				}
				else
				{
					if ((glfwGetTime()-raidenTiempo) > 3)
					{
						raiden = !raiden;
					}
				}
			}
			else
			{
				if (raidenSubeBaja > -8.0f)
				{
					raidenSubeBaja -= raidenSubeBajaOffset * deltaTime;
					raidenRota -= raidenRotaOffset * deltaTime;
				}
				else
				{
					printf("YA NO VUELVE A ENTRAR");
					raidenCont02 += 1;
				}
			}
		}
		

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
		glm::mat4 modelaux(1.0);

		// MATRIZ AUXILIAR PARA LAS CASILLAS
		glm::mat4 modelauxCasillas(1.0);

		// MATRIZ AUXILIAR PARA EL AVATAR DE RECORRIDO (SUBZERO)
		glm::mat4 modelauxTorso(1.0);
		glm::mat4 modelauxBrazoDerecho(1.0);
		glm::mat4 modelauxBrazoIzquierdo(1.0);
		glm::mat4 modelauxCintura(1.0);
		glm::mat4 modelauxPiernaDerecha(1.0);
		glm::mat4 modelauxPiernaIzquierda(1.0);

		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		// PISO (PASTO)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pasto.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		// DADO DE 4 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, subeBajaDado4, 20.0));
		// ANIMACION DEL DADO
		model = glm::rotate(model, rotaDadox4 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotaDadoy4 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dado4CarasM.RenderModel();

		// DADO DE 8 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, subeBajaDado8, -20.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		// ANIMACION DEL DADO
		model = glm::rotate(model, rotaDadox8 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotaDadoz8 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, rotaDadoy8 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		//casilla01M.RenderModel();
		casilla01A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 2
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla02M.RenderModel();
		casilla02A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 3
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla03M.RenderModel();
		casilla03A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 4
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla04M.RenderModel();
		casilla04A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 5
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla05M.RenderModel();
		casilla05A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 6
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla06M.RenderModel();
		casilla06A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 7
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla07M.RenderModel();
		casilla07A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 8
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla08M.RenderModel();
		casilla08A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 9
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla09M.RenderModel();
		casilla09A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 10
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla10M.RenderModel();
		casilla10A.RenderModel();
		model = modelauxCasillas; // A PARTIR DE 

		// 11
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla11M.RenderModel();
		casilla11A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 12
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla12M.RenderModel();
		casilla12A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 13
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla13M.RenderModel();
		casilla13A.RenderModel();


		model = modelauxCasillas; // A PARTIR DE 

		// 14
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla14M.RenderModel();
		casilla14A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 15
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));
		/*model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla15M.RenderModel();
		casilla15A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 16
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla16M.RenderModel();
		casilla16A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 17
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla17M.RenderModel();
		casilla17A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 18
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla18M.RenderModel();
		casilla18A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 19
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla19M.RenderModel();
		casilla19A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 20
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla20M.RenderModel();
		casilla20A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 21
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla21M.RenderModel();
		casilla21A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 22
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla22M.RenderModel();
		casilla22A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 23
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla23M.RenderModel();
		casilla23A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 24
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla24M.RenderModel();
		casilla24A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 25
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla25M.RenderModel();
		casilla25A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 26
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla26M.RenderModel();
		casilla26A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 27
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla27M.RenderModel();
		casilla27A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 28
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));
		/*model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla28M.RenderModel();
		casilla28A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 29
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla29M.RenderModel();
		casilla29A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 30
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla30M.RenderModel();
		casilla30A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 31
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla31M.RenderModel();
		casilla31A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 32
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla32M.RenderModel();
		casilla32A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 33
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla33M.RenderModel();
		casilla33A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 34
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla34M.RenderModel();
		casilla34A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 35
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla35M.RenderModel();
		casilla35A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 36
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla36M.RenderModel();
		casilla36A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 37
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla37M.RenderModel();
		casilla37A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 38
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla38M.RenderModel();
		casilla38A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 39
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla39M.RenderModel();
		casilla39A.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 40
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casilla40M.RenderModel();
		casilla40A.RenderModel();

		// MODELOS DE LAS CASILLAS

		// RAIDEN - CASILLA 02
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*9.9f*/raidenSubeBaja, 80.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -raidenRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla01M.RenderModel();

		// SCORPION - CASILLA 03
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 10.1f, 60.0));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla02M.RenderModel();

		// SHAO KAHN - CASILLA 04
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 9.9f, 40.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla03M.RenderModel();

		// HELL MOUNTAIN - CASILLA 05
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 4.4f, 20.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla04M.RenderModel();

		// VIEWER - CASILLA 06
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 5.5f, 0.0));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla05M.RenderModel();

		// TREE STUMP - CASILLA 07
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 8.55f, -20.0));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla06M.RenderModel();

		// PINE TREE - CASILLA 08
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 9.7f, -40.0));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla07M.RenderModel();

		// FIRE DRAGON - CASILLA 09
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 6.0f, -55.0));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla08M.RenderModel();

		// SCORPION - CASILLA 10
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, 5.9f, -80.0));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla09M.RenderModel();

		// WOLF - CASILLA 11
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-100.0f, 5.9f, -120.0));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla11M.RenderModel();

		// BARAKA - CASILLA 12
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-80.0f, 10.0f, -120.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.5f, 8.5f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla12M.RenderModel();

		// BO RAI CHO - CASILLA 13
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-60.0f, 8.5f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla13M.RenderModel();

		// CASSIE CAGE - CASILLA 14
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-40.0f, 10.0f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.5f, 8.5f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla14M.RenderModel();

		// SKULL - CASILLA 15
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-20.0f, 2.0f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.325f, 0.325f, 0.325f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla15M.RenderModel();

		// ROCKY ROAD - CASILLA 16
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, 2.0f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.325f, 0.325f, 0.325f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla16M.RenderModel();

		// NEOCORTEX - CASILLA 17
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(20.0f, 4.0f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla17M.RenderModel();

		// FROG - CASILLA 18
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(40.0f, 2.0f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla18M.RenderModel();

		// POLAR - CASILLA 19
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(60.0f, 5.0f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla19M.RenderModel();

		// WIZARD - CASILLA 20
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(80.0f, 6.8f, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.18f, 0.18f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla20M.RenderModel();

		// PINSTRIPE - CASILLA 21
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, 9.5f, -100.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla21M.RenderModel();

		// LION - CASILLA 22
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, 6.0f, -80.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla22M.RenderModel();

		// BABY T - CASILLA 23
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, 5.2f, -60.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla23M.RenderModel();

		// AKU AKU - CASILLA 24
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, 4.0f, -40.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla24M.RenderModel();

		// PALM_TREE - CASILLA 25
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, 6.0f, -20.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla25M.RenderModel();

		// FLOWERS - CASILLA 26
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, 4.2f, 0.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla26M.RenderModel();

		// BASIC_TREE - CASILLA 27
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, 5.2f, 20.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla27M.RenderModel();

		//Brian - Casilla28
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 7.5f, 40.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla28.RenderModel();

		//Ernie - Casilla29
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(124.0f, 9.5f, 60.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla29.RenderModel();

		//Lois - Casilla30
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 9.5f, 80.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla30.RenderModel();

		//Meg - Casilla31
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 9.0f, 120.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla31.RenderModel();

		//Peter - Casilla32
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 9.0f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla32.RenderModel();

		//Joe - Casilla33
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, 9.0f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla33.RenderModel();

		//Chris - Casilla34
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -1.0f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla34.RenderModel();

		//Drunken - Casilla35
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 4.5f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla35.RenderModel();

		//Arbol - Casilla36
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 9.5f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla36.RenderModel();

		//Arbol Navidad - Casilla37
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 7.0f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla37.RenderModel();

		//Vinny - Casilla38
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 7.5f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla38.RenderModel();

		//Flores - Casilla39
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, 7.0f, 140.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla39.RenderModel();

		//Carter - Casilla40
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 9.6f, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla40.RenderModel();

		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 20.0f, 100.0));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casillaM.RenderModel();*/

		// AVATAR SUB ZERO PARA RECORRIDO
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-100.0f, 19.8f, 100.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar01));
		model = glm::rotate(model, rotaAvatar01 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar02));
		model = glm::rotate(model, rotaAvatar02 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar03));
		model = glm::rotate(model, rotaAvatar03 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar04));
		model = glm::rotate(model, rotaAvatar04 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));


		modelauxTorso = model; // GUARDA TORSO

		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		torsoSubZero.RenderModel();

		model = modelauxTorso; // A PARTIR DE TORSO

		model = glm::translate(model, glm::vec3(-3.5f, 2.0f, -0.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		modelauxBrazoDerecho = model; // GUARDA BRAZO DERECHO

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxBrazoDerecho; // A PARTIR DE BRAZO DERECHO

		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.1f));
		model = glm::rotate(model, -rotaBrazoD * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoDerechoSubZero.RenderModel();

		model = modelauxTorso; // A PARTIR DE TORSO

		model = glm::translate(model, glm::vec3(3.5f, 2.0f, -0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		modelauxBrazoIzquierdo = model; // GUARDA BRAZO IZQUIERDO

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxBrazoIzquierdo; // A PARTIR DE BRAZO IZQUIERDO

		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.1f));
		model = glm::rotate(model, rotaBrazoI * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoIzquieroSubZero.RenderModel();

		model = modelauxTorso; // A PARTIR DE TORSO

		model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));

		modelauxCintura = model; // GUARDA CINTURA

		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cinturaSubZero.RenderModel();

		model = modelauxCintura; //  PARTIR DE LA CINTURA

		model = glm::translate(model, glm::vec3(-1.3f, -1.5f, 0.0f));

		modelauxPiernaDerecha = model; // GUARDA PIERNA DERECHA

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxPiernaDerecha; // A PARTIR DE LA PIERNA DERECHA

		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		model = glm::rotate(model, rotaPiernaD * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaDerechaSubZero.RenderModel();

		model = modelauxCintura; //  PARTIR DE LA CINTURA

		model = glm::translate(model, glm::vec3(1.3f, -1.5f, 0.0f));

		modelauxPiernaIzquierda = model; // GUARDA PIERNA IZQUIERDA

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxPiernaIzquierda; // A PARTIR DE LA PIERNA IZQUIERDA

		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		model = glm::rotate(model, rotaPiernaI * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaIzquierdaSubZero.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
