#pragma once
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Waterdrop
{
public:
	Waterdrop();
	~Waterdrop();

	Sprite* waterdropImage;									// 물방울 이미지
	bool stopping;											// 정지하는 중인지 체크
	bool needDelete;										// 삭제해야하는지

	bool CollideCheck(float x, float y, float size);		// 과일과의 충돌 체크
	void Move();											// 앞으로 움직이기
	void Stop();											// 정지하기
	void StopEnd();											// 정지 끝내기
};

