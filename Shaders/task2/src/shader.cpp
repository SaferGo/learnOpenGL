#include "shader.h"
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CompileStatus(vertex, 1);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CompileStatus(fragment, 2);

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	LinkStatus(id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() const {
	glUseProgram(id);
}

void Shader::setBool(const std::string &name, const bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, const int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set4Float(const std::string &name, const float value[]) const {
	glUniform4f(
		glGetUniformLocation(id, name.c_str()),
		value[0],
		value[1],
		value[2],
		value[3]
	);
}

void Shader::CompileStatus(const unsigned int &shader, const uint8_t &type) const {
	int status;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (!status) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::";

		if (type == 1) {
			std::cout << "VERTEX";
		} else {
			std::cout << "FRAGMENT";
		}
		std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::LinkStatus(const unsigned int &shader) const {
	int status;
	char infoLog[512];

	glGetProgramiv(shader, GL_LINK_STATUS, &status);

	if (!status) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error::PROGRAM::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
