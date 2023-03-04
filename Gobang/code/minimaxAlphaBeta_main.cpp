/*
 * @author    : gonzalez
 * @time      : 2022.5.2-2022.5.9
 * @function  : AlphaBeta main������
 */

#include "minimaxAlphaBeta_head.h"
using namespace std;

//main����
int main()
{
	initgraph(PICTUREBKLENGTH, PICTUREBKWIDTH, EW_SHOWCONSOLE);         //��ʼ��ͼ�ν���
	setbkcolor(BLACK);                                                  //���ñ�����ɫ
    char board[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };  //��������
	
	while (true) {
		//initiate
		vector<short>blackChess;
		vector<short>whiteChess;
		refreshBoard(board);
		showUI ui;
		ui.uiLoad();
		//��ʼ����
		while (true) {
			int orderBack = ui.uiGetBack(board);//ִ��ָ��
			//�ؿ�
			if (orderBack == RESTART) {
				break;
			}
			//����
			else if (orderBack == REGRET) {
				if (blackChess.size() >= 1 && whiteChess.size() >= 1) {
					int black = blackChess[blackChess.size() - 1];
					int white = whiteChess[whiteChess.size() - 1];
					board[black / 100][black % 100] = '*';
					board[white / 100][white % 100] = '*';
					blackChess.erase(blackChess.end()-1);                 //��¼������ɾ��ָ��Ԫ��
					whiteChess.erase(whiteChess.end()-1);                 //��¼������ɾ��ָ��Ԫ��
					ui.refresh(board);
				}
			}
			//����
			else {
				blackChess.push_back(orderBack);                          //��Ӻ���
				board[orderBack / 100][orderBack % 100] = BLACKCHESS;     //�޸������������
				int judge = judgeWinner(board);                           //�ж���Ӯ
				if (judge == BLACKWIN) {
					ui.winShow();                                         //�˹���ʤ
					break;
				}
				//�˹���������
				searchAlphaBeta AB(board);
				ui.showThinking();
				int whiteBack = AB.alphabetaGetBack();
				ui.showNormal();
				ui.addWhite(whiteBack);
				board[whiteBack / 100][whiteBack % 100] = WHITECHESS;
				whiteChess.push_back(whiteBack);
				judge = judgeWinner(board);      //�ж���Ӯ
				if (judge == WHITEWIN) { 
					ui.loseShow();               //�˹�ʧ��
					break;
				}
			}
		}
	}
	closegraph();                                //�ر���Ϸ����
	

	return 0;
}

