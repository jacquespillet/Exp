#include "BaseObjects.hpp"
#include "TransformComponent.hpp"

namespace KikooRenderer {

namespace CoreEngine {


Object3D* GetCube(Scene* scene, std::string name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, Shader shader, bool physics) {
     //Start each Object3D in scene
    Object3D* newObject = new Object3D(name, scene, shader);
   

    //Setup mesh
    // MeshFilterComponent* mesh = GetCubeMesh(glm::vec3(1), _color, newObject);
    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec4> colors;
    std::vector<int> triangles;
    //
    ///Vertices
    //

    //Front
    vertex.push_back(glm::vec3(-0.5, -0.5, -0.5)); //bottom left
    vertex.push_back(glm::vec3(-0.5, 0.5, -0.5)); // top left
    vertex.push_back(glm::vec3(0.5, 0.5, -0.5)); //Top right
    vertex.push_back(glm::vec3(0.5, -0.5, -0.5)); //Bottom right

    // Back
    vertex.push_back(glm::vec3(0.5, -0.5, 0.5)); //Bottom Left
    vertex.push_back(glm::vec3(0.5, 0.5, 0.5)); //Top left
    vertex.push_back(glm::vec3(-0.5, 0.5, 0.5)); // top right
    vertex.push_back(glm::vec3(-0.5, -0.5, 0.5)); //bottom right

    // Right
    vertex.push_back(glm::vec3(0.5, -0.5, -0.5)); // Bottom left
    vertex.push_back(glm::vec3(0.5, 0.5, -0.5)); //Top left
    vertex.push_back(glm::vec3(0.5, 0.5, 0.5)); //Top right
    vertex.push_back(glm::vec3(0.5, -0.5, 0.5)); //Bottom right

    // Left
    vertex.push_back(glm::vec3(-0.5, -0.5, 0.5)); //Bottom Left
    vertex.push_back(glm::vec3(-0.5, 0.5, 0.5)); //Top left
    vertex.push_back(glm::vec3(-0.5, 0.5, -0.5)); //Top right
    vertex.push_back(glm::vec3(-0.5, -0.5,-0.5)); // Bottom right

    // Top
    vertex.push_back(glm::vec3(-0.5, 0.5, -0.5)); //Bottom Left
    vertex.push_back(glm::vec3(-0.5, 0.5, 0.5)); //Top Left
    vertex.push_back(glm::vec3(0.5, 0.5, 0.5)); // top right
    vertex.push_back(glm::vec3(0.5, 0.5, -0.5)); //bottom right

    // Bottom
    vertex.push_back(glm::vec3( -0.5, -0.5,  0.5)); //bottom left
    vertex.push_back(glm::vec3( -0.5, -0.5, -0.5)); // top left
    vertex.push_back(glm::vec3(0.5, -0.5, -0.5)); //Top right
    vertex.push_back(glm::vec3(0.5, -0.5,  0.5)); //Bottom right


    //
    ///Normals
    //

    //Front
    normals.push_back(glm::vec3(0, 0, -1));
    normals.push_back(glm::vec3(0, 0, -1));
    normals.push_back(glm::vec3(0, 0, -1));
    normals.push_back(glm::vec3(0, 0, -1));
    
    //Back
    normals.push_back(glm::vec3(0, 0, 1));
    normals.push_back(glm::vec3(0, 0, 1));
    normals.push_back(glm::vec3(0, 0, 1));
    normals.push_back(glm::vec3(0, 0, 1));
    
    //Right
    normals.push_back(glm::vec3(1, 0, 0));
    normals.push_back(glm::vec3(1, 0, 0));
    normals.push_back(glm::vec3(1, 0, 0));
    normals.push_back(glm::vec3(1, 0, 0));

    //Left
    normals.push_back(glm::vec3(-1, 0, 0));
    normals.push_back(glm::vec3(-1, 0, 0));
    normals.push_back(glm::vec3(-1, 0, 0));
    normals.push_back(glm::vec3(-1, 0, 0));
    
    //Top
    normals.push_back(glm::vec3(0, 1, 0));
    normals.push_back(glm::vec3(0, 1, 0));
    normals.push_back(glm::vec3(0, 1, 0));
    normals.push_back(glm::vec3(0, 1, 0));

    //Bottom
    normals.push_back(glm::vec3(0, -1, 0));
    normals.push_back(glm::vec3(0, -1, 0));
    normals.push_back(glm::vec3(0, -1, 0));
    normals.push_back(glm::vec3(0, -1, 0));


    //
    ////UV
    //

    //Front
    uv.push_back(glm::vec2(0, 1));
    uv.push_back(glm::vec2(0, 0));
    uv.push_back(glm::vec2(1, 0));
    uv.push_back(glm::vec2(1, 1));
    
    //Back
    uv.push_back(glm::vec2(0, 1));
    uv.push_back(glm::vec2(0, 0));
    uv.push_back(glm::vec2(1, 0));
    uv.push_back(glm::vec2(1, 1));
    
    //Right
    uv.push_back(glm::vec2(0, 1));
    uv.push_back(glm::vec2(0, 0));
    uv.push_back(glm::vec2(1, 0));
    uv.push_back(glm::vec2(1, 1));
    
    //Left
    uv.push_back(glm::vec2(0, 1));
    uv.push_back(glm::vec2(0, 0));
    uv.push_back(glm::vec2(1, 0));
    uv.push_back(glm::vec2(1, 1));
    
    //Top
    uv.push_back(glm::vec2(0, 1));
    uv.push_back(glm::vec2(0, 0));
    uv.push_back(glm::vec2(1, 0));
    uv.push_back(glm::vec2(1, 1));
    
    //Bottom
    uv.push_back(glm::vec2(0, 1));
    uv.push_back(glm::vec2(0, 0));
    uv.push_back(glm::vec2(1, 0));
    uv.push_back(glm::vec2(1, 1));


    //
    ////Colors
    //

    //Front
    colors.push_back(glm::vec4(255, 0, 0, 255));
    colors.push_back(glm::vec4(0, 255, 0, 255));
    colors.push_back(glm::vec4(0, 0, 255, 255));
    colors.push_back(glm::vec4(255, 0, 0, 255));
    
    //Back
    colors.push_back(glm::vec4(255, 0, 0, 255));
    colors.push_back(glm::vec4(0, 255, 0, 255));
    colors.push_back(glm::vec4(0, 0, 255, 255));
    colors.push_back(glm::vec4(255, 0, 0, 255));
    
    //Right
    colors.push_back(glm::vec4(255, 0, 0, 255));
    colors.push_back(glm::vec4(0, 255, 0, 255));
    colors.push_back(glm::vec4(0, 0, 255, 255));
    colors.push_back(glm::vec4(255, 0, 0, 255));
    
    //Left
    colors.push_back(glm::vec4(255, 0, 0, 255));
    colors.push_back(glm::vec4(0, 255, 0, 255));
    colors.push_back(glm::vec4(0, 0, 255, 255));
    colors.push_back(glm::vec4(255, 0, 0, 255));
    
    //Top
    colors.push_back(glm::vec4(255, 0, 0, 255));
    colors.push_back(glm::vec4(0, 255, 0, 255));
    colors.push_back(glm::vec4(0, 0, 255, 255));
    colors.push_back(glm::vec4(255, 0, 0, 255));
    
    //Bottom
    colors.push_back(glm::vec4(255, 0, 0, 255));
    colors.push_back(glm::vec4(0, 255, 0, 255));
    colors.push_back(glm::vec4(0, 0, 255, 255));
    colors.push_back(glm::vec4(255, 0, 0, 255));


    //
    ////Triangles
    //

    //Front
    int index = 0;
    triangles.push_back(index + 0);
    triangles.push_back(index + 2);
    triangles.push_back(index + 1);
    triangles.push_back(index + 3);
    triangles.push_back(index + 2);
    triangles.push_back(index + 0);
    
    index = 4;
    triangles.push_back(index + 0);
    triangles.push_back(index + 2);
    triangles.push_back(index + 1);
    triangles.push_back(index + 3);
    triangles.push_back(index + 2);
    triangles.push_back(index + 0);

    index = 8;
    triangles.push_back(index + 0);
    triangles.push_back(index + 2);
    triangles.push_back(index + 1);
    triangles.push_back(index + 3);
    triangles.push_back(index + 2);
    triangles.push_back(index + 0);

    index = 12;
    triangles.push_back(index + 0);
    triangles.push_back(index + 2);
    triangles.push_back(index + 1);
    triangles.push_back(index + 3);
    triangles.push_back(index + 2);
    triangles.push_back(index + 0);

    index = 16;
    triangles.push_back(index + 0);
    triangles.push_back(index + 2);
    triangles.push_back(index + 1);
    triangles.push_back(index + 3);
    triangles.push_back(index + 2);
    triangles.push_back(index + 0);
    
    index = 20;
    triangles.push_back(index + 0);
    triangles.push_back(index + 2);
    triangles.push_back(index + 1);
    triangles.push_back(index + 3);
    triangles.push_back(index + 2);
    triangles.push_back(index + 0);
    //Setup mesh
    MeshFilterComponent* mesh = new MeshFilterComponent();
    mesh->LoadFromBuffers(vertex, normals, uv, colors, triangles);

    //Setup transform
    TransformComponent* transform = new TransformComponent();
    transform->position = _position;
    transform->rotation = _rotation;
    transform->scale = _scale;
    
	newObject->transform = transform;
    newObject->AddComponent(mesh);


    return newObject;
}

Object3D* GetQuad(Scene* scene, std::string name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, Shader shader, bool physics) {
    //Start each Object3D in scene
    Object3D* quad = new Object3D(name, scene, shader);
    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec4> colors;
    std::vector<int> triangles;
    
    vertex.push_back(glm::vec3(-0.5, -0.5, 0.0)); //bottom left
    vertex.push_back(glm::vec3(-0.5, 0.5, 0.0)); // top left
    vertex.push_back(glm::vec3(0.5, 0.5, 0.0)); //Top right
    vertex.push_back(glm::vec3(0.5, -0.5, 0.0)); //Bottom right

    normals.push_back(glm::vec3(0, 0, -1));
    normals.push_back(glm::vec3(0, 0, -1));
    normals.push_back(glm::vec3(0, 0, -1));
    normals.push_back(glm::vec3(0, 0, -1));
    
    uv.push_back(glm::vec2(0, 0));
    uv.push_back(glm::vec2(0, 1));
    uv.push_back(glm::vec2(1, 1));
    uv.push_back(glm::vec2(1, 0));

    colors.push_back(glm::vec4(255, 255, 255, 255));
    colors.push_back(glm::vec4(255, 255, 255, 255));
    colors.push_back(glm::vec4(255, 255, 255, 255));
    colors.push_back(glm::vec4(255, 255, 255, 255));

    int index = 0;
    triangles.push_back(index + 0);
    triangles.push_back(index + 2);
    triangles.push_back(index + 1);
    triangles.push_back(index + 3);
    triangles.push_back(index + 2);
    triangles.push_back(index + 0);

    MeshFilterComponent* mesh = new MeshFilterComponent();
    mesh->LoadFromBuffers( vertex, normals, uv, colors, triangles);
    
    TransformComponent* transform = new TransformComponent();
    transform->position = _position;
    transform->rotation = _rotation;
    transform->scale = _scale;    
    
    quad->AddComponent(mesh);
    quad->transform = transform;    

    return quad;
}

}
}