#pragma once
/*
 * @author    : gonzalez
 * @time      : 2022.5.2-2022.5.9
 * @function  : AlphaBeta ͷ�ļ�
 */


#include <vector>              // vector����
#include <iostream>            // ��׼��
#include <algorithm>           // �㷨��
#include <stack>               // ���ȶ���
#include <graphics.h>          // EasyX��
#include <conio.h>             // EasyX��
using namespace std;


/**********************************************************************/
//@author    : gonzalez
//@time      : 2022.4.27-2022.5.9
//@function  : ����alphabeta����ʵ�ּ�������ai
//@notice    : ����ֵ�涨-->True�ɹ���Falseʧ��
//             '1'����  '0'����  '*'����
//             Ĭ���°���
/**********************************************************************/

//�궨������
#define BOARDLENGHT 15  //���̳���
#define BOARDWIDTH  15  //���̿��
#define BOARDADD    2   //���������ֵ


#define BLACKCHESS     '1'  // ������Ӵ��� 
#define WHITECHESS     '0'  // ������Ӵ���
#define NONECHESS      '*'  // ��������̴���
#define EACHSEARCH     2    // ����ÿ���̽������
#define EXPLORELAYER   6    // ����̽������

//@function:�����Ϣ�ṹ��
struct NODE {
	vector<NODE>children;               //���ӽ��
	vector<short> blackAdd;             //��ӵĺ������� row*100+col
	vector<short> whiteAdd;             //��ӵİ������� row*100+col
	short layer = 0;
	int alpha = INT_MIN;                //�ý���alphaֵ-->���ֵ
	int beta = INT_MAX;                 //�ý���betaֵ-->��Сֵ
};

//@function:ͳ�Ʊ߽���Ϣ
struct BORDER{
	int left = 0;
	int top = 0;
	int right = 0;
	int down = 0;
};

//@function:����Ѱ�ҽ�����չ��
struct NODESCORE {
	short rowSite = 0;
	short colSite = 0;
	int score;
};

//@function:alpha-beta��֦������
class searchAlphaBeta {
protected:
	NODE head;
	char board[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { '\0' };
protected:
    
	int getScoreFromString(string& get);                                                                              //�õ�һ��string���������÷�
    int toneUpAssessIn(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site);                                   //���溯���ڲ�����
    void toneUpAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site, char sort);	                      //��������
	bool searchThreeMust(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& get, char chessSort);                  //�����������
	bool searchFiveMust(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& get, char chessSort);                   //������������
	bool fiveMust(string& get, char chessSort);                                                                       //�������������ڲ�ִ�к���
	bool firstLayerAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], int& feeBack);                                   //��һ����������
	bool chessAround(int row, int col, char(*chess)[BOARDLENGHT + BOARDADD]);                                         //�ж�NONECHESS��Χ�Ƿ����CEHSS
	bool findBorder(char(*chessBoard)[BOARDLENGHT + BOARDADD], BORDER& bor);                                          //�ҵ������߽�
	int eachGet(string& extract);                                                                                     //���ۺ����жԲ�ͬ��������ز�ͬ�÷�
	int assessBoardValue(char(*chessBoard)[BOARDLENGHT + BOARDADD]);                                                  //ȫ����������
	bool seekBestPoint(char(*chessBoard)[BOARDLENGHT + BOARDADD], char chessClass, vector<NODESCORE>& result);        //�ҵ����ŵļ���������������չ
	int alphabetaAlgorithm(char(*chessBoard)[BOARDLENGHT + BOARDADD], int depth, int alpha, int beta);                //����alpha-beta��֦����

public:
	searchAlphaBeta(char(*chessBoard)[BOARDLENGHT + BOARDADD]);                                                       //�������̺���                             
	int alphabetaGetBack(void);                                                                                       //ִ�к���
};


/**********************************************************************/
//@author    : gonzalez
//@time      : 2022.4.27-2022.5.9
//@function  : ������ӻ�
/**********************************************************************/

//@function : �洢���沼�ֵĽṹ��
struct SURFACE{
	short left = 0;
	short top = 0;
	short right = 0;
	short bottom = 0;
};

//@function : ����ͼ��ĳ�ʼ��
#define PICTUREBKWIDTH    700//��Ϸ������
#define PICTUREBKLENGTH   1000//��Ϸ���泤��
#define CBbetweenBK       25//��˵���
#define PICTURECBWIDTH    650//���̿��

#define CHESSMID          42//���̸��ӿ��
#define CHESSWIDTH        36//�ж��������ȷ������ֱ��

#define BUTTONLENGTH     255//��������
#define BUTTONWIDTH      125//�������
#define PICTURELENGTH    255//���½�ͼƬ����
#define PICTUREWIDTH     335//���½�ͼƬ���

#define ENDPICLENGTH     394//����ͼƬ����
#define ENDPICWIDTH      250//����ͼƬ���

#define REGRET            -1//����ָ��
#define RESTART           -2//�ؿ�ָ��

#define NOWINNER   0//��ʤ��
#define BLACKWIN   1//����ʤ
#define WHITEWIN   2//����ʤ

//@function : ͼ��UI������ʾ��
class showUI {
protected:

	//���沼�ֽṹ�嶨��
	SURFACE boardImage;
	SURFACE regretButton;
	SURFACE restartButton;
	SURFACE pictureSite;
	SURFACE winloseShow;

	//����ͼƬ���ö���
	IMAGE backGround;
	IMAGE chessBoard;
	IMAGE chessBlack;
	IMAGE chessWhite;
	IMAGE chessWhitePre;

	IMAGE regretImage;
	IMAGE regretMouseImage;
	IMAGE restartImage;
	IMAGE restartMouseImage;
	IMAGE thinkingImage;
	IMAGE userImage;

	IMAGE winImage;
	IMAGE loseImage;

	bool findXY(int x, int y, int& boardX, int& boardY);            //�ҵ�xy����Ӧ�������е�λ��
	void endShow(void);                                             //������ֻ�ܰ������¿�ʼ��ť
public:
	showUI(void);                                                   //���캯��
	bool refresh(char(*chessBoard)[BOARDLENGHT + BOARDADD]);        //���ý������
	bool uiLoad(void);                                              //���ر������溯��
	int uiGetBack(char(*chessBoard)[BOARDLENGHT + BOARDADD]);       //��������ִ�к���
	bool addWhite(int site);                                        //����������Ӱ���
	void winShow(void);                                             //�ɹ���ʾ
	void loseShow(void);                                            //ʧ����ʾ
	void showThinking(void);                                        //�л�ͼƬ
	void showNormal(void);                                          //�л�ͼƬ
};


/**********************************************************************/
//@author    : gonzalez
//@time      : 2022.5.4-2022.5.9
//@function  : ���๤�ߺ���
/**********************************************************************/
int judgeWinner(char(*chessBoard)[BOARDLENGHT + BOARDADD]);         //�ж��Ƿ�ɹ�
void refreshBoard(char(*chessBoard)[BOARDLENGHT + BOARDADD]);       //��������

