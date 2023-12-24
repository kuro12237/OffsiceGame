#pragma once
#include"./Collider/SphereCollider.h"
#include"./Collider/OBBCollider.h"
#include"Pch.h"
#include "VectorTransform.h"
#include"MatrixTransform.h"

class CollisionManager {
public:

	void CheckAllCollision();
	void ClliderClear();


	void SphereClliderPush(SphereCollider* collider) { sphereColliders_.push_back(collider); }
	
	void ObbColliderPush(OBBCollider* collider) { obbColliders_.push_back(collider); }

private:
	void CheckBallCollisionPair(SphereCollider* cA, SphereCollider* cB);
	bool CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2);

	void ChackObbCollisionPair(OBBCollider* oA, OBBCollider* oB);
	bool ChackObbCollision(OBB_param oA, OBB_param oB);

	OBB_param SettingOBBProperties(OBBCollider* c);

	// 射影の重複チェック
	bool TestAxis(const Vector3& axis, const OBB_param& obb1, const OBB_param& obb2);

	// 実際に重なってるかの計算
	bool projectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2);
	std::pair<float, float> obbProjection(const OBB_param& obb, const Vector3& axis);


	std::list<SphereCollider*> sphereColliders_;
	std::list<OBBCollider*> obbColliders_;
};
