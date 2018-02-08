#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <GL/glew.h>
#include <string>

class GLSLProgram {
public:
    GLSLProgram();
    GLSLProgram(const GLSLProgram& orig);
    virtual ~GLSLProgram();

    void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilepath);
    void linkShaders();

    void addAttribute(const std::string &attributeName);

    void use();
    void unuse();

private:
    int m_numAttributes = 0;

    GLuint m_programID = 0;
    GLuint m_vertexShaderID = 0;
    GLuint m_fragmentShaderID = 0;

    void compileShader(const std::string filePath, GLuint id);
};

#endif /* GLSLPROGRAM_H */

