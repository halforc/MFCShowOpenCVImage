
// MFCApplication3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication3Dlg �Ի���



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


// CMFCApplication3Dlg ��Ϣ�������

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton1()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
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
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
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
    fopen_s(&fpw, filenamechar, "wb");//���û���򴴽�������������ͷ��ʼд  
    if(fpw == NULL) {
        fclose(fpw);
        return false;
    }
    int channl = image.channels();//��һ���ֽ�  ͨ��  
    int rows = image.rows;     //�ĸ��ֽڴ� ����  
    int cols = image.cols;   //�ĸ��ֽڴ� ����  

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
    fread(&channl, sizeof(char), 1, fpr);//��һ���ֽ� ͨ��  
    fread(&imagerows, sizeof(char), 4, fpr); //�ĸ��ֽڴ� ����  
    fread(&imagecols, sizeof(char), 4, fpr); //�ĸ��ֽڴ� ����  
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
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
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
