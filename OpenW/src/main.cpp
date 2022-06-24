#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include <filesystem>

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Utils.h"

void setupVertices();

#define numVAOs 1
#define numVBOs 2


float cameraX, cameraY, cameraZ;
float cubeX, cubeY, cubeZ;
int width, height;
float aspect;
GLuint mvLoc, projLoc;
glm::mat4 proj, view, model, modelView;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint CreateShaderProgram()
{
	std::string vPath = std::filesystem::current_path().append("src").append("shaders").append("vShader.vert").u8string();
	std::string fPath = std::filesystem::current_path().append("src").append("shaders").append("fShader.frag").u8string();


	std::cout << vPath << std::endl;
	std::string vSourceStr = ReadTextFile(vPath.c_str());
	std::string fSourceStr = ReadTextFile(fPath.c_str());

	const char* vSource = vSourceStr.c_str();
	const char* fSource = fSourceStr.c_str();

	GLCall(GLuint vShader = glCreateShader(GL_VERTEX_SHADER));
	GLCall(GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER));

	GLCall(glShaderSource(vShader, 1, &vSource, NULL));
	GLCall(glShaderSource(fShader, 1, &fSource, NULL));
	GLCall(glCompileShader(vShader));
	GLCall(glCompileShader(fShader));

	GLCall(GLuint vfProgram = glCreateProgram());
	GLCall(glAttachShader(vfProgram, vShader));
	GLCall(glAttachShader(vfProgram, fShader));

	//after attaching the shaders you need to make sure they are compatible i.e. vertex shader and fragment shader in this case
	GLCall(glLinkProgram(vfProgram));

	return vfProgram;
}
void init(GLFWwindow* window)
{
	renderingProgram = CreateShaderProgram();
	/*GLCall(glGenVertexArrays(numVAOs, vao));
	GLCall(glBindVertexArray(vao[0]));*/
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 8.0f;
	cubeX = 0.0f;
	cubeY = -2.0f;
	cubeZ = 0.0f;
	setupVertices();
}

struct Point
{
	GLfloat x;
	GLfloat y;
};
/// <summary>
/// Callback for when user resizes the GLFW window.
/// </summary>
/// <param name="window">The window that is being resized.</param>
/// <param name="width">The new width.</param>
/// <param name="height">The new heights.</param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// The first two parameters of glViewport set the location of the lower left corner of the window.
	// The third and fourth parameter set the width and height of the rendering window in pixels, which we set equal to GLFW's window size.
	GLCall(glViewport(0, 0, width, height));
	//aspect = (float)width / (float)height;
	//proj = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}
void math_draw()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	const int N_POINTS = 2000;
	Point points[N_POINTS];
	for (int i = 0; i < N_POINTS; i++)
	{
		float x = (i - 1000.0) / 100.0;
		points[i].x = x;
		points[i].y = sin(x * 10.0) / (1.0 + x * x);
	}

	GLuint vbo;
	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(
		0,   // attribute
		2,                   // number of elements per vertex, here (x,y)
		GL_FLOAT,            // the type of each element
		GL_FALSE,            // take our values as-is
		0,                   // no space between values
		0                    // use the vertex buffer object
	));

	GLCall(glUseProgram(renderingProgram));
	GLCall(glPointSize(5.0f));
	GLCall(glDrawArrays(GL_POINTS, 0, 2000));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}
void setupVertices(void)
{
	float vertexPositions[108] = {
		 -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
		 -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};

	GLCall(glGenVertexArrays(1, vao));
	GLCall(glBindVertexArray(vao[0]));
	GLCall(glGenBuffers(numVBOs, vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW));

}
void display(GLFWwindow* window, double currentTime)
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	GLCall(glUseProgram(renderingProgram));
	GLCall(mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix"));
	GLCall(projLoc = glGetUniformLocation(renderingProgram, "proj_matrix"));

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	proj = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	model = glm::translate(glm::mat4(1.0f), glm::vec3(cubeX, cubeY, cubeZ));
	modelView = view * model;

	GLCall(glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(modelView)));
	GLCall(glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj)));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LEQUAL));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	//math_draw();
	//GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
	//GLCall(glClear(GL_COLOR_BUFFER_BIT));
	//GLCall(glUseProgram(renderingProgram));
	//GLCall(glPointSize(30.0f));
	//GLCall(glDrawArrays(GL_POINTS, 0, 1));
}
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{

	//initializing glfw
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenW", NULL, NULL);
	glfwMakeContextCurrent(window);
	//initializing glew
	if (glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);

	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	init(window);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

	bool showDemoWindow = false;

	//rendering the frame buffer to the window
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);
		//Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (showDemoWindow)
			ImGui::ShowDemoWindow(&showDemoWindow);
		else
		{
			//insert your code in here 
			{
				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
				ImGui::Text("This is some useful text.");
				ImGui::End();
			}
		}
		ImGui::Render();
		display(window, glfwGetTime());
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//destroying glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}