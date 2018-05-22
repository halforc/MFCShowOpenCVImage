
// MFCApplication3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication3Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton1()
{
    // TODO:  在此添加控件通知处理程序代码
    cv::Mat imgSrc = cv::imread("img.png");

    CRect rect;
    GetDlgItem(IDC_STATIC1)->GetClientRect(&rect);
    cv::Size winSize(rect.right, rect.bottom);

    // Resize the source to the size of the destination image if necessary  
    cv::Mat cvImgTmp(winSize, CV_8UC3);
    if(imgSrc.size() != winSize) {
        cv::resize(imgSrc, cvImgTmp, winSize);
    } else {
        cvImgTmp = imgSrc;
    }

    CImage imgDst;
    Mat2CImage(&cvImgTmp, imgDst);
    imgDst.Draw(GetDlgItem(IDC_STATIC1)->GetDC()->GetSafeHdc(), rect);
}


void CMFCApplication3Dlg::OnBnClickedButton2()
{
    // TODO:  在此添加控件通知处理程序代码
    cv::Mat imgSrc = cv::imread("img.png");
    imageToStreamFile(imgSrc, "test.dat");
}

int CMFCApplication3Dlg::Mat2CImage(Mat *mat, CImage &img)
{
    if(!mat || mat->empty())
        return -1;
    int nBPP = mat->channels() * 8;
    img.Create(mat->cols, mat->rows, nBPP);
    if(nBPP == 8) {
        static RGBQUAD pRGB[256];
        for(int i = 0; i < 256; i++)
            pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed = i;
        img.SetColorTable(0, 256, pRGB);
    }
    uchar* psrc = mat->data;
    uchar* pdst = (uchar*)img.GetBits();
    int imgPitch = img.GetPitch();
    for(int y = 0; y < mat->rows; y++) {
        memcpy(pdst, psrc, mat->cols*mat->channels());//mat->step is incorrect for those images created by roi (sub-images!)  
        psrc += mat->step;
        pdst += imgPitch;
    }
    return 0;
}

bool CMFCApplication3Dlg::imageToStreamFile(cv::Mat image, std::string filename)
{
    if(image.empty()) return false;
    const char *filenamechar = filename.c_str();
    FILE *fpw;
    fopen_s(&fpw, filenamechar, "wb");//如果没有则创建，如果存在则从头开始写  
    if(fpw == NULL) {
        fclose(fpw);
        return false;
    }
    int channl = image.channels();//第一个字节  通道  
    int rows = image.rows;     //四个字节存 行数  
    int cols = image.cols;   //四个字节存 列数  

    fwrite(&channl, sizeof(char), 1, fpw);
    fwrite(&rows, sizeof(char), 4, fpw);
    fwrite(&cols, sizeof(char), 4, fpw);
    char* dp = (char*)image.data;
    if(channl == 3) {
        for(int i = 0; i < rows*cols; i++) {
            fwrite(&dp[i * 3], sizeof(char), 1, fpw);
            fwrite(&dp[i * 3 + 1], sizeof(char), 1, fpw);
            fwrite(&dp[i * 3 + 2], sizeof(char), 1, fpw);
        }
    } else if(channl == 1) {
        for(int i = 0; i < rows*cols; i++) {
            fwrite(&dp[i], sizeof(char), 1, fpw);
        }
    }
    fclose(fpw);
    return true;
}

bool CMFCApplication3Dlg::StreamFileToImage(std::string filename, cv::Mat &image)
{
    const char *filenamechar = filename.c_str();
    FILE *fpr;
    errno_t err = fopen_s(&fpr, filenamechar, "rb");
    if(err != 0) {
        fclose(fpr);
        return false;
    }
    int channl(0);
    int imagerows(0);
    int imagecols(0);
    fread(&channl, sizeof(char), 1, fpr);//第一个字节 通道  
    fread(&imagerows, sizeof(char), 4, fpr); //四个字节存 行数  
    fread(&imagecols, sizeof(char), 4, fpr); //四个字节存 列数  
    if(channl == 3) {
        image = Mat::zeros(imagerows, imagecols, CV_8UC3);
        char* pData = (char*)image.data;
        for(int i = 0; i < imagerows*imagecols; i++) {
            fread(&pData[i * 3], sizeof(char), 1, fpr);
            fread(&pData[i * 3 + 1], sizeof(char), 1, fpr);
            fread(&pData[i * 3 + 2], sizeof(char), 1, fpr);
        }
    } else if(channl == 1) {
        image = Mat::zeros(imagerows, imagecols, CV_8UC1);
        char* pData = (char*)image.data;
        for(int i = 0; i < imagerows*imagecols; i++) {
            fread(&pData[i], sizeof(char), 1, fpr);
        }
    }
    fclose(fpr);
    return true;
}

void CMFCApplication3Dlg::OnBnClickedButton3()
{
    // TODO:  在此添加控件通知处理程序代码
    Mat img;
    StreamFileToImage("test.dat", img);

    CRect rect;
    GetDlgItem(IDC_STATIC1)->GetClientRect(&rect);
    cv::Size winSize(rect.right, rect.bottom);

    // Resize the source to the size of the destination image if necessary  
    cv::Mat cvImgTmp(winSize, CV_8UC3);
    if(img.size() != winSize) {
        cv::resize(img, cvImgTmp, winSize);
    } else {
        cvImgTmp = img;
    }

    CImage imgDst;
    Mat2CImage(&cvImgTmp, imgDst);
    imgDst.Draw(GetDlgItem(IDC_STATIC1)->GetDC()->GetSafeHdc(), rect);
}
