#include "Game3dObject.h"

void Game3dObject::Create()
{
	MaterialBuffer_ = nullptr;
	
	MaterialBuffer_ = CreateResources::CreateBufferResource(sizeof(Material), MaterialBuffer_.Get());
}

void Game3dObject::SetModel(uint32_t index)
{
	if (prevModelIndex_ != index)
	{
	    model_ = ModelManager::GetModel(index);
		texHandle_ = ModelManager::GetObjData(index).material.handle;
	}
	prevModelIndex_ = index;
}

void Game3dObject::Draw(const WorldTransform& worldTransform, const ViewProjection& view)
{
	if (model_ == nullptr)
	{
		return;
	}

	//Material転送
	Material * materialData;
	MaterialBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	materialData->shininess = shininess;
	materialData->color = color_;
	materialData->uvTransform = MatrixTransform::AffineMatrix(uvScale_, uvRotate, uvTranslate);

	//パイプラインつむ
	model_->CommandCallPipelineVertex(true);
	Commands command = DirectXCommon::GetInstance()->GetCommands();

	command.m_pList->SetGraphicsRootConstantBufferView(0, MaterialBuffer_->GetGPUVirtualAddress());
	command.m_pList->SetGraphicsRootConstantBufferView(1, worldTransform.buffer_->GetGPUVirtualAddress());
	command.m_pList->SetGraphicsRootConstantBufferView(2, view.buffer_->GetGPUVirtualAddress());
	DescriptorManager::rootParamerterCommand(3, texHandle_);
	model_->Draw(view);
}
