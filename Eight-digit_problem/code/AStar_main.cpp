/*
 * @author  : gonzalez
 * @time    : 2022.3.28-2022.3...
 * @function: ʵ��A���������������������
 */

#include<iostream>
#include"AStar_head.h"
using namespace std;

/*int main()
{
	AStarEightDigital Astar;
	//*********
	//*  2 8 3
	//*  1   4
	//*  7 6 5
	//*********
	char ST[BoardSize][BoardSize] = { {'2','8','3'},{'1','0','4'},{'7','6','5'} };
	//char ST[BoardSize][BoardSize] = { {'2','8','3'},{'1','6','4'},{'7','0','5'} };
	//char ST[BoardSize][BoardSize] = { {'0','1','2'},{'3','4','5'},{'6','7','8'} };

	//*********
    //*  1 2 3
    //*  4   5
    //*  6 7 8
    //*********
	char EN[BoardSize][BoardSize] = { {'1','2','3'},{'8','0','4'},{'7','6','5'} };
	//char EN[BoardSize][BoardSize] = { {'1','2','3'},{'8','0','4'},{'7','6','5'} };
	//char EN[BoardSize][BoardSize] = { {'8','7','6'},{'5','4','3'},{'2','0','1'} };

	Astar.setup(ST, EN);
	Astar.AStar();

	//show the result
	for (int i = 0; i < (int)Astar.CloseStorage.size(); i++) {
		cout << Astar.CloseStorage[i].Quelayout << ' ';
		cout << Astar.CloseStorage[i].Queprice << ' ';
		cout << Astar.CloseStorage[i].Queinspire << endl;
	}
	cout << "Close���飺"<<Astar.CloseStorage.size() << endl;
	cout << "********************************************************" << endl;
	for (int i = 0; i < (int)Astar.TreeList.size(); i++) {
		cout << Astar.TreeList[i].FatherNote << '-';
		cout << boolalpha << Astar.TreeList[i].Find <<'-';
		cout << Astar.TreeList[i].Treeprice << '-';
		cout << Astar.TreeList[i].Treeinspire << endl;
		Simple_show(Astar.TreeList[i].Treelayout);
	}
	cout << "Tree���飺" << Astar.TreeList.size() << endl;

	return 0;
}*/

int main()
{
	initgraph(BKLENGTH, BKWIDTH, EW_SHOWCONSOLE);
	setbkcolor(BKCOLOR);
	char start[BoardSize][BoardSize] = { {'*','*','*'},{'*','*','*'},{'*','*','*'} };
	char end[BoardSize][BoardSize] = { {'*','*','*'},{'*','*','*'},{'*','*','*'} };
	char TempState[BoardSize][BoardSize] = { {'*','*','*'},{'*','*','*'},{'*','*','*'} };
	while (true) {
		arrayclear(start);                                                    // ��������
		arrayclear(end);
		arrayclear(TempState);
		EasyXSHOW show;
		show.InitialPage(start, end);                                         // PageFirst
		show.mainbg(start, TempState, end);
		int sign = show.mainoperate();
		if (sign == FAIL)                                                     // ����
			continue;
		if (sign == MYGO) {                                                   // �Լ�ִ��
			int result = show.Gomyself(TempState, end);
			if (result == WIN)
				show.winshow();
			if (result != SYGO)
				continue;
		}

		if (answerExist(start, end)) {                                                         // ϵͳִ�н׶�...

			AStarEightDigital Astar;
			clock_t startTime, endTime;
			int expandNum, generateNum;
			unsigned long long endstate;

			Astar.setup(start, end);
			startTime = clock();                                                               // ��ʱ��ʼ
			Astar.AStar();
			endTime = clock();                                                                 // ��ʱ����
			vector<unsigned long long> routeResult;
			Astar.routeGet(routeResult);
			Astar.expandGet(expandNum);
			Astar.generateGet(generateNum);
			show.resultDataShow(endTime - startTime, expandNum, generateNum, routeResult);     // ��ʾ������Ϣ

			show.processShow(routeResult);                                                     // ��ʾ�����
			Astar.GraphChangeData(end, endstate);                 
			show.searchTreeShow(Astar.TreeList, endstate);                                     // ��ʾ������
			if (Astar.TreeList.size() <= 100)                                                  // �����������࣬��û�д�ӡ�ı�Ҫ
				TreePrint(Astar.TreeList);                                                     // cmd��ӡ������
		}
		else                                                                                   //��ʱ�޽�
			show.resultNone();
		cout << "success������" << endl;
	}

	closegraph();


	return 0;
}