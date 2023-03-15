
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "mesh.h"
#include <vector>
#include "model.h"
#include "generate_cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<Vertex> initVertices(std::vector<glm::vec3> coords, std::vector<glm::vec2> tex_coords, std::vector<glm::vec3> normals);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInputCamera(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1300;


// camera
Camera camera(glm::vec3(-16.3448f, 19.6481f, -35.0483f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //setup textures
   vector<Texture> textures ;
    Texture tex ;

    //----------------------------room mesh-----------------------------------------------------------------

    std::vector<glm::vec3> room_cube_coords = generateCubeVertices(glm::vec3(-20.0, 10.0, -65.0), 45.0, 45.0) ;
    std::vector<unsigned int> room_cube_indices =  generateCubeIndices() ;
    std::vector<glm::vec3> room_cube_normals = generateCubeNormales (room_cube_coords, false) ;
    std::vector<glm::vec2> room_cube_tex_coords ;

    //pour l'instant on met les coordonnées de texture à 1 partout car pas de texture pour le moment
    for (int i= 0 ; i < room_cube_coords.size() ; ++i)
    {
        room_cube_tex_coords.push_back(glm::vec2(1.0, 1.0));
    }

    vector<Vertex> room_vertices= initVertices(room_cube_coords, room_cube_tex_coords, room_cube_normals);

    Mesh* roomMesh = new Mesh(room_vertices, room_cube_indices, textures, false);
	roomMesh->setupMesh();

    
    //----------------------------light1 mesh -----------------------------------------------------------------

     std::vector<glm::vec3> light1_cube_coords = generateCubeVertices(glm::vec3(-20.0, 10.0, -65.0), 5.0, 5.0) ;
    std::vector<unsigned int> light1_cube_indices =  generateCubeIndices() ;
    std::vector<glm::vec3> light1_cube_normals = generateCubeNormales (light1_cube_coords, true) ;

    vector<Vertex> light1_vertices= initVertices(light1_cube_coords, room_cube_tex_coords, light1_cube_normals);

    Mesh* light1Mesh = new Mesh(light1_vertices, light1_cube_indices, textures, false);
	light1Mesh->setupMesh();


    const std::string path = "models/Hand.glb" ;
    std::string const &path_ref = path;
    
    Model ourModel(path_ref);

    //----------------------------bones mesh -----------------------------------------------------------------

    std::vector<glm::vec3> boneCoords = ourModel.GetBonePositions();
    std::vector<unsigned int> boneIndices = ourModel.GetBoneIndices();
    //on s'en fiche des normales vu qu'on veut juste afficher le wireframe
    std::vector<glm::vec3> boneNormals =  generateCubeNormales (boneCoords, true) ;

    vector<Vertex> bone_vertices= initVertices(boneCoords, room_cube_tex_coords, light1_cube_normals);


    Mesh* boneMesh = new Mesh(bone_vertices, boneIndices, textures, true);
	boneMesh->setupMesh();

    std::cout << "boneCoords.size() = " << boneCoords.size() << std::endl;
    for (int i = 0 ; i < boneCoords.size() ; ++i)
    {
        std::cout << "boneCoords[" << i << "] = " << boneCoords[i].x << " " << boneCoords[i].y << " " << boneCoords[i].z << std::endl;
    }


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/floor.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    tex.id = texture ;
    tex.type = "diffuse" ;
    textures.push_back(tex); 
    
    stbi_image_free(data);

    
    Shader* roomShader;
	roomShader = new Shader("shaders/model_loading_vs.glsl", "shaders/light_fs.glsl");

    Shader* light1Shader;
	light1Shader = new Shader("shaders/model_loading_vs.glsl", "shaders/light_source_fs.glsl");

    Shader* ourShader;
	ourShader = new Shader("shaders/weight_vs.glsl", "shaders/weight_fs.glsl");


    // render loop
    // -----------
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        // input
        // -----
        processInputCamera(window);
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
        glfwSetCursorPosCallback(window, mouse_callback);  


        //roomMesh->Draw(roomShader, camera, false);   
        ourModel.Draw(ourShader, camera, false);  
        
        //light1Mesh->Draw(light1Shader, camera, false) ;
        boneMesh->Draw(light1Shader, camera, true) ;
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


std::vector<unsigned int> initIndices(std::vector<Vertex> vertices)
{
	std::vector<unsigned int> indices;
	for (int i = 0; i < vertices.size(); i++)
	{
		indices.push_back(i);
	}
	return indices;
}

std::vector<Vertex> initVertices(std::vector<glm::vec3> coords, std::vector<glm::vec2> tex_coords, std::vector<glm::vec3> normals)
{
	std::vector<Vertex> vertices;
    Vertex temp;
	for (int i = 0; i < coords.size(); i++)
	{
        temp.Position = coords[i];
		temp.Normal = normals[i] ;
		temp.TexCoords = tex_coords[i] ;
		vertices.push_back(temp);
	}
	return vertices;
}


//---------------functions to handle camera and mouse-------------------------------------------------

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInputCamera(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}