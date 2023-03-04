/*
 * @author    : gonzalez
 * @time      : 2022.4.26-2022.5.9
 * @function  : AlphaBeta UI界面实现函数
 */

#include "minimaxAlphaBeta_head.h"

using namespace std;

//*******************************************************************UI函数*******************************************************************
//@function:
showUI::showUI()
{
	//picture information
	loadimage(&backGround, _T("./image/background.png"), PICTUREBKLENGTH, PICTUREBKWIDTH, false);
	loadimage(&chessBoard, _T("./image/chessboard.png"), PICTURECBWIDTH, PICTURECBWIDTH, false);
	loadimage(&chessBlack, _T("./image/black.png"), CHESSWIDTH, CHESSWIDTH, false);
	loadimage(&chessWhite, _T("./image/white.png"), CHESSWIDTH, CHESSWIDTH, false);
	loadimage(&chessWhitePre, _T("./image/burning.png"), CHESSWIDTH, CHESSWIDTH, false);

	loadimage(&regretImage, _T("./image/regret.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&regretMouseImage, _T("./image/regretMouse.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&restartImage, _T("./image/restart.png"), BUTTONLENGTH, BUTTONWIDTH, false);
	loadimage(&restartMouseImage, _T("./image/restartMouse.png"), BUTTONLENGTH, BUTTONWIDTH, false);

	//think and normal
	loadimage(&thinkingImage, _T("./image/thinking.png"), PICTURELENGTH, PICTUREWIDTH, false);
	loadimage(&userImage, _T("./image/user.png"), PICTURELENGTH, PICTUREWIDTH, false);

	//win and lose
	loadimage(&winImage, _T("./image/win.png"), ENDPICLENGTH, ENDPICWIDTH, false);
	loadimage(&loseImage, _T("./image/lose.png"), ENDPICLENGTH, ENDPICWIDTH, false);

    
	//loction information
	boardImage.left = 55;
	boardImage.top = 55;
	boardImage.right = 645;
	boardImage.bottom = 645;

	regretButton.left = CBbetweenBK + PICTURECBWIDTH + 35;
	regretButton.top = 35;
	regretButton.right = regretButton.left + BUTTONLENGTH;
	regretButton.bottom = regretButton.top + BUTTONWIDTH;

	restartButton.left = CBbetweenBK + PICTURECBWIDTH + 35;
	restartButton.right = restartButton.left + BUTTONLENGTH;
	restartButton.top = 35 + BUTTONWIDTH + 20;
	restartButton.bottom = restartButton.top + BUTTONWIDTH;

	pictureSite.top = restartButton.bottom + 40;
	pictureSite.left = restartButton.left;
	pictureSite.right = pictureSite.left+PICTURELENGTH;
	pictureSite.bottom = pictureSite.top + PICTUREWIDTH;

	winloseShow.left = boardImage.left + (boardImage.right - boardImage.left) / 2 - ENDPICLENGTH / 2;
	winloseShow.top = boardImage.top + (boardImage.bottom - boardImage.top) / 2 - ENDPICWIDTH / 2;
	winloseShow.right = winloseShow.left + ENDPICLENGTH;
	winloseShow.bottom = winloseShow.top + ENDPICWIDTH;


}

//@function:将图片显示至图像上
bool showUI::uiLoad(void)
{
	cleardevice();//清除游戏界面
	putimage(0, 0, &backGround);
	putimage(CBbetweenBK, CBbetweenBK, &chessBoard);

	putimage(regretButton.left, regretButton.top, &regretImage);
	putimage(restartButton.left, restartButton.top, &restartImage);

	putimage(pictureSite.left, pictureSite.top, &userImage);

	return true;
}

//@function:执行ui函数
int showUI::uiGetBack(char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	ExMessage msg;
	int chessX = 1;
	int chessY = 1;
	bool regret = false;
	bool restart = false;
	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {//鼠标点击
				//下棋落子
				if (findXY(msg.x, msg.y, chessX, chessY)) {
					if (chessBoard[chessY][chessX] == NONECHESS) {
						putimage(boardImage.left - CHESSWIDTH / 2 + (chessX - 1) * CHESSMID, boardImage.top - CHESSWIDTH / 2 + (chessY - 1) * CHESSMID, &chessBlack);//棋子添加
						return (chessY * 100 + chessX);//返回对应落子位
					}
				}
				//悔棋
				else if (regret && (msg.x >= regretButton.left && msg.x <= regretButton.right && msg.y >= regretButton.top && msg.y <= regretButton.bottom)) {
					putimage(regretButton.left, regretButton.top, &regretImage);
					regret = false;
					return REGRET;
				}
				//重新开始
				else if (restart && (msg.x >= restartButton.left && msg.x <= restartButton.right && msg.y >= restartButton.top && msg.y <= restartButton.bottom)) {
					putimage(restartButton.left, restartButton.top, &restartImage);
					restart = false;
					return RESTART;
				}
			}
			else if (msg.message == WM_MOUSEMOVE) {//鼠标移动
				//悔棋区域
				if ((!regret)&&(msg.x >= regretButton.left && msg.x <= regretButton.right && msg.y >= regretButton.top && msg.y <= regretButton.bottom)) {
					//cout << "悔棋" << endl;//for test
					putimage(regretButton.left, regretButton.top, &regretMouseImage);
					regret = true;
				}
				//重开区域
				else if ((!restart) && (msg.x >= restartButton.left && msg.x <= restartButton.right && msg.y >= restartButton.top && msg.y <= restartButton.bottom)) {
					//cout << "重开" << endl;//for test
					putimage(restartButton.left, restartButton.top, &restartMouseImage);
					restart = true;
				}
				//其他区域
				else {
					if ((regret)&&(!(msg.x >= regretButton.left && msg.x <= regretButton.right && msg.y >= regretButton.top && msg.y <= regretButton.bottom))) {
						putimage(regretButton.left, regretButton.top, &regretImage);
						regret = false;
					}
					if ((restart)&&(!(msg.x >= restartButton.left && msg.x <= restartButton.right && msg.y >= restartButton.top && msg.y <= restartButton.bottom))) {
						putimage(restartButton.left, restartButton.top, &restartImage);
						restart = false;
					}
				}
			}
		}
	}
}

//@function: 根据鼠标信息找到所需点击的对应棋子坐标
bool showUI::findXY(int x, int y, int& boardX, int& boardY)
{
	
	int tempX = boardImage.left;
	int tempY = boardImage.top;
	int findX = -1;
	int findY = -1;
	for (int i = 0; i < BOARDLENGHT; i++) {
		if (x >= tempX + i * CHESSMID - CHESSWIDTH / 2 && x <= tempX + i * CHESSMID + CHESSWIDTH / 2) {
			findX = i + 1;
			break;
		}
	}
	for (int i = 0; i < BOARDLENGHT; i++) {
		if (y >= tempY + i * CHESSMID - CHESSWIDTH / 2 && y <= tempY + i * CHESSMID + CHESSWIDTH / 2) {
			findY = i + 1;
			break;
		}
	}
	if (findX != -1 && findY != -1) {
		boardX = findX;
		boardY = findY;
		return true;
	}
	else
		return false;
}

//@function: 更新棋局 用于悔棋和重新开始
bool showUI::refresh(char(*board)[BOARDLENGHT + BOARDADD])
{
	int tempX = 0;
	int tempY = 0;
	putimage(CBbetweenBK, CBbetweenBK, &chessBoard);//更新界面进行覆盖
	for(int row =1;row<=BOARDWIDTH;row++)
		for (int col = 1; col <= BOARDLENGHT; col++)
			if (board[row][col] != NONECHESS) {
				tempX = boardImage.left - CHESSWIDTH / 2 + (col - 1) * CHESSMID;
				tempY = boardImage.top - CHESSWIDTH / 2 + (row - 1) * CHESSMID;
				if (board[row][col] == BLACKCHESS)
					putimage(tempX, tempY, &chessBlack);
				else if (board[row][col] == WHITECHESS)
					putimage(tempX, tempY, &chessWhite);
			}
	return true;
}

//@function: 在界面上添加白棋
bool showUI::addWhite(int site)
{
	int SLEEPTIME = 200;
	int Times = 3;
	int row = site / 100;
	int col = site % 100;
	for (int i = 1; i <= Times; i++) {
		putimage(boardImage.left - CHESSWIDTH / 2 + (col - 1) * CHESSMID, boardImage.top - CHESSWIDTH / 2 + (row - 1) * CHESSMID, &chessWhitePre);
		Sleep(SLEEPTIME);
		putimage(boardImage.left - CHESSWIDTH / 2 + (col - 1) * CHESSMID, boardImage.top - CHESSWIDTH / 2 + (row - 1) * CHESSMID, &chessWhite);
		if (i != Times)
			Sleep(SLEEPTIME);
	}
	return true;
}

//@function: 结束的情况显示
void showUI::endShow(void)
{
	ExMessage msg;
	bool restart = false;
	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {//鼠标点击
				//重新开始
				if (restart && (msg.x >= restartButton.left && msg.x <= restartButton.right && msg.y >= restartButton.top && msg.y <= restartButton.bottom)) {
					putimage(restartButton.left, restartButton.top, &restartImage);
					restart = false;
					return;
				}
			}
			else if (msg.message == WM_MOUSEMOVE) {//鼠标移动
				//重开区域
				if ((!restart) && (msg.x >= restartButton.left && msg.x <= restartButton.right && msg.y >= restartButton.top && msg.y <= restartButton.bottom)) {
					putimage(restartButton.left, restartButton.top, &restartMouseImage);
					restart = true;
				}
				//其他区域
				else {
					if ((restart) && (!(msg.x >= restartButton.left && msg.x <= restartButton.right && msg.y >= restartButton.top && msg.y <= restartButton.bottom))) {
						putimage(restartButton.left, restartButton.top, &restartImage);
						restart = false;
					}
				}
			}
		}
	}
}

//@function: 显示赢了的情况
void showUI::winShow(void)
{
	putimage(winloseShow.left, winloseShow.top, &winImage);
	endShow();
	return;
}

//@function: 显示输了的情况
void showUI::loseShow(void)
{
	putimage(winloseShow.left, winloseShow.top, &loseImage);
	endShow();
	return;
}

//@function: 机器思考过程中显示正在思考的情况
void showUI::showThinking(void)
{
	putimage(pictureSite.left, pictureSite.top, &thinkingImage);
	return;
}

//@function: 玩家执行过程中显示一般情况
void showUI::showNormal(void)
{
	putimage(pictureSite.left, pictureSite.top, &userImage);
	return;
}


//******************************************************************其他函数******************************************************************
//@function:判断输赢
int judgeWinner(char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	int len = 5;
	//从上至下
	for (int row = 1; row <= BOARDWIDTH; row++)
		for (int col = 1; col <= (BOARDLENGHT - len + 1); col++) {
			string temp = "";
			for (int i = 0; i < len; i++)
				temp += chessBoard[row][col + i];
			if (temp == "11111")
				return BLACKWIN;
			else if (temp == "00000")
				return WHITEWIN;

		}
	//从左至右
	for (int col = 1; col <= BOARDLENGHT; col++)
		for (int row = 1; row <= (BOARDWIDTH - len + 1); row++) {
			string temp = "";
			for (int i = 0; i < len; i++)
				temp += chessBoard[row + i][col];
			if (temp == "11111")
				return BLACKWIN;
			else if (temp == "00000")
				return WHITEWIN;

		}

	//左上至右下
	for (int row = len; row <= BOARDWIDTH; row++)
		for (int col = 1; col <= (BOARDLENGHT - len + 1); col++) {
			string temp = "";
			for (int i = 0; i < len; i++)
				temp += chessBoard[row - i][col + i];
			if (temp == "11111")
				return BLACKWIN;
			else if (temp == "00000")
				return WHITEWIN;

		}

	//右上至左下
	for (int row = 1; row <= (BOARDWIDTH - len + 1); row++)
		for (int col = 1; col <= (BOARDLENGHT - len + 1); col++) {
			string temp = "";
			for (int i = 0; i < len; i++)
				temp += chessBoard[row + i][col + i];
			if (temp == "11111")
				return BLACKWIN;
			else if (temp == "00000")
				return WHITEWIN;

		}

	return NOWINNER;
}


//@function:更新函数
void refreshBoard(char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	for (int row = 0; row < BOARDWIDTH + BOARDADD; row++) {
		for (int col = 0; col < BOARDLENGHT + BOARDADD; col++) {
			chessBoard[row][col] = '*';
		}
	}
}





