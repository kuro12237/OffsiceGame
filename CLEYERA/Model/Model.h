#pragma once
#include"Graphics/TextureManager/TextureManager.h"
#include"Light/LightingManager.h"

#include"GraphicsPipelineManager.h"

#include"WorldTransform.h"
#include"ViewProjection.h"


class Model
{
public:
	Model() {};
	~Model();
	

	void CreateObj(SModelData modeldata);

	void CommandCallPipelineVertex(bool LightingFlag);

	void Draw( const ViewProjection &viewprojection);

#pragma region Get



	SModelData GetModelData() { return modelData_; }

	void SetFilePath(string path) { filePath_ = path; }

	//Light GetLight() { return testLight_; }
#pragma endregion 

private:
	SModelData modelData_;

	ComPtr<ID3D12Resource>buffer_ = nullptr;
	D3D12_VERTEX_BUFFER_VIEW BufferView{};

	bool LightingFlag_ = false;
	string filePath_;
};

