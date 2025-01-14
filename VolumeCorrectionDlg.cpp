
// VolumeCorrectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VolumeCorrection.h"
#include "VolumeCorrectionDlg.h"
#include "afxdialogex.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "fstream"
#include "gsl/gsl_fit.h"
#include "Vfw.h"

#define WM_MYMSG1 (WM_USER+1)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;

double input[25600];
double temp[256000];
double output[25600];
int DiffRawtoNew[25600];
char averaging = 1;
int zscale = 100;
int yscale = 100;
HANDLE transferevent;

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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVolumeCorrectionDlg dialog



CVolumeCorrectionDlg::CVolumeCorrectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VOLUMECORRECTION_DIALOG, pParent)
	, m_averaging(1)
	, m_alpha(0.001)
	, m_threshold(60)
	, m_zscale(50)
	, m_yscale(64)
	, m_filter_ratio(25)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVolumeCorrectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AVERAGING, m_averaging);
	DDX_Text(pDX, IDC_EDIT_ZSCALE, m_zscale);
	DDV_MinMaxFloat(pDX, m_zscale, 1, 200);
	DDX_Text(pDX, IDC_EDIT_YSCALE, m_yscale);
	DDV_MinMaxFloat(pDX, m_yscale, 1, 200);
	
	DDX_Text(pDX, IDC_EDIT1, m_alpha);
	DDV_MinMaxFloat(pDX, m_alpha, 0, 10);
	DDX_Text(pDX, IDC_SURFACETH, m_threshold);
	DDX_Text(pDX, IDC_EDIT_FILTERRATIO, m_filter_ratio);
	DDV_MinMaxInt(pDX, m_filter_ratio, 1, 255);
}

BEGIN_MESSAGE_MAP(CVolumeCorrectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MYMSG1, OnCustomMessage)
	ON_BN_CLICKED(IDC_BUTTON_START, &CVolumeCorrectionDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CVolumeCorrectionDlg::OnBnClickedButtonTest)
	ON_EN_CHANGE(IDC_BROWSE_INPUT1, &CVolumeCorrectionDlg::OnEnChangeBrowseInput1)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CVolumeCorrectionDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// CVolumeCorrectionDlg message handlers

BOOL CVolumeCorrectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, false);

	// TODO: Add extra initialization here
	CString name1, name2;
	
	name1 = _T("D:\\raw.avi");
	name2 = _T("D:\\");

	SetDlgItemText(IDC_BROWSE_INPUT1, name1);
	SetDlgItemText(IDC_BROWSE_OUTPUT, name2);

	m_bInitializing = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVolumeCorrectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVolumeCorrectionDlg::OnPaint()
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
HCURSOR CVolumeCorrectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVolumeCorrectionDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here

	CString sourcename0, sourcename1, sourcename2, filepath, dstname0, dstname1, dstname2, dstname0_xy, dstname1_xy, dstname2_xy;

	UpdateData(true);
	averaging = m_averaging;
	zscale = m_zscale;
	yscale = m_yscale;


	GetDlgItemText(IDC_BROWSE_INPUT1, sourcename0);
	GetDlgItemText(IDC_BROWSE_INPUT2, sourcename1);
	GetDlgItemText(IDC_BROWSE_INPUT3, sourcename2);

	GetDlgItemText(IDC_BROWSE_OUTPUT, filepath);


	USES_CONVERSION;
	std::string sourcenamestr0(W2A(sourcename0));
	std::string sourcenamestr1(W2A(sourcename1));
	std::string sourcenamestr2(W2A(sourcename2));



	dstname0 = filepath + _T("\\new.avi");
	dstname1 = filepath + _T("\\new1.avi");
	dstname2 = filepath + _T("\\new2.avi");

	dstname0_xy = filepath + _T("\\newxy.avi");
	dstname1_xy = filepath + _T("\\new1xy.avi");
	dstname2_xy = filepath + _T("\\new2xy.avi");


	std::string filepathstr(W2A(filepath));
	std::string dstnamestr0(W2A(dstname0));
	std::string dstnamestr1(W2A(dstname1));
	std::string dstnamestr2(W2A(dstname2));

	std::string dstnamexystr0(W2A(dstname0_xy));
	std::string dstnamexystr1(W2A(dstname1_xy));
	std::string dstnamexystr2(W2A(dstname2_xy));



	DWORD retwait;
	transferevent = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("TransferEvent")  // object name
	);

	struct MyStruct
	{
		HWND MyDlgHandle;
		String Tr_sname0;
		String Tr_sname1;
		String Tr_sname2;
		String Tr_dname0;
		String Tr_dname1;
		String Tr_dname2;
		String Tr_dname0xy;
		String Tr_dname1xy;
		String Tr_dname2xy;
		String Tr_dfpath;
		bool Tr_ch2checked;
		bool Tr_ch3checked;
		bool Tr_keepsurfacechecked;
		bool Tr_xysliceChecked;
		float Tr_alpha;
		int Tr_threshold;
		int Tr_filter_ratio;
	} mystructTotransfer;
	mystructTotransfer.MyDlgHandle = this->m_hWnd;

	mystructTotransfer.Tr_sname0 = sourcenamestr0;
	mystructTotransfer.Tr_sname1 = sourcenamestr1;
	mystructTotransfer.Tr_sname2 = sourcenamestr2;

	mystructTotransfer.Tr_dname0 = dstnamestr0;
	mystructTotransfer.Tr_dname1 = dstnamestr1;
	mystructTotransfer.Tr_dname2 = dstnamestr2;

	mystructTotransfer.Tr_dname0xy = dstnamexystr0;
	mystructTotransfer.Tr_dname1xy = dstnamexystr1;
	mystructTotransfer.Tr_dname2xy = dstnamexystr2;

	mystructTotransfer.Tr_dfpath = filepathstr;
	mystructTotransfer.Tr_alpha = m_alpha;
	mystructTotransfer.Tr_threshold = m_threshold;
	mystructTotransfer.Tr_filter_ratio = m_filter_ratio;

	CButton *m_ctlCheck2 = (CButton*)GetDlgItem(IDC_CHECK_INPUT2);
	int ChkBox = m_ctlCheck2->GetCheck();
	if (ChkBox == BST_UNCHECKED)
		mystructTotransfer.Tr_ch2checked = false;
	else if (ChkBox == BST_CHECKED)
		mystructTotransfer.Tr_ch2checked = true;

	CButton *m_ctlCheck3 = (CButton*)GetDlgItem(IDC_CHECK_INPUT3);
	ChkBox = m_ctlCheck3->GetCheck();
	if (ChkBox == BST_UNCHECKED)
		mystructTotransfer.Tr_ch3checked = false;
	else if (ChkBox == BST_CHECKED)
		mystructTotransfer.Tr_ch3checked = true;

	CButton* m_ctlCheck_xyslice = (CButton*)GetDlgItem(IDC_CHECK_XYSLICE);
	ChkBox = m_ctlCheck_xyslice->GetCheck();
	if (ChkBox == BST_UNCHECKED)
		mystructTotransfer.Tr_xysliceChecked = false;
	else if (ChkBox == BST_CHECKED)
		mystructTotransfer.Tr_xysliceChecked = true;

	CButton *m_ctlCheck4 = (CButton*)GetDlgItem(IDC_CHECK_KEPT);
	ChkBox = m_ctlCheck4->GetCheck();
	if (ChkBox == BST_UNCHECKED)
		mystructTotransfer.Tr_keepsurfacechecked = false;
	else if (ChkBox == BST_CHECKED)
		mystructTotransfer.Tr_keepsurfacechecked = true;

	AfxBeginThread(DataProcessing, &mystructTotransfer);
	retwait = WaitForSingleObject(transferevent, INFINITE);
	if (retwait == WAIT_OBJECT_0) //20190624 ; deleted;
	CloseHandle(transferevent);

}


UINT CVolumeCorrectionDlg::DataProcessing(LPVOID pParam)
{

	struct MyStruct
	{
		HWND MyDlgHandle;
		String Tr_sname0;
		String Tr_sname1;
		String Tr_sname2;
		String Tr_dname0;
		String Tr_dname1;
		String Tr_dname2;
		String Tr_dname0xy;
		String Tr_dname1xy;
		String Tr_dname2xy;
		String Tr_dfpath;
		bool Tr_ch2checked;
		bool Tr_ch3checked;
		bool Tr_keepsurfacechecked;
		bool Tr_xysliceChecked;
		float Tr_alpha;
		int Tr_threshold;
		int Tr_filter_ratio;

	};
	MyStruct *mystructTotransfer = static_cast<struct MyStruct*>(pParam);

	HWND DlgHandle;
	String sname0;
	String sname1;
	String sname2;
	String dname0;
	String dname1;
	String dname2;

	String dname0xy;
	String dname1xy;
	String dname2xy;

	String dfpath;
	bool ch2checked;
	bool ch3checked;
	bool xysliceChecked;

	bool keepsurfacechecked;
	float intensity_alpha;
	int depth_threshold;
	double m_x, m_y, m_z;// size of the source video file
	int tempmax, tempmin;
	int tempframenumber1=0, tempframenumber2=0;
	int surfacethreshold = 150;//50;
	int filter_ratio = 25;

	int ref_line = 200; //where is the flat surface is located;
	

	sname0 = mystructTotransfer->Tr_sname0;
	sname1 = mystructTotransfer->Tr_sname1;
	sname2 = mystructTotransfer->Tr_sname2;
	dname0 = mystructTotransfer->Tr_dname0;
	dname1 = mystructTotransfer->Tr_dname1;
	dname2 = mystructTotransfer->Tr_dname2;
	dname0xy = mystructTotransfer->Tr_dname0xy;
	dname1xy = mystructTotransfer->Tr_dname1xy;
	dname2xy = mystructTotransfer->Tr_dname2xy;

	dfpath = mystructTotransfer->Tr_dfpath;
	intensity_alpha = mystructTotransfer->Tr_alpha;
	depth_threshold = mystructTotransfer->Tr_threshold;
	filter_ratio = mystructTotransfer->Tr_filter_ratio;
	DlgHandle = mystructTotransfer->MyDlgHandle;
	ch2checked = mystructTotransfer->Tr_ch2checked;
	ch3checked = mystructTotransfer->Tr_ch3checked;
	xysliceChecked = mystructTotransfer->Tr_xysliceChecked;
	keepsurfacechecked = mystructTotransfer->Tr_keepsurfacechecked;
	
	

	VideoCapture inputVideo(sname0);


	SetEvent(transferevent); // inform the mainthread that all the parameters have been read

	if (ch2checked)
	{
		VideoCapture inputVideo1(sname1);
		if (!inputVideo1.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 0, (LPARAM)(LPVOID)_T("can't open the source file 1 "));
			return -1;
		}
		tempframenumber1 = inputVideo1.get(CAP_PROP_FRAME_COUNT); //inputVideo1.get(CV_CAP_PROP_FRAME_COUNT);
	   inputVideo1.release();
	}
	if (ch3checked)
	{
		VideoCapture inputVideo2(sname2);
		if (!inputVideo2.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 0, (LPARAM)(LPVOID)_T("can't open the source file 2 "));
			return -1;
		}
		tempframenumber2 = inputVideo2.get(CAP_PROP_FRAME_COUNT);
		inputVideo2.release();
	}


	m_y = inputVideo.get(CAP_PROP_FRAME_COUNT);     // frame numbers;

	if ((tempframenumber1!=0) && (m_y > tempframenumber1)) m_y = tempframenumber1;
	if ((tempframenumber2!= 0) && (m_y > tempframenumber2)) m_y = tempframenumber2;


	
	m_z = inputVideo.get(CAP_PROP_FRAME_HEIGHT);// rows of frames
	m_x = inputVideo.get(CAP_PROP_FRAME_WIDTH); // columns of framees
	int ex = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));     // Get Codec Type- Int form
	char EXT[] = { ex & 0XFF , (ex & 0XFF00) >> 8,(ex & 0XFF0000) >> 16,(ex & 0XFF000000) >> 24, 0 };
	Mat Oneframe, chans[3];

	inputVideo >> Oneframe;// output one frame of input video.

	int framechannel = Oneframe.channels();
	CString video_information;
	video_information.Format(_T("%f %f %f %d"), m_y, m_z, m_x, framechannel);
	::PostMessage(DlgHandle, WM_MYMSG1, 1, (LPARAM)(LPVOID)(&video_information)); // show video information


	inputVideo.release();
	inputVideo = VideoCapture(sname0);
  /******************************get surface positions**********************************************/
	int i;
	int debug_point = 0;
	Mat thickness(m_x, m_y, CV_32SC1, Scalar::all(0));
	//inputVideo.set(CAP_PROP_POS_FRAMES, 0);
	CString state_text;
	state_text = _T("acquiring raw surface data");
	::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information
	int why;
	for (i = 0; i < m_y; i++) //process frame by frame
	{
		
		if (i == 1105)
		{
			int why;
			why = m_y;
		}
		Mat SingleChFrame((int)(m_x), (int)(m_z), CV_8UC1);

		inputVideo >> Oneframe;
		
		if (i > 15197)
		{
			int tempnumofframes = inputVideo.get(CAP_PROP_FRAME_COUNT);
			int tempcurrentframe= inputVideo.get(CAP_PROP_POS_FRAMES);

			int why;
			why = i;
			why = m_x;

		}
		split(Oneframe, chans);
		SingleChFrame = chans[0];
		medianBlur(SingleChFrame, SingleChFrame, 3);
		//get thickness data in the newframe;
		int mytemp = m_z;
		if (SingleChFrame.empty()!=1)
		{
			for (int k = 0; k < m_x; k++) // process column by column
			{
				mytemp = m_z;
				for (int m = 0; m < m_z - 1; m++)//process by pixel by pixel from top to bottom.
				{
					if ((SingleChFrame.at<uchar>(m, k) > surfacethreshold) && (SingleChFrame.at<uchar>(m + 1, k) > surfacethreshold))
					{
						if (mytemp > m)
						{
							mytemp = m;
							thickness.at<int>(k, i) = m_z - mytemp;
							if (i == 173 && k == 56)
							{
								debug_point = thickness.at<int>(k, i);
								debug_point = thickness.at<int>(k, i);
							}
						}

					}
				}
				if (mytemp == m_z)
					thickness.at<int>(k, i) = 0;


			}
		}

		::PostMessage(DlgHandle, WM_MYMSG1, 3, i);//send message to dlg to show how many frames have been processed.
	}

	/************************************ finished gettting surface positin data***********************************************/



	state_text = _T("processing surface data");
	::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information
	/*****************************get shift****************************************************/


	int nrows = m_x;// column number in a single frame 
	int nframes = m_y;//equal to frame numbers
	Mat Diffofthickness(1, nrows, CV_32SC1, Scalar::all(0));
	Mat frameshift(1, nframes, CV_32SC1, Scalar::all(0));
	Mat motionshift(1, nframes, CV_32SC1, Scalar::all(0));
	Mat correction_mat(m_x,nframes,CV_32SC1,Scalar::all(0));
	Mat filteredthickness;
	double* newDiff = new double[m_x];//array to save difference value
	int newDiffSize[2] = {0,1};
	double polyfitresult=0;
	double diff_factor;


	int absdiff;
	int a, b;
	//sort(thickness, Mmedianthickness, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);
	//for(int i=0;i<ncols;i++)
	    //medianthickness.at<int>(i)= Mmedianthickness.at<int>(round(nrows / 2), i);   // get the surface position of every frame.

	int max_value, max_index;
	int k = 0;
	int j_previous;
	int interval = 5;
	int interval_max, interval_min;
	double newindex;
	for (int j = 1; j < nframes; j++)
		{
			
		    k = 0;
			j_previous= floor((j - 1)*1.0 / averaging)*averaging;
			for (i = 0; i < nrows; i++)
			{
				if ((thickness.at<int>(i, j) != 0) && (thickness.at<int>(i, j_previous) != 0))
				{
					
					Diffofthickness.at<int>(k) = thickness.at<int>(i, j) - thickness.at<int>(i, j_previous);
					k++;
				}		
			}
			if (k != 0)
			{
				max_index = GetIndexofHistMax(Diffofthickness, k, &max_value); //get the value with maximum count;
				TRACE("maxIndex=%d at j=%d\r\n", max_index,j);
				if (max_value ==0) max_index = 0;
				interval_max = max_index + 5;
				if (interval_max >=m_z)
					interval_max = m_z;
				interval_min = max_index - 5;
				if (interval_min <= -m_z)
					interval_min = -m_z;
				newindex = 0;
				for (i = 0; i < k; i++)
				{
					if ((Diffofthickness.at<int>(i) >= interval_min) && (Diffofthickness.at<int>(i) <= interval_max))
					{
						newDiff[(int)newindex] = Diffofthickness.at<int>(i);
						newindex++;
					}
				}
				double sum_newDiff=0;
				for (int i = 0; i < newindex; i++)
				{
					sum_newDiff = sum_newDiff + newDiff[i];
					
				}
							
				polyfitresult = sum_newDiff / newindex;
				if (keepsurfacechecked)
				{
					if (averaging == 10)
						diff_factor = 0.5;
					else diff_factor = 0.5;
					if (abs(polyfitresult) < diff_factor) polyfitresult = 0;
				}
				
				frameshift.at<int>(j) = round(polyfitresult);
			}
			else frameshift.at<int>(j) = 0;
			motionshift.at<int>(j) = motionshift.at<int>(j_previous) + frameshift.at<int>(j);


		}
	std::ofstream myoutput0_0("motionshift0.txt");
	for (int j = 0; j < nframes; j++)
	{
		myoutput0_0 << motionshift.at<int>(j);
		myoutput0_0 << "\r\n";

	}
	myoutput0_0.close();
	std::ofstream myoutput0_fshift("frameshift.txt");
	for (int j = 0; j < nframes; j++)
	{
		myoutput0_fshift << frameshift.at<int>(j);
		myoutput0_fshift << "\r\n";

	}
	myoutput0_fshift.close();
	/********get the trend of the motion******/


	//debug_point = thickness.at<int>(56, 173);

	if (keepsurfacechecked)
	{
		int newncols = 25600;
		int pixelend = newncols - nframes;
		double poly_p[2];
		double polyfit2Result[25600];
		double c0, c1, cov00, cov01, cov11, sumsq;
		for (int j = 0; j < nframes; j++)
		{
			input[j] = j;
			output[j] = motionshift.at<int>(j);
		}
		gsl_fit_linear(input, 1, output, 1, nframes, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);
		for (int j = 0; j < nframes; j++)
			polyfit2Result[j] = j*c1 + c0;
		for (int j = 0; j < nframes; j++)
			{
				motionshift.at<int>(j) = motionshift.at<int>(j) - polyfit2Result[j];
			}
		std::ofstream myoutput0_1("polyfit.txt");
		for (int j = 0; j < nframes; j++)
			{
			 myoutput0_1 << polyfit2Result[j];
			 myoutput0_1 << "\r\n";

			}
		 myoutput0_1.close();
		 for (int j = 0; j < nframes; j++)
			 for (int i = 0; i < m_x; i++)
				 correction_mat.at<int>(i, j) = motionshift.at<int>(j);
	}
	else
	{
		/*******get the surface profile of the whole volume********************************/

		Mat newthickness = thickness.clone(); // this is very important when dealing with mat data structure. Only using mat.clone you got the real copy otherwise you may only get an ponter to the address of the referenced data.
		Mat postthickness = thickness.clone();
		int nonzeroindex = 0;
		Mat padded, complex, magI;
		int m = getOptimalDFTSize(thickness.rows+200);
		int n = getOptimalDFTSize(thickness.cols+200);
		// create output image of optimal size
		// fill the zero values of the thickness matrix with it's neighbour non-zero values.
		for (int j = 0; j < nframes; j++)
		{
			for (int i = 1; i < m_x; i++)
			{
				if (postthickness.at<int>(i, j) == 0) postthickness.at<int>(i, j) = postthickness.at<int>(i - 1, j);
			}
			if (postthickness.at<int>(0, j) == 0)
			{
				for (int i = 1; i < m_x; i++)
					if (postthickness.at<int>(i, j) != 0)
					{
						nonzeroindex = i;
						break;
					}
				for (int i = 0; i < nonzeroindex; i++)
					postthickness.at<int>(i, j) = postthickness.at<int>(nonzeroindex, j);
						
			}

		}

		//

		for (int j = 0; j < nframes; j++)
		{
			for (int i = 0; i < m_x; i++)
				newthickness.at<int>(i, j) = postthickness.at<int>(i, j) - motionshift.at<int>(j);
		}
		copyMakeBorder(newthickness, padded, 100, m - newthickness.rows-100, 100, n - newthickness.cols-100, BORDER_REPLICATE, Scalar::all(0));
		imwrite("thickness.jpg", padded);
		complex = computeDFT(padded);
		debug_point = complex.rows;
		debug_point = complex.rows; 
		debug_point = complex.cols;
		debug_point = complex.cols;

		magI = ShowMag(complex) * 256;
		imwrite("magI.jpg", magI);
		Mat planes[] = { Mat_< float>(padded), Mat::zeros(padded.size(), CV_32F),Mat::zeros(padded.size(),CV_32F) };
		Size mask_size = complex.size();
		Mat mask = createButtworthFilterMask(mask_size, newthickness.cols/filter_ratio, newthickness.rows/filter_ratio);
		shift(mask);
		Mat kernel_spec;
		planes[0] = mask;
		planes[1] = mask;
		merge(planes, 2, kernel_spec);
		mulSpectrums(complex, kernel_spec, complex, 0); // only DFT_ROWS accepted
		Mat magI2 = ShowMag(complex) * 256;
		imwrite("magI2.jpg", magI2);
		imwrite("mask.jpg", mask * 256);
		filteredthickness = GetFFTfilteredResult(complex);
		filteredthickness.convertTo(filteredthickness, CV_32SC1);
		filteredthickness = filteredthickness(Rect(100, 100, thickness.cols, thickness.rows));
		imwrite("filtered.jpg", filteredthickness);
		
		Mat flat_thickness = filteredthickness.clone();
		flat_thickness = flat_thickness-ref_line;
		for (int j = 0; j < nframes; j++)
		{
			for (int i = 0; i < m_x; i++)
				flat_thickness.at<int>(i,j)= motionshift.at<int>(j) + flat_thickness.at<int>(i, j);
		}
		correction_mat = flat_thickness.clone();
		std::ofstream myoutputtemp("postthickness.txt");
		for (int j = 0; j < nframes; j++)
		{
			myoutputtemp << postthickness.at<int>(1,j);
			myoutputtemp << "\r\n";

		}
		myoutputtemp.close();
		//debug_point = postthickness.at<int>(1, 3036);
		//debug_point = postthickness.at<int>(1, 3036);
	}
	//debug_point = thickness.at<int>(56, 173);
	//debug_point = thickness.at<int>(56, 173);


    

	/***************/
		
	/******************************get shift end*********************************/

	//***************************save necessary data************************//


	std::ofstream myoutput0("motionshift.txt");
	for (int j = 0; j < nframes; j++)
	{
		myoutput0 << motionshift.at<int>(j);
		myoutput0 << "\r\n";

	}
	myoutput0.close();
	std::ofstream myoutput1("frameshift.txt");
	for (int j = 0; j < nframes; j++)
	{
		myoutput1 << frameshift.at<int>(j);
		myoutput1 << "\r\n";

	}
	myoutput1.close();

	//***************************finished saving necessary data************************//
	tempmax = 0;
	tempmin = 0;

	for (int j = 0; j < nframes; j++)
	{
		for(int i=0;i<m_x;i++)
		{
			if (tempmax < correction_mat.at<int>(i, j))
				tempmax = correction_mat.at<int>(i, j);
			if (tempmin > correction_mat.at<int>(i, j))
				tempmin = correction_mat.at<int>(i, j);
		}
		
	}

	state_text = _T("output vidoe 0 ...");
	::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information
	int m_newz = m_z + tempmax - tempmin;
	
	int m_croppednewz;
	

	int m_newzscaled;
	
	if (keepsurfacechecked)
	{
		m_croppednewz = m_newz;
	}
	else
	{
		m_croppednewz = m_z;	
	}
	m_newzscaled = round(m_croppednewz * zscale / 100);
	Size S = Size((int)(m_x), m_newzscaled);    // Acquire input size	
	//***************************correct and output video0 using aviAPI*****************************/
	
	//***************************correct and output video0******************************************/
	int four_cc=VideoWriter::fourcc('F','F','V','1'); // Uncompressed yuv420p in avi container.
	VideoWriter outputVideo(dname0,0,15,S,false);    // Open the output 

	if (!outputVideo.isOpened())
	{
		::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the output file 0 "));
		return -1;
	}

	inputVideo.set(CAP_PROP_POS_FRAMES, 0);
	int frameaveraged =0;
	Mat tempFrame(m_newz, (int)(m_x), CV_32SC1, Scalar::all(0));
	bool grabsucess;
	grabsucess = 1;
	for (i = 0; i < nframes; i++)
	{
		
		Mat SingleChFrame(m_z, m_x, CV_8UC1, Scalar::all(0));
		Mat newFrame(m_newz, (int)(m_x), CV_8UC1, Scalar::all(0));
		inputVideo >> Oneframe;
		
		if (!Oneframe.empty())
		{
			split(Oneframe, chans);
			SingleChFrame = chans[0];	  
		}
		

		if (i > 15197)
		{
			debug_point = i;

		}
		for (int j = 0; j < m_x; j++)
		{
			if (i==15199 && j == 56)
			{
				 debug_point= thickness.at<int>(j,i);
				
			}
			for (int k = (m_z - thickness.at<int>(j, i)+depth_threshold); k < m_z; k++)
			{
				int temp = SingleChFrame.at<uchar>(k, j);
				temp = temp*exp(2 * intensity_alpha*(k -(m_z - thickness.at<int>(j, i)+ depth_threshold)));
				if (temp > 255) temp = 255;
				SingleChFrame.at<uchar>(k, j) = temp;

			}
		}
		for (int j = 0; j < m_x; j++)
		{
			if (i == 15199 && j == 0)
			{
				debug_point = thickness.at<int>(j, i);

			}
			for (int k = correction_mat.at<int>(j, i) - tempmin; k < correction_mat.at<int>(j, i) - tempmin + m_z; k++)
				newFrame.at<uchar>(k, j) = SingleChFrame.at<uchar>(k + tempmin - correction_mat.at<int>(j, i), j);
		}

		if (frameaveraged <= averaging)
		{
			Mat E;
			newFrame.convertTo(E, CV_32SC1);
			tempFrame = tempFrame + E;
			frameaveraged++;

		}
		if (frameaveraged == averaging)
		{
			Mat B,B_result;
			tempFrame = tempFrame / averaging;
			tempFrame.convertTo(B, CV_8UC1);
			if (keepsurfacechecked)
			{
				B_result = B;
			}
			else
				B_result = B.rowRange(-tempmin+(m_z-ref_line-8), -tempmin+m_z+tempmax);

			resize(B_result, B_result, S, 0, 0, INTER_AREA);
			outputVideo << B_result;
			frameaveraged =0;

			tempFrame = Mat::zeros(m_newz, (int)(m_x), CV_32SC1);
		}

		::PostMessage(DlgHandle, WM_MYMSG1, 3, i);//send message to dlg to show how many frames have been processed.

	}

	//for (int j = 0; j < m_x; j++)
	//{
	//	Mat newFrame((int)(m_z + tempmax - tempmin), (int)(m_y), CV_8UC1, Scalar::all(0));
	//	Mat averagedFrame;
	//	inputVideo.set(CAP_PROP_POS_FRAMES, 0);
	//	for (i = 0; i < m_y; i++)
	//	{
	//		Mat SingleChFrame((int)(m_z), (int)(m_x), CV_8UC1, Scalar::all(0));

	//		inputVideo >> Oneframe;
	//		split(Oneframe, chans);
	//		SingleChFrame = chans[0];
	//		for (int k = DiffRawtoNew[j][i] - tempmin; k < DiffRawtoNew[j][i] - tempmin + m_z; k++)
	//			newFrame.at<uchar>(k, i) = SingleChFrame.at<uchar>(k + tempmin - DiffRawtoNew[j][i], j);
	//	}
	//	resize(newFrame, averagedFrame, Size(), 1.0/averaging,1, CV_INTER_AREA);
	//	outputVideo << averagedFrame;
	//	::PostMessage(DlgHandle, WM_MYMSG1, 3, j);//send message to dlg to show how many frames have been processed.
	//}

	inputVideo.release();
	outputVideo.release();
	//***************************finish correcting and outputting video0******************************************/

	//****************************reslice video0 and do yscale****************************************************

	int m_yscaled = round(m_y * yscale / 100);
	if (m_yscaled % 4 != 0)
		m_yscaled = m_yscaled - (m_yscaled % 4);


	Size S_xy = Size(m_yscaled, (int)(m_x));    // Acquire input size	

	if (xysliceChecked)
	{
		state_text = _T("output video newxy ...");
		::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information

		VideoCapture inputVideo0_xz(dname0);
		//int four_cc = VideoWriter::fourcc('F', 'F', 'V', '1'); // Uncompressed yuv420p in avi container.

		VideoWriter outputVideo_xy(dname0xy, 0, 15, S_xy, false);    // Open the output 

		if (!outputVideo_xy.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the output file newxy.avi"));
			return -1;
		}

		if (!inputVideo0_xz.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the input file new.avi"));
			return -1;
		}

		std::vector<Mat> vinputvideo;
		inputVideo0_xz.set(CAP_PROP_POS_FRAMES, 0);
		vinputvideo.clear();
		for (int i = 0; i < m_y; i++)
		{
			Mat tempxzFrame;
			Mat tempxzFrameSingleCh;
			inputVideo0_xz >> tempxzFrame;
			split(tempxzFrame, chans);
			tempxzFrameSingleCh = chans[0];
			vinputvideo.push_back(tempxzFrameSingleCh.clone());
		}

		for (int i = 0; i < m_newzscaled; i++)
		{
			Mat tempxyFrame(m_x, m_y, CV_8UC1, Scalar::all(0));

			/*Mat tempxzFrame;
			Mat tempxzFrameSingleCh;

			inputVideo0_xz.set(CAP_PROP_POS_FRAMES, 0);*/
			for (int j = 0; j < m_y; j++)
			{
				/*inputVideo0_xz >> tempxzFrame;
				split(tempxzFrame, chans);
				tempxzFrameSingleCh = chans[0];*/
				Mat temp = vinputvideo.at(j).row(i);
				temp = temp.t();
				temp.copyTo(tempxyFrame.col(j));

			}
			Mat Fscaled;
			cv::resize(tempxyFrame, Fscaled, S_xy, 0, 0, INTER_AREA);
			outputVideo_xy << Fscaled;

			::PostMessage(DlgHandle, WM_MYMSG1, 3, i);//send message to dlg to show how many frames have been processed.

		}
		inputVideo0_xz.release();
		outputVideo_xy.release();

		for (int i = 0; i < m_y; i++)
			vinputvideo.at(i).release();
		vinputvideo.clear();

	}
	

	//**************************end of reslicing****************************************************/


	//***************************correct and output video1******************************************/
	if (ch2checked)
	{
		state_text = _T("output vidoe 1 ...");
		::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information
		VideoCapture inputVideo1(sname1);
		if (!inputVideo1.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the source file 1 "));
			return -1;
		}

		//VideoWriter outputVideo1;    // Open the output

		//int four_cc = VideoWriter::fourcc('F', 'F', 'V', '1'); // Uncompressed yuv420p in avi container.
		VideoWriter outputVideo1(dname1, 0, 15, S, false);    // Open the output 
		//outputVideo1.open(dname1, ex, 15, S, false);
		if (!outputVideo1.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the output file 1 "));
			return -1;
		}

		inputVideo1.set(CAP_PROP_POS_FRAMES, 0);
		int frameaveraged = 0;
		Mat tempFrame((int)(m_z + tempmax - tempmin), (int)(m_x), CV_32SC1, Scalar::all(0));
		for (i = 0; i < nframes; i++)
		{
			Mat SingleChFrame((int)(m_z), (int)(m_x), CV_8UC1, Scalar::all(0));
			Mat newFrame((int)(m_z + tempmax - tempmin), (int)(m_x), CV_8UC1, Scalar::all(0));

			inputVideo1 >> Oneframe;
			split(Oneframe, chans);
			SingleChFrame = chans[0];
			for (int j = 0; j < m_x; j++)
			{
				for (int k = correction_mat.at<int>(j, i) - tempmin; k < correction_mat.at<int>(j, i) - tempmin + m_z; k++)
					newFrame.at<uchar>(k, j) = SingleChFrame.at<uchar>(k + tempmin - correction_mat.at<int>(j, i), j);
			}

			if (frameaveraged <= averaging)
			{
				Mat E;
				newFrame.convertTo(E, CV_32SC1);
				tempFrame = tempFrame + E;
				frameaveraged++;

			}
			if (frameaveraged == averaging)
			{
				/*Mat B;
				tempFrame = tempFrame / averaging;
				tempFrame.convertTo(B, CV_8UC1);
				resize(B, B, S, 0, 0, INTER_AREA);
				outputVideo1 << B;
				frameaveraged = 0;

				tempFrame = Mat::zeros((int)(m_z + tempmax - tempmin), (int)(m_x), CV_32SC1);*/


				Mat B, B_result;
				tempFrame = tempFrame / averaging;
				tempFrame.convertTo(B, CV_8UC1);
				if (keepsurfacechecked)
				{
					B_result = B;
				}
				else
					B_result = B.rowRange(-tempmin + (m_z - ref_line - 8), -tempmin + m_z + tempmax);

				resize(B_result, B_result, S, 0, 0, INTER_AREA);
				outputVideo1 << B_result;
				frameaveraged = 0;

				tempFrame = Mat::zeros(m_newz, (int)(m_x), CV_32SC1);
			}

			::PostMessage(DlgHandle, WM_MYMSG1, 3, i);//send message to dlg to show how many frames have been processed.

		}

		inputVideo1.release();
		outputVideo1.release();
	}
	//***************************finish correcting and outputting video1******************************************/

	//****************************reslice video1 and do yscale****************************************************
	if (ch2checked&&xysliceChecked)
	{
		state_text = _T("output video new1xy ...");
		::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information

		VideoCapture inputVideo1_xz(dname1);
		//int four_cc = VideoWriter::fourcc('F', 'F', 'V', '1'); // Uncompressed yuv420p in avi container.

	//	Size S_xy = Size(m_yscaled, (int)(m_x));    // Acquire input size	
		VideoWriter outputVideo1_xy(dname1xy, 0, 15, S_xy, false);    // Open the output 

		if (!outputVideo1_xy.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the output file new1xy.avi"));
			return -1;
		}

		std::vector<Mat> vinputvideo;
		inputVideo1_xz.set(CAP_PROP_POS_FRAMES, 0);
		vinputvideo.clear();
		for (int i = 0; i < m_y; i++)
		{
			Mat tempxzFrame;
			Mat tempxzFrameSingleCh;
			inputVideo1_xz >> tempxzFrame;
			split(tempxzFrame, chans);
			tempxzFrameSingleCh = chans[0];
			vinputvideo.push_back(tempxzFrameSingleCh.clone());
		}


		for (int i = 0; i < m_newzscaled; i++)
		{
			Mat tempxyFrame(m_x, m_y, CV_8UC1, Scalar::all(0));

			/*Mat tempxzFrame;
			Mat tempxzFrameSingleCh;

			inputVideo1_xz.set(CAP_PROP_POS_FRAMES, 0);*/
			for (int j = 0; j < m_y; j++)
			{
				
				Mat temp = vinputvideo.at(j).row(i);
				temp = temp.t();
				temp.copyTo(tempxyFrame.col(j));

			}
			Mat Fscaled;
			resize(tempxyFrame, Fscaled, S_xy, 0, 0, INTER_AREA);
			outputVideo1_xy << Fscaled;

			::PostMessage(DlgHandle, WM_MYMSG1, 3, i);//send message to dlg to show how many frames have been processed.

		}
		inputVideo1_xz.release();
		outputVideo1_xy.release();
		for (int i = 0; i < m_y; i++)
			vinputvideo.at(i).release();
		vinputvideo.clear();

	}
	
	//end of reslicing of new1 video****************************************************************/
	
	//***************************correct and output video2******************************************/
	if (ch3checked)
	{
		state_text = _T("output vidoe 2 ...");
		::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information
		VideoCapture inputVideo2(sname2);
		if (!inputVideo2.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the source file 2 "));
			return -1;
		}

		VideoWriter outputVideo2(dname2, 0, 15, S, false);    // Open the output 
		//VideoWriter outputVideo2;    // Open the output 
		//outputVideo2.open(dname2, ex, 15, S, false);
		if (!outputVideo2.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the output file 2 "));
			return -1;
		}

		inputVideo2.set(CAP_PROP_POS_FRAMES, 0);
		int frameaveraged = 0;
		Mat tempFrame((int)(m_z + tempmax - tempmin), (int)(m_x), CV_32SC1, Scalar::all(0));
		for (i = 0; i < nframes; i++)
		{
			Mat SingleChFrame((int)(m_z), (int)(m_x), CV_8UC1, Scalar::all(0));
			Mat newFrame((int)(m_z + tempmax - tempmin), (int)(m_x), CV_8UC1, Scalar::all(0));

			inputVideo2 >> Oneframe;
			split(Oneframe, chans);
			SingleChFrame = chans[0];
			for (int j = 0; j < m_x; j++)
			{
				for (int k = correction_mat.at<int>(j, i) - tempmin; k <correction_mat.at<int>(j, i) - tempmin + m_z; k++)
					newFrame.at<uchar>(k, j) = SingleChFrame.at<uchar>(k + tempmin - correction_mat.at<int>(j, i), j);
			}

			if (frameaveraged <= averaging)
			{
				Mat E;
				newFrame.convertTo(E, CV_32SC1);
				tempFrame = tempFrame + E;
				frameaveraged++;

			}
			if (frameaveraged == averaging)
			{
				/*Mat B;
				tempFrame = tempFrame / averaging;
				tempFrame.convertTo(B, CV_8UC1);
				resize(B, B, S, 0, 0, INTER_AREA);
				outputVideo2 << B;
				frameaveraged = 0;

				tempFrame = Mat::zeros((int)(m_z + tempmax - tempmin), (int)(m_x), CV_32SC1);*/
				Mat B, B_result;
				tempFrame = tempFrame / averaging;
				tempFrame.convertTo(B, CV_8UC1);
				if (keepsurfacechecked)
				{
					B_result = B;
				}
				else
					B_result = B.rowRange(-tempmin + (m_z - ref_line - 8), -tempmin + m_z + tempmax);

				resize(B_result, B_result, S, 0, 0, INTER_AREA);
				outputVideo2 << B_result;
				frameaveraged = 0;

				tempFrame = Mat::zeros(m_newz, (int)(m_x), CV_32SC1);
			}

			::PostMessage(DlgHandle, WM_MYMSG1, 3, i);//send message to dlg to show how many frames have been processed.

		}

		inputVideo2.release();
		outputVideo2.release();
	}

	//****************************reslice video2 and do yscale****************************************************
	if (ch3checked && xysliceChecked)
	{

		state_text = _T("output video new2xy ...");
		::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information

		VideoCapture inputVideo2_xz(dname2);
		//int four_cc = VideoWriter::fourcc('F', 'F', 'V', '1'); // Uncompressed yuv420p in avi container.

	//	Size S_xy = Size(m_yscaled, (int)(m_x));    // Acquire input size	
		VideoWriter outputVideo2_xy(dname2xy, 0, 15, S_xy, false);    // Open the output 

		if (!outputVideo2_xy.isOpened())
		{
			::PostMessage(DlgHandle, WM_MYMSG1, 2, (LPARAM)(LPVOID)_T("can't open the output file new2xy.avi"));
			return -1;
		}

		std::vector<Mat> vinputvideo;
		inputVideo2_xz.set(CAP_PROP_POS_FRAMES, 0);
		vinputvideo.clear();
		for (int i = 0; i < m_y; i++)
		{
			Mat tempxzFrame;
			Mat tempxzFrameSingleCh;
			inputVideo2_xz >> tempxzFrame;
			split(tempxzFrame, chans);
			tempxzFrameSingleCh = chans[0];
			vinputvideo.push_back(tempxzFrameSingleCh.clone());
		}

		for (int i = 0; i < m_newzscaled; i++)
		{
			Mat tempxyFrame(m_x, m_y, CV_8UC1, Scalar::all(0));

			for (int j = 0; j < m_y; j++)
			{
				Mat temp = vinputvideo.at(j).row(i);
				temp = temp.t();
				temp.copyTo(tempxyFrame.col(j));

			}
			Mat Fscaled;
			resize(tempxyFrame, Fscaled, S_xy, 0, 0, INTER_AREA);
			outputVideo2_xy << Fscaled;

			::PostMessage(DlgHandle, WM_MYMSG1, 3, i);//send message to dlg to show how many frames have been processed.

		}
		inputVideo2_xz.release();
		outputVideo2_xy.release();
		for (int i = 0; i < m_y; i++)
			vinputvideo.at(i).release();
		vinputvideo.clear();
	}
	

	//end of reslicing of new1 video****************************************************************/


	//***************************finish correcting and outputting video2******************************************/		

	state_text = _T("Finished");
	::PostMessage(DlgHandle, WM_MYMSG1, 4, (LPARAM)(LPVOID)(&state_text)); // show video information
	Sleep(50);
	/******************release all mat data**********************/
	//thickness.release();
	//Diffofthickness.release();
	//frameshift.release();
	//motionshift.release();
	//correction_mat.release();
	//filteredthickness.release();

	



	return 0;
}


LRESULT CVolumeCorrectionDlg::OnCustomMessage(WPARAM w, LPARAM l)
{
	if (w == 0)
	{
		MessageBox((LPCTSTR)l);
	}
	if (w == 1)
	{
		CString *text = (CString*)l;
		SetDlgItemText(IDC_EDIT_VIDEOINFO, *text);
	}
	if (w == 2)
	{
		MessageBox((LPCTSTR)l);
	}
	if (w == 3) //frame number processed
	{
		SetDlgItemInt(IDC_EDIT_PROGRESS, l);
	}
	if (w == 4)
	{
		CString *text = (CString*)l;
		SetDlgItemText(IDC_EDIT_STATE, *text);
	}

	return 0;
}


int CVolumeCorrectionDlg::GetIndexofHistMax(Mat m_input, int m_cols, int *max_value)
{

	//this function works like histcounts in matlab which counts the times of each number appears in the m_input array.
	// m_input is a arry to store pxiel-wise z shift compared to last frame. It has a value range from minValue to maxValue;
	// return the index which has maximum counts and the corresponding value;
	int* hist;
	int temp;	
	int tempmax = 0;
	int tempindex=0;

	double maxValue;
	double minValue;
	minMaxLoc(m_input, &minValue, &maxValue);
	int histSize = (int)(maxValue - minValue + 1);
	hist = new int[histSize];
	std::fill_n(hist,histSize,0);
	//convert element value to index by adding the abs(minValue). This convert the minimum value to index of 0;
	//and all other values to the corresponding index as well.
	//the size of the index equals to maxValue - minValue +1;
	for (int i = 0; i < m_cols; i++)
	{
		temp = m_input.at<int>(i);
		hist[temp-(int)(minValue)]++;
	}

	for (int i = 0; i < histSize; i++)
	{
		if (tempmax < hist[i])
		{
			tempmax = hist[i];//the maximum of count.
			tempindex = i; //the value that has maximum count;
		}
	}
	*max_value = tempmax;
	delete[] hist;
	return (tempindex + (int)(minValue));
}


void CVolumeCorrectionDlg::OnBnClickedButtonTest()
{
	// TODO: Add your control notification handler code here
	double myarray[256] = {1,1,2,2,20};
	
	double m_length = 4;
	int myarraysize[2] = { 0, 1};
	double temp;
	CString outputtext;
	double tempdata[25600];
	for (int i = 0; i < m_length; i++)
		tempdata[i] = myarray[i];
	temp = 0;
	outputtext.Format(_T("%.2f"), temp);
	SetDlgItemText(IDC_TEST, outputtext);

}


Mat CVolumeCorrectionDlg::GetFFTfilteredResult(Mat complex)
{
	Mat work;
	idft(complex, work);
	Size mask_size = complex.size();
	//  dft(complex, work, DFT_INVERSE + DFT_SCALE);
	Mat planes[] = { Mat::zeros(complex.size(), CV_32F), Mat::zeros(complex.size(), CV_32F) };
	split(work, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

	magnitude(planes[0], planes[1], work);    // === sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
											  //normalize(work, work, 0, 1, NORM_MINMAX);
	int debug_test = mask_size.width*mask_size.height;

	return planes[0] / (mask_size.width*mask_size.height);
}

Mat  CVolumeCorrectionDlg::computeDFT(Mat padded) {

	// copy the source image, on the border add zero values
	Mat planes[] = { Mat_< float>(padded), Mat::zeros(padded.size(), CV_32F) };
	// create a complex matrix
	Mat complex;
	merge(planes, 2, complex);
	dft(complex, complex, DFT_COMPLEX_OUTPUT);  // fourier transform
	return complex;
}

Mat  CVolumeCorrectionDlg::ShowMag(Mat complex) {
	Mat magI;
	Mat planes[] = {
		Mat::zeros(complex.size(), CV_32F),
		Mat::zeros(complex.size(), CV_32F)
	};
	split(complex, planes); // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], magI); // sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
										   // switch to logarithmic scale: log(1 + magnitude)
	magI += Scalar::all(1);
	log(magI, magI);
	shift(magI); // rearrage quadrants
				 // Transform the magnitude matrix into a viewable image (float values 0-1)
	normalize(magI, magI, 1, 0, NORM_INF);
	return magI;
}
void  CVolumeCorrectionDlg::shift(Mat magI) {

	// crop if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);                     // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
}
Mat CVolumeCorrectionDlg::createButtworthFilterMask(Size mask_size, int ksizex, int ksizey) {

	// create empty mask
	Mat mask = Mat::zeros(mask_size, CV_32F);
	for (int i = 0; i<mask_size.width; i++)
		for (int j = 0; j < mask_size.height; j++)
		{
			float dy = abs(j - mask_size.height / 2);
			float dx = abs(i - mask_size.width / 2);
			mask.at<float>(j, i) = 1 / (1 + (pow((dx / ksizex), 2) + pow((dy / ksizey), 2)));
		}

	return mask;
}

void CVolumeCorrectionDlg::OnEnChangeBrowseInput1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString tempName, folderName;

	GetDlgItemText(IDC_BROWSE_INPUT1, tempName);
	
	int index = tempName.ReverseFind(_T('\\'));
	folderName = tempName.Left(index);
	SetDlgItemText(IDC_BROWSE_OUTPUT, folderName);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_BROWSE_INPUT1);
	if (pEdit)
	{
		// Scroll the text to the rightmost position
		pEdit->SetSel(tempName.GetLength(), tempName.GetLength());
	}


	//automatically update file name for shg and tpf channel
	CString searchPathTPF = folderName + _T("\\") + _T("*") + _T("TPF") + _T("*");
	CString searchPathSHG = folderName + _T("\\") + _T("*") + _T("SHG") + _T("*");

	//autofill shg and tpf channel
	if (!m_bInitializing)
	{
		CFileFind finder;

		volatile BOOL bFound = 0;
		bFound =finder.FindFile(searchPathTPF);
		BOOL bfoundSHG = false;
		BOOL bfoundTPF = false;

		while (bFound)
		{
			bFound = finder.FindNextFile();

			// Exclude "." and ".." directories
			if (!finder.IsDots())
			{
				// Print or process the file name
				CString fileName = finder.GetFilePath();
				SetDlgItemText(IDC_BROWSE_INPUT2, fileName);
				bfoundTPF = true;

				CEdit* pEdit = (CEdit*)GetDlgItem(IDC_BROWSE_INPUT2);
				if (pEdit)
				{
					// Scroll the text to the rightmost position
					pEdit->SetSel(fileName.GetLength(), fileName.GetLength());
				}

			}
		}
		if(!bfoundTPF)
		{
			CButton* m_ctlCheck2 = (CButton*)GetDlgItem(IDC_CHECK_INPUT2);
			int ChkBox = m_ctlCheck2->GetCheck();
		    if (ChkBox == BST_CHECKED)
				MessageBox(_T("no TPF file was found."), _T("Warnning"));
			//delete m_ctlCheck2;
		}
		
		bFound = 0;
		bFound = finder.FindFile(searchPathSHG);
		while (bFound)
		{
			bFound = finder.FindNextFile();

			// Exclude "." and ".." directories
			if (!finder.IsDots())
			{
				// Print or process the file name
				CString fileName = finder.GetFilePath();
				SetDlgItemText(IDC_BROWSE_INPUT3, fileName);
				bfoundSHG = true;

				CEdit* pEdit = (CEdit*)GetDlgItem(IDC_BROWSE_INPUT3);
				if (pEdit)
				{
					// Scroll the text to the rightmost position
					pEdit->SetSel(fileName.GetLength(), fileName.GetLength());
				}


			}
		}
		if (!bfoundSHG)
		{
			CButton* m_ctlCheck3 = (CButton*)GetDlgItem(IDC_CHECK_INPUT3);
			int ChkBox = m_ctlCheck3->GetCheck();
			if (ChkBox == BST_CHECKED)
				MessageBox(_T("no SHG file was found."), _T("Warnning"));
			//delete m_ctlCheck3;
		}

		finder.Close();
	}

	


}


void CVolumeCorrectionDlg::OnBnClickedButtonHelp()
{
	// TODO: Add your control notification handler code here
	LPCTSTR longText = _T("1. The motion correction is based on selected video in the RCM channel,"
		"check the SHG and TPF channel, the program will automatically localize the files with SHG and TPF in their names.\n"
		"2. The Alpha value was used for depth intensity correction, the initial value can be set at 0.001 - 0.006.\n"
		"3. If Keep Surface Profile is checked, surface flattening will not be applied.\n"
		"4. With the video in the RCM channel selected, click the START CORRECTION button to start the correction procedure.");
	MessageBox(longText, _T("Instructions"));
}
