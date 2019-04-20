#pragma once
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Board
{
public:
	Board();
	~Board();

	Sprite* boardImage;										// 물방울 이미지
	bool stopping;											// 정지하는 중인지 체크
	bool madeBoard;											// 다음 나무판자를 만들었는지 체크

	void Move();											// 앞으로 움직이기
	void Stop();											// 정지하기
	void StopEnd();											// 정지 끝내기
	bool CheckNeedMake();									// 다음 나무판자를 만들어야하는지 확인하기
	bool CheckNeedDelete();									// 삭제해야하는지 확인하기
};

