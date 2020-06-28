#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_opengl3.h"
#include"imgui/imgui_impl_glfw.h"

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK)
	{
		std::cout << "error";
	};
	{
		float positions[] = {
			100.0f, 100.0f, 0.0f, 0.0f, //0
			200.0f, 100.0f, 1.0f, 0.0f, //1
			200.0f, 200.0f, 1.0f, 1.0f,//2
			100.0f, 200.0f, 0.0f, 1.0f,//3
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		

		VertexArray va;
		VertexBuffer vb(positions, sizeof(positions));
		VertexBufferLayout layout;
		
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);
		
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));  
	
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUnform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		
		Texture texture("res/textures/The_death.png");
		texture.Bind();
		shader.SetUnform1i("u_Texture", 0);

		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui::StyleColorsDark();
		glm::vec3 translation(200, 200, 0);


		while (!glfwWindowShouldClose(window))
		{
			
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;

			shader.SetUnform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
			shader.SetUnformMat4f("u_MVP", mvp);

			va.Bind();
			ib.Bind();

			renderer.Draw(va, ib, shader);

			{
				ImGui::SliderFloat3("translation", &translation.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}



			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
						
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}