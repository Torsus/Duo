
// DuoDlg.h : header file
//

#pragma once
#include <iostream>
#include <vector>
using namespace std;
// CDuoDlg dialog
class CDuoDlg : public CDialogEx
{
// Construction
public:
	CDuoDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DUO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	float duoodds_spelade[20][20];
	float duoodds_nominella[20][20];
	float Vinnarodds[20];
	float aterbetsumma;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void kalkylera_nominella_odds();
	afx_msg void kakylera_nominellt_odds(int a, int b);
	afx_msg void kalkylera_vinnande();
	afx_msg void kalkylera_aterbetalning();
	int m_antalspelbara;
	float m_chans;
	float m_kvot;
	CString m_spelbarakombinationer;
	int m_loppid;
	double m_ater;
	struct vinnande_kombination
	{
		int hast_a;
		int hast_b;
		int odds;
		float kvot;
		int insats;
		float for_vinst;
	};
	typedef vector<vinnande_kombination, allocator<vinnande_kombination> > Vinnande_kombinationer;
	Vinnande_kombinationer vko;
	afx_msg void OnEnChangeEdit5();
	int m_quinellaaterbetalning;
	afx_msg void OnBnClickedButton3();
};
