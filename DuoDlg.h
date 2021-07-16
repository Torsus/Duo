
// DuoDlg.h : header file
//

#pragma once


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
	int m_antalspelbara;
	float m_chans;
	float m_kvot;
	CString m_spelbarakombinationer;
	int m_loppid;
};
