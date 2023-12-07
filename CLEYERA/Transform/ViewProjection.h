#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"MatrixTransform.h"
#include"CreateResource.h"

struct ViewProjection {
	
	~ViewProjection() {};

	/// <summary>
	/// 定数バッファ
	/// </summary>
	ComPtr<ID3D12Resource>buffer_ = nullptr;

	/// <summary>
	/// GPUに送る用
	/// </summary>
	TransformationViewMatrix* BufferMatrix_ = nullptr;

	Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	Vector3 translation_ = { 0.0f,0.0f,-15.0f };
	Matrix4x4 matView_{};
	Matrix4x4 matProjection_{};
	Matrix4x4 OrthographicMatrix_{};

	float fov_ = 0.45f;
	float aspectRatio_ = float(WinApp::GetkCilientWidth()) / float(WinApp::GetkCilientHeight());

	float nearClip_ = 0.1f;
	float farClip_ = 1000.0f;

	void Initialize(Vector3 r={0.0f,0.0f,0.0f},Vector3 t={0.0f,0.0f,-5.0f});

	void UpdateMatrix();

	void CreateBuffer();

	void Map();
	void UnMap();
	void TransfarMatrix();	
};