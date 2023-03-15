#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
 //position en haut a gauche au fond

std::vector<glm::vec3> generateCubeVertices(glm::vec3 position, float length1, float length2){

    std::vector<glm::vec3> vertices;



    // left face
    vertices.push_back(position); // 0 
    vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); //  1 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // 2 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // 3 

    // right face 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2])); // 4 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1)); // 5 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1)); // 6 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2])); // 7

    // upper face
    vertices.push_back(position); // 0 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2])); // 4 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1)); // 5 
    vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); //  1 

    // botton face
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // 3 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2])); // 7 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1)); // 6 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // 2 

    // front face
    vertices.push_back(glm::vec3(position[0], position[1], position[2]+length1)); //  1 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2]+length1)); // 2 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2]+length1)); // 6
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2]+length1)); // 5 

    // back face
    vertices.push_back(position); // 0 
    vertices.push_back(glm::vec3(position[0], position[1]-length1, position[2])); // 3 
    vertices.push_back(glm::vec3(position[0]+length2, position[1]-length1, position[2])); // 7 
    vertices.push_back(glm::vec3(position[0]+length2, position[1], position[2])); // 4 

    return vertices;
}


std::vector<unsigned int> generateCubeIndices (){
    std::vector<unsigned int> indices;

    for (int i = 0; i < 6; i++){
        int idx = i * 4;
        indices.push_back(idx);
        indices.push_back(idx+1);
        indices.push_back(idx+2);
        indices.push_back(idx+2);
        indices.push_back(idx+3);
        indices.push_back(idx);
    }
    return indices;
}



std::vector <glm::vec3> generateCubeNormales (std::vector <glm::vec3> vertices, bool normal_dir){
    std::vector<glm::vec3> normales;
    float dir = (normal_dir)?1.0f:-1.0f;
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(-1.0f, 0.0f, 0.0f)); // Left face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(1.0f, 0.0f, 0.0f)); // Right face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, 1.0f, 0.0f)); // upper face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, -1.0f, 0.0f)); // bottom face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, 0.0f, 1.0f)); // front face
    }
    for (int i = 0; i < 4; i++){
        normales.push_back(dir * glm::vec3(0.0f, 0.0f, -1.0f)); // back face
    }
    std::cout << "Il y a " << vertices.size() << " vertices et " << normales.size() << " normales" << std::endl;
    return normales;
}

