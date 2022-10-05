#include "Shader.h"


Shader::Shader() {
	_shaderId = 0;
	_uniformModel = 0;
	_uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertex_code, const char* fragment_code)
{
	CompileShader(vertex_code, fragment_code);
}

void Shader::CompileShader(const char* vertex_code, const char* fragment_code)
{
	_shaderId = glCreateProgram();

	if (!_shaderId)
	{
		std::cerr << "Error creating shader program" << std::endl;
		return;
	}

	AddShader(_shaderId, vertex_code, GL_VERTEX_SHADER);
	AddShader(_shaderId, fragment_code, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(_shaderId);
	glGetProgramiv(_shaderId, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(_shaderId, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error linking program:" << eLog << std::endl;
		return;
	}

	glValidateProgram(_shaderId);
	glGetProgramiv(_shaderId, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(_shaderId, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error validating program:" << eLog << std::endl;
		return;
	}

	_uniformModel = glGetUniformLocation(_shaderId, "model");
	_uniformProjection = glGetUniformLocation(_shaderId, "projection");
}

void Shader::AddShader(GLuint the_program, const char* shader_code, GLenum shader_type)
{
	GLuint the_shader = glCreateShader(shader_type);

	const GLchar* the_code[1];
	the_code[0] = shader_code;

	GLint code_length[1];
	code_length[0] = strlen(shader_code);

	glShaderSource(the_shader, 1, the_code, code_length);
	glCompileShader(the_shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(the_shader, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error compiling the " << shader_type << " shader:'" << eLog << "'" << std::endl;
		return;
	}

	glAttachShader(the_program, the_shader);
}

GLuint Shader::GetProjectionLocation()
{
	return _uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return _uniformModel;
}

void Shader::UseShader()
{
	glUseProgram(_shaderId);
}

void Shader::ClearShader()
{
	if(_shaderId != 0) 
	{
		glDeleteProgram(_shaderId);
		_shaderId = 0;
	}

	_uniformModel = 0;
	_uniformProjection = 0;
}


Shader::~Shader() {
	ClearShader();
}
