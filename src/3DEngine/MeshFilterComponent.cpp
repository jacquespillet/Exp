#include "MeshFilterComponent.hpp"

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#define GLV QOpenGLFunctions_3_3_Core
#define GETGL GLV* ogl = QOpenGLContext::currentContext()->versionFunctions<GLV>(); if(ogl==NULL){std::cout << "could not get opengl context";}

namespace KikooRenderer {
namespace CoreEngine {

MeshFilterComponent::MeshFilterComponent() : Component("MeshFilter") {
    inited= false;
}
void MeshFilterComponent::OnStart(){}
void MeshFilterComponent::OnEnable(){
    InitBuffers();
	RebuildBuffers();
}
void MeshFilterComponent::OnUpdate(){}
void MeshFilterComponent::OnRender(){
	GETGL
	//
	//bind VAO
	//
	
	ogl->glBindVertexArray(vertexArrayObject);
	
	//
	//Draw
	//
	
	//draw elements
	if(renderInstanced) {
		ogl->glDrawElementsInstanced(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0, numInstances);
	} else {
		ogl->glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, (void*)0);
	}
	//
	//unbind VAO
	//
	
	ogl->glBindVertexArray(0);
} 


void MeshFilterComponent::LoadFromBuffers(std::vector<glm::vec3> _vertex,
std::vector<glm::vec3> _normals,
std::vector<glm::vec2> _uv,
std::vector<glm::vec4> _colors,
std::vector<int> _triangles) {
    this->triangles = _triangles;
    for(int i=0; i<_vertex.size(); i++) {
        Vertex vertex = {
            _vertex[i],
            _normals[i],
            _uv[i],
            _colors[i].r,
            _colors[i].g,
            _colors[i].b,
            _colors[i].a
        };
        vertices.push_back(vertex);
    }
}

void MeshFilterComponent::InitBuffers() {
    GETGL
	ogl->glGenBuffers(1, &vertexBuffer);
	ogl->glGenBuffers(1, &elementBuffer);
	ogl->glGenVertexArrays(1, &vertexArrayObject);
	
	//Bind VAO
	ogl->glBindVertexArray(vertexArrayObject);
	
	//bind buffers
	ogl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	
	//set vertex attributes
	ogl->glEnableVertexAttribArray(0);
	ogl->glEnableVertexAttribArray(1);
	ogl->glEnableVertexAttribArray(2);
	ogl->glEnableVertexAttribArray(3);
	ogl->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)0));
	ogl->glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)12));
	ogl->glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)24));
	ogl->glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void*)((uintptr_t)32));
	ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Init matrices buffer
	ogl->glGenBuffers(1, &matricesBuffer);
	ogl->glBindBuffer(GL_ARRAY_BUFFER, matricesBuffer);

  	GLsizei vec4Size = sizeof(glm::vec4);
    ogl->glEnableVertexAttribArray(5); 
    ogl->glEnableVertexAttribArray(6); 
    ogl->glEnableVertexAttribArray(7); 
    ogl->glEnableVertexAttribArray(8);
    ogl->glEnableVertexAttribArray(9);
    ogl->glEnableVertexAttribArray(10);

    ogl->glVertexAttribPointer(5,  4, GL_FLOAT, GL_FALSE, sizeof(InstanceAttribute), (void*)(0 * vec4Size));
    ogl->glVertexAttribPointer(6,  4, GL_FLOAT, GL_FALSE, sizeof(InstanceAttribute), (void*)(1 * vec4Size));
    ogl->glVertexAttribPointer(7,  4, GL_FLOAT, GL_FALSE, sizeof(InstanceAttribute), (void*)(2 * vec4Size));
    ogl->glVertexAttribPointer(8,  4, GL_FLOAT, GL_FALSE, sizeof(InstanceAttribute), (void*)(3 * vec4Size));
    ogl->glVertexAttribPointer(9,  4, GL_FLOAT, GL_FALSE, sizeof(InstanceAttribute), (void*)(4 * vec4Size));
    ogl->glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceAttribute), (void*)(5 * vec4Size));

    ogl->glVertexAttribDivisor(5, 1);
    ogl->glVertexAttribDivisor(6, 1);
    ogl->glVertexAttribDivisor(7, 1);
    ogl->glVertexAttribDivisor(8, 1);
    ogl->glVertexAttribDivisor(9, 1);
    ogl->glVertexAttribDivisor(10, 1);

	//Unbind VAO
	ogl->glBindVertexArray(0);
	
	//Unbind array and element buffers
	ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);
	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	inited = true; 
}

void MeshFilterComponent::RebuildBuffers() {
	GETGL
	//Bind VAO
	ogl->glBindVertexArray(vertexArrayObject);
	
	//Bind buffers
	ogl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	
	//copy data to buffers
	ogl->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), (uint8_t*)&vertices[0], GL_STATIC_DRAW);
	ogl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), (uint8_t*)&triangles[0], GL_STATIC_DRAW);
	
	
	instanceAttributes = std::vector<InstanceAttribute>(numInstances);
	for(int i=0; i<numInstances; i++) {
		instanceAttributes[i].modelMatrix = glm::translate(glm::mat4(1), glm::vec3(0, (float)i, 0));
		instanceAttributes[i].additionalData1 = glm::vec4(0, 0, 0, 0);
		instanceAttributes[i].additionalData2 = glm::vec4(0, 0, 0, 0);
	}
	ogl->glBindBuffer(GL_ARRAY_BUFFER, matricesBuffer);
	ogl->glBufferData(GL_ARRAY_BUFFER, numInstances * sizeof(InstanceAttribute), (uint8_t*)&instanceAttributes[0], GL_STREAM_DRAW);


	//Unbind VAO
	ogl->glBindVertexArray(0);
	
	//Unbind array and element buffers
	ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);
	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);    
}


void MeshFilterComponent::SetInstanceAttributes(std::vector<InstanceAttribute> instanceAttributes) {
	GETGL
	//Bind VAO
	ogl->glBindVertexArray(vertexArrayObject);
	
	//Bind buffers
	ogl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	ogl->glBindBuffer(GL_ARRAY_BUFFER, matricesBuffer);
	ogl->glBufferData(GL_ARRAY_BUFFER, numInstances * sizeof(InstanceAttribute), (uint8_t*)&instanceAttributes[0], GL_STREAM_DRAW);
	
	//Unbind array and element buffers
	ogl->glBindVertexArray(0);
	ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);

}

}
}