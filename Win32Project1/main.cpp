
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include "Controller.h"

#define ID_Save 1
#define ID_Load 2
#define ID_Exit 3
#define ID_Undo 4
#define ID_Redo 5
#define ID_VWS 6
PROPSHEETHEADER	m_PropSheet;
PROPSHEETPAGE m_psp[2];

HWND runButton;
void propertyPages(HINSTANCE);
int c1 = 0;
int c2 = 0;
Controller* con = new Controller;
//CSpinButtonCtrl spinCtrl;
//---------------------------------------------------------------------------
HWND hWnd;
HWND hHealthBar1, hHealthBar2, champ_Health_1, champ_Health_2, champ_Name_1, champ_Name_2, run_Time,
hManaBar1, hManaBar2, champ_Mana_1, champ_Mana_2;
HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void SetStdOutToNewConsole();
//---------------------------------------------------------------------------
struct simData {

	HWND hProgressWindow1_Struct,
		hProgressWindow2_Struct,
		champ_Health_1_Struct,
		champ_Health_2_Struct;
	Controller* dCon;
} data;
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;
	//DLGPROC MyDLGProc;
	
	propertyPages(hInstance);//loads property pages
	InitCommonControls();// possible to allow for controlls maybe MFC Controlls, also for modern visual
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1),
		hWnd, reinterpret_cast<DLGPROC>(DlgProc));
	
	//spinCtrl.SetRange32(1, 18);
	return FALSE;
}
//---------------------------------------------------------------------------

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	HMENU hMenubar = CreateMenu();
	HMENU hFile = CreateMenu();
	HMENU hEdit = CreateMenu();
	HMENU hHelp = CreateMenu();

	INITCOMMONCONTROLSEX InitCtrlEx;
	//HDC hdc;
	//PAINTSTRUCT ps;
	//CHamp 1 Stats To String
	CString AS_1;
	AS_1.Format(_T("%g"), con->champ1->attackSpeed);
	CString AD_1;
	AD_1.Format(_T("%g"), con->champ1->attackDamage);
	CString HR_1;
	HR_1.Format(_T("%g"), con->champ1->healthRegen);
	CString MD_1;
	MD_1.Format(_T("%g"), con->champ1->magicDamage);
	CString MG_1;
	MG_1.Format(_T("%g"), con->champ1->manaRegen);
	CString MR_1;
	MR_1.Format(_T("%g"), con->champ1->magicRes);
	CString AR_1;
	AR_1.Format(_T("%g"), con->champ1->armor);
	CString R_1;
	R_1.Format(_T("%d"), con->champ1->range);
	//Missing Speed, manaregen

	//CHamp 2 Stats To String
	CString AS_2;
	AS_2.Format(_T("%g"), con->champ2->attackSpeed);
	CString AD_2;
	AD_2.Format(_T("%g"), con->champ2->attackDamage);
	CString HR_2;
	HR_2.Format(_T("%g"), con->champ2->healthRegen);
	CString MD_2;
	MD_2.Format(_T("%g"), con->champ2->magicDamage);
	CString MG_2;
	MG_2.Format(_T("%g"), con->champ1->manaRegen);
	CString MR_2;
	MR_2.Format(_T("%g"), con->champ2->magicRes);
	CString AR_2;
	AR_2.Format(_T("%g"), con->champ2->armor);
	CString R_2;
	R_2.Format(_T("%d"), con->champ2->range);
	//Missing Speed, manaregen

	//Convert number to string
	CString champ_1_Health_to_String;
	champ_1_Health_to_String.Format(_T("%d"), con->getHealth1());
	CString champ_2_Health_to_String;
	champ_2_Health_to_String.Format(_T("%d"), con->getHealth2());
	CString run_Time_to_String;
	run_Time_to_String.Format(_T("%d"), con->GetCounter());
	CString champ_1_Mana_to_String;
	champ_1_Mana_to_String.Format(_T("%d"), (INT)con->champ1->mana);
	CString champ_2_Mana_to_String;
	champ_2_Mana_to_String.Format(_T("%d"), (INT)con->champ2->mana);
	//end converts
	LPCWSTR playSound = L"play Sounds\\lockinchampion.mp3";
	LPCWSTR openSound = L"open Sounds\\lockinchampion.mp3 type mpegvideo";
	LPCTSTR soundComplete = L"play C:/Riot Games/League of Legends/RADS/projects/lol_air_client\releases/0.0.1.65/deploy/assets/sounds/newSounds/hit.mp3";

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_PROGRESS_CLASS;
	InitCommonControlsEx(&InitCtrlEx);
	
	switch (Msg)
	{
	case WM_INITDIALOG:
	
		//Menu Items
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hFile, L"File");
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hEdit, L"Edit");
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hHelp, L"Help");
		AppendMenu(hFile, MF_STRING, ID_Save, L"Save");
		AppendMenu(hFile, MF_STRING, ID_Load, L"Load");
		AppendMenu(hFile, MF_STRING, ID_Exit, L"Exit");
		AppendMenu(hEdit, MF_STRING, ID_Undo, L"Undo");
		AppendMenu(hEdit, MF_STRING, ID_Redo, L"Redo");
		AppendMenu(hHelp, MF_STRING, ID_VWS, L"Visit website");

		//Might be Use Full
		//SetDlgItemText(hWndDlg, IDC_MY_STATIC1, L"test");
		run_Time = CreateWindowEx(0, L"STATIC", L"0:00", WS_VISIBLE | WS_CHILD, 200, 240, 90, 20, hWndDlg, NULL, hInst, NULL);
		//top
		champ_Health_1 = CreateWindowEx(0, L"STATIC", champ_1_Health_to_String, WS_VISIBLE | WS_CHILD , 100, 60, 60, 20, hWndDlg, NULL, hInst, NULL);
		//bottom
		champ_Health_2 = CreateWindowEx(0, L"STATIC", champ_2_Health_to_String, WS_VISIBLE | WS_CHILD , 100, 140, 60, 20, hWndDlg, NULL, hInst, NULL);
		//top
		SetDlgItemText(hWndDlg, IDC_STATIC1, champ_1_Mana_to_String);
		champ_Mana_1 = GetDlgItem(hWndDlg, IDC_STATIC1);
		//champ_Mana_1 = CreateWindowEx(0, L"STATIC", champ_1_Health_to_String, WS_VISIBLE | WS_CHILD, 100, 60, 60, 20, hWndDlg, NULL, hInst, NULL);
		//bottom
		SetDlgItemText(hWndDlg, IDC_STATIC2, champ_2_Mana_to_String);
		champ_Mana_2 = GetDlgItem(hWndDlg, IDC_STATIC2);
		//champ_Mana_1 = CreateWindowEx(0, L"STATIC", champ_2_Health_to_String, WS_VISIBLE | WS_CHILD, 100, 140, 60, 20, hWndDlg, NULL, hInst, NULL);
		//top
		champ_Name_1 = CreateWindowEx(0, L"STATIC", con->champ1->name , WS_VISIBLE | WS_CHILD, 5, 60, 90, 20, hWndDlg, NULL, hInst, NULL);
		//bottom
		champ_Name_2 = CreateWindowEx(0, L"STATIC", con->champ2->name, WS_VISIBLE | WS_CHILD, 5, 140, 90, 20, hWndDlg, NULL, hInst, NULL);
		//top health
		hHealthBar1 = CreateWindowEx(0, PROGRESS_CLASS, NULL,
			WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
			5, 80, 260, 17,
			hWndDlg, NULL, hInst, NULL);
		SendMessage(hHealthBar1, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hHealthBar1, PBM_SETSTEP, 1, 0L);
		SendMessage(hHealthBar1, PBM_SETBARCOLOR, 0, 0x0000AA00);
		SendMessage(hHealthBar1, PBM_SETPOS, (WPARAM) 100, 0L);
		//bottom health
		hHealthBar2 = CreateWindowEx(0, PROGRESS_CLASS, NULL,
			WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
			5, 160, 260, 17,
			hWndDlg, NULL, hInst, NULL);
		SendMessage(hHealthBar2, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hHealthBar2, PBM_SETSTEP, 1, 0L);
		SendMessage(hHealthBar2, PBM_SETBARCOLOR, 0, 0x009400d3);
		SendMessage(hHealthBar2, PBM_SETPOS, (WPARAM) 100, 0L);
		//top mana
		hManaBar1 = GetDlgItem(hWndDlg, IDC_PROGRESS2);
		SendMessage(hManaBar1, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hManaBar1, PBM_SETSTEP, 1, 0L);
		SendMessage(hManaBar1, PBM_SETBARCOLOR, 0, 0x0000AA00);
		SendMessage(hManaBar1, PBM_SETPOS, (WPARAM) 100, 0L);
		//bottom mana
		hManaBar2 = GetDlgItem(hWndDlg, IDC_PROGRESS3);
		SendMessage(hManaBar2, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hManaBar2, PBM_SETSTEP, 1, 0L);
		SendMessage(hManaBar2, PBM_SETBARCOLOR, 0, 0x009400d3);
		SendMessage(hManaBar2, PBM_SETPOS, (WPARAM) 100, 0L);
		//Initilize Struct Data 
		data.hProgressWindow1_Struct = hHealthBar1;
		data.hProgressWindow2_Struct = hHealthBar2;
		data.champ_Health_1_Struct = champ_Health_1;
		data.champ_Health_2_Struct = champ_Health_2;
		//Load Menu
		SetMenu(hWndDlg,hMenubar);

		return TRUE;
		break;
	case WM_PAINT:
		//another way to put in text using paint, not needed for now
		//hdc = BeginPaint(hWndDlg, &ps);
		//TextOut(hdc, 70, 50, yiHealth, yiHealth.GetLength());
		//EndPaint(hWndDlg, &ps);
		break;
	case WM_CTLCOLORSTATIC:
		//SetBkMode((HDC) wParam, TRANSPARENT);
		//return (LONG) GetStockObject(NULL_BRUSH);
		
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		
			//con->SetStdOutToNewConsole();
			mciSendString(openSound, NULL, 0, 0);
			mciSendString(playSound, NULL, 0, 0);
			con->runSim(hHealthBar1, hHealthBar2, champ_Health_1, champ_Health_2, run_Time, hManaBar1, hManaBar2, champ_Mana_1, champ_Mana_2);
			runButton = GetDlgItem(hWndDlg, IDOK);//diables runButton
			Button_Enable(runButton, false);
			return TRUE;
		
		case IDC_BUTTON1:{
			c1 = GetDlgItemInt(hWndDlg, IDC_EDIT1, 0, 0);
		//	SetStdOutToNewConsole();
			Controller::choice1 = c1;
			cout << "TEST: " << Controller::choice1;
			//data.dCon = new Controller(choice1,choice2);
			//con = data.dCon;
			MessageBox(0, L"Champ 1 Stats\n\nHealth" + champ_1_Health_to_String + "\nHealth Regen: " + HR_1
				+ "\nAttack Speed: " + AS_1 + "\nAttack Damage: " + AD_1 + "\nArmor: " + AR_1 + "\nMagic Damage: " + MD_1 + "\nMana Regen: " + MG_1 + "\nMagic Resist: " + MR_1 + "\nRange: " + R_1
				, L"Champ 1 Stats", MB_OK);
		}
			return TRUE;
			break;
		case IDC_BUTTON2:
			MessageBox(0, L"Champ 2 Stats\n\nHealth: " + champ_2_Health_to_String + "\nHealth Regen: " + HR_2
				+ "\nAttack Speed: " + AS_2 + "\nAttack Damage: " + AD_2 + "\nArmor: " + AR_2 + "\nMagic Damage: " + MD_2 + "\nMana Regen: " + MG_2 + "\nMagic Resist: " + MR_2 + "\nRange: " + R_1
				, L"Champ 2 Stats", MB_OK);
			
			return TRUE;
			break;
		//case ID_APPLY_NOW:
		//	PropertySheet(&m_PropSheet);
		//	break;
		case IDCANCEL:
			EndDialog(hWndDlg, 0);
			return TRUE;
		case ID_VWS:
			ShellExecute(NULL, L"Open", L"http://www.google.com/", NULL, NULL, SW_SHOWNORMAL);
			return TRUE;
			break;
		case ID_Exit:
			EndDialog(hWndDlg, 0);
			return TRUE;
			break;
		}
		break;
	}


	return FALSE;
}

void propertyPages(HINSTANCE hInstance){

	memset(m_psp, 0, sizeof(m_psp));
	memset(&m_PropSheet, 0, sizeof(m_PropSheet));

	m_psp[0].dwSize = sizeof(PROPSHEETPAGE);
	m_psp[0].dwFlags = PSH_WIZARD;
	m_psp[0].hInstance = hInstance;
	m_psp[0].pszTemplate = (LPCWSTR) IDD_PROPPAGE_LARGE;
	m_psp[0].pszTitle = L"Champ 1 Scenario";
	//m_psp[0].pfnDlgProc = myDLGProc;

	m_psp[1].dwSize = sizeof(PROPSHEETPAGE);
	m_psp[1].dwFlags = PSP_USETITLE;
	m_psp[1].hInstance = hInstance;
	m_psp[1].pszTemplate = (LPCWSTR) IDD_PROPPAGE_LARGE1;
	m_psp[1].pszTitle = L"Champ 2 Scenario";

	m_PropSheet.dwSize = sizeof(PROPSHEETHEADER);
	m_PropSheet.dwFlags = PSH_PROPSHEETPAGE;
	m_PropSheet.hInstance = hInstance;
	m_PropSheet.pszCaption = L"Champion Level/Runes/Masteries";
	m_PropSheet.nPages = 2;
	m_PropSheet.nStartPage = 0;
	m_PropSheet.ppsp = (LPCPROPSHEETPAGE) m_psp;
	//SendMessage(GetParent(hDlg), PSM_CHANGED, IDD_PROPPAGE_LARGE, 0);
	//PropSheet_Changed(PROPSHEETPAGE, m_psp);
	PropertySheet(&m_PropSheet);

}


///----------------ConSole---------------------------
void SetStdOutToNewConsole()
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