#pragma once
#include"Pch.h"

/// <summary>
/// OBB
/// </summary>
struct OBB_param {
	Vector3 center;			   // !< 中心点
	Vector3 orientations[3]{}; // !< 座標軸。正規化・直交必須
	Vector3 halfSize;          // !< 座標軸方向の長さの半分。中心から面までの距離
};

class OBBCollider {

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	virtual void OnCollision(uint32_t id) = 0;

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	virtual Vector3 GetWorldPosition() = 0;

#pragma region Size

	/// <summary>
	/// Sizeの取得
	/// </summary>
	virtual Vector3 GetSize() = 0;

	/// <summary>
	/// Sizeの設定
	/// </summary>
	void SetSize(Vector3 size) { size_ = size; }

#pragma endregion

#pragma region Rotate

	/// <summary>
	/// Rotateの取得
	/// </summary>
	Vector3 GetRotate() { return rotate_; }

	/// <summary>
	/// Rotateの設定
	/// </summary>
	void SetRotate(Vector3 rotate) { rotate_ = rotate; }

#pragma endregion

#pragma region Get

	/// <summary>
    /// IDの取得
    /// </summary>
	uint32_t GetID() { return id_; }

	/// <summary>
	/// collisionAttributeの取得
	/// </summary>
	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }

	/// <summary>
	/// CollisionMaskの取得
	/// </summary>
	uint32_t GetCollisionMask() const { return CollisionMask_; }

#pragma endregion

#pragma region Set

	/// <summary>
	/// IDの設定
	/// </summary>
	void SetID(uint32_t id) { id_ = id; }
	
	/// <summary>
    /// collisionAttributeの設定
    /// </summary>
	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }

	/// <summary>
	/// CollisionMaskの設定
	/// </summary>
	void SetCollisionMask(uint32_t collisionMask) { CollisionMask_ = collisionMask; }

#pragma endregion


private:

	OBB_param obb_{};

	uint32_t id_ = 0xffffffff;
	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t CollisionMask_ = 0xffffffff;

	Vector3 size_ = { 1.0f, 1.0f ,1.0f };
	Vector3 rotate_ = { 0.0f, 0.0f, 0.0f };
};