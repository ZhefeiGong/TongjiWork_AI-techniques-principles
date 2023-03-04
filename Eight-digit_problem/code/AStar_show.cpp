/*
 * @author  : gonzalez
 * @time    : 2022.3.28-2022.3...
 * @function: ʵ�ֽ���Ŀ��ӻ�����
 */

#include  <iostream>
#include "AStar_head.h"

using namespace std;


/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/

// @function: ��ӡһ���ַ���
int EasyXSHOW::block(int x, int y, int num)
{
	int length = BLOCKSIZE;
	int HIGHT = BLOCKSIZE - 10;
	setbkmode(TRANSPARENT);
	setfillcolor(LIGHTGRAY);
	fillroundrect(x, y, x + length, y + length, 10, 10);
	int mx = x + 2;
	int my = y + 2;
	length = length - 4;
	fillroundrect(mx, my, mx + length, my + length, 10, 10);
	settextstyle(HIGHT, 0, _T("����"));                         //��������     
	TCHAR text[5] = _T(" ");
	if (num != 0)
		_stprintf_s(text, _T("%d"), num);
	int tx = mx + (length - textwidth(text)) / 2;
	int ty = my + (length - textheight(text)) / 2;
	outtextxy(tx, ty, text);

	return FINE;
}

// @function: ��ӡ�ַ�����
int EasyXSHOW::blockshow(int x,int y,char(*array)[BoardSize])
{
	int tempx = x;
	int tempy = y;
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (array[i][j] != '*') {                             //����*ʱ ����ʾ
				tempx = x + j * BLOCKSIZE;
				tempy = y + i * BLOCKSIZE;
				block(tempx, tempy, (int)(array[i][j] - '0'));
			}
		}
	}
	return FINE;
}

// @function: EasySHOE��Ԥ������
EasyXSHOW::EasyXSHOW()
{
	/*��ƬԤ����*/
	loadimage(&num[1], _T("./image/1.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[2], _T("./image/2.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[3], _T("./image/3.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[4], _T("./image/4.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[5], _T("./image/5.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[6], _T("./image/6.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[7], _T("./image/7.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[8], _T("./image/8.jpg"), PICWIDE, PICWIDE, false);
	loadimage(&num[0], _T("./image/0.jpg"), PICWIDE, PICWIDE, false);
	//�ܽ���λ����Ϣ
	General.left = 0;
	General.right = BKLENGTH;
	General.top = 0;
	General.bottom = BKWIDTH;
	//�������λ����Ϣ
	cherkerboard.left = 0;
	cherkerboard.right = 360;
	cherkerboard.top = 0;
	cherkerboard.bottom = 420;
	//�Ҳ����ݿ�λ����Ϣ
	dataout.left = 360;
	dataout.right = 800;
	dataout.top = 0;
	dataout.bottom = 420;
	//���²���ʼ��ֹ״̬λ����Ϣ
	stateshow.left = 360;
	stateshow.right = 800;
	stateshow.top = 420;
	stateshow.bottom = 600;
	//��������
	buttonoperate.left = 0;
	buttonoperate.right = 360;
	buttonoperate.top = 420;
	buttonoperate.bottom = 600;
	//����������λ����Ϣ
	eightborad.left = 0;
	eightborad.right = 360;
	eightborad.top = 30;
	eightborad.bottom = 390;
	//���½���ʼ״̬λ����Ϣ
	startstate.left = stateshow.left + 10 + 60;
	startstate.right = startstate.left + 120;
	startstate.top = stateshow.top + 15;
	startstate.bottom = startstate.top + 120;
	//���½���ֹ״̬λ����Ϣ
	endstate.left = startstate.right + 60;
	endstate.right = endstate.left + 120;
	endstate.top = stateshow.top + 15;
	endstate.bottom = endstate.top + 120;

	//������ťλ����Ϣ
	//ϵͳִ��
	systemgo.left = 50;
	systemgo.right = 50 + 80;
	systemgo.top = 420 + 40;
	systemgo.bottom = 420 + 40 + 30;
	//�Լ�ִ��
	myselfgo.left = 50;
	myselfgo.right = 50 + 80;
	myselfgo.top = 600 - 70;
	myselfgo.bottom = 600 - 40;
	//����
	upbutton.left = 180 + 15 + 50;
	upbutton.right = upbutton.left + 50;
	upbutton.top = 420 + 15;
	upbutton.bottom = upbutton.top + 50;
	//����
	downbutton.left = 180 + 15 + 50;
	downbutton.right = downbutton.left + 50;
	downbutton.top = 420 + 15 + 100;
	downbutton.bottom = downbutton.top + 50;
	//����
	leftbutton.left = 180 + 15;
	leftbutton.right = leftbutton.left + 50;
	leftbutton.top = 420 + 15 + 50;
	leftbutton.bottom = leftbutton.top + 50;
	//����
	rightbutton.left = 180 + 15 + 100;
	rightbutton.right = rightbutton.left + 50;
	rightbutton.top = 420 + 15 + 50;
	rightbutton.bottom = rightbutton.top + 50;
	//���ð���
	reset.left = 0;
	reset.right = 40;
	reset.top = 580;
	reset.bottom = 600;
	//��ʼ��ʼ��
	initialbegin.left = 130;
	initialbegin.right = 130 + 100;
	initialbegin.top = 420 + 30;
	initialbegin.bottom = initialbegin.top + 45;
	//��ֹ��ʼ��
	initialend.left = 130;
	initialend.right = 130 + 100;
	initialend.top = 600 - 75;
	initialend.bottom = initialend.top + 45;

}

// @function: ��ʼ״̬������ʾ
int EasyXSHOW::Initialbg(void)
{

	int mid = 5;
	setbkcolor(BKCOLOR);

	setfillcolor(RGB(128, 64, 0));
	fillroundrect(cherkerboard.left, cherkerboard.top, cherkerboard.right, cherkerboard.bottom, 10, 10);
	fillroundrect(cherkerboard.left, cherkerboard.top + mid, cherkerboard.right, cherkerboard.bottom - mid, 10, 10);

	setfillcolor(BLACK);
	fillrectangle(dataout.left, dataout.top, dataout.right, dataout.bottom);

	setfillcolor(RGB(123, 123, 123));
	fillrectangle(stateshow.left, stateshow.top, stateshow.right, stateshow.bottom);
	fillrectangle(stateshow.left + mid, stateshow.top + mid, stateshow.right - mid, stateshow.bottom - mid);
	
	settextstyle(20, 0, _T("����"));                         //��������  
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	outtextxy(startstate.left+ 20, startstate.bottom+10, _T("��ʼ״̬"));
	outtextxy(endstate.left + 20, endstate.bottom + 10, _T("��ֹ״̬"));

	TCHAR text1[] = _T("����");
	button(reset.left, reset.top, reset.right- reset.left,reset.bottom- reset.top, text1);
	TCHAR text2[] = _T("��ʼ��ʼ��");
	button(initialbegin.left, initialbegin.top, initialbegin.right- initialbegin.left, initialbegin.bottom- initialbegin.top, text2);
	TCHAR text3[] = _T("��ֹ��ʼ��");
	button(initialend.left, initialend.top, initialend.right - initialend.left, initialend.bottom - initialend.top, text3);

	return FINE;
}

// @function: ��eightborad�����ӡͼƬ���
int EasyXSHOW::Boardshow(char(*array)[BoardSize])
{
	int tx, ty;
	int size = PICWIDE;
	int get = 0;
	for(int i=0;i<BoardSize;i++)
		for (int j = 0; j < BoardSize; j++) {
			tx = eightborad.left + j * size;
			ty = eightborad.top + i * size;
			if (array[i][j] != '*') {
				get = array[i][j] - '0';
				putimage(tx, ty, &num[get]);
			}
			else {
				setfillcolor(RGB(128, 64, 0));
				fillroundrect(tx, ty, tx + PICWIDE, ty + PICWIDE, 10, 10);
			}
		}
	return FINE;
}

// @function: ��ť�������
int EasyXSHOW::button(int x, int y, int length, int width, TCHAR text[])
{
	int HIGHT = BUTTONHIGHT;
	setbkmode(TRANSPARENT);
	setfillcolor(BLUE);
	fillroundrect(x, y, x + length, y + width, 10, 10);
	settextstyle(HIGHT, 0, _T("����"));
	int tx = x + (length - textwidth(text)) / 2;
	int ty = y + (width - textheight(text)) / 2;
	outtextxy(tx, ty, text);

	return FINE;
}

// @function: �ƶ�����ʵ��
int EasyXSHOW::moveinitial(char(*state)[BoardSize], AREA& site)
{
	ExMessage msg;
	char original[BoardSize][BoardSize] = { {'1','2','3'},{'4','5','6'},{'7','8','0'} };
	Boardshow(original);
	blockshow(site.left, site.top, state);

	int press = 0;
	int goal = 0;
	int tx = 0, ty = 0;
	while (press < 9) {
		while (1) {
			if (peekmessage(&msg, EM_MOUSE)) {
				if (msg.message == WM_LBUTTONDOWN) {
					if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {
						return FAIL;
					}
					int tx = (msg.y - eightborad.top) / 120;
					int ty = (msg.x - eightborad.left) / 120;
					if (tx >= 0 && tx < BoardSize && ty >= 0 && ty < BoardSize) {
						if (original[tx][ty] != '*') {
							state[goal / 3][goal % 3] = original[tx][ty];
							original[tx][ty] = '*';
							press++;
							goal++;
							Boardshow(original);
							blockshow(site.left, site.top, state);
							break;//����ѭ��
						}
					}
				}
			}
		}
	}
	return FINE;
}

// @function: ��ʼ��״̬ѡ��
int EasyXSHOW::stateinitial(char(*start)[BoardSize], char(*end)[BoardSize])
{
	bool start_flag = false;
	bool end_flag = false;
	ExMessage msg;
	while (!start_flag||!end_flag) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {
					return FAIL;
				}
				else if (msg.x >= initialbegin.left && msg.x <= initialbegin.right && msg.y >= initialbegin.top && msg.y <= initialbegin.bottom) {  //��ʼ״̬
					if (!start_flag) {
						setfillcolor(BKCOLOR);
						fillrectangle(initialbegin.left, initialbegin.top, initialbegin.right, initialbegin.bottom);
						if (moveinitial(start, startstate) == FAIL)//reset
							return FAIL;
						start_flag = true;
					}
				}
				else if (msg.x >= initialend.left && msg.x <= initialend.right && msg.y >= initialend.top && msg.y <= initialend.bottom) {          //����״̬
					if (!end_flag) {
						setfillcolor(BKCOLOR);
						fillrectangle(initialend.left, initialend.top, initialend.right, initialend.bottom);
						if (moveinitial(end, endstate) == FAIL)//reset
							return FAIL;
						end_flag = true;
					}
				}
			}
		}
	}
	return FINE;
}

// @function: ��ʼ���ܽ���
int EasyXSHOW::InitialPage(char(*start)[BoardSize], char(*end)[BoardSize])
{
	cleardevice();
	setbkcolor(BKCOLOR);
	Initialbg();
	while (1) {
		if (stateinitial(start, end) == FINE)
			return FINE;
		else {
			cleardevice();
			setbkcolor(BKCOLOR);
			arrayclear(start);
			arrayclear(end);
			Initialbg();
		}
	}
	return FAIL;
}

// @function:
int EasyXSHOW::mainbg(char(*start)[BoardSize], char(*state)[BoardSize], char(*end)[BoardSize])
{
	int mid = 5;
	setbkcolor(BKCOLOR);

	setfillcolor(RGB(128, 64, 0));
	fillroundrect(cherkerboard.left, cherkerboard.top, cherkerboard.right, cherkerboard.bottom, 10, 10);
	fillroundrect(cherkerboard.left, cherkerboard.top + mid, cherkerboard.right, cherkerboard.bottom - mid, 10, 10);

	setfillcolor(BLACK);
	fillrectangle(dataout.left, dataout.top, dataout.right, dataout.bottom);

	setfillcolor(RGB(123, 123, 123));
	fillrectangle(stateshow.left, stateshow.top, stateshow.right, stateshow.bottom);
	fillrectangle(stateshow.left + mid, stateshow.top + mid, stateshow.right - mid, stateshow.bottom - mid);

	settextstyle(20, 0, _T("����"));                         //��������  
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	outtextxy(startstate.left + 20, startstate.bottom + 10, _T("��ʼ״̬"));
	outtextxy(endstate.left + 20, endstate.bottom + 10, _T("��ֹ״̬"));

	TCHAR text1[] = _T("����");
	button(reset.left, reset.top, reset.right - reset.left, reset.bottom - reset.top, text1);
	TCHAR text2[] = _T("ϵͳִ��");
	button(systemgo.left, systemgo.top, systemgo.right - systemgo.left, systemgo.bottom - systemgo.top, text2);
	TCHAR text3[] = _T("�Լ�ִ��");
	button(myselfgo.left, myselfgo.top, myselfgo.right - myselfgo.left, myselfgo.bottom - myselfgo.top, text3);
	TCHAR text4[] = _T("��");
	button(upbutton.left, upbutton.top, upbutton.right - upbutton.left, upbutton.bottom - upbutton.top, text4);
	TCHAR text5[] = _T("��");
	button(downbutton.left, downbutton.top, downbutton.right - downbutton.left, downbutton.bottom - downbutton.top, text5);
	TCHAR text6[] = _T("��");
	button(rightbutton.left, rightbutton.top, rightbutton.right - rightbutton.left, rightbutton.bottom - rightbutton.top, text6);
	TCHAR text7[] = _T("��");
	button(leftbutton.left, leftbutton.top, leftbutton.right - leftbutton.left, leftbutton.bottom - leftbutton.top, text7);

	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			state[i][j] = start[i][j];
	Boardshow(state);
	blockshow(startstate.left, startstate.top, start);
	blockshow(endstate.left, endstate.top, end);

	return FINE;

}

//return  1  -->  ϵͳִ��
//return  0  -->  �Լ�ִ��
//return -1  -->  reset
int EasyXSHOW::mainoperate(void)
{
	ExMessage msg;
	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {//reset
					return FAIL;
				}
				else if (msg.x >= systemgo.left && msg.x <= systemgo.right && msg.y >= systemgo.top && msg.y <= systemgo.bottom) {//ϵͳִ��
					setfillcolor(BKCOLOR);
					fillrectangle(systemgo.left, systemgo.top, systemgo.right, systemgo.bottom);
					return SYGO;
				}
				else if (msg.x >= myselfgo.left && msg.x <= myselfgo.right && msg.y >= myselfgo.top && msg.y <= myselfgo.bottom) {//�Լ�ִ��
					setfillcolor(BKCOLOR);
					fillrectangle(myselfgo.left, myselfgo.top, myselfgo.right, myselfgo.bottom);
					return MYGO;
				}
			}
		}
	}

}

// @function: �Լ�ִ����Ϸ����
int EasyXSHOW::Gomyself(char(*state)[BoardSize], char(*end)[BoardSize])
{
	ExMessage msg;
	int x, y;
	char move;
	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				bool win = true;
				if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {                            //reset
					return FAIL;
				}
				else if (msg.x >= systemgo.left && msg.x <= systemgo.right && msg.y >= systemgo.top && msg.y <= systemgo.bottom) {           //ϵͳִ��
					setfillcolor(BKCOLOR);
					fillrectangle(systemgo.left, systemgo.top, systemgo.right, systemgo.bottom);
					return SYGO;
				}
				else {
					//�ҵ��ո�����λ��
					for(int i=0;i<BoardSize;i++)
						for(int j=0;j<BoardSize;j++)
							if (state[i][j] == '0') {
								x = i;
								y = j;
							}
					if (msg.x >= upbutton.left && msg.x <= upbutton.right && msg.y >= upbutton.top && msg.y <= upbutton.bottom) {//����
						if (x < 2) {
							move = state[x + 1][y];
							state[x + 1][y] = state[x][y];
							state[x][y] = move;
							Boardshow(state);
						}
					}
					else if (msg.x >= rightbutton.left && msg.x <= rightbutton.right && msg.y >= rightbutton.top && msg.y <= rightbutton.bottom) {//����
						if (y > 0) {
							move = state[x][y - 1];
							state[x][y - 1] = state[x][y];
							state[x][y] = move;
							Boardshow(state);
						}
					}
					else if (msg.x >= downbutton.left && msg.x <= downbutton.right && msg.y >= downbutton.top && msg.y <= downbutton.bottom) {//����
						if (x > 0) {
							move = state[x - 1][y];
							state[x - 1][y] = state[x][y];
							state[x][y] = move;
							Boardshow(state);
						}
					}
					else if (msg.x >= leftbutton.left && msg.x <= leftbutton.right && msg.y >= leftbutton.top && msg.y <= leftbutton.bottom) {//����
						if (y < 2) {
							move = state[x][y + 1];
							state[x][y + 1] = state[x][y];
							state[x][y] = move;
							Boardshow(state);
						}
					}

					for (int i = 0; i < BoardSize; i++)
						for (int j = 0; j < BoardSize; j++)
							if (state[i][j] != end[i][j])
								win = false;
					if (win)
						break;//������ɹ�״̬-->����ѭ��
				}
			}
		}
	}

	return WIN;                                                                                                                              //�ɹ��ߵ�
}

// @function: �Լ�ִ�гɹ������ӡ
void EasyXSHOW::winshow(void)
{
	TCHAR text[] = _T("�ɹ�");
	button(360, 285-50, 80, 30, text);
	TCHAR text1[] = _T("���� ���� ������");
	button(300, 350-50, 200, 30, text1);
	ExMessage msg;
	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {                            //reset
					return;
				}
			}
		}
	}
}

// @function:չ����Ϸ����
int EasyXSHOW::processShow(vector<unsigned long long>& routeResult)
{
	int num = routeResult.size();
	char array[BoardSize][BoardSize] = { {'*','*' ,'*'},{'*','*' ,'*'},{'*','*' ,'*'} };
	AStarEightDigital AT;
	for (int i = num - 1; i >= 0; i--) {
		AT.DataChangeGraph(routeResult[i], array);
		Boardshow(array);
		Sleep(SLEEPTIME);
	}
	return FINE;
}

// @function:��ʾ��Ϸ����
int EasyXSHOW::resultDataShow(clock_t time, int expandNum, int generateNum,vector<unsigned long long> routeResult)
{
	const int HIGHT = 18;
	const int BUFFER = 30;
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTCYAN);
	settextstyle(HIGHT, 0, _T("����"));                         //��������   

#ifdef OUFOFPOSITION
	TCHAR s1[] = _T("ʹ�÷���Ϊ    ������λ������");
#endif
#ifdef DISTANCETOTARGET
	TCHAR s1[] = _T("ʹ�÷���Ϊ    ��Ŀ�����֮��");
#endif
#ifdef EULERDISTANCE
	TCHAR s1[] = _T("ʹ�÷���Ϊ    ��ŷ�����뷨");
#endif
#ifdef COEFFICIENTMANHANTTAN
	TCHAR s1[] = _T("ʹ�÷���Ϊ    ��ϵ�������ٷ�");
#endif

	TCHAR s2[BUFFER];
	_stprintf_s(s2, _T("����ʱ��Ϊ    ��%d ms"), time);
	TCHAR s3[BUFFER];
	_stprintf_s(s3, _T("���ɽ����    ��%d"), generateNum);
	TCHAR s4[BUFFER];
	_stprintf_s(s4, _T("��չ�����    ��%d"), expandNum);
	TCHAR s5[BUFFER];
	_stprintf_s(s5, _T("��·������    ��%d"), routeResult.size() - 1);

	int leftInterval = 10;
	int topInterval = 10;

	outtextxy(dataout.left + leftInterval, dataout.top + topInterval, s1);
	outtextxy(dataout.left + leftInterval, dataout.top + topInterval + HIGHT * 1, s2);
	outtextxy(dataout.left + leftInterval, dataout.top + topInterval + HIGHT * 2, s3);
	outtextxy(dataout.left + leftInterval, dataout.top + topInterval + HIGHT * 3, s4);
	outtextxy(dataout.left + leftInterval, dataout.top + topInterval + HIGHT * 4, s5);

	TCHAR s6[]=_T("��࿪ʼִ�н�·������...");
	outtextxy(dataout.left + leftInterval, dataout.top + topInterval + HIGHT * 6, s6);

	return 0;
}

// @function:��������ʾҳ��
int EasyXSHOW::searchTreeShow(vector<AStarTreeNote>& TreeList,unsigned long long  end)
{
	//��ʾ��ť
	int length = 100;
	int width = 40;
	int x = dataout.right - length - 10;
	int y = dataout.bottom - width - 10;
	TCHAR text[] = _T("��ʾ������");
	button(x, y, length, width, text);

	ExMessage msg;
	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {//���¿�ʼ
					return FAIL;
				}
				else if (msg.x >= x && msg.x <= x + length && msg.y >= y && msg.y <= y + width)
					break;
			}
		}
	}

	//��ʾ������...
	searchTreeShowIn(TreeList, end);

	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {//���¿�ʼ
					return FAIL;
				}
			}
		}
	}

	return FINE;

}

// @function:��������ʾҳ��
int EasyXSHOW::searchTreeShowIn(vector<AStarTreeNote>& TreeList, unsigned long long  end)
{
	setfillcolor(BLACK);
	fillrectangle(cherkerboard.left, cherkerboard.top, stateshow.right, stateshow.bottom);
	TCHAR text1[] = _T("����");
	button(reset.left, reset.top, reset.right - reset.left, reset.bottom - reset.top, text1);

	//...����ѡ�������ӡ...
	int len = TreeList.size();
	int blockHigh = 60;
	int blockWide = 45;
	int blockMid = 30;
	int bottom = dataout.bottom;
	int right = dataout.right;

	//������ӡ��������
	vector<TreeShow>Tree;
	int maxLayer = 0;
	for (int i = 0; i < len; i++)
		if (maxLayer < TreeList[i].Treeprice)
			maxLayer = TreeList[i].Treeprice;
	int numLayer = 0;
	int interval = 0;
	int site = 0;
	for (int i = 0; i <= maxLayer; i++) {                               //ÿ�����
		numLayer = 0;
		site = 0;
		for(int j=0;j<len;j++){
			if (TreeList[j].Treeprice == i)
				numLayer++;
		}
		interval = right / (numLayer + 1);                              //ÿ����ȷ��
		for (int j = 0; j < len; j++) {
			if (TreeList[j].Treeprice == i) {
				site += interval;
				TreeShow temp;
				temp.x = site;
				temp.y = i * (blockHigh + blockMid);
				temp.dad = TreeList[j].FatherNote;
				temp.lay = TreeList[j].Treelayout;
				Tree.push_back(temp);
				searchTreeShowNode(temp.x, temp.y, TreeList[j], end);   //��ӡ���
			}
		}
	}
	//��ӡ����
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int half = 23;
	unsigned long long  father = 0;
	for (int i = 0; i < (int)Tree.size(); i++) {
		if (Tree[i].dad != 0) {
			father = Tree[i].dad;
			x1 = Tree[i].x;
			y1 = Tree[i].y;
			for (int j = 0; j < (int)Tree.size(); j++) {
				if (Tree[j].lay == father) {
					x2 = Tree[j].x;
					y2 = Tree[j].y;
					break;
				}
			}
			line(x1 + half, y1, x2 + half, y2 + 60);
		}
	}

	settextcolor(LIGHTCYAN);
	settextstyle(15, 0, _T("����"));  //��������  
	TCHAR notice1[25] = _T("��ɫ��ʾ��չ���");
	outtextxy(650, 10, notice1);	 //��ʾ��ʾ��Ϣ
	TCHAR notice2[25] = _T("��ɫ��ʾĿ����");
	outtextxy(650, 25, notice2);	 //��ʾ��ʾ��Ϣ
	return FINE;
}

// @function:��������ʾһ���������
int EasyXSHOW::searchTreeShowNode(int x, int y, AStarTreeNote& node, unsigned long long  end)
{
	char array[BoardSize][BoardSize] = { 0 };
	AStarEightDigital Astar;
	Astar.DataChangeGraph(node.Treelayout, array);

	int length = 15;
	int HIGHT = 15;
	int tempX = x;
	int tempY = y;
	setbkmode(TRANSPARENT);
	settextstyle(HIGHT, 0, _T("����"));  //��������  
	setfillcolor(LIGHTGRAY);
	if(node.Treelayout==end)
		settextcolor(YELLOW);            //��ֹ���չʾ
	else {
		if (node.Find)
			settextcolor(RED);               //��չ���չʾ
		else
			settextcolor(BLACK);             //���ɽ��չʾ 
	}
	//��ʾ״̬
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tempX = x + j * length;
			tempY = y + i * length;
			fillrectangle(tempX, tempY, tempX + length, tempY + length);
			TCHAR text[5] = _T(" ");
			if (array[i][j] != '0')
				_stprintf_s(text, _T("%d"), array[i][j] - '0');
			int tx = tempX + (length - textwidth(text)) / 2;
			int ty = tempY + (length - textheight(text)) / 2;
			outtextxy(tx, ty, text);
		}
	}

	//��ʾf(n)
	settextstyle(10, 0, _T("����"));//�������� 
	TCHAR text[25] = _T(" ");
	_stprintf_s(text, _T("f(n)=%d"), node.Treeinspire + node.Treeprice);
	tempX = x;
	tempY = y + 3 * length;
	fillrectangle(tempX, tempY, tempX + length * 3, tempY + length * 1);
	outtextxy(tempX, tempY + (length - textheight(text)) / 2, text);

	return FINE;

}

// @function:�����ڽ�������ʾ
int EasyXSHOW::resultNone(void)
{
	TCHAR text[] = _T("��ʱ�޽� ����������¿�ʼ");
	button(290, 270, 220, 60, text);
	ExMessage msg;
	while (true) {
		if (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= reset.left && msg.x <= reset.right && msg.y >= reset.top && msg.y <= reset.bottom) {                            //reset
					return FINE;
				}
			}
		}
	}
}



