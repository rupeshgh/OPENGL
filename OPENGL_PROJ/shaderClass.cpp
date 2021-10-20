#pragma once
#include"shaderClass.h"
#include"errorCheck.h"

struct ShaderSource {
	std::string veretxSource;
	std::string fragmentSource;

};
static ShaderSource parseShader(const std::string& filepath) {

	std::ifstream stream(filepath);

	enum class ShaderType {

		None = -1, vertex = 0, fragment = 1

	};

	ShaderType type = ShaderType::None;


	std::string line;
	std::stringstream ss[2];

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				//set to vertex mode
				type = ShaderType::vertex;

			else if (line.find("fragment") != std::string::npos)
				//set to fragment
				type = ShaderType::fragment;
		}

		else {
			ss[(int)type] << line << '\n';  //typecasting to int  ...type either fragment=1 or vertex=0, shader as defined on enum class..
		}
	}

	return { ss[0].str(),ss[1].str() }; // ss[].str() --to get and set string object whose content is present in stream.
}




shader::shader(const char* shaderFile) {
	ShaderSource source = parseShader(shaderFile);

	std::string vertexCode = source.veretxSource;
	std::string fragmentCode = source.fragmentSource;
	std::cout << vertexCode << std::endl;
	std::cout << fragmentCode << std::endl;

	
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);


	compileErrors(vertexShader, "VERTEX");


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	compileErrors(vertexShader, "fragment");


	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);


	glValidateProgram(ID);

	compileErrors(ID, "PROGRAM");




	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



}


std::string  get_file_contents(const char* filename) {

	std::ifstream in(filename, std::ios::binary);
	if (in) {


		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();

		return(contents);

	}
	throw(errno);
}








	shader::shader(const char* vertexFile, const char* fragmentFile) {

	/*ShaderSource source = parseShader("Basic.shader");

	std::string vertexCode = source.veretxSource;
	std::string fragmentCode = source.fragmentSource;
	std::cout << vertexCode << std::endl;
	std::cout << fragmentCode << std::endl;*/
	
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);
		std::cout << vertexCode;
	std::cout << fragmentCode << std::endl;
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);


	compileErrors(vertexShader, "VERTEX");


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	compileErrors(vertexShader, "fragment");


	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	

	glValidateProgram(ID);
	
	compileErrors(ID, "PROGRAM");
	



	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


		   
}
void shader::Activate() {
	glUseProgram(ID);

}
void shader::Delete() {
	glDeleteProgram(ID);
}

void shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}