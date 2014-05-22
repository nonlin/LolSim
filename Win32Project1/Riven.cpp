#include "stdafx.h"
#include "Riven.h"


Riven::Riven()
{
	levelMultiplier = 1;
	healthM = 86;
	healthRegenM = 0.5;
	manaM = 0;
	manaRegenM = 0.0;
	ADM = 3;
	ASM = 3.5;
	ARM = 3.2;
	MRM = 1.25;
	/////////////
	alive = true;
	attackCounter = 0;
	health = 414 + (levelMultiplier * healthM);
	maxHealth = 444 + (levelMultiplier * healthM);
	healthRegen = 2.5 + (levelMultiplier * healthRegenM);
	mana = 180 + (levelMultiplier * manaM);
	maxMana = 180 + (levelMultiplier * manaM);
	manaRegen = 6.5 + (levelMultiplier * manaRegenM);
	range = 125;
	attackDamage = 51 + (levelMultiplier * ADM);
	attackSpeed = 0.625;
	attackSpeed = floor((attackSpeed + (((levelMultiplier * ASM) / 100) * attackSpeed)) * 1000 + 0.5) / 1000;
	armor = 19 + (levelMultiplier * ARM);
	magicRes = 30 + (levelMultiplier * MRM);
	magicDamage = 0;
	coolDownQ = 18;
	coolDownW = 35;
	coolDownE = 18;
	coolDownR = 75;
	damageOut = 0;
	physicalDamage = 0;
	critChance = 0;
	name = L"Riven";
	out.open("rivenLog.txt");

}


Riven::~Riven()
{
}

UINT Riven::passive(Champion* enemy){


	return 0;
}

void Riven::q(Champion* enemy){

	if (mana >= 70){
		mana = mana - 70;
		physicalDamage = 25 + (attackDamage);
		dealDamage(physicalDamage, 0, enemy);
	}
}

void Riven::w(double time, Champion* enemy){

}

void Riven::basicAttack(double clock, Champion* enemy){

	range = 125;
	clock = floor(clock * 10 + 0.5) / 10;
	out << "TIME TO ATTCK: " << clock << endl;
	//cout << "TIME TO ATTACK: " << clock << endl;
	coolDownQ = coolDownQ - 1;
	dealDamage(attackDamage, 0, enemy);
	attackCounter++;
}

double Riven::dealDamage(double damage, double magicDamage, Champion* enemy){


	out << "Master Yi Attacking with " << damage << " damage" << endl;
	cout << "Master Yi Attacking with " << damage << " damage" << endl;
	enemy->getDamage(damage, magicDamage);


	return damageOut;
}

void Riven::getDamage(double damage, double magicDamage){

	if (armor >= 0)
		damage = damage * (100 / (100 + armor));
	else
		damage = damage * (2 - (100 / (100 + armor)));

	if (magicRes >= 0)
		magicDamage = magicDamage * (100 / (100 + magicRes));
	else
		magicDamage = magicDamage * (2 - (100 / (100 + magicRes)));

	if (health > 0){
		health = health - damage;
		health = health - magicDamage;
	}
	char str[256];

	sprintf_s(str, "Skarner Recieved Damage of", damage);
	OutputDebugString((LPCWSTR) str);
	cout << "Riven Recieved Damage of" << damage << endl;
	out << "Riven Recieved Damage of" << damage << endl;
}

void Riven::healthRegeneration(double clock){

	//out << "Calling health regen." << endl;
	if (health < maxHealth)
		health = health + (healthRegen / 5);

}

bool Riven::isAlive(){

	if (health <= 0){

		return false;
	}
	else
		return true;

}
