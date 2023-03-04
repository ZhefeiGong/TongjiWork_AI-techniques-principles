/*
 * @author    : gonzalez
 * @time      : 2022.5.2-2022.5.9
 * @function  : AlphaBeta main主函数
 */

#include "minimaxAlphaBeta_head.h"
using namespace std;

//main函数
int main()
{
	initgraph(PICTUREBKLENGTH, PICTUREBKWIDTH, EW_SHOWCONSOLE);         //初始化图形界面
	setbkcolor(BLACK);                                                  //设置背景颜色
    char board[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };  //定义棋盘
	
	while (true) {
		//initiate
		vector<short>blackChess;
		vector<short>whiteChess;
		refreshBoard(board);
		showUI ui;
		ui.uiLoad();
		//开始下棋
		while (true) {
			int orderBack = ui.uiGetBack(board);//执行指令
			//重开
			if (orderBack == RESTART) {
				break;
			}
			//悔棋
			else if (orderBack == REGRET) {
				if (blackChess.size() >= 1 && whiteChess.size() >= 1) {
					int black = blackChess[blackChess.size() - 1];
					int white = whiteChess[whiteChess.size() - 1];
					board[black / 100][black % 100] = '*';
					board[white / 100][white % 100] = '*';
					blackChess.erase(blackChess.end()-1);                 //记录黑棋中删除指定元素
					whiteChess.erase(whiteChess.end()-1);                 //记录白棋中删除指定元素
					ui.refresh(board);
				}
			}
			//下棋
			else {
				blackChess.push_back(orderBack);                          //添加黑棋
				board[orderBack / 100][orderBack % 100] = BLACKCHESS;     //修改落子坐标情况
				int judge = judgeWinner(board);                           //判断输赢
				if (judge == BLACKWIN) {
					ui.winShow();                                         //人工获胜
					break;
				}
				//人工智能下棋
				searchAlphaBeta AB(board);
				ui.showThinking();
				int whiteBack = AB.alphabetaGetBack();
				ui.showNormal();
				ui.addWhite(whiteBack);
				board[whiteBack / 100][whiteBack % 100] = WHITECHESS;
				whiteChess.push_back(whiteBack);
				judge = judgeWinner(board);      //判断输赢
				if (judge == WHITEWIN) { 
					ui.loseShow();               //人工失败
					break;
				}
			}
		}
	}
	closegraph();                                //关闭游戏界面
	

	return 0;
}

