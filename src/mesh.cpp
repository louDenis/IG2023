#include "mesh.h"

void Mesh::setVertex(vector<Vertex> v)
{
    this->vertices = v;
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, bool wireframe)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
    this->wireframe = wireframe;
    //rotateMesh() ;
   
    Light l1 ;
    l1.pos = glm::vec3(-20.0, 10.0, -65.0) ;
    l1.color = glm::vec3(1.0f, 1.0f, 1.0f) ;
    l1.constant =  1.0f;
    l1.linear = 0.09f ;
    l1.quadratic = 0.032f ;   
    this->lights.push_back(l1) ;
}



void Mesh::setupMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                 &indices[0], GL_STATIC_DRAW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  
                  
    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));


}  

 

void Mesh::Draw(Shader * shader, Camera camera, int option)
{
   if (!(this->wireframe))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    shader->use();

// render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -20.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);

    shader->setMat4("projection", projection);
    shader->setVec3("objectColor", 10.0f, 10.0f, 10.0f);
    shader->setVec3("lightColor", this->lights[0].color);
    shader->setVec3("lightPos", this->lights[0].pos);
    shader->setVec3("cameraPos", camera.Position);
    shader->setMat4("model", model);

    

        //strong attenuation
        shader->setFloat("constant", 1.0f);
        shader->setFloat("linear",  0.7f );
        shader->setFloat("quadratic", 1.8f);

        //soft attenuation
        //shader->setFloat("constant", 1.0f);
        //shader->setFloat("linear",  0.07f );
        //shader->setFloat("quadratic", 0.017f);



    //std::cout << "position" << camera.Position.x << camera.Position.y << camera.Position.z << std::endl ;
 

    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    shader->setMat4("view", view);

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        string name = textures[i].type;
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        glUniform1i(glGetUniformLocation(shader->ID, (name).c_str()), i);

        glBindTexture(GL_TEXTURE_2D, textures.at(i).id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
} 

vector<Vertex> Mesh::getVerticesNormal()
{
    vector<Vertex> normals_vertices ; 
    for (int i= 0 ; i < vertices.size() ; ++i)
    {
        Vertex v1 ;
        Vertex v2 ; 
        v1.Position = vertices[i].Position ;
        v2.Position = normalize(vertices[i].Position + vertices[i].Normal) ;
        normals_vertices.push_back(v1);
        normals_vertices.push_back(v2);
    }
    return normals_vertices ;
}


int Mesh::IX(int i, int j, int N)
{
	return i * N + j;
}