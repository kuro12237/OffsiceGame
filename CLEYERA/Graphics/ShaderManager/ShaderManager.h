#pragma once
#include"Pch.h"
#include"LogManager.h"
struct  SShaderMode
{
	ComPtr<IDxcBlob> vertexBlob;
	ComPtr<IDxcBlob> pixelBlob;
};
struct SDXCProperty
{
	ComPtr<IDxcIncludeHandler>m_pIncludeHandler;
	ComPtr<IDxcUtils> m_pUtils;
	ComPtr<IDxcCompiler3> m_pCompiler;
};

struct SShaders
{
	SShaderMode shape;
	SShaderMode sprite3d;
	SShaderMode sprite2d;
	SShaderMode light;
	SShaderMode Particle;

};

class ShaderManager
{
public:

	static ShaderManager* Getinstance();

	static void Initialize();

#pragma region Get
	SShaders GetShader() { return ShaderManager::Getinstance()->shaders_; }

#pragma endregion
private:

	/// <summary>
	/// �V�F�[�_�[�̃R���p�C���֐�
	/// </summary>
	static IDxcBlob* CompilerShaderFanc(
		const std::wstring& filePath,
		const wchar_t* profile
	);

	static void DxcCreate();
	static void includeHandlerSetting();

	static void ShaderComples();

	static void ShapeShader();
	static void Sprite3dShader();
	static void Sprite2dShader();
	static void LightShader();
	static void ParticleShader();


	SDXCProperty dxc = {};
	SShaders shaders_ = {};

};

