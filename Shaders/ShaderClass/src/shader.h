#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
 public:
	unsigned int id;
	
	Shader(const char *vertexPath, const char *fragmentPath);
	
	void use() const;
	void setBool(const std::string &name, const bool &value) const;
	void setInt(const std::string &name, const int &value) const;
	void setFloat(const std::string &name, const float &value) const;
	void set4Float(const std::string &name, const float value[]) const;
 private:
	void CompileStatus(const unsigned int &shader, const uint8_t &type) const;
	void LinkStatus(const unsigned int &shader) const;
};

#endif
