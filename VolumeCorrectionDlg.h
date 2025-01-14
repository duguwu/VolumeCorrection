
// VolumeCorrectionDlg.h : header file
//

#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

// CVolumeCorrectionDlg dialog
class CVolumeCorrectionDlg : public CDialogEx
{
// Construction
public:
	CVolumeCorrectionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VOLUMECORRECTION_DIALOG };
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
	afx_msg void OnBnClickedButtonStart();
	static UINT DataProcessing(LPVOID pParam);
	int m_averaging;
	afx_msg LRESULT OnCustomMessage(WPARAM w, LPARAM l);
	static int GetIndexofHistMax(Mat m_input, int m_cols, int *max_value);
	afx_msg void OnBnClickedButtonTest();
	float m_alpha;
	int m_threshold;
	static Mat GetFFTfilteredResult(Mat complex);
	static Mat computeDFT(Mat padded);
	static Mat ShowMag(Mat complex);
	static void shift(Mat magI);
	static Mat createButtworthFilterMask(Size mask_size, int ksizex, int ksizey);
	int m_filter_ratio;
	afx_msg void OnEnChangeBrowseInput1();
	int m_zscale;
	int m_yscale;
	afx_msg void OnBnClickedButtonHelp();
	BOOL m_bInitializing = true;
};
