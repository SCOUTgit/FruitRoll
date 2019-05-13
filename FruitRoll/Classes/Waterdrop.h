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
	bool moving;											// 움직이는 중인지 체크
	float width;											// 물방울의 가로 길이
	float height;											// 물방울의 세로 길이
	Size visibleSize;										// 해상도

	void Remove();											// 스폰장소로 이동하기
	void Move();											// 앞으로 움직이기
	void Stop();											// 정지하기
	void StopEnd();											// 정지 끝내기
	bool CheckNeedDelete();								// 삭제해야하는지 확인
};
