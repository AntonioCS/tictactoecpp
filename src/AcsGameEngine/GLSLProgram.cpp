#include "GLSLProgram.h"
#include <iostream>
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() {
}

GLSLProgram::GLSLProgram(const GLSLProgram& orig) {
}

GLSLProgram::~GLSLProgram() {
}

void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilepath) {

    m_programID = glCreateProgram();

    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0) {
        std::cout << "Error vertex shader\n";
    }

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0) {
        std::cout << "Error fragment shader\n";
        exit(-1);
    }

    compileShader(vertexShaderFilePath, m_vertexShaderID);
    compileShader(fragmentShaderFilepath, m_fragmentShaderID);
}

void GLSLProgram::compileShader(const std::string filePath, GLuint id) {
    std::ifstream vertexFile{filePath};
    if (vertexFile.fail()) {
        std::cout << "Failed to open shader file\n";
        exit(-1);
    }

    std::string fileContents{""};
    std::string line;

    while (std::getline(vertexFile, line)) {
        fileContents.append(line + '\n');
    }

    vertexFile.close();

    //to make glShaderSource work
    const char *contentPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentPtr, nullptr);
    glCompileShader(id);

    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    //https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language
    if (success == GL_FALSE) {
        std::cout << "ERROR!\n";
    }
}

//https://www.khronos.org/opengl/wiki/Shader_Compilation

void GLSLProgram::linkShaders() {
    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.


    // Attach our shaders to our program
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

    // Link our program
    glLinkProgram(m_programID);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, (int *) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

        std::cout << "ERROR LINK\n";

        // We don't need the program anymore.
        glDeleteProgram(m_programID);
        // Don't leak shaders either.
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);

    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string &attributeName) {
    glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

void GLSLProgram::use() {
    glUseProgram(m_programID);
    for (int i = 0; i < m_numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < m_numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}