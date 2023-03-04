/*
 * @author   : gonzalez
 * @time     : 2022.5.26-2022.6.2
 * @function : 
 */

#include "logicalReasoning_head.h"
using namespace std;


int main()
{
	initgraph(UILENGTH, UIWIDTH, EW_SHOWCONSOLE);         //初始化图形界面
	setbkcolor(BLACK);                                    //设置背景颜色
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
				cout << "请输入推断子句集（notice:请以#结尾）" << endl;
				dataIn(originalSentence);
				cout << "输入结束" << endl;
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
				cout << "归结过程如下:" << endl;
				Sleep(1000);
				c.allShow();
				c.ansShow();
			}
			else if (getOrder == MOUSEBEST) {
				system("cls");
				cout << "最优过程如下:" << endl;
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