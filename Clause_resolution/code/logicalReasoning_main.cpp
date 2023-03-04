/*
 * @author   : gonzalez
 * @time     : 2022.5.26-2022.6.2
 * @function : 
 */

#include "logicalReasoning_head.h"
using namespace std;


int main()
{
	initgraph(UILENGTH, UIWIDTH, EW_SHOWCONSOLE);         //��ʼ��ͼ�ν���
	setbkcolor(BLACK);                                    //���ñ�����ɫ
	clauseUI ui;
	ui.bgShow();
	while (true) {
		// initiate
		clauseResolution c;
		vector<string> originalSentence;
		bool haveIn = false;
		// input
		while (true) {
			if (ui.orderChoose() == MOUSEINPUT) {
				haveIn = true;
				cout << "�������ƶ��Ӿ伯��notice:����#��β��" << endl;
				dataIn(originalSentence);
				cout << "�������" << endl;
				Sleep(1000);
				break;
			}
		}
		// operate
		c.clausInput(originalSentence);
		c.resolution();
		c.traceBack();
		// show
		while (true) {
			int getOrder = ui.orderChoose(haveIn);
			if (getOrder == MOUSEALL) {
				system("cls");
				cout << "����������:" << endl;
				Sleep(1000);
				c.allShow();
				c.ansShow();
			}
			else if (getOrder == MOUSEBEST) {
				system("cls");
				cout << "���Ź�������:" << endl;
				Sleep(1000);
				c.bestShow();
				c.ansShow();
			}
			else if (getOrder == MOUSEREST) {
				system("cls");
				break;
			}
		}
		system("cls");
	}


	return 0;
}