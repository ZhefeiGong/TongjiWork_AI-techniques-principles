/*
 * @author  : gonzalez
 * @time    : 2022.3.28-2022.4.12
 * @function: ʵ��A���������������ͷ�ļ�
 */

#pragma once
#include <vector>              //vector����
#include <queue>               //����
#include <graphics.h>          //EasyX��
#include <conio.h>             //EasyX��
#include <windows.h>           //sleep����
#include <time.h>              //��¼ִ��ʱ��
#include <string>              //ʹ��string�ַ���
using namespace std;           //ʹ��vector����

#define FINE         1         //��������
#define FAIL        -1         //���󷵻�
#define BoardSize    3         //����������洢��Χ


/*��������ѡ������ʽ����*/
//#define OUFOFPOSITION                //����λ��������
//#define COEFFICIENTMANHANTTAN        //ϵ�������پ��뷨--->���ܴ��ڸ߹����������˲��ǿɲ��ɵģ�������ܲ������Ž�       
//#define EULERDISTANCE                //ŷ�����뷨
#define DISTANCETOTARGET             //�����پ��뷨�������ӵ���Ŀ��λ�õľ����

/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
struct AStarTreeNote {                                           //A*�������洢�ṹ��
	unsigned long long FatherNote = 0;
	unsigned long long Treelayout = 0;
	int Treeprice = 0;
	int Treeinspire = 0;
	bool Find = false;                                           //�Ƿ񱻱���
};
struct AStarQueNote{                                             //open/close��洢�ṹ��
	unsigned long long Quelayout = 0;
	int Queprice = 0;                                            //���ۺ���ֵ
	int Queinspire = 0;                                          //��������ֵ
};

/*Ĭ��char���ַ��洢�����뷽ʽ����(0��ʾ�ո�)
        * * * * * * *
        * 0 * 1 * 2 *
        * * * * * * *     
        * 3 * 4 * 5 *      --ת��--��   012345678
        * * * * * * *
        * 6 * 7 * 8 *
        * * * * * * *
 */

class AStarEightDigital {
public:
	char start [BoardSize][BoardSize] = { '\0' };                //��ʼ��������ʽ
	char end   [BoardSize][BoardSize] = { '\0' };                //�յ��������ʽ
	vector<AStarQueNote> OpenStorage;                            //open����vector
	vector<AStarQueNote> CloseStorage;                           //close����vector
 	vector<AStarTreeNote> TreeList;                              //�洢���������е�������
public:
	AStarEightDigital();                                                     //���캯��
	int setup(char(*s)[BoardSize], char(*e)[BoardSize]);                     //��ʼ��
	int DataChangeGraph(unsigned long long& in , char(*arry)[BoardSize]);    //unsigned long long ת char��ʽ����������
	int GraphChangeData(char(*arry)[BoardSize], unsigned long long& in);     //unsigned long long ת unsigned long long 
	int setInspire(AStarQueNote& in);                                        //��ȡ����ʽ������ֵ
	int FindOpenMin(int& site);
	bool FindOpen(unsigned long long& in, int& site);
	bool FindClose(unsigned long long& in, int& site);
	int AStarMove(char(*arry)[BoardSize], AStarTreeNote& father);
	int FindFather(AStarQueNote& node, AStarTreeNote& father);
	int AStar(void);

	int routeGet(vector<unsigned long long>& routeResult);                    //���������·��
	int generateGet(int& get);                                                //�������ɽ����
	int expandGet(int& get);                                                  //������չ�����

};


/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
struct AREA{                                            //���ӻ�����洢
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
};
struct TreeShow {                                       //���ӻ����ʹ�ӡ�洢�ṹ��
	int x = 0;
	int y = 0;
	unsigned long long dad = 0;
	unsigned long long lay = 0;
};

#define BKCOLOR         WHITE
#define PICWIDE         120
#define BKLENGTH        800
#define BKWIDTH         600
#define BLOCKSIZE       40
#define BUTTONHIGHT     15
#define SYGO            1
#define MYGO            0
#define SLEEPTIME       350                             //������ʾ֮��ļ��ʱ��
#define WIN           6

class EasyXSHOW {
public:
	IMAGE num[9];
	AREA General, cherkerboard, dataout, stateshow, buttonoperate;
	AREA eightborad, startstate, endstate;
	AREA systemgo, myselfgo;
	AREA upbutton, rightbutton, downbutton, leftbutton;
	AREA reset,initialbegin, initialend;
public:
	EasyXSHOW();                                      //���ӻ���ʼ���캯��
	int Initialbg(void);
	int Boardshow(char(*array)[BoardSize]);
	int blockshow(int x, int y, char(*array)[BoardSize]);
	int block(int x, int y, int num);
	int button(int x, int y, int length, int width, TCHAR text[]);
	int stateinitial(char(*st)[BoardSize], char(*end)[BoardSize]);
	int moveinitial(char(*state)[BoardSize], AREA& site);
	int InitialPage(char(*start)[BoardSize], char(*end)[BoardSize]);
	int mainbg(char(*start)[BoardSize], char(*state)[BoardSize], char(*end)[BoardSize]);
	int mainoperate(void);
	int Gomyself(char(*state)[BoardSize], char(*end)[BoardSize]);
	void winshow(void);

	int processShow(vector<unsigned long long>& routeResult);
	int resultDataShow(clock_t time, int expandNum, int generateNum, vector<unsigned long long> routeResult);
	int searchTreeShow(vector<AStarTreeNote>& TreeList, unsigned long long  end);
	int searchTreeShowIn(vector<AStarTreeNote>& TreeList, unsigned long long  end);
	int searchTreeShowNode(int x, int y, AStarTreeNote& node, unsigned long long  end);
	int resultNone(void);
};

/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
int Simple_show(unsigned long long& in);
int arrayclear(char(*array)[BoardSize]);
bool answerExist(char(*arr1)[BoardSize], char(*arr2)[BoardSize]);
int TreePrint(vector<AStarTreeNote>& TreeList);


