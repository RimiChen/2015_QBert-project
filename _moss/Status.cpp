#include "Status.h"

void GameStatus::updateNumber(){
	digits[0] = score/10000;
	digits[1] = (score%10000)/1000;
	digits[2] = (score%1000)/100;
	digits[3] = (score%100)/10;
	digits[4] = score%10;
}