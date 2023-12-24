#include"CollisionManager.h"


void CollisionManager::CheckAllCollision()
{
	std::list<SphereCollider*>::iterator itrA = sphereColliders_.begin();

	for (; itrA != sphereColliders_.end(); ++itrA) {

		SphereCollider* colliderA = *itrA;

		std::list<SphereCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != sphereColliders_.end(); ++itrB) {
			SphereCollider* colliderB = *itrB;
		
			CheckBallCollisionPair(colliderA, colliderB);
		}
	}


	std::list<OBBCollider*>::iterator itrObbA = obbColliders_.begin();

	for (; itrObbA != obbColliders_.end(); ++itrObbA) {

	    OBBCollider* colliderA = *itrObbA;

		std::list<OBBCollider*>::iterator itrObbB = itrObbA;
		itrObbB++;
		for (; itrObbB != obbColliders_.end(); ++itrObbB) {
			OBBCollider* colliderB = *itrObbB;
			ChackObbCollisionPair(colliderA, colliderB);
		}

	}


}

void CollisionManager::ClliderClear()
{
	sphereColliders_.clear();
	obbColliders_.clear();
}

void CollisionManager::CheckBallCollisionPair(SphereCollider* cA, SphereCollider* cB) {

	
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) 
	{
		return;
	}

	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();

	float cAradious = cA->GetRadious();
	float cBradious = cB->GetRadious();

	if (CheckBallCollosion(cApos, cAradious, cBpos, cBradious)) {
		cA->OnCollision(cB->GetId());
		cB->OnCollision(cA->GetId());
	}
}


bool CollisionManager::CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2) {
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = vr1 + vr2;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;
}


// OBBの設定

void CollisionManager::ChackObbCollisionPair(OBBCollider* oA, OBBCollider* oB)
{
	if ((oA->GetCollosionAttribute() & oB->GetCollisionMask()) == 0 ||
		(oA->GetCollisionMask() & oB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	OBB_param obbA = SettingOBBProperties(oA);
	OBB_param obbB = SettingOBBProperties(oB);


	// 衝突判定
	if (ChackObbCollision(obbA,obbB))
	{
		oA->OnCollision(oB->GetID());
		oB->OnCollision(oA->GetID());
	}
}


bool CollisionManager::ChackObbCollision(OBB_param oA, OBB_param oB)
{
	// 分離軸テスト
	for (const auto& axis : oA.orientations) {
		if (!TestAxis(axis, oA, oB)) {
			return false;
		}
	}

	for (const auto& axis : oB.orientations) {
		if (!TestAxis(axis, oA, oB)) {
			return false;
		}
	}

	// OBB1の軸とOBB2の軸に垂直な軸をテスト
	for (const auto& axis : {
			Vector3{oA.orientations[1].x * oB.orientations[2].x - oA.orientations[2].x * oB.orientations[1].x,
					oA.orientations[1].y * oB.orientations[2].y - oA.orientations[2].y * oB.orientations[1].y,
					oA.orientations[1].z * oB.orientations[2].z - oA.orientations[2].z * oB.orientations[1].z},
			Vector3{oA.orientations[2].x * oB.orientations[0].x - oA.orientations[0].x * oB.orientations[2].x,
					oA.orientations[2].y * oB.orientations[0].y - oA.orientations[0].y * oB.orientations[2].y,
					oA.orientations[2].z * oB.orientations[0].z - oA.orientations[0].z * oB.orientations[2].z},
			Vector3{oA.orientations[0].x * oB.orientations[1].x - oA.orientations[1].x * oB.orientations[0].x,
					oA.orientations[0].y * oB.orientations[1].y - oA.orientations[1].y * oB.orientations[0].y,
					oA.orientations[0].z * oB.orientations[1].z - oA.orientations[1].z * oB.orientations[0].z} 
		})
	{
		if (!TestAxis(axis, oA, oB)) {
			return false;
		}
	}

	return true;
}

bool CollisionManager::TestAxis(const Vector3& axis, const OBB_param& obb1, const OBB_param& obb2)
{
	// OBBの射影を計算
	auto projection1 = obbProjection(obb1, axis);
	auto projection2 = obbProjection(obb2, axis);

	// 射影が重なっているかチェック
	return projectionOverlap(projection1, projection2);
}

OBB_param CollisionManager::SettingOBBProperties(OBBCollider* c)
{
	OBB_param result{};

	result.center = c->GetWorldPosition();

	Matrix4x4 rotateMat = MatrixTransform::RotateXYZMatrix(c->GetRotate().x, c->GetRotate().y, c->GetRotate().z);
	result.orientations[0].x = rotateMat.m[0][0];
	result.orientations[0].y = rotateMat.m[0][1];
	result.orientations[0].z = rotateMat.m[0][2];
	result.orientations[1].x = rotateMat.m[1][0];
	result.orientations[1].y = rotateMat.m[1][1];
	result.orientations[1].z = rotateMat.m[1][2];
	result.orientations[2].x = rotateMat.m[2][0];
	result.orientations[2].y = rotateMat.m[2][1];
	result.orientations[2].z = rotateMat.m[2][2];

	result.halfSize = {
		.x = c->GetSize().x / 2.0f,
		.y = c->GetSize().y / 2.0f,
		.z = c->GetSize().z / 2.0f,
	};

	return result;
}


bool CollisionManager::projectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2)
{
	// 射影が重なっているかチェック
	return projection1.second >= projection2.first && projection2.second >= projection1.first;
}

std::pair<float, float> CollisionManager::obbProjection(const OBB_param& obb, const Vector3& axis)
{

	float val = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z); // 正規化
	float newAxis = 0.0f;
	newAxis = newAxis / val;

	// OBB上の頂点を取得
	std::array<Vector3, 8> vertices{};
	for (int i = 0; i < 8; ++i) {
		Vector3 sign = { (i & 1) ? 1.0f : -1.0f, (i & 2) ? 1.0f : -1.0f, (i & 4) ? 1.0f : -1.0f };
		vertices[i] = {
			obb.center.x + obb.orientations[0].x * sign.x * obb.halfSize.x +
						  obb.orientations[1].x * sign.y * obb.halfSize.y +
						  obb.orientations[2].x * sign.z * obb.halfSize.z,
			obb.center.y + obb.orientations[0].y * sign.x * obb.halfSize.x +
						  obb.orientations[1].y * sign.y * obb.halfSize.y +
						  obb.orientations[2].y * sign.z * obb.halfSize.z,
			obb.center.z + obb.orientations[0].z * sign.x * obb.halfSize.x +
						  obb.orientations[1].z * sign.y * obb.halfSize.y +
						  obb.orientations[2].z * sign.z * obb.halfSize.z
		};
	}

	// 頂点を軸に射影
	std::array<float, 8> projections{};
	for (int i = 0; i < 8; ++i) {
		projections[i] = vertices[i].x * axis.x + vertices[i].y * axis.y + vertices[i].z * axis.z;
	}

	auto minmax = std::minmax_element(projections.begin(), projections.end());
	return std::make_pair(*minmax.first, *minmax.second);
}
