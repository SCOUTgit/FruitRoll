#pragma once
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Obstacle
{
public:
	Obstacle(string type);
	~Obstacle();

	string obstacleType;									// 장애물의 종류
	Sprite* obstacleImage;									// 장애물의 이미지
	bool stopping;											// 정지하는 중인지 체크

	bool CollideCheck(float x, float y, float size);		// 과일과의 충돌 체크
	void Stop();											// 정지하기
	void StopEnd();											// 정지 끝내기
	void Move();											// 앞으로 움직이기
	void Fall();											// 떨어지는 장애물일 경우 떨어지기
	bool CheckNeedDelete();									// 삭제해야하는지 확인
};