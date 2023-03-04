/*
 * @author  : gonzalez
 * @time    : 2022.3.28-2022.3...
 * @function: 实现类的功能函数部分
 */

#include<iostream>
#include<queue>
#include<math.h>
#include"AStar_head.h"

using namespace std;

/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/

//@function : AStarEightDigital中默认构造函数
AStarEightDigital::AStarEightDigital()
{
	;//暂时均无需构造
}

//@function : AStar算法中的始末状态构造函数
int AStarEightDigital::setup(char(*s)[BoardSize], char(*e)[BoardSize])
{
	//状态数组初始化
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			start[i][j] = s[i][j];
			end[i][j] = e[i][j];
		}
	}

	//优先队列初始化
	AStarQueNote note;
	note.Queprice = 0;
	GraphChangeData(start, note.Quelayout);
	setInspire(note);
	OpenStorage.push_back(note);

	//线索树列表初始化
	AStarTreeNote root;
	root.FatherNote = 0;
	root.Find = false;
	root.Treeinspire = note.Queinspire;
	root.Treeprice = 0;
	root.Treelayout = note.Quelayout;
	TreeList.push_back(root);

	return FINE;
}

//@function : unsigned long long 转换成 char型可视化数据
int AStarEightDigital::DataChangeGraph(unsigned long long &in, char(*arry)[BoardSize])
{
	unsigned long long data = in;
	char temp;
	//数据转字符
	for(int i= BoardSize-1;i>=0;i--)
		for (int j = BoardSize - 1; j >= 0; j--) {
			temp = '0' + data % 10;
			arry[i][j] = char(temp);
			data = data / 10;
		}
	return FINE;
}

//@function : char型可视化数据 转换成 unsigned long long
int AStarEightDigital::GraphChangeData(char(* arry)[BoardSize], unsigned long long& in)
{
	unsigned long long data = 0;
	//字符转数据
	for(int i=0;i<BoardSize;i++)
		for (int j = 0; j < BoardSize; j++) {
			data = data * 10;
			data = data + (int)(arry[i][j] - '0');
		}
			
	in = data;
	return FINE;
}


/*！！！影响算法关键因素的启发式函数！！！*/

//@function : 不在位的棋子数作为启发式函数值
#ifdef OUFOFPOSITION
int AStarEightDigital::setInspire(AStarQueNote& in)
{
	char st[BoardSize][BoardSize];
	DataChangeGraph(in.Quelayout,st);
	int price = 0;
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			if (st[i][j] != '0')//仅讨论棋子数
				if (st[i][j] != end[i][j])
					price++;

	in.Queinspire = price;
	
	return FINE;
}
#endif // OUFOFPOSITION

//@function : 所有棋子到其目标位置的距离和作为启发式函数值（曼哈顿法）
#ifdef DISTANCETOTARGET
int AStarEightDigital::setInspire(AStarQueNote& in)
{
	char st[BoardSize][BoardSize];
	DataChangeGraph(in.Quelayout, st);
	int price = 0;
	char TempState;
	for(int i=0;i<BoardSize;i++)
		for (int j = 0; j < BoardSize; j++)
			if (st[i][j] != '0') {//仅考虑为棋子的情况
				bool sign = false;
				int ti = 0;
				int tj = 0;
				TempState = st[i][j];
				for (ti = 0; ti < BoardSize; ti++) {
					for (tj = 0; tj < BoardSize; tj++) {
						if (end[ti][tj] == TempState)
							sign = true;
						if(sign)
							break;
					}
					if (sign)
						break;
				}
				price += abs(ti - i) + abs(tj - j);
			}
	in.Queinspire = price;

	return FINE;

}
#endif // DISTANCETOTARGET

//@function : 所有棋子到其目标位置的直线距离(欧氏距离)作为启发式函数值
#ifdef EULERDISTANCE
int AStarEightDigital::setInspire(AStarQueNote& in)
{
	char st[BoardSize][BoardSize];
	DataChangeGraph(in.Quelayout, st);
	int price = 0;
	char TempState;
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			if (st[i][j] != '0') {//仅考虑为棋子的情况
				bool sign = false;
				int ti = 0;
				int tj = 0;
				TempState = st[i][j];
				for (ti = 0; ti < BoardSize; ti++) {
					for (tj = 0; tj < BoardSize; tj++) {
						if (end[ti][tj] == TempState)
							sign = true;
						if (sign)
							break;
					}
					if (sign)
						break;
				}
				price += int(sqrt((ti - i) * (ti - i) + (tj - j) * (tj - j)));//欧式距离
			}
	in.Queinspire = price;
	return FINE;
}
#endif//EULERDISTANCE

//@function : 系数曼哈顿距离法
#ifdef COEFFICIENTMANHANTTAN
int AStarEightDigital::setInspire(AStarQueNote& in)
{
	char st[BoardSize][BoardSize];
	DataChangeGraph(in.Quelayout, st);
	int price = 0;
	vector<int>nowState(10, 0);
	vector<int>endState(10, 0);
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++) {
			nowState[i * BoardSize + j] = st[i][j] - '0';
			endState[i * BoardSize + j] = end[i][j] - '0';
		}

	for (int i = 0; i < 9; i++) {
		if (nowState[i] != 0) {
			for (int j = 0; j < 9; j++) {
				if (nowState[i] == endState[j])
					price += abs(j - i);
			}
		}
	}
			
	in.Queinspire = price;
	return FINE;
}
#endif//COEFFICIENTMANHANTTAN


//@function : 找到open数组中的最小值
int AStarEightDigital::FindOpenMin(int& site)
{
	int Value = OpenStorage[0].Queinspire + OpenStorage[0].Queprice;
	int siteget = 0;
	for (int i = 0; i < (int)OpenStorage.size(); i++)
		if (OpenStorage[i].Queinspire + OpenStorage[i].Queprice <= Value) {
			Value = OpenStorage[i].Queinspire + OpenStorage[i].Queprice;
			siteget = i;
		}
	site = siteget;//site from [0 -- OpenStorage.size()-1]
	return FINE;
}

//@function : 找到返回true;未找到返回false
bool AStarEightDigital::FindOpen(unsigned long long& in,int&site)
{
	for (int i = 0; i < (int)OpenStorage.size(); i++)
		if (OpenStorage[i].Quelayout == in) {
			site = i;
			return true;
		}
	site = -1;
	return false;
}

//@function : 找到返回true;未找到返回false
bool AStarEightDigital::FindClose(unsigned long long& in, int& site)
{
	for (int i = 0; i < (int)CloseStorage.size(); i++)
		if (CloseStorage[i].Quelayout == in) {
			site = i;
			return true;
		}
	site = -1;
	return false;
}

//@function : 进行八数码A*算法中的棋子移动
int AStarEightDigital::AStarMove(char(*arry)[BoardSize], AStarTreeNote&father)
{	
	//新建初始化
	unsigned long long num;
	GraphChangeData(arry, num);
	AStarQueNote quenote;	
	quenote.Queprice = father.Treeprice + 1;
	quenote.Quelayout = num;
	setInspire(quenote);                                       //获取启发式函数值
	AStarTreeNote treenote;
	treenote.FatherNote = father.Treelayout;
	treenote.Treeprice = quenote.Queprice;
	treenote.Treelayout = num;
	treenote.Treeinspire = quenote.Queinspire;
	treenote.Find = false;
	
	//根据open/close表中有无相关数据分别执行内容
	int site;
	if (FindOpen(num, site)) {                                 //OpenStorage中存在相同值
		if (quenote.Queprice + quenote.Queinspire < OpenStorage[site].Queprice + OpenStorage[site].Queinspire){
			OpenStorage[site].Queprice = quenote.Queprice;     //显示较小的f(n)值
			OpenStorage[site].Queinspire = quenote.Queprice;   //显示较小的f(n)值
			TreeList.push_back(treenote);                      //送入搜索树
		}
	}
	else if (FindClose(num, site)) {                           //CloseStorage中存在相同值
		if (quenote.Queprice+quenote.Queinspire >= CloseStorage[site].Queprice + CloseStorage[site].Queinspire)
			;
		else {
			CloseStorage.erase(CloseStorage.begin() + site);   //删除close中原结点
			TreeList.push_back(treenote);                      //进入搜索树中
			OpenStorage.push_back(quenote);                    //新的较小结点送入open队列中
		}

	}
	else {                                                     //均不存在相同值
		OpenStorage.push_back(quenote);
		TreeList.push_back(treenote);
	}

	return FINE;
}

//@function : 在搜索树vector中找到对应结点
int AStarEightDigital::FindFather(AStarQueNote& node, AStarTreeNote& father)
{
	for (int i = 0; i < (int)TreeList.size(); i++) {
		if(TreeList[i].Treelayout==node.Quelayout)                  //布局一致
			if(TreeList[i].Treeprice==node.Queprice)                //代价值一致
				if (TreeList[i].Treeinspire == node.Queinspire) {   //启发函数值一致
					TreeList[i].Find = true;                        //已经被遍历
					father.FatherNote = 0;
					father.Find = true;
					father.Treelayout = TreeList[i].Treelayout;
					father.Treeinspire = TreeList[i].Treeinspire;
					father.Treeprice = TreeList[i].Treeprice;
					break;
				}
	}

	return FINE;
}

//@function : "A*"算法
int AStarEightDigital::AStar(void)
{
	AStarQueNote temp;
	AStarTreeNote FatherNode;
	unsigned long long EndState;                          //结果状态信息
	GraphChangeData(end, EndState);                       //结果信息状态转换

	while (true) {
		if (OpenStorage.size() == 0)                      //未找到解路径
			return FAIL;
		int MinNum = 0;

		//计算最小值的个数
		int site;
		FindOpenMin(site);
		int value = OpenStorage[site].Queinspire + OpenStorage[site].Queprice;
		for (int i = 0; i < (int)OpenStorage.size(); i++) {
			if (OpenStorage[i].Queinspire + OpenStorage[i].Queprice <= value)
				MinNum++;
		}

		//开始拓展
		for (int i = 1; i <= MinNum; i++) {

			//open-->close
			int popsite;
			FindOpenMin(popsite);
			temp = OpenStorage[popsite];
			OpenStorage.erase(OpenStorage.begin() + popsite);
			CloseStorage.push_back(temp);
			FindFather(temp, FatherNode);                 //找到线索树中的该点所对应的点

			if (temp.Quelayout == EndState)               //找到结果
				return FINE;

			//begin to extend
			char st[BoardSize][BoardSize];
			char move;
			int ZeroSite[2] = { 0,0 };
			DataChangeGraph(temp.Quelayout, st);
			for(int i= 0;i<BoardSize;i++)                 //找到空格位置
				for (int j = 0; j < BoardSize; j++)
					if (st[i][j] == '0') {
						ZeroSite[0] = i;
						ZeroSite[1] = j;
					}

			//Up
			if (ZeroSite[0] > 0) {
				//move
				move = st[ZeroSite[0] - 1][ZeroSite[1]];
				st[ZeroSite[0] - 1][ZeroSite[1]] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;

				AStarMove(st, FatherNode);                                        //moving
				
				//move back
				move = st[ZeroSite[0] - 1][ZeroSite[1]];
				st[ZeroSite[0] - 1][ZeroSite[1]] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;
			}
			//Dowm
			if (ZeroSite[0] < 2) {
				//move
				move = st[ZeroSite[0] + 1][ZeroSite[1]];
				st[ZeroSite[0] + 1][ZeroSite[1]] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;

				AStarMove(st, FatherNode);                                        //moving

				//move back
				move = st[ZeroSite[0] + 1][ZeroSite[1]];
				st[ZeroSite[0] + 1][ZeroSite[1]] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;
			}
			//Left
			if (ZeroSite[1] > 0) {
				//move
				move = st[ZeroSite[0]][ZeroSite[1] - 1];
				st[ZeroSite[0]][ZeroSite[1] - 1] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;

				AStarMove(st, FatherNode);                                        //moving

				//move back
				move = st[ZeroSite[0]][ZeroSite[1] - 1];
				st[ZeroSite[0]][ZeroSite[1] - 1] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;
			}
			//Right
			if (ZeroSite[1] < 2) {
				//move
				move = st[ZeroSite[0]][ZeroSite[1] + 1];
				st[ZeroSite[0]][ZeroSite[1] + 1] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;

				AStarMove(st, FatherNode);                                        //moving

				//move back
				move = st[ZeroSite[0]][ZeroSite[1] + 1];
				st[ZeroSite[0]][ZeroSite[1] + 1] = st[ZeroSite[0]][ZeroSite[1]];
				st[ZeroSite[0]][ZeroSite[1]] = move;
			}
		}
	}

}

//@function : 求出解路径
int AStarEightDigital::routeGet(vector<unsigned long long>& routeResult)
{
	unsigned long long startShow;
	unsigned long long endShow;
	GraphChangeData(start, startShow);
	GraphChangeData(end, endShow);

	unsigned long long lastSite;
	lastSite = endShow;
	while (true) {
		routeResult.push_back(lastSite);
		for (int i = 0; i < (int)TreeList.size(); i++)
			if (TreeList[i].Find) {
				if (TreeList[i].Treelayout == lastSite) {
					lastSite = TreeList[i].FatherNote;
					break; //跳出for循环
				}
			}
		if (lastSite == startShow) {
			routeResult.push_back(lastSite);
			break;//跳出while循环
		}
	}

	return FINE;
}

//@function : 求出生成结点数
int AStarEightDigital::generateGet(int& get)
{
	get = TreeList.size();
	return FINE;
}

//@function : 求出拓展结点数
int AStarEightDigital::expandGet(int& get)
{
	int num = 0;
	for (int i = 0; i < (int)TreeList.size(); i++){
		if (TreeList[i].Find)
			num++;
	}
	get = num - 1;//终止结点不算拓展结点
	return FINE;
}



/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
//@function:显示一个八数码问题界面
int Simple_show(unsigned long long& in)
{
	unsigned long long divied = 100000000;
	unsigned long long temp = 0;
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			temp = in / divied;
			if (temp)
				cout << temp << ' ';
			else
				cout << "  ";
			in = in - in / divied * divied;
			divied = divied / 10;
		}
		cout << endl;
	}
	return 0;
}

//@function : 清除初始化数组标记
int arrayclear(char(*array)[BoardSize])
{
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			array[i][j] = '*';
	return FINE;
}

//@function : 判断是否存在结果-->start和end的逆序数不变
bool answerExist(char(*arr1)[BoardSize], char(*arr2)[BoardSize])
{
	vector<int>list1;
	vector<int>list2;

	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++) {
			list1.push_back(arr1[i][j] - '0');
			list2.push_back(arr2[i][j] - '0');
		}
	int num1 = 0;
	int num2 = 0;
	int Temp = 0;
	for (int i = 0; i < (int)list1.size(); i++) {
		if (list1[i] != 0) {//空格不检查
			Temp = list1[i];
			for (int j = 0; j < i; j++) {
				if (list1[j] > Temp)
					num1++;
			}
		}
	}
	for (int i = 0; i < (int)list2.size(); i++) {
		if (list2[i] != 0) {//空格不检查
			Temp = list2[i];
			for (int j = 0; j < i; j++) {
				if (list2[j] > Temp)
					num2++;
			}
		}
	}

	if (num1 % 2 == num2 % 2)      //奇偶性一致
		return true;
	else                           //奇偶性不同
		return false;

}

//@function : cmd显示结果树（如遇可视化界面不足的情况）
int TreePrint(vector<AStarTreeNote>& TreeList)
{
	cout << "搜索树为为：" << endl;
	cout << "********************************************************" << endl;
	for (int i = 0; i < (int)TreeList.size(); i++) {
		cout << "父亲结点为 ：" << TreeList[i].FatherNote << endl;

		cout << "是否被拓展 ：" << boolalpha << TreeList[i].Find << endl;
		cout << "代价函数值 ：" << TreeList[i].Treeprice << endl;
		cout << "激励函数值 ：" << TreeList[i].Treeinspire << endl;
		cout << "该结点信息 ：" << endl;
		Simple_show(TreeList[i].Treelayout);
		cout << "----------------------" << endl;
	}

	return FINE;
}

