#pragma once
#include "Champion.h"

class MasterYi : virtual public Champion
{
public:
	MasterYi();
	~MasterYi();
	bool isAlive();
	UINT passive(Champion*);
	void q(Champion* enemy);
	void w(double time, Champion* enemy);
	double dealDamage(double,double,  Champion*);
	void getDamage(double,double);
	void healthRegeneration(double);
	void  basicAttack(double, Champion*);
	int attackCounter;
};

