/*
 * @author   : gonzalez
 * @time     : 2022.5.26-2022.6.2
 * @function : ��Ŀͷ�ļ�
 */
#pragma once

#include<iostream>             // ��׼��
#include<vector>               // SRL����
#include<string>               // string
#include<queue>                // STL����
#include<algorithm>            // �����㷨��
#include<iomanip>              // ��ʽ���������
#include<windows.h>            // windowsϵͳ��
#include<graphics.h>           // EasyX��
#include<conio.h>              // EasyX��

using namespace std;

//*********************************************************************
//* @function  : һ���߼��ڲ�����ʵ��
//* @notice    : ��
//*********************************************************************

// @notice:
// K(x,y)  ��ʾ  ����xɱ��y
// L(x)    ��ʾ  x�������ⶰ������
// H(x,y)  ��ʾ  x��y
// R(x,y)  ��ʾ  x��y����
// E(x,y)  ��ʾ  x��y���
// A(x)    ��ʾ  x������������
//
// ���� -- a-z
// ���� -- A-Z
// ���� -- f(x)��'&'��ʾ����

// @function : ���ȹ�����Ƴ���
#define  LENGTHEDGE      3
// @function : ��������
#define  FUNCTION       '&'
// @function : ���ʽ����
#define  OR             '|'
#define  NOT            '~'
#define  DOT            ','
#define  LEFTBRACKET    '('
#define  RIGHTBRACKET   ')'
#define  EQUAL          'E'
#define  ANSWER         'A'


// �����ṹ��
struct FUNC {
	char name = '\0';
	char parameter = '\0';
};
// �������ʽ
struct EXPRE{
	bool IsNot = true;        // ���ʽ�Ƿ�ȡ��
	char type = '\0';         // ���ʽ�����
	vector<char>element;      // ���ʽ�е�Ԫ��
	FUNC func;                // �����洢�������ʽ
};
// �����Ӿ�
struct CLAUSES{
	string name;              // �Ӿ���
	vector<EXPRE>expressions; // �Ӿ���ʽ�ϼ�
};
// ���̼�¼
struct RECORD{
	string resultName;   // ����߼�����
	string result;       // �߼����ʽ
	string father1Name;  // ���ڵ�1����
	string father2Name;  // ���ڵ�2����
	string change;       // �û���һ�仯
};

// @function : �Ӿ���ִ���ں�
class clauseResolution {
protected:

	// �ڲ�����
	CLAUSES answer;                                                  // ���ս��
	int countNum = 0;                                                // ���ڼ�¼ת������
	vector<char>expressionType;                                      // ���ƶ������б��ʽ���������� --> 'A'-'Z'����
	vector<CLAUSES>clauseBag;                                        // �洢����ת������Ӿ伯

	// ���ӻ�����洢
	vector<RECORD>initialList;                                       // ��ʼ�����ݴ洢
	vector<RECORD>recordList;                                        // �������ݴ洢
	vector<RECORD>bestPath;                                          // ���Ź��·��

	// �ڲ�����
	void initialRecord(void);                                                                      // ��ʼ�߼���¼
	void processRecord(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData, RECORD& get); // �����̼�¼
	void traceBackIn(RECORD& c);                                                                   // Ѱ����ѹ��·���ڲ��ݹ麯��
	void expressionInput(string& original, CLAUSES& c);                                            // ��һ���ַ���ת����
	bool clausesUpdate(CLAUSES& ans, vector<char>& record, vector<char>& upData);                  // �Ӿ����
	bool judgeAnswer(CLAUSES& c1);                                                                 // �ж��Ƿ��ᵽ�յ�
	bool equalDeal(CLAUSES& c, vector<CLAUSES>& tempBag);                                          // ��ʽ���[��ΪE(f(A),B)��f(A)�滻ΪB]
	bool containDeal(CLAUSES& c, vector<CLAUSES>& tempBag);                                        // ���ݹ��
	bool lengthDeal(CLAUSES& c, vector<CLAUSES>& tempBag);                                         // ��������
	bool twoClauseResolu(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& record);            // �����Ӿ��� 
	void processShow(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData);                // ����̨��ӡ����
	void initialShow(void);                                                                        // ����̨��ӡ��ʼ����


public:
	// �ⲿ����
    void traceBack(void);                                            // Ѱ����ѹ��·��
	void clausInput(vector<string> &originalSentence);               // �������Ӿ�ת��Ϊ�׼���ṹ�Ӿ�
	void resolution(void);                                           // ִ���Ӿ���
	void allShow(void);                                              // չʾ���й�����
	void bestShow(void);                                             // չʾ���Ź�����
	void ansShow(void);                                              // ��ʾ���ս��

	void tempShow(void);                                             // for test 
};



//*********************************************************************
//* @function  : UI������
//* @notice    : ��
//*********************************************************************

// ҳ�沼�ֽṹ��
struct SURFACE {
	short left = 0;
	short top = 0;
};

#define UILENGTH   758
#define UIWIDTH    400

#define BUTTONLENGTH 189
#define BUTTONWIDTH  70
#define RESTARTLEN   50


#define MOUSEINPUT    1
#define MOUSEALL      2
#define MOUSEBEST     3
#define MOUSEREST     4

// @function : �־���UI����
class clauseUI {
protected:
	// ���沼�ֽṹ�嶨��
	SURFACE backArea;
	SURFACE inputArea;
	SURFACE showallArea;
	SURFACE showbestArea;
	SURFACE restartArea;

	// ����ͼƬ���ö���
	IMAGE background;
	IMAGE input;
	IMAGE inputActive;
	IMAGE showAll;
	IMAGE showAllActive;
	IMAGE showBest;
	IMAGE showBestActive;
	IMAGE restart;
	IMAGE restartActive;

public:
	clauseUI(void);                           // ��ʼ��
	void bgShow(void);                        // չʾ����
	int orderChoose(bool haveIn = false);     // ����ָʾ

};



//*********************************************************************
//* @function  : ���ߺ���
//* @notice    : ��
//*********************************************************************

// @function : ���ߺ���
void dataIn(vector<string>& originalSentence);//�����Ӧ������





