
// DuoDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Duo.h"
#include "DuoDlg.h"
#include "afxdialogex.h"
#include "stdafx.h"
#include <stdio.h>
#include <chrono>
#include <WinInet.h>
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo2();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAboutDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CDuoDlg dialog



CDuoDlg::CDuoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DUO_DIALOG, pParent)
	, m_antalspelbara(0)
	, m_chans(0)
	, m_kvot(0)
	, m_spelbarakombinationer(_T(""))
	, m_loppid(0)
	, m_ater(0)
	, m_quinellaaterbetalning(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDuoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_antalspelbara);
	DDX_Text(pDX, IDC_EDIT2, m_chans);
	DDX_Text(pDX, IDC_EDIT3, m_kvot);
	DDX_CBString(pDX, IDC_COMBO1, m_spelbarakombinationer);
	DDX_Text(pDX, IDC_EDIT4, m_loppid);
	DDX_Text(pDX, IDC_EDIT5, m_ater);
	DDX_Text(pDX, IDC_EDIT6, m_quinellaaterbetalning);
}

BEGIN_MESSAGE_MAP(CDuoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDuoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDuoDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT5, &CDuoDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON3, &CDuoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDuoDlg message handlers

BOOL CDuoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDuoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDuoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDuoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDuoDlg::kakylera_nominellt_odds(int a, int b)
{
//	CDuoDlg::duoodds_nominella[1][2] = 17;
	if (a != 0 && b != 0) {
		float nom_a, nom_b, dela, delb,sum;
		nom_a = 1 / (float)Vinnarodds[a];
		nom_a /= (1/aterbetsumma);
		nom_b = 1 / (float)Vinnarodds[b];
		nom_b /= (1/aterbetsumma);
		dela = nom_a * (nom_b * (1- nom_a));
		delb = nom_b * (nom_a * (1-nom_b));
		sum = dela + delb;
		sum = 1 / sum;
		duoodds_nominella[a][b] = sum;
	}
}

void CDuoDlg::kalkylera_nominella_odds()
{
	m_antalspelbara = 0;
	m_chans  = 0.0;
	UpdateData(false);
	aterbetsumma = 0.0;
	for (int c = 0; c < 20; c++) {
		float temp;
		if (Vinnarodds[c] != 0) {
			temp = 1 / Vinnarodds[c];
			aterbetsumma += temp;
		}
	}
	for (int a = 0; a < 20; a++) {
		for (int b = a + 1; b < 20; b++) {
			kakylera_nominellt_odds(a, b);
		}
	}
}

void CDuoDlg::kalkylera_vinnande()
{
	char buffer[12];
	CString tempstring;
	int length;
	int indexx = -1;
	float Ins;
	vinnande_kombination vk;
	UpdateData(true);
	CComboBox* pLC2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	//pLC2->SetCurSel(0);
//	pLC2->InsertString(-1, "init");
	UpdateData(false);
	for (int a = 0; a < 20; a++)
	{
		for (int b = 0; b < 20; b++)
		{
			if (duoodds_nominella[a][b] != 0 && duoodds_spelade[a][b] != 0)
			{
				if (duoodds_nominella[a][b]*m_kvot < duoodds_spelade[a][b])
				{
					int t1, t2;
					float temp;
					t1 = duoodds_nominella[a][b];
					t2 = duoodds_spelade[a][b];
					m_antalspelbara++;
					temp = 1 / (float)t1;
					m_chans = m_chans + temp;
					vk.hast_a = a;
					vk.hast_b = b;
					vk.odds = t1;
					vk.kvot = (float)duoodds_spelade[a][b] / (float)duoodds_nominella[a][b];
					//beräkna insats
					Ins = (m_ater) * 0.5 * (m_quinellaaterbetalning) / (duoodds_nominella[a][b] * vk.kvot) * (sqrt(vk.kvot) - 1);
					vk.insats = Ins;
					vko.push_back(vk);
					UpdateData(false);
					tempstring = "";
#pragma warning(suppress : 4996)
					tempstring = itoa(a, buffer, 10);
					tempstring += "-";
#pragma warning(suppress : 4996)
					tempstring += itoa(b, buffer, 10);
					tempstring += "   ";
#pragma warning(suppress : 4996)
					tempstring += itoa(t1, buffer, 10);
					tempstring += "   ";
#pragma warning(suppress : 4996)
					tempstring += itoa(t2, buffer, 10);
				
				//	m_spelbarakombinationer.Append(tempstring);
					
					length = m_spelbarakombinationer.GetLength();
				//	m_spelbarakombinationer.Insert(length, tempstring);
					indexx++;
					int count = pLC2->GetCount();
					pLC2->InsertString(-1,tempstring);
					pLC2->Invalidate(true);
					UpdateData(false);
				}
			}
		}
	}
}

void CDuoDlg::kalkylera_aterbetalning()
{
	double ater;
	ater = 0;
	for (int a = 0; a < 20; a++) {
		for (int b = 0; b < 20; b++) {
			if (duoodds_spelade[a][b] != 0) {
				ater += 1/duoodds_spelade[a][b];
			}
		}
	}

	m_ater = 1/ater;
	UpdateData(false);
}

void CDuoDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	char  sUrlOrg[300];
	CInternetSession m_Session;
	CStdioFile* pFile;
	char buffer[500000];
	FILE* str;
	int status;
	UpdateData(true);
	//sprintf_s(sUrlOrg, "view-source:https://spela.svenskaspel.se/trav-och-galopp/spela/cabourg/lopp-3/vinnare/2021-07-13");
	//sprintf_s(sUrlOrg, "https://api.spela.svenskaspel.se/racing/1/race/12141/quinellaodds?");
	//pFile = m_Session.OpenURL(sUrlOrg, 1, INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_EXISTING_CONNECT  | INTERNET_FLAG_TRANSFER_ASCII);
	//pFile->ReadString(buffer, 24099);
	int err;
	err = fopen_s(&str, "vinnarodds.txt", "r");
	fread(buffer, sizeof(char), 500000, str);
	int lasindex = 0;
	int horseNumber;
	float odds;
	for (int a = 0; a < 20; a++) {
		Vinnarodds[a] = 0.0;
	}
	status = 0;
	do {
		if ((buffer[lasindex] == 'p') && (status == 0))
		{
			status = 1;
		}
		else if ((buffer[lasindex] == 'a') && (status == 1))
		{
			status = 2;
		}
		else if ((buffer[lasindex] == 'r') && (status == 2))
		{
			status = 3;
		}
		else if ((buffer[lasindex] == 't') && (status == 3))
		{
			status = 4;
		}
		else if ((buffer[lasindex] == 'i') && (status == 4))
		{
			status = 5;
		}
		else if ((buffer[lasindex] == 'c') && (status == 5))
		{
			status = 6;
		}
		else if ((buffer[lasindex] == 'i') && (status == 6))
		{
			status = 7;
		}
		else if ((buffer[lasindex] == 'p') && (status == 7))
		{
			status = 8;
		}
		else if ((buffer[lasindex] == 'a') && (status == 8))
		{
			status = 9;
		}
		else if ((buffer[lasindex] == 'n') && (status == 9))
		{
			status = 10;
		}
		else if ((buffer[lasindex] == 't') && (status == 10))
		{
			status = 11;
		}
		else if ((buffer[lasindex] == 'N') && (status == 11))
		{
			status = 12;
		}
		else if ((buffer[lasindex] == 's') && (status == 11))
		{
			status = 0;
		}
		else if ((buffer[lasindex] == 'u') && (status == 12))
		{
			status = 13;
		}
		else if ((buffer[lasindex] == ':') && (status == 13))
		{
			status = 14;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 14))
		{
			status = 15;
			horseNumber = (buffer[lasindex] - 48);
		}
		else if ((buffer[lasindex] == ',') && (status == 15))
		{
			status = 155;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 15))
		{
			status = 155;
			int tmp;
			tmp = (buffer[lasindex] - 48);
			horseNumber *= 10;
			horseNumber += tmp;
		}
		else if ((buffer[lasindex] == 'c') && (status == 155))
		{
			status = 16;
		}
		else if ((buffer[lasindex] == 'a') && (status == 16))
		{
			status = 17;
		}
		else if ((buffer[lasindex] == 'n') && (status == 17))
		{
			status = 18;
		}
		else if ((buffer[lasindex] == 'c') && (status == 18))
		{
			status = 19;
		}
		else if ((buffer[lasindex] == 'e') && (status == 19))
		{
			status = 20;
		}
		else if ((buffer[lasindex] == 'l') && (status == 20))
		{
			status = 21;
		}
		else if ((buffer[lasindex] == 'e') && (status == 21))
		{
			status = 22;
		}
		else if ((buffer[lasindex] == 'd') && (status == 22))
		{
			status = 23;
		}
		else if ((buffer[lasindex] == 't') && (status == 23))
		{
		status = 29;
		}
		else if ((buffer[lasindex] == 'f') && (status == 23))
		{
		status = 24;
		}
		else if ((buffer[lasindex] == 'L') && (status == 24))
		{
		status = 241;
        }
		else if ((buffer[lasindex] == 'a') && (status == 241))
		{
		status = 242;
		}
		else if ((buffer[lasindex] == 't') && (status == 242))
		{
		status = 243;
		}
		else if ((buffer[lasindex] == 'e') && (status == 243))
		{
		status = 244;
		}
		else if ((buffer[lasindex] == 's') && (status == 244))
		{
		status = 245;
		}
		else if ((buffer[lasindex] == 't') && (status == 245))
		{
		status = 246;
		}
		else if ((buffer[lasindex] == ':') && (status == 246))
		{
		status = 25;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 25))
		{
		status = 26;
		odds= (buffer[lasindex] - 48);
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 26))
		{
		status = 26;
		int tmp;
		tmp = (buffer[lasindex] - 48);
		odds *= 10;
		odds += tmp;
		}
		else if ((buffer[lasindex] == '.') && (status == 26))
		{
		status = 27;
		}
		else if ((buffer[lasindex] == '}') && (status == 26))
		{
		status = 29;
		Vinnarodds[horseNumber] = odds;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 27))
		{
		status = 28;
		float tmp;
		tmp = (buffer[lasindex] - 48);
		odds += tmp*0.1;
		}
		else if ((buffer[lasindex] == '}') && (status == 28))
		{
		Vinnarodds[horseNumber] = odds;
		status = 29;
		}
		else if ((buffer[lasindex] == ',') && (status == 29))
		{
		status = 0;
		}
		else if ((buffer[lasindex] == ']') && (status == 29))
		{
		status = 1000;
		}
		lasindex++;
	} while (status < 1000);
	int a;
	a = 1;
	kalkylera_nominella_odds();
	//UpdateData(false);
}


void CDuoDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	char  sUrlOrg[300];
	CInternetSession m_Session;
	CStdioFile* pFile;
	char buffer[25000];
	int status;
	UpdateData(true);
	sprintf_s(sUrlOrg, "https://api.spela.svenskaspel.se/racing/1/race/%d/quinellaodds?",m_loppid);

	//sprintf_s(sUrlOrg, "https://api.spela.svenskaspel.se/racing/1/race/12163/quinellaodds?");
	pFile = m_Session.OpenURL(sUrlOrg, 1, INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_TRANSFER_ASCII);
	pFile->ReadString(buffer, 24099);
	status = 0;
	int lasindex = 0;
	int pair1, pair2,odds;
	int quinellaomsattning;
	quinellaomsattning = 0;

	do {
		if ((buffer[lasindex] == 't') && (status == 0)) {
			status = 1;
		}
		else if ((buffer[lasindex] == 'u') && (status == 1)) {
			status = 2;
		}
		else if ((buffer[lasindex] == 'r') && (status == 2)) {
			status = 3;
		}
		else if ((buffer[lasindex] == 'n') && (status == 3)) {
			status = 4;
		}
		else if ((buffer[lasindex] == 'o') && (status == 4)) {
			status = 5;
		}
		else if ((buffer[lasindex] == 'v') && (status == 5)) {
			status = 6;
		}
		else if ((buffer[lasindex] == 'e') && (status == 6)) {
			status = 7;
		}
		else if ((buffer[lasindex] == 'r') && (status == 7)) {
			status = 8;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 8))
		{
			status = 9;
			quinellaomsattning = (buffer[lasindex] - 48);
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 9))
		{
			status = 9;
			int tmp;
			tmp = (buffer[lasindex] - 48);
			quinellaomsattning *= 10;
			quinellaomsattning += tmp;
		}
		else if ((buffer[lasindex] == ',') && (status == 9)) {
			status = 100;
		}
		lasindex++;
	} while (status < 100);

	m_quinellaaterbetalning = quinellaomsattning;
	UpdateData(false);

	status = 0;

	do
	{ 
		if ((buffer[lasindex] == 'N') && (status ==0)) {
			status = 1;
		}
		else if ((buffer[lasindex] == 'u') && (status == 1)) {
			status = 2;
		}
		else if ((buffer[lasindex] == 'm') && (status == 2)) {
			status = 3;
		}
		else if ((buffer[lasindex] == 'b') && (status == 3)) {
			status = 4;
		}
		else if ((buffer[lasindex] == 'e') && (status == 4)) {
			status = 5;
		}
		else if ((buffer[lasindex] == 'r') && (status == 5)) {
			status = 6;
		}
		else if ((buffer[lasindex] == ':') && (status == 6)) {
			status = 7;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 7))
		{
			status = 8;
			pair1 = (buffer[lasindex] - 48);
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 8))
		{
			status = 8;
			int tmp;
			tmp = (buffer[lasindex] - 48);
			pair1 *= 10;
			pair1 += tmp;
		}
		else if ((buffer[lasindex] ==  ':'  && status == 8))
		{
			status = 9;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 9))
		{
			status = 10;
			pair2 = (buffer[lasindex] - 48);
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 10))
		{
			status = 10;
			int tmp;
			tmp = (buffer[lasindex] - 48);
			pair2 *= 10;
			pair2 += tmp;
		}
		else if ((buffer[lasindex] == ':' && status == 10))
		{
			status = 11;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 11))
		{
			status = 12;
			odds = (buffer[lasindex] - 48);
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 12))
		{
			status = 12;
			int tmp;
			tmp = (buffer[lasindex] - 48);
			odds *= 10;
			odds += tmp;
		}
		else if ((buffer[lasindex] >= '0' && (buffer[lasindex] <= '9') && status == 12))
		{
			status = 12;
			int tmp;
			tmp = (buffer[lasindex] - 48);
			odds *= 10;
			odds += tmp;
		}
		else if ((buffer[lasindex] == ',' && status == 12))
		{
			status = 13;
			duoodds_spelade[pair1][pair2] = odds;
		}
		else if ((buffer[lasindex] == 'N') && (status == 13)) {
			status = 1;
		}
		else if ((buffer[lasindex] == ']' && status == 13))
		{
			status = 100;
		}
		lasindex++;
	} while (status < 100);
	int a;
	a = 0;
	//kalkylera_vinnande();
	kalkylera_aterbetalning();
	kalkylera_vinnande();
	//m_spelbarakombinationer.Append("test");
	//UpdateData(false);
}


void CAboutDlg::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
}


void CDuoDlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CDuoDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CStdioFile report;
	char	filename[32];
	char buf[250];
	vinnande_kombination vkomb;
	sprintf_s(filename, "Quinella_rapport.txt");
	if (report.Open(filename, CFile::modeWrite | CFile::modeCreate, 0))
	{
		sprintf_s(buf,"Omsättning %d     Återbetalning %f\n\n", m_quinellaaterbetalning, m_ater);
		report.WriteString(buf);
		report.WriteString("Komb             Odds    Kvot Spelat belopp  Beräknat spelbelopp\n");
		for (int x = 0; x < vko.size(); x++) {
			vkomb = vko.at(x);
			
			sprintf_s(buf, "%d - %d             %d  %f    %d\n", vkomb.hast_a, vkomb.hast_b,vkomb.odds,vkomb.kvot,vkomb.insats);
			report.WriteString(buf);
		}
		report.Close();
		char cmdstr[64];
		sprintf_s(cmdstr, "notepad.exe  %s", filename);
		::WinExec(cmdstr, SW_SHOWNORMAL);
	}
}
