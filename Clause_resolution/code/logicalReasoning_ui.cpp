/*
 * @author   : gonzalez
 * @time     : 2022.5.26-2022.6.2
 * @function : 
 */

#include"logicalReasoning_head.h"

using namespace std;

// @function : clauseUI���ʼ��
clauseUI::clauseUI(void) {

	// ��Ƭ��ʼ��
	loadimage(&background, _T("./image/background.png"), UILENGTH, UIWIDTH, false);

	loadimage(&input, _T("./image/input1.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&inputActive, _T("./image/input2.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&showAll, _T("./image/showAll1.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&showAllActive, _T("./image/showAll2.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&showBest, _T("./image/showBest1.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&showBestActive, _T("./image/showBest2.png"), BUTTONLENGTH, BUTTONWIDTH, false);

	loadimage(&restart, _T("./image/restart1.png"), RESTARTLEN, RESTARTLEN, false);
	loadimage(&restartActive, _T("./image/restart2.png"), RESTARTLEN, RESTARTLEN, false);

	// ȫ������
	backArea.left = 0;
	backArea.top = 0;

	// ���밴ť����
	inputArea.left = 500;
	inputArea.top = 70;

	// չʾ�����̰�ť����
	showallArea.left = 500;
	showallArea.top = 165;

	// չʾ���Ź��·����ť����
	showbestArea.left = 500;
	showbestArea.top = 260;

	// ������ť����
	restartArea.left = 702;
	restartArea.top = 344;

}


// @function : չʾ����
void clauseUI::bgShow(void) {
	putimage(backArea.left, backArea.top, &background);
	putimage(inputArea.left, inputArea.top, &input);
	putimage(showallArea.left, showallArea.top, &showAll);
	putimage(showbestArea.left, showbestArea.top, &showBest);
	putimage(restartArea.left, restartArea.top, &restart);
	return;
}


// @function : �������¼�
int clauseUI::orderChoose(bool haveIn) {
	ExMessage msg;
	while (true) {
		//����¼�
		if (peekmessage(&msg, EM_MOUSE)) {
			// �����
			if (msg.message == WM_LBUTTONDOWN) {
				if ((msg.x >= inputArea.left && msg.x <= inputArea.left + BUTTONLENGTH)
					&& (msg.y >= inputArea.top && msg.y <= inputArea.top + BUTTONWIDTH)) {
					if (!haveIn) {
						putimage(inputArea.left, inputArea.top, &input);
						return MOUSEINPUT;// ����
					}
				}
				if ((msg.x >= showallArea.left && msg.x <= showallArea.left + BUTTONLENGTH)
					&& (msg.y >= showallArea.top && msg.y <= showallArea.top + BUTTONWIDTH)) {
					putimage(showallArea.left, showallArea.top, &showAll);
					return MOUSEALL;// չʾ����
				}
				if ((msg.x >= showbestArea.left && msg.x <= showbestArea.left + BUTTONLENGTH)
					&& (msg.y >= showbestArea.top && msg.y <= showbestArea.top + BUTTONWIDTH)) {
					putimage(showbestArea.left, showbestArea.top, &showBest);
					return MOUSEBEST;// չʾ���
				}
				if ((msg.x >= restartArea.left && msg.x <= restartArea.left + RESTARTLEN)
					&& (msg.y >= restartArea.top && msg.y <= restartArea.top + RESTARTLEN)) {
					putimage(restartArea.left, restartArea.top, &restart);
					return MOUSEREST;// ����
				}
			}
			// ����ƶ�
			else if (msg.message == WM_MOUSEMOVE) {
				if ((msg.x >= inputArea.left && msg.x <= inputArea.left + BUTTONLENGTH)
					&& (msg.y >= inputArea.top && msg.y <= inputArea.top + BUTTONWIDTH)) {
					if (!haveIn)
						putimage(inputArea.left, inputArea.top, &inputActive);
				}
				else if ((msg.x >= showallArea.left && msg.x <= showallArea.left + BUTTONLENGTH)
					&& (msg.y >= showallArea.top && msg.y <= showallArea.top + BUTTONWIDTH)) {
					putimage(showallArea.left, showallArea.top, &showAllActive);
				}
				else if ((msg.x >= showbestArea.left && msg.x <= showbestArea.left + BUTTONLENGTH)
					&& (msg.y >= showbestArea.top && msg.y <= showbestArea.top + BUTTONWIDTH)) {
					putimage(showbestArea.left, showbestArea.top, &showBestActive);
				}
				else if ((msg.x >= restartArea.left && msg.x <= restartArea.left + RESTARTLEN)
					&& (msg.y >= restartArea.top && msg.y <= restartArea.top + RESTARTLEN)) {
					putimage(restartArea.left, restartArea.top, &restartActive);
				}
				else {
					putimage(inputArea.left, inputArea.top, &input);
					putimage(showallArea.left, showallArea.top, &showAll);
					putimage(showbestArea.left, showbestArea.top, &showBest);
					putimage(restartArea.left, restartArea.top, &restart);
				}
			}
		}
	}
}




