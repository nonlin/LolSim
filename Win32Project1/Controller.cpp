#include "stdafx.h"
#include <commctrl.h>
#include "Resource.h"
#include "Controller.h"
#include <string>
Controller::Controller()
{
	PCFreq = 0.0;
	CounterStart = 0;
	out.open("finalStats.txt");
	CounterCheck = 0;
	yi = shared_ptr<Champion> (new MasterYi);
	riven = shared_ptr<Champion>(new Riven);
	skarner = shared_ptr<Champion>(new Skarner);
	//champ1 = move(yi);
	//champ2 = move(riven);

	pChampions.emplace_back(yi);//0
	pChampions.emplace_back(skarner);//1
	pChampions.emplace_back(riven);//2
	champ1 = pChampions.at(choice1);
	champ2 = pChampions.at(choice2);
}

Controller::~Controller()
{

}
int Controller::choice1 = 0;
int Controller::choice2 = 1;
BOOL StopRequested;
CRITICAL_SECTION   BufferLock;
HANDLE baseAttackTimerHandler_C1 = NULL;
HANDLE baseAttackTimerHandler_C2 = NULL;
HANDLE healthRegenHandler = NULL;
HANDLE runTimeHandler = NULL;
HANDLE champ2_QHandeler = NULL, champ2_WHandeler = NULL;
HANDLE champ1_QHandeler = NULL;
HANDLE updateManaHandler = NULL;
HANDLE waitTimer = CreateWaitableTimer(NULL,TRUE,NULL);
CONDITION_VARIABLE yiQ;
LPCWSTR playSoundOnDeath = L"play Sounds\\hit.mp3";
LPCWSTR openSoundOnDeath = L"open Sounds\\hit.mp3 type mpegvideo";

struct Handles{

	HWND bar1,bar2,
		mBar1,mBar2,
		 h1, h2,
		 m1, m2,
		timeToDisplay;
	Controller thisObj;
}handle;
void Controller::runSim(HWND hHealthBar1, HWND hHealthBar2, HWND health1, HWND health2, HWND timeDisplay, HWND hManaBar1, HWND hManaBar2, HWND mana1, HWND mana2){

	champ1 = pChampions.at(choice1);
	champ2 = pChampions.at(choice2);
	handle.bar1 = hHealthBar1;
	handle.bar2 = hHealthBar2;
	handle.h1 = health1;
	handle.h2 = health2;
	handle.mBar1 = hManaBar1;
	handle.mBar2 = hManaBar2;
	handle.m1 = mana1;
	handle.m2 = mana2;
	handle.timeToDisplay = timeDisplay;

	InitializeConditionVariable(&yiQ);//so I can  use it
	InitializeCriticalSection(&BufferLock);// so I can use it
	//clock = GetCounter();
	//Have to think about which timer should call the deathCheck FUnction Cause not it seems it gets called to soon ? Or too late? 
	//update display, timer
	BOOL updateTimer = ::CreateTimerQueueTimer(
		&runTimeHandler,
		NULL,
		callToUpdateTime,
		this,
		0,
		100,
		WT_EXECUTEDEFAULT);
	//Health Update Timers
	BOOL healthRegenTimer = ::CreateTimerQueueTimer(
		&healthRegenHandler,
		NULL,
		callToHealthRegen,
		this,
		0,
		500,//seems to suggest that health regen is called faster than .5 seconds
		WT_EXECUTEDEFAULT);
	//Mana Update Timers
	BOOL manaUpdateTimer = ::CreateTimerQueueTimer(
		&updateManaHandler,
		NULL,
		callToUpdateMana,
		this,
		0,
		500,
		WT_EXECUTEDEFAULT);
	//Yi's Q timer
	/*BOOL champ1_Q = ::CreateTimerQueueTimer(
		&champ1_QHandeler,
		NULL,
		callChamp1Q,
		this,
		0,
		(DWORD) champ1->coolDownQ * 1000,
		WT_EXECUTEDEFAULT);
	///
	StopRequested = champ1_Q;*/
	//EnterCriticalSection(&BufferLock);
	//Yi's Basic Attacks timer
	BOOL champ1_Success = ::CreateTimerQueueTimer(
		&baseAttackTimerHandler_C1,
		NULL,
		callBaseAttackC1,
		this,
		0,
		(DWORD) (1000 / (champ1->attackSpeed)),
		WT_EXECUTEDEFAULT);

	//Skarners Q timer
	/*BOOL champ2_Q = ::CreateTimerQueueTimer(
			&champ2_QHandeler,
			NULL,
			callChamp2Q,
			this,
			0,
			(DWORD) champ2->coolDownQ * 1000,
			WT_EXECUTEDEFAULT);

	//Skarners W timer
	BOOL champ2_W = ::CreateTimerQueueTimer(
		&champ2_WHandeler,
		NULL,
		callChamp2W,
		this,
		0,
		(DWORD) champ2->coolDownW * 1000,
		WT_EXECUTEDEFAULT);*/
	//Skarners basic attack timer
	BOOL champ2_Success = ::CreateTimerQueueTimer(
		&baseAttackTimerHandler_C2,
		NULL,
		callBaseAttackC2,
		this,
		0,
		(DWORD) (1000 / (champ2->attackSpeed)),
		WT_EXECUTEDEFAULT);


	//LeaveCriticalSection(&BufferLock);
		
	CString str1;
	str1.Format(_T("%d"), clock);


}
//------------------------------------------------------------------------------------------------------------------
void Controller::basicAttackC1_TimeHandler() // called every elTime milliseconds
{	//Might not need to keep these functions as thread * Special note to self
	clock = GetCounter();
	thread basic_Attack_Champ_1(&Champion::basicAttack, champ1.get(), clock, champ2.get());
	basic_Attack_Champ_1.join();
	thread passive_Champ_1(&Champion::passive, champ1.get(), champ2.get());
	passive_Champ_1.join();

	

}

void CALLBACK Controller::callBaseAttackC1(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;
	//cout << "IF CHECK1: " << !(obj->champ1->isAlive() && obj->champ2->isAlive())<< endl << endl;
	stopTimeOnDeath(obj, baseAttackTimerHandler_C1);
	obj->basicAttackC1_TimeHandler();
}
//------------------------------------------------------------------------------------------------------------------
void Controller::basicAttackC2_TimeHandler() // called every elTime milliseconds
{
	clock = GetCounter();
	thread basic_Attack_Champ_2(&Champion::basicAttack, champ2.get(), clock, champ1.get());
	basic_Attack_Champ_2.join();
	thread passive_Champ_2(&Champion::passive, champ2.get(), champ1.get());
	passive_Champ_2.join();

}

void CALLBACK Controller::callBaseAttackC2(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg, Can't use "this"
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;
	//cout << "IF CHECK2: " << !(obj->champ1->isAlive() && obj->champ2->isAlive()) << endl << endl;
	stopTimeOnDeath(obj, baseAttackTimerHandler_C2);
	obj->basicAttackC2_TimeHandler();
}

//------------------------------------------------------------------------------------------------------------------
void Controller::updateRunTimeHandler() // called every elTime milliseconds
{
	StartCounter();
	checkDeath();
	update_Time(handle.timeToDisplay);

}

void CALLBACK Controller::callToUpdateTime(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;
	stopTimeOnDeath(obj,runTimeHandler);
	obj->updateRunTimeHandler();
}
//------------------------------------------------------------------------------------------------------------------

void Controller::updateHealthRegen() // called every elTime milliseconds
{
	thread regen_Champ_1(&Champion::healthRegeneration, champ2.get(), clock);
	regen_Champ_1.join();
	thread regen_Champ_2(&Champion::healthRegeneration, champ1.get(), clock);
	regen_Champ_2.join();
	updateChamp_1_HealthBar(handle.h1, handle.bar1);
	updateChamp_2_HealthBar(handle.h2, handle.bar2);

}

void CALLBACK Controller::callToHealthRegen(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;
	stopTimeOnDeath(obj, healthRegenHandler);
	obj->updateHealthRegen();
}
//------------------------------------------------------------------------------------------------------------------

void Controller::updateMana() // called every elTime milliseconds
{
	//thread regen_Champ_1(&Champion::healthRegeneration, champ2, clock);
	//regen_Champ_1.join();
	//thread regen_Champ_2(&Champion::healthRegeneration, champ1, clock);
	//regen_Champ_2.join();

	updateChamp_1_ManaBar(handle.m1, handle.mBar1);
	updateChamp_2_ManaBar(handle.m2, handle.mBar2);

}

void CALLBACK Controller::callToUpdateMana(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;
	stopTimeOnDeath(obj, updateManaHandler);
	obj->updateMana();
}
//------------------------------------------------------------------------------------------------------------------

void Controller::champ2Q() // called every elTime milliseconds
{
	champ2->q(champ1.get());
	//out << champ2->attackSpeed;
}

void CALLBACK Controller::callChamp2Q(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;
	stopTimeOnDeath(obj, champ2_QHandeler);
	obj->champ2Q();
}
//------------------------------------------------------------------------------------------------------------------

void Controller::champ2W() // called every elTime milliseconds
{
	champ2->w(GetCounter(), champ1.get());
	//out << champ2->attackSpeed;
}

void CALLBACK Controller::callChamp2W(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;
	stopTimeOnDeath(obj, champ2_WHandeler);
	obj->champ2Q();
}
//------------------------------------------------------------------------------------------------------------------

void Controller::champ1Q() // called every elTime milliseconds
{
	//When timer is off for  Q wait 1400ms for anything between Enter and LeaveCriticleSection, probably good for stun
	//if (StopRequested)
	//	SleepConditionVariableCS(&yiQ, &BufferLock, 1400);
	champ1->q(champ2.get());

}

void CALLBACK Controller::callChamp1Q(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{
	// This is used only to call QueueTimerHandler
	// Typically, this function is static member of CTimersDlg
	Controller* obj = (Controller*) lpParametar;
	obj = &handle.thisObj;

	stopTimeOnDeath(obj, champ1_QHandeler);
	obj->champ1Q();
}
//------------------------------------------------------------------------------------------------------------------

void Controller::StartCounter()
{//Where to call this for most accurate time, also hate having ot use CouterCheck
	LARGE_INTEGER li;
	CounterCheck++;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";
	if (CounterCheck == 1){
		PCFreq = double(li.QuadPart);

		QueryPerformanceCounter(&li);
		CounterStart = li.QuadPart;
	}
	else
		CounterCheck = 2;
}
double Controller::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return (double(li.QuadPart - CounterStart) / PCFreq);//+ 1 or 2 to correct for call order delay
}

INT Controller::getHealth1(){

	return (INT) champ1->health;
}

INT Controller::getHealth2(){

	return (INT) champ2->health;
}

///----------------ConSole---------------------------
void Controller::SetStdOutToNewConsole()
{
	int hConHandle;
	long lStdHandle;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long) GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;

	setvbuf(stdout, NULL, _IONBF, 0);
}
///---------------^ConSole^--------------------------

///---------------Update Health Bars------------------
void Controller::updateChamp_1_HealthBar(HWND healthNumUpdate, HWND barUpdadte){
	//updates num
	wchar_t health_1_toString[256];
	swprintf_s(health_1_toString, L"%d", getHealth1());
	SendMessage(healthNumUpdate, WM_SETTEXT, NULL, (LPARAM) health_1_toString);
	//updates bar
	INT percentHealth1 = (INT) ((getHealth1() / champ1->maxHealth) * 100);
	SendMessage(barUpdadte, PBM_SETPOS, (WPARAM) percentHealth1, 0L);
}

void Controller::updateChamp_2_HealthBar(HWND healthNumUpdate, HWND barUpdadte){
	//updates num
	wchar_t health_1_toString[256];
	swprintf_s(health_1_toString, L"%d", getHealth2());
	SendMessage(healthNumUpdate, WM_SETTEXT, NULL, (LPARAM) health_1_toString);
	//updates bar
	INT percentHealth2 = (INT)((getHealth2() / champ2->maxHealth) * 100);
	SendMessage(barUpdadte, PBM_SETPOS, (WPARAM) percentHealth2, 0L);

}
///--------------^Update Health Bars^-----------------

///---------------Update Mana Bars------------------
void Controller::updateChamp_1_ManaBar(HWND manaNumUPdate, HWND barUpdadte){
	//updates num
	wchar_t manaToString[256];
	swprintf_s(manaToString, L"%d", (INT) champ1->mana);
	SendMessage(manaNumUPdate, WM_SETTEXT, NULL, (LPARAM) manaToString);
	//updates bar
	INT percentMana = (INT) ((champ1->mana / champ1->maxMana) * 100);
	SendMessage(barUpdadte, PBM_SETPOS, (WPARAM) percentMana, 0L);
}

void Controller::updateChamp_2_ManaBar(HWND manaNumUPdate, HWND barUpdadte){
	//updates num
	wchar_t manaToString[256];
	swprintf_s(manaToString, L"%d", (INT) champ2->mana);
	SendMessage(manaNumUPdate, WM_SETTEXT, NULL, (LPARAM) manaToString);
	//updates bar
	INT percentMana = (INT) ((champ2->mana / champ2->maxMana) * 100);
	SendMessage(barUpdadte, PBM_SETPOS, (WPARAM) percentMana, 0L);

}
///--------------^Update Mana Bars^-----------------

void Controller::update_Time(HWND timeToScreen){
	//updates num
	wchar_t run_time[156];
	swprintf_s(run_time, L"%g", GetCounter());
	//updates time to screen
	//cout << GetCounter() << "TIME " << endl;
	SendMessage(timeToScreen, WM_SETTEXT, NULL, (LPARAM) run_time);

}

void Controller::stopTimeOnDeath(Controller* obj, HANDLE timerHandleToStop){

	if (!(obj->champ1.get()->isAlive() && obj->champ2.get()->isAlive())){
	
		if (!DeleteTimerQueueTimer(NULL, timerHandleToStop, NULL)){
			printf("2-Base Attack Timer failed (%d)\n", GetLastError());
			obj->out << "2-Base A Timer Failed " << GetLastError() << endl;
		}
		//DeleteTimerQueueEx(timerHandleToStop, NULL);
	}
}

void Controller::checkDeath(){
	
	LPCTSTR soundComplete = L"hit.wav";
	if (!(champ2->isAlive() && champ1->isAlive())){
	//	CounterStart = GetCounter();
		out << "Yi's Final Health: " << getHealth1();
		out.close();
	}
	if (!champ1->isAlive()){
		mciSendString(openSoundOnDeath, NULL, 0, 0);
		mciSendString(playSoundOnDeath, NULL, 0, 0);
		MessageBox(NULL, L"Champ 1 Has Died", L"Champ 2 Victor", MB_OK);
		cout << "Champ 1 Has Died" << endl << endl;
	}
	if (!champ2->isAlive()){
		mciSendString(openSoundOnDeath, NULL, 0, 0);
		mciSendString(playSoundOnDeath, NULL, 0, 0);
		MessageBox(NULL, L"Champ 2 Has Died", L"Champ 1 Victor", MB_OK);
		cout << "Champ 2 Has Died" << endl << endl;
	}

}
