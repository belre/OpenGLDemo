#include <fstream>
#include <sstream>
#include "Shader.h"


Shader::Shader() {
	_shaderId = 0;
	_uniformModel = 0;
	_uniformProjection = 0;
	_uniformView = 0;

	_pointLightCount = 0;
}

void Shader::CreateFromString(const char* vertex_code, const char* fragment_code)
{
	CompileShader(vertex_code, fragment_code);
}

void Shader::CreateFromFiles(const char* vertex_location, const char* fragment_location)
{
	auto vertex_string = ReadFile(vertex_location);
	auto fragment_string = ReadFile(fragment_location);

	CompileShader(vertex_string.c_str(), fragment_string.c_str());
}

const std::string Shader::ReadFile(const char* file_location)
{
	std::string content;
	std::ifstream if_stream(file_location, std::ios::in);

	if(!if_stream) 
	{
		std::cerr << "Failed to read " << file_location << " doesn't exist." << std::endl;
		return "";
	}

	std::string line;
	while(!if_stream.eof()) 
	{
		std::getline(if_stream, line);
		content.append(line + "\n");
	}

	if_stream.close();

	return content;
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

	_uniformProjection = glGetUniformLocation(_shaderId, "projection");
	_uniformModel = glGetUniformLocation(_shaderId, "model");
	_uniformView = glGetUniformLocation(_shaderId, "view");
	_uniformDirectionalLight._uniformColor = glGetUniformLocation(_shaderId, "directionalLight.base.color");
	_uniformDirectionalLight._uniformAmbientIntensity = glGetUniformLocation(_shaderId, "directionalLight.base.ambientIntensity");
	_uniformDirectionalLight._uniformDirectionalLight = glGetUniformLocation(_shaderId, "directionalLight.direction");
	_uniformDirectionalLight._uniformDiffuseIntensity = glGetUniformLocation(_shaderId, "directionalLight.base.diffuseIntensity");
	_uniformSpecularIntensity = glGetUniformLocation(_shaderId, "material.specularIntensity");
	_uniformShininess = glGetUniformLocation(_shaderId, "material.shininess");
	_uniformEyePosition = glGetUniformLocation(_shaderId, "eyePosition");

	_uniformPointLightCount = glGetUniformLocation(_shaderId, "pointLightCount");

	for(size_t i = 0 ; i < MAX_POINT_LIGHTS; i++) 
	{
		std::stringstream loc_buff_str;
		loc_buff_str << "pointLights[" << i << "].base.color";
		_uniformPointLight[i]._uniformColor = glGetUniformLocation(_shaderId, loc_buff_str.str().c_str());

		loc_buff_str = std::stringstream();
		loc_buff_str << "pointLights[" << i << "].base.ambientIntensity";
		_uniformPointLight[i]._uniformAmbientIntensity = glGetUniformLocation(_shaderId, loc_buff_str.str().c_str());

		loc_buff_str = std::stringstream();
		loc_buff_str << "pointLights[" << i << "].base.diffuseIntensity";
		_uniformPointLight[i]._uniformDiffuseIntensity = glGetUniformLocation(_shaderId, loc_buff_str.str().c_str());

		loc_buff_str = std::stringstream();
		loc_buff_str << "pointLights[" << i << "].position";
		_uniformPointLight[i]._uniformPosition = glGetUniformLocation(_shaderId, loc_buff_str.str().c_str());

		loc_buff_str = std::stringstream();
		loc_buff_str << "pointLights[" << i << "].constant";
		_uniformPointLight[i]._uniformCoefConstant = glGetUniformLocation(_shaderId, loc_buff_str.str().c_str());

		loc_buff_str = std::stringstream();
		loc_buff_str << "pointLights[" << i << "].linear";
		_uniformPointLight[i]._uniformCoefLinear = glGetUniformLocation(_shaderId, loc_buff_str.str().c_str());

		loc_buff_str = std::stringstream();
		loc_buff_str << "pointLights[" << i << "].exponent";
		_uniformPointLight[i]._uniformCoefExponent = glGetUniformLocation(_shaderId, loc_buff_str.str().c_str());
	}

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


void Shader::SetDirectionalLight(DirectionalLight* dLight)
{
	dLight->UseLight(_uniformDirectionalLight._uniformAmbientIntensity, _uniformDirectionalLight._uniformColor,
		_uniformDirectionalLight._uniformDiffuseIntensity, _uniformDirectionalLight._uniformDirectionalLight);
}

void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
	if( lightCount > MAX_POINT_LIGHTS) 
	{
		lightCount = MAX_POINT_LIGHTS;
	}

	glUniform1i(_uniformPointLightCount, lightCount);

	for(size_t i = 0 ; i < lightCount; i ++ ) 
	{
		pLight[i].UseLight(
			_uniformPointLight[i]._uniformAmbientIntensity, _uniformPointLight[i]._uniformColor,
			_uniformPointLight[i]._uniformDiffuseIntensity, _uniformPointLight[i]._uniformPosition,
			_uniformPointLight[i]._uniformCoefConstant, _uniformPointLight[i]._uniformCoefLinear, _uniformPointLight[i]._uniformCoefExponent);
	}
}

GLuint Shader::GetProjectionLocation()
{
	return _uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return _uniformModel;
}

GLuint Shader::GetViewLocation()
{
	return _uniformView;
}

GLuint Shader::GetEyePositionLocation()
{
	return _uniformEyePosition;
}

GLuint Shader::GetAmbientColorLocation()
{
	return _uniformDirectionalLight._uniformColor;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return _uniformDirectionalLight._uniformAmbientIntensity;
}

GLuint Shader::GetDiffuseIntensityLocation()
{
	return _uniformDirectionalLight._uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation()
{
	return _uniformDirectionalLight._uniformDirectionalLight;
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return _uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation()
{
	return _uniformShininess;
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
	_uniformView = 0;
}


Shader::~Shader() {
	ClearShader();
}
