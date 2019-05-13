#pragma once
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Board
{
public:
	Board();
	~Board();

	Sprite* boardImage;			// 나무판자 이미지
	bool stopping;				// 정지하는 중인지 체크
	float width;				// 나무판자의 가로 길이
	float height;				// 나무판자의 세로 길이
	Size visibleSize;			// 해상도

	void Move();				//앞으로 움직이기
	void Remove();				// 스폰장소로 이동하기
	void Stop();				// 정지하기
	void StopEnd();				// 정지 끝내기
	bool CheckNeedDelete();		// 삭제해야하는지 확인하기
};

