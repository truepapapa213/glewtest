// glewtest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>    

// GLEW    
//#define GLEW_STATIC    
#include <GL/glew.h>    

// GLFW    
#include <GLFW/glfw3.h>    

#include "shader.h"


//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Function prototypes    
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions    
const GLuint WIDTH = 1200, HEIGHT = 1200;

// Triangle vertices
float vertices[] = {
	 0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

float vertices1[] = {
	 0.5f, 0.5f, 0.0f,   // 右上角
	-0.5f, 0.5f, 0.0f,   // 左上角
	0.0f,-0.5f,0.0f
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};	

float cubevertices[] = {
	 -0.3f, -0.3f,-0.3f,1.0f,0.0f,0.0f,
	 0.3f, -0.3f,-0.3f,1.0f,0.0f,0.0f,
	 0.3f, 0.3f,-0.3f,1.0f,0.0f,0.0f,
	 -0.3f, 0.3f,-0.3f,1.0f,0.0f,0.0f,
	 -0.3f, -0.3f,0.3f,0.0f,1.0f,0.0f,
	 0.3f, -0.3f,0.3f,0.0f,1.0f,0.0f,
	 0.3f, 0.3f,0.3f,0.0f,1.0f,0.0f,
	 -0.3f, 0.3f,0.3f,0.0f,1.0f,0.0f
};

unsigned int cubeindices[] = { // 注意索引从0开始! 
	0, 1,2,
	0,2,3,
	4,5,6,
	4,6,7,
	1,2,6,
	1,5,6,
	0,3,7,
	0,4,7

};

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

unsigned int cubeindices1[] = { // 注意索引从0开始! 
	0, 1,2, 3,
	0,1, 5,4,
	1,2,6,5,
	2,3,7,6,
	3,0,4,7,
	5,4,7,6

};

// The MAIN function, from here we start the application and run the game loop    
int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW    
	glfwInit();
	// Set all the required options for GLFW    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions    
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set the required callback functions    
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions    
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers    
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions    
	glViewport(0, 0, WIDTH, HEIGHT);


	//Create shader Program
	Shader program("shader.vert", "shader.frag");
	//GLuint program = loadProgram("shader.vert","shader.frag");
	GLuint VBO, VAO,EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubevertices), cubevertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeindices), cubeindices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	

	glEnable(GL_DEPTH_TEST);

	// Game loop    
	while (!glfwWindowShouldClose(window))
	{
		// Clear the colorbuffer    
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// Render    
		glUseProgram(program.ID);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(program.ID, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model;
			//model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(1.0, 0.0, 0.0));
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i* timeValue;
			model = glm::rotate(model,  glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));


			unsigned int modelLoc = glGetUniformLocation(program.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glm::mat4 view;
			// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
			view = glm::translate(view, glm::vec3(0.0f, -0.0f, -3.0f));

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);



			unsigned int viewLoc = glGetUniformLocation(program.ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			unsigned int projectionLoc = glGetUniformLocation(program.ID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			
		}
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);


		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Swap the screen buffers    
		glfwSwapBuffers(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions    
		glfwPollEvents();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.    
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW    
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
