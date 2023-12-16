#include "Model.h"

Model::~Model()
{
}


void Model::CreateObj(SModelData modeldata)
{
	modelData_ = modeldata;

	buffer_ = CreateBufferResource(
		sizeof(VertexData) * modelData_.vertices.size());

	BufferView =
		CreateResources::VertexCreateBufferView(
			sizeof(VertexData) * modelData_.vertices.size(),
			buffer_.Get(),
			int(modelData_.vertices.size()
				));
}

void Model::CommandCallPipelineVertex(bool LightingFlag)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	LightingFlag_ = LightingFlag;
	if (LightingFlag_)
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Lighting;
	}

	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &BufferView);

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::Draw(const ViewProjection& viewprojection)
{

	VertexData* vertexData = nullptr;
	
	buffer_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	memcpy(vertexData, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	
	if (LightingFlag_)
	{
		commands.m_pList->SetGraphicsRootConstantBufferView(4, viewprojection.buffer_->GetGPUVirtualAddress());
		DescriptorManager::rootParamerterCommand(5, LightingManager::dsvHandle());
		commands.m_pList->SetGraphicsRootConstantBufferView(6, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	}

	commands.m_pList->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);
	
}



