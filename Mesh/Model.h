//
// Created by guoxiaofei on 2020-7-13.
//

#ifndef HELLOWINDOW_MODEL_H
#define HELLOWINDOW_MODEL_H

#include "shader.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
    std::vector<Texture> textures_loaded;
    /*  函数   */

    Model(std::string const &path)
    {
        std::cout << "Model construct" << std::endl;
        loadModel(path);
    }
    void Draw(Shader shader);

private:
    /*  模型数据  */
    std::vector<Mesh> meshes;
    std::string directory;
    /*  函数   */
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);
};


#endif //HELLOWINDOW_MODEL_H
