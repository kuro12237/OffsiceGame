#include "ModelObjState.h"

ModelObjState::~ModelObjState()
{

}

void ModelObjState::Initialize(Model* state)
{
	SModelData ModelData_ = {};
	ModelData_ = ModelManager::GetObjData(state->GetModelHandle());
	state->SetTexHandle(ModelData_.material.handle);

	resource_.Vertex = (CreateResources::CreateBufferResource(sizeof(VertexData) * ModelData_.vertices.size()));
	resource_.Material = (CreateResources::CreateBufferResource(sizeof(Material)));

	resource_.BufferView = (CreateResources::VertexCreateBufferView(sizeof(VertexData) * ModelData_.vertices.size(), resource_.Vertex.Get(), int(ModelData_.vertices.size())));
	if (state->GetUseLight())
	{	
		resource_.Light = (CreateResources::CreateBufferResource(sizeof(LightData)));
	}

	ModelData_.vertices.clear();
}

void ModelObjState::Draw(Model* state, const WorldTransform& worldTransform, const ViewProjection& viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	SModelData ModelData_ = {};
	ModelData_ = ModelManager::GetObjData(state->GetModelHandle());
	memcpy(vertexData, ModelData_.vertices.data(), sizeof(VertexData) * ModelData_.vertices.size());

	materialData->shininess = 70.0f;
	materialData->color = state->GetColor();
	materialData->uvTransform = MatrixTransform::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());
	if (state->GetUseLight() != NONE)
	{
		LightData* lightData = nullptr;
		resource_.Light->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

		lightData->color = { 1.0f,1.0f,1.0f,1.0f };
		lightData->direction = testLightDirection;
		lightData->intensity = 1.0f;

	}

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	if (state->GetUseLight())
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Lighting;
	}

	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());
	commands.m_pList->SetGraphicsRootConstantBufferView(1, worldTransform.buffer_->GetGPUVirtualAddress());
	commands.m_pList->SetGraphicsRootConstantBufferView(2, viewprojection.buffer_->GetGPUVirtualAddress());
	DescriptorManager::rootParamerterCommand(3, state->GetTexHandle());
	if (state->GetUseLight())
	{
		commands.m_pList->SetGraphicsRootConstantBufferView(4, resource_.Light->GetGPUVirtualAddress());
		commands.m_pList->SetGraphicsRootConstantBufferView(5, viewprojection.buffer_->GetGPUVirtualAddress());
		DescriptorManager::rootParamerterCommand(6, LightingManager::dsvHandle());
		commands.m_pList->SetGraphicsRootConstantBufferView(7, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	}

	commands.m_pList->DrawInstanced(UINT(ModelData_.vertices.size()), 1, 0, 0);

}

ID3D12Resource* ModelObjState::CreateBufferResource(size_t sizeInbyte)
{
	ID3D12Device* device = DirectXCommon::GetInstance()->GetDevice();
	ID3D12Resource* result = nullptr;

	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC ResourceDesc{};
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInbyte;
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT hr = {};
	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&result));
	assert(SUCCEEDED(hr));

	return result;
}
