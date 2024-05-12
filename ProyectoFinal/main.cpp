#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "modelAnim.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();


// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 10.0f, 30.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float movCamera = 0.0f;
float tiempo;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

bool active;

//VARIABLES DE ANIMACION

//SILLA
//Rotacion negativa 
bool animS1 = false;
//Rotacion positiva 
bool animS2 = false;
//Variable para los grados
float rotS = 0.0f;
//Variable para guardar que se ha alcanzado cierta posicion
bool animS3 = false;

//AVION
//Rotacion negativa 
bool anim = false;
//Rotacion positiva 
bool animm = false;
//Variable para los grados
float rot = 0.0f;
//Variable para guardar que se ha alcanzado cierta posicion
bool animmm = false;

//CAJON
//Rotacion negativa 
bool animC1 = false;
//Rotacion positiva 
bool animC2 = false;
//Variable para los grados
float transC = 15.214f;
//Variable para guardar que se ha alcanzado cierta posicion
bool animC3 = false;

//PUERTA
//Rotacion negativa 
bool animP1 = false;
//Rotacion positiva 
bool animP2 = false;
//Variable para los grados
float rotP = 0.0f;
//Variable para guardar que se ha alcanzado cierta posicion
bool animP3 = false;

//variables extra para la tecla espacio
double lastKeyPressTime = 0.0;
double doubleTapInterval = 10.0;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame



// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	//glm::vec3(posX,posY,posZ),
	glm::vec3(20.875f, 22.026f, -9.025f),
	glm::vec3(-2,-2,0), 
	glm::vec3(-2,-2,0), 
	glm::vec3(22.642f, 11.15f, -13.202f) 
};

glm::vec3 LightP1;
glm::vec3 Light1 = glm::vec3(0);


int main()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final Teoria", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);


	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.frag");
	Shader Anim2("Shaders/anim2.vs", "Shaders/anim2.frag");

	//OBJETOS
	Model fachada((char*)"Models/Cocina2/fachada3/fachada.obj");
	Model cama((char*)"Models/Cuarto/Cama/cama.obj");
	Model mesa((char*)"Models/Cuarto/MesaCuarto/MesaCuarto.obj");
	Model lampara((char*)"Models/Cuarto/Lampara/lampara.obj");
	Model pizarron((char*)"Models/Cuarto/Blackboard/Blackboard.obj");
	Model avion((char*)"Models/Cuarto/avion/avion.obj");
	Model archivero((char*)"Models/Cuarto/Archivero/Archivero.obj");
	Model tronco((char*)"Models/Arbol/tronco.obj");
	Model hojas((char*)"Models/Arbol/arbol.obj");
	Model pc((char*)"Models/Cuarto/PC/pc.obj");
	Model cuerpo((char*)"Models/Cuarto/Alien/cuerpo.obj");
	Model ojos((char*)"Models/Cuarto/Alien/ojos.obj");

	//VENTANA
	Model ventana((char*)"Models/Cuarto/Ventana/ventana.obj");
	Model cristal((char*)"Models/Cuarto/Ventana/cristal.obj");
	//ESCRITORIO
	Model escritorio((char*)"Models/Cuarto/Escritorio/Escritorio.obj");
	Model cajonEsc((char*)"Models/Cuarto/Escritorio/cajon.obj");

	//SILLA
	Model sillaSup((char*)"Models/Cuarto/Silla/sillaSup.obj");
	Model sillaInf((char*)"Models/Cuarto/Silla/sillaInf.obj");

	//PUERTA JIMMY
	Model puerta((char*)"Models/Cuarto/Puerta/puerta.obj");
	Model marcoPuerta((char*)"Models/Cuarto/Puerta/marco.obj");

	//===================================================
	//====================C O C I N A====================
	//===================================================
	
	//MESA
	Model mesaC((char*)"Models/Cocina2/table/table.obj");

	//REFRIGERADOR
	Model refri((char*)"Models/Cocina2/fridge/fridge.obj");

	//LAMPARA
	Model lamparaC((char*)"Models/Cocina2/lamp/lamp.obj");

	//TELEFONO
	Model telefono((char*)"Models/Cocina2/phone/phone.obj");

	//FREGADERO
	Model lavaT((char*)"Models/Cocina2/completo/muebleCompleto.obj");

	//PUERTA - CS
	Model puertaCS((char*)"Models/Cocina2/door/door.obj");
	Model cristalCS((char*)"Models/Cocina2/door/cristal.obj");

	//PUERTA - CP
	Model puertaCP((char*)"Models/Cocina2/doorCP/door.obj");
	Model cristalCP((char*)"Models/Cocina2/doorCP/cristal.obj");

	//VENTANA1
	Model ventana1((char*)"Models/Cocina2/window_l/window.obj");
	Model cristal1((char*)"Models/Cocina2/window_l/cristal.obj");

	//VENTANA2
	Model ventana2((char*)"Models/Cocina2/window_r/window.obj");
	Model cristal2((char*)"Models/Cocina2/window_r/cristales.obj");

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1,&skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/Day/left.bmp");
	faces.push_back("SkyBox/Day/right.bmp");
	faces.push_back("SkyBox/Day/top.bmp");
	faces.push_back("SkyBox/Day/bottom.bmp");
	faces.push_back("SkyBox/Day/back.bmp");
	faces.push_back("SkyBox/Day/front.bmp");
	
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);


	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);



		// Point light 1
		glm::vec3 lightColor;
		//Para encender y apagar la lampara
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = abs(sin(glfwGetTime() * Light1.z));

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		//Specula es el punto brilloso que se ve al rebotar la luz en una superficie
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		//Definen que tan brillante y grande
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 1.8f);




		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.44f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.44f);


		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.2f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.20f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);

		//Carga de modelo 
		view = camera.GetViewMatrix();
		glm::mat4 model(1);

		//CARGA DE CAMA JIMMY
		model = glm::translate(model, glm::vec3(17.211f, 17.05f, 0.494f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cama.Draw(lightingShader);


		//CARGA DE FACHADA 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		fachada.Draw(lightingShader);

		//CARGA DE MESA
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.866f, 17.05f, -8.602f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		mesa.Draw(lightingShader);

		//CARGA DE LAMPARA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(21.0f, 20.0f, -9.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		lampara.Draw(lightingShader);

		//CARGA DE PIZARRÓN
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.189f, 20.196f, -17.34f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		pizarron.Draw(lightingShader);

		//CARGA DE AVIONCITO
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(18.5f, 25.6f, -11.0f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		avion.Draw(lightingShader);

		//CARGA DE ESCRITORIO
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(17.296f, 18.0f, 15.214f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		escritorio.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(17.296f, 18.0f, transC));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		cajonEsc.Draw(lightingShader);

		//CARGA DE ARCHIVERO
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(22.6f, 17.15f, 11.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		archivero.Draw(lightingShader);

		//CARGA DE SILLA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(15.202f, 20.5f, 11.911f));
		model = glm::rotate(model, glm::radians(rotS), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		sillaSup.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(15.202f, 20.5f, 11.911f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		sillaInf.Draw(lightingShader);

		//PUERTA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.685f, 22.188f, -16.311f));
		model = glm::rotate(model, glm::radians(-rotP), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		puerta.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.22f, 22.14f, -16.311f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		marcoPuerta.Draw(lightingShader);

		//VENTANA TRASERA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.72f, 20.526f, -17.85f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ventana.Draw(lightingShader);

		//VENTANA FRONTAL
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(16.72f, 23.526f, 17.8f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ventana.Draw(lightingShader);

		//TRONCO ARBOL
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		tronco.Draw(lightingShader);

		//PC JIMMY
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.5f, 21.0f, 15.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		pc.Draw(lightingShader);

		//ojos aliem
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(11.5f, 16.4f, 6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ojos.Draw(lightingShader);
	

		//===================================================
		//====================C O C I N A====================
		//===================================================
		
		//MESA COCINA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(22.642f, 0.261f, -13.209f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		mesaC.Draw(lightingShader);

		//REFRIGERADOR
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(11.0f, 0.3f, -1.468f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		refri.Draw(lightingShader);

		//LAMPARA COCINA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(22.642f, 10.894f, -13.202f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		lamparaC.Draw(lightingShader);

		//TELEFONO DE PARED
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.444f, 7.5f, -16.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		telefono.Draw(lightingShader);

		//FREGADERO
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.983f, 0.2f, -17.688f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		lavaT.Draw(lightingShader);

		//PUERTA COCINA - SALA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.914f, 0.135f, -11.74f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		puertaCS.Draw(lightingShader);

		//PUERTA COCINA - PATIO
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		puertaCP.Draw(lightingShader);

		//VENTANA IZQUIERDA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ventana1.Draw(lightingShader);

		//VENTANA DERECHA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "transparencia"), 0.0);
		ventana2.Draw(lightingShader);

		//Traslucidez
		//Ventana Cuarto Jimmy
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.72f, 20.526f, -17.6f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 0.0, 1.0, 0.0, 0.25);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 0.882, 0.95, 0.95, 0.25);
		cristal.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(16.72f, 23.526f, 17.8f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 0.0, 1.0, 0.0, 0.25);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 0.882, 0.95, 0.95, 0.25);
		cristal.Draw(lightingShader);


		//=====================================================================================================
		//======================================C O C I N A ===================================================
		//=====================================================================================================

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.914f, 0.135f, -11.74f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.2);
		cristalCS.Draw(lightingShader);

		model = glm::mat4(1);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.2);
		cristalCP.Draw(lightingShader);

		model = glm::mat4(1);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.2);
		cristal1.Draw(lightingShader);

		model = glm::mat4(1);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.2);
		cristal2.Draw(lightingShader);

		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glEnable(GL_DEPTH_TEST);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glBindVertexArray(0);

		Anim2.Use();
		tiempo = glfwGetTime() * 0.5f;
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(Anim2.Program, "model");
		viewLoc = glGetUniformLocation(Anim2.Program, "view");
		projLoc = glGetUniformLocation(Anim2.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Anim2.Program, "time"), tiempo);
		hojas.Draw(Anim2);

		glBindVertexArray(0);

		animShader.Use();
		tiempo = glfwGetTime() * 0.3f;
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(animShader.Program, "model");
		viewLoc = glGetUniformLocation(animShader.Program, "view");
		projLoc = glGetUniformLocation(animShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(11.5f, 17.2f, 6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(animShader.Program, "time"), tiempo);
		cuerpo.Draw(animShader);

		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	if (keys[GLFW_KEY_1])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 1.0f);
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}

	if (GLFW_KEY_2 == key && GLFW_PRESS == action)
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastKeyPressTime < doubleTapInterval)
		{
			if (!anim && !animm)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto no est rotando actualmente
				anim = true;
			}
			else if (anim && !animm)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido negativo
				anim = false;
				animm = true;
			}
			else if (!anim && animm)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido positivo
				anim = true;
				animm = false;
			}
			lastKeyPressTime = currentTime;
		}
		else
		{
			anim = true;
			lastKeyPressTime = currentTime;
		}
	}

	if (GLFW_KEY_3 == key && GLFW_PRESS == action)
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastKeyPressTime < doubleTapInterval)
		{
			if (!animS1 && !animS2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto no est rotando actualmente
				animS1 = true;
			}
			else if (animS1 && !animS2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido negativo
				animS1 = false;
				animS2 = true;
			}
			else if (!animS1 && animS2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido positivo
				animS1 = true;
				animS2 = false;
			}
			lastKeyPressTime = currentTime;
		}
		else
		{
			animS1 = true;
			lastKeyPressTime = currentTime;
		}
	}

	if (GLFW_KEY_4 == key && GLFW_PRESS == action)
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastKeyPressTime < doubleTapInterval)
		{
			if (!animC1 && !animC2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto no est rotando actualmente
				animC1 = true;
			}
			else if (animC1 && !animC2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido negativo
				animC1 = false;
				animC2 = true;
			}
			else if (!animC1 && animC2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido positivo
				animC1 = true;
				animC2 = false;
			}
			lastKeyPressTime = currentTime;
		}
		else
		{
			animC1 = true;
			lastKeyPressTime = currentTime;
		}
	}

	if (GLFW_KEY_5 == key && GLFW_PRESS == action)
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastKeyPressTime < doubleTapInterval)
		{
			if (!animP1 && !animP2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto no est rotando actualmente
				animP1 = true;
			}
			else if (animP1 && !animP2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido negativo
				animP1 = false;
				animP2 = true;
			}
			else if (!animP1 && animP2)
			{
				// La tecla "Espacio" se ha pulsado una vez y el objeto est rotando en sentido positivo
				animP1 = true;
				animP2 = false;
			}
			lastKeyPressTime = currentTime;
		}
		else
		{
			animP1 = true;
			lastKeyPressTime = currentTime;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	//PARA LA ROTACION DEL AVIONCITO
	if (!animmm && anim)
	{
		if (rot > -360.0f)
		{
			rot -= 0.11f;
		}
		else
		{
			animmm = true;
			anim = false;
		}
	}
	if (animm)
	{
		if (animmm && rot < 0.0f)
		{
			rot += 0.11f;
		}
		else
		{
			animmm = false;
			animm = false;
		}
	}

	//PARA LA ROTACION DE LA SILLA
	if (!animS3 && animS1)
	{
		if (rotS > -360.0f)
		{
			rotS -= 0.15f;
		}
		else
		{
			animS3 = true;
			animS1 = false;
		}
	}
	if (animS2)
	{
		if (animS3 && rotS < 0.0f)
		{
			rotS += 0.15f;
		}
		else
		{
			animS3 = false;
			animS2 = false;
		}
	}

	//PARA LA TRASLACION DEL CAJON
	if (!animC3 && animC1)
	{
		if (transC > 13.5f)
		{
			transC -= 0.01f;
		}
		else
		{
			animC3 = true;
			animC1 = false;
		}
	}
	if (animC2)
	{
		if (animC3 && transC < 15.214f)
		{
			transC += 0.01f;
		}
		else
		{
			animC3 = false;
			animC2 = false;
		}
	}

	//PARA LA ROTACION DE LA PUERTA
	if (!animP3 && animP1)
	{
		if (rotP > -90.0f)
		{
			rotP -= 0.15f;
		}
		else
		{
			animP3 = true;
			animP1 = false;
		}
	}
	if (animP2)
	{
		if (animP3 && rotP < 0.0f)
		{
			rotP += 0.15f;
		}
		else
		{
			animP3 = false;
			animP2 = false;
		}
	}

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

}