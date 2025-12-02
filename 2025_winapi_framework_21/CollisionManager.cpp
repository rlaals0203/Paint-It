#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
void CollisionManager::Update()
{
	for (UINT Row = 0; Row < (UINT)Layer::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)Layer::END; ++Col)
		{
			if (m_objectLayer[Row] & (1 << Col))
			{
				//int a = 0;
				CollisionLayerUpdate((Layer)Row, (Layer)Col);
			}
		}
	}
}

void CollisionManager::CheckLayer(Layer _left, Layer _right)
{
	// 작은쪽을 행으로 씁시다.
	// 작은 값을 LAYER의 행으로, 큰 값을 열
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);
	//m_arrLayer[Row];
	//Col;

	//// 비트 연산
	// 체크가 되어있다면
	if (m_objectLayer[Row] & (1 << Col))
	{
		// 체크 풀기
		m_objectLayer[Row] &= ~(1 << Col);
	}
	// 체크가 안되어있다면r
	else
	{
		m_objectLayer[Row] |= (1 << Col);
	}
	int a = 0;
}

void CollisionManager::CheckReset()
{
	// 메모리 초기화
	memset(m_objectLayer, 0, sizeof(UINT) * (UINT)Layer::END);
}

void CollisionManager::CollisionLayerUpdate(Layer _left, Layer _right)
{
	std::shared_ptr<Scene> pCurrentScene = GET_SINGLE(SceneManager)->GetCurScene();
	const vector<Object*>& vecLeftLayer = pCurrentScene->GetLayerObjects(_left);
	const vector<Object*>& vecRightLayer = pCurrentScene->GetLayerObjects(_right);
	std::unordered_map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeftLayer.size(); ++i)
	{
		Collider* pLeftCollider = vecLeftLayer[i]->GetComponent<Collider>();
		// 충돌체 없는 경우
		if (nullptr == pLeftCollider)
			continue;
		for (size_t j = 0; j < vecRightLayer.size(); j++)
		{
			Collider* pRightCollider = vecRightLayer[j]->GetComponent<Collider>();
			// 충돌체가 없거나, 자기자신과의 충돌인 경우
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			// 두 충돌체로만 만들 수 있는 ID
			ULONGLONG colliderID = MakePairKey(pLeftCollider->GetID(), pRightCollider->GetID());

			iter = m_mapCollisionInfo.find(colliderID);
			// 이전 프레임 충돌한 적 없다.
			if (iter == m_mapCollisionInfo.end())
			{
				// 충돌 정보가 미등록된 상태인 경우 등록(충돌하지 않았다로)
				m_mapCollisionInfo.insert({ colliderID, false });
				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = m_mapCollisionInfo.find(colliderID);
			}

			// 충돌여부 확인
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// 이전에도 충돌중
				if (iter->second)
				{
					if (vecLeftLayer[i]->GetIsDead() || vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->ExitCollision(pRightCollider);
						pRightCollider->ExitCollision(pLeftCollider);
						iter->second = false;
					}
					else
					{
						pLeftCollider->StayCollision(pRightCollider);
						pRightCollider->StayCollision(pLeftCollider);
					}
				}
				else // 이전에 충돌 x
				{
					if (!vecLeftLayer[i]->GetIsDead() && !vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->EnterCollision(pRightCollider);
						pRightCollider->EnterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else // 충돌 안하네?
			{
				if (iter->second) // 근데 이전에 충돌중
				{
					pLeftCollider->ExitCollision(pRightCollider);
					pRightCollider->ExitCollision(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}

}

float CollisionManager::Dot(Vec2 a, Vec2 b)
{
	//내적 구하기
	return a.x * b.x + a.y * b.y;
}

bool CollisionManager::IsCollision(Collider* A, Collider* B)
{

#pragma region 이전 코드
	/*Vec2 leftPos = A->GetUpdatedPos();
	Vec2 rightPos = B->GetUpdatedPos();
	Vec2 leftSize = A->GetSize();
	Vec2 rightSize = B->GetSize();
	return (fabsf(rightPos.x - leftPos.x) < (leftSize.x + rightSize.x) / 2.f
		&& fabsf(rightPos.y - leftPos.y) < (leftSize.y + rightSize.y) / 2.f);*/
#pragma endregion

	// 중심
	Vec2 cA = A->GetUpdatedPos();
	Vec2 cB = B->GetUpdatedPos();

	// 크기 → 반너비
	Vec2 sA = A->GetSize() * 0.5f;
	Vec2 sB = B->GetSize() * 0.5f;

	// 회전 값 => 라디안으로 변경후 저장
	float rA = A->GetRotation() * PI / 180;
	float rB = B->GetRotation() * PI / 180;

	// A의 로컬축
	// A를 기준으로 x축과 y축의 방향이 어디로 되어있는지
	// 예)회전 0도일 때 X축 = (1, 0), Y축 = (0, 1)
	//회전이 90도일때 X축 = (0, 1), Y축 = (-1, 0)
	
	//x축
	Vec2 uA_x = { cosf(rA), sinf(rA) };
	//y축 (x축으로부터 반시계 방향으로 90도 회전한 값)
	Vec2 uA_y = { -sinf(rA), cosf(rA) };
	
	//B의 로컬축
	//x축
	Vec2 uB_x = { cosf(rB), sinf(rB) };
	//y축 (x축으로부터 반시계 방향으로 90도 회전한 값)
	Vec2 uB_y = { -sinf(rB), cosf(rB) };

	//중심간의 거리
	Vec2 d = { cB.x - cA.x, cB.y - cA.y };

	Vec2 axes[4] = { uA_x, uA_y, uB_x, uB_y };

	//축 오차 줄이기 및 정규화 값 0확인
	const float EPS = 1e-6f;

	for (int i = 0; i < 4; ++i)
	{
		Vec2 axis = axes[i];

		// 정규화
		float len = sqrtf(axis.x * axis.x + axis.y * axis.y);
		if (len < EPS)
			continue;

		axis.x /= len;
		axis.y /= len;

		//fabsf는 절대값을 구하는 함수

		// 중심 거리의 투영
		float dist = fabsf(Dot(d, axis));

		// A의 투영 반경
		float rAproj =
			fabsf(Dot(uA_x, axis)) * sA.x +
			fabsf(Dot(uA_y, axis)) * sA.y;

		// B의 투영 반경
		float rBproj =
			fabsf(Dot(uB_x, axis)) * sB.x +
			fabsf(Dot(uB_y, axis)) * sB.y;

		// 축 안겹침
		if (dist > rAproj + rBproj + EPS)
			return false;
	}
	
	//모든 축의 겹침 즉 충돌
	return true;
}

ULONGLONG CollisionManager::MakePairKey(UINT a, UINT b)
{
	// 좌우 순서를 무의미하게: 작은 값을 lo, 큰 값을 hi
	COLLIDER_ID id = {};
	id.lo_ID = (a < b) ? a : b;
	id.hi_ID = (a < b) ? b : a;
	return id.ID;
}
