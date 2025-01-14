#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//vertex shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {
	//Init GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL we are using
	//In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	//Vertices coordinates
	GLfloat vertices[] = {
		-0.8f,-0.8f * float(sqrt(3)) / 3,0.0f, //lower left corner
		0.2f,-0.2f * float(sqrt(3)) / 3,0.0f,  //Lower right corner
		0.0f,0.8f * float(sqrt(3)) * 2 / 3,0.0f //upper corner

	};


	//Create a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	//Check if the window was created
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Make the window the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	//Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 800, 800);


	//Create vertex shader object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(vertexShader);
	
	//Create fragment shader object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compile the fragment shader into machine code
	glCompileShader(fragmentShader);

	//Create shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	//Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Link all the shaders together in the shader program
	glLinkProgram(shaderProgram);
	//Delete the vertex and fragment shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO,VBO;

	//Generate the VAO and VBO with only one object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	//Bind the VBO and VAO to 0 so that we don't accidentally unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Set the bg color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//clean the back buffer and assign the new color to the buffer
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	//Main while loop
	while (!glfwWindowShouldClose(window)) {


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		//Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		//Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		//Take care of all GLFW Events
		glfwPollEvents();
	}

	//Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Terminate GLFW
	glfwDestroyWindow(window);
	
	//Terminate GLFW
	glfwTerminate();
	return 0;
}