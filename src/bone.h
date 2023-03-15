/*#pragma once
#include "shader.h"
#include <iostream>
#include <fstream> 
#include <string> 
#include <sstream>  
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "model.h"

using namespace std;

class Bone
{
    private :
        std::vector<int> indices_parents ;

        int id;
        glm::mat4 offset;
        int parentIndex;
        int numChildren;

	std::vector<int> parents;


        std::vector<int> compute_indices_parents()
        {
            std 
        
        }

    public:
        Bone(BoneInfo boneInfo)
        {
            boneInfo.id = id;
            boneInfo.offset = offset;
            boneInfo.parentIndex = parentIndex;
            boneInfo.numChildren = numChildren;
            indices_parents = compute_indices_parents() ;
        }
      
        std::vector<int> getIndicesParents()
        {
            return indices_parents ;
        }

        //void printBoneInfo();
};*/