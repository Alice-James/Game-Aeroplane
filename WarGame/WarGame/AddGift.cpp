#include "AddGift.h"


bool AddGift(vector<Gift*>& gift, IMAGE& Giftimg) {
	Gift* e = new Gift(Giftimg, abs(rand()) % (swidth - Giftimg.getwidth()));
	gift.push_back(e);
	return true;
}
