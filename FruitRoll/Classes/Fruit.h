#pragma once
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Fruit
{
public:
	Fruit(string type);
	~Fruit();

	string fruitType;			// 과일의 종류
	bool jumping;				// 점프하는 중인지 체크
	bool stopping;				// 정지하는 중인지 체크
	Sprite* fruitImage;			// 과일의 이미지
	Animation* fruitAnimation;	// 과일애니메이션

	void MakeSprite();			// 애니메이트 생성
	void Jump();				// 점프하기
	void JumpEnd();				// 점프 끝내기
	void Stop();				// 정지하기
	void StopEnd();				// 정지 끝내기
	void Rotate();				// 구르기
	void PlayAnimation();				// 충돌 시 애니메이션 실행
};