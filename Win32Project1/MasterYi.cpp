#include "stdafx.h"
#include "MasterYi.h"


MasterYi::MasterYi()
{
	levelMultiplier = 1;
	healthM = 92;
	healthRegenM = 0.65;
	manaM = 42;
	manaRegenM = 0.45;
	ADM = 3;
	ASM = 2;
	ARM = 3;
	MRM = 1.25;
	/////////////
	alive = true;
	attackCounter = 0;
	health = 444 + (levelMultiplier * healthM);
	maxHealth = 444 + (levelMultiplier * healthM);
	healthRegen = 6.5 + (levelMultiplier * healthRegenM);
	mana = 180 + (levelMultiplier * manaM);
	maxMana = 180 + (levelMultiplier * manaM);
	manaRegen = 6.5 + (levelMultiplier * manaRegenM);
	range = 125;
	attackDamage = 55 + (levelMultiplier * ADM);
	attackSpeed = 0.679;
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
	name = L"Master Yi";
	out.open("yiLog.txt");

}


MasterYi::~MasterYi()
{
}

UINT MasterYi::passive(Champion* enemy){

	double critAttack = attackDamage * .50;
	if (attackCounter == 4){

		cout << "Yi Passive 1st Attack!" << endl;
		out << "Yi Passive 1st Attack!" << endl;
		dealDamage(attackDamage, 0,enemy);

		cout << "2nd Crit!" << endl<<endl<<endl;
		out << "2nd Crit!" << endl << endl << endl;
		dealDamage(critAttack, 0,enemy);
		attackCounter = 0;
	}
	return 0;
}

void MasterYi::q(Champion* enemy){
	
	if (mana >= 70){
		mana = mana - 70;
		physicalDamage = 25 + (attackDamage);
		dealDamage(physicalDamage, 0,enemy);
	}
}

void MasterYi::w(double time, Champion* enemy){

}

void MasterYi::basicAttack(double clock, Champion* enemy){

	range = 125;
	clock = floor(clock * 10 + 0.5) / 10;
	out << "TIME TO ATTCK: " << clock << endl;
	//cout << "TIME TO ATTACK: " << clock << endl;
	coolDownQ = coolDownQ - 1;
	dealDamage(attackDamage, 0,enemy);
	attackCounter++;
}

double MasterYi::dealDamage(double damage, double magicDamage, Champion* enemy){


	out << "Master Yi Attacking with " << damage << " damage" << endl;
	cout << "Master Yi Attacking with " << damage << " damage" << endl;
	enemy->getDamage(damage, magicDamage);


	return damageOut;
}

void MasterYi::getDamage(double damage, double magicDamage){

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
	cout << "Yi Recieved Damage of" << damage << endl;
	out << "Yi Recieved Damage of" << damage << endl;
}

void MasterYi::healthRegeneration(double clock){

		//out << "Calling health regen." << endl;
		if (health < maxHealth)
			health = health + (healthRegen / 10);
	
}

bool MasterYi::isAlive(){

	if (health <= 0){

		return false;
	}
	else
		return true; 

}
