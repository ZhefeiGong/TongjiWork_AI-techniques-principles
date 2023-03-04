/*
 * @author  : gonzalez
 * @time    : 2022.3.28-2022.3...
 * @function: 实现A星求解八数码问题的主函数
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
	cout << "Close数组："<<Astar.CloseStorage.size() << endl;
	cout << "********************************************************" << endl;
	for (int i = 0; i < (int)Astar.TreeList.size(); i++) {
		cout << Astar.TreeList[i].FatherNote << '-';
		cout << boolalpha << Astar.TreeList[i].Find <<'-';
		cout << Astar.TreeList[i].Treeprice << '-';
		cout << Astar.TreeList[i].Treeinspire << endl;
		Simple_show(Astar.TreeList[i].Treelayout);
	}
	cout << "Tree数组：" << Astar.TreeList.size() << endl;

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
		arrayclear(start);                                                    // 数组重置
		arrayclear(end);
		arrayclear(TempState);
		EasyXSHOW show;
		show.InitialPage(start, end);                                         // PageFirst
		show.mainbg(start, TempState, end);
		int sign = show.mainoperate();
		if (sign == FAIL)                                                     // 重置
			continue;
		if (sign == MYGO) {                                                   // 自己执行
			int result = show.Gomyself(TempState, end);
			if (result == WIN)
				show.winshow();
			if (result != SYGO)
				continue;
		}

		if (answerExist(start, end)) {                                                         // 系统执行阶段...

			AStarEightDigital Astar;
			clock_t startTime, endTime;
			int expandNum, generateNum;
			unsigned long long endstate;

			Astar.setup(start, end);
			startTime = clock();                                                               // 计时开始
			Astar.AStar();
			endTime = clock();                                                                 // 计时结束
			vector<unsigned long long> routeResult;
			Astar.routeGet(routeResult);
			Astar.expandGet(expandNum);
			Astar.generateGet(generateNum);
			show.resultDataShow(endTime - startTime, expandNum, generateNum, routeResult);     // 显示搜索信息

			show.processShow(routeResult);                                                     // 显示解过程
			Astar.GraphChangeData(end, endstate);                 
			show.searchTreeShow(Astar.TreeList, endstate);                                     // 显示搜索树
			if (Astar.TreeList.size() <= 100)                                                  // 若搜索树过多，则没有打印的必要
				TreePrint(Astar.TreeList);                                                     // cmd打印搜索树
		}
		else                                                                                   //此时无解
			show.resultNone();
		cout << "success！！！" << endl;
	}

	closegraph();


	return 0;
}