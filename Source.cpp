#include<iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"	FragColor = vec4(0.6f, 0.2f, 0.1f, 0.0f);\n"
"}\0";

int main() {

	// Initializa glfw for window creation 
	glfwInit();

	// Let glfw know which version of OpenGL we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// using the CORE profile for only modern OpenGL functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		//First triangle

		-1.0f, 1.0f, 0.0f,  //top right
		-1.0f, 0.0f, 0.0f,  //bottom right
		0.0f,  0.0f, 0.0f, 	//top left
		//Second Triangle
		0.0f, 0.0f, 0.0f, // Bottom right
		1.0f, 0.0f, 0.0f, // bottom left
		1.0f, -1.0, 0.0f // top left
	};

	GLuint indices[] ={	
		0, 1, 2, 3, 4, 5
	};
	// Create a GLFWwindow object 
	GLFWwindow* window = glfwCreateWindow(800, 800, "Dwaine's Window", NULL, NULL);

	// Error handling if window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Window intoduction in it's current context 
	glfwMakeContextCurrent(window); 
	// Loads glad for opengl
	gladLoadGL();


	// x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Linking to shader program

	GLuint shaderProgram;
	shaderProgram = glCreateProgram(); //creates a program 
									   //and returns the ID reference to 
										//the newly created program object.

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// use the shaders
	glUseProgram(shaderProgram);

	// Delete the shaders 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// window background color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Assign a new color to back buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap back buffer with front buffer
	glfwSwapBuffers(window);

	// Vertex Buffer Object and Vertex Array Object
	GLuint VAO, VBO, EBO;     // VBO Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); //Generate buffers 
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds Buffers

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	// Game Loop
	while (!glfwWindowShouldClose(window)) {
		
		//Drawing the triangle 
		glClearColor(0.1f, 0.9f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();

	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	
	// Delete the window
	glfwDestroyWindow(window);
	glfwTerminate(); //ends window
	return 0;
}