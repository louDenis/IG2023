#pragma once
#include "shader.h"
#include <iostream>
#include <fstream> 
#include <string> 
#include <sstream>  
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#define MAX_BONE_INFLUENCE 10

//#include <windows.h>
#include "camera.h"
using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;


    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

//struct with each triangle vertex
struct Triangle
{
    Vertex a;
    Vertex b;
    Vertex c;
    glm::vec3 triangleNormale;
    glm::vec3 centroid;
    //vector<Triangle> neighbors;
};



struct Texture {
    unsigned int id;
    string type;
    string path;
};

struct Light
{
    glm::vec3 pos ;
    glm::vec3 color ;

    float constant;
    float linear;
    float quadratic;
} ;

class Mesh
{
public:
	// lighting
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    bool wireframe;
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, bool wireframe);
    vector< glm::vec3> coords;
    vector< glm::vec3> normal;
    vector< glm::vec2> texCoords;
    vector< Light > lights ;
    vector <int> faceIndex;
    vector<int> textureIndex;
    unsigned int VAO, VBO, NBO, EBO;

    vector<Vertex> vertices;
    vector<Texture> textures ;
    vector<unsigned int> indices;

    void setupMesh();
    void Draw(Shader * shader, Camera camera, int option);
    //void rotateMesh() ;

    void generateMeshFromPoints(int N);
    int IX(int i, int j, int N);
	

    vector<Triangle> trianglesVec;
    glm::vec3 computeNormalofTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    vector<Triangle> getTrianglesVector();
	Vertex getVertexAt(int i);
    void computeAllTriangleNormal();
    vector<Vertex> getTriangleCentroid(Triangle t);
    vector<Vertex> getAllTriangleCentroid(Triangle t);
    vector<Triangle> getTrianglesOfVertex(Vertex v);
    
	//functions to get normal of vertices
    void computeVertexNormal();
    vector<Vertex> getVertexNormal();

    void setVertex(vector<Vertex> v);
    vector<Vertex> getVerticesNormal();
	
};
