/*
 * @author  : gonzalez
 * @time    : 2022.3.28-2022.4.12
 * @function: 实现A星求解八数码问题的头文件
 */

#pragma once
#include <vector>              //vector数组
#include <queue>               //队列
#include <graphics.h>          //EasyX库
#include <conio.h>             //EasyX库
#include <windows.h>           //sleep函数
#include <time.h>              //记录执行时间
#include <string>              //使用string字符串
using namespace std;           //使用vector数组

#define FINE         1         //正常返回
#define FAIL        -1         //错误返回
#define BoardSize    3         //八数码数组存储范围


/*条件编译选择启发式函数*/
//#define OUFOFPOSITION                //不在位的棋子数
//#define COEFFICIENTMANHANTTAN        //系数曼哈顿距离法--->可能存在高估的情况，因此并非可采纳的，结果可能不是最优解       
//#define EULERDISTANCE                //欧拉距离法
#define DISTANCETOTARGET             //曼哈顿距离法所有棋子到其目标位置的距离和

/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
struct AStarTreeNote {                                           //A*遍历树存储结构体
	unsigned long long FatherNote = 0;
	unsigned long long Treelayout = 0;
	int Treeprice = 0;
	int Treeinspire = 0;
	bool Find = false;                                           //是否被遍历
};
struct AStarQueNote{                                             //open/close表存储结构体
	unsigned long long Quelayout = 0;
	int Queprice = 0;                                            //代价函数值
	int Queinspire = 0;                                          //激励函数值
};

/*默认char型字符存储八数码方式如下(0表示空格)
        * * * * * * *
        * 0 * 1 * 2 *
        * * * * * * *     
        * 3 * 4 * 5 *      --转换--》   012345678
        * * * * * * *
        * 6 * 7 * 8 *
        * * * * * * *
 */

class AStarEightDigital {
public:
	char start [BoardSize][BoardSize] = { '\0' };                //起始八数码形式
	char end   [BoardSize][BoardSize] = { '\0' };                //终点八数码形式
	vector<AStarQueNote> OpenStorage;                            //open数组vector
	vector<AStarQueNote> CloseStorage;                           //close数组vector
 	vector<AStarTreeNote> TreeList;                              //存储搜索过程中的线索树
public:
	AStarEightDigital();                                                     //构造函数
	int setup(char(*s)[BoardSize], char(*e)[BoardSize]);                     //初始化
	int DataChangeGraph(unsigned long long& in , char(*arry)[BoardSize]);    //unsigned long long 转 char格式化数组数据
	int GraphChangeData(char(*arry)[BoardSize], unsigned long long& in);     //unsigned long long 转 unsigned long long 
	int setInspire(AStarQueNote& in);                                        //获取启发式函数的值
	int FindOpenMin(int& site);
	bool FindOpen(unsigned long long& in, int& site);
	bool FindClose(unsigned long long& in, int& site);
	int AStarMove(char(*arry)[BoardSize], AStarTreeNote& father);
	int FindFather(AStarQueNote& node, AStarTreeNote& father);
	int AStar(void);

	int routeGet(vector<unsigned long long>& routeResult);                    //根据求出解路径
	int generateGet(int& get);                                                //返回生成结点数
	int expandGet(int& get);                                                  //返回拓展结点数

};


/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
struct AREA{                                            //可视化区域存储
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
};
struct TreeShow {                                       //可视化树型打印存储结构体
	int x = 0;
	int y = 0;
	unsigned long long dad = 0;
	unsigned long long lay = 0;
};

#define BKCOLOR         WHITE
#define PICWIDE         120
#define BKLENGTH        800
#define BKWIDTH         600
#define BLOCKSIZE       40
#define BUTTONHIGHT     15
#define SYGO            1
#define MYGO            0
#define SLEEPTIME       350                             //单步演示之间的间隔时长
#define WIN           6

class EasyXSHOW {
public:
	IMAGE num[9];
	AREA General, cherkerboard, dataout, stateshow, buttonoperate;
	AREA eightborad, startstate, endstate;
	AREA systemgo, myselfgo;
	AREA upbutton, rightbutton, downbutton, leftbutton;
	AREA reset,initialbegin, initialend;
public:
	EasyXSHOW();                                      //可视化初始构造函数
	int Initialbg(void);
	int Boardshow(char(*array)[BoardSize]);
	int blockshow(int x, int y, char(*array)[BoardSize]);
	int block(int x, int y, int num);
	int button(int x, int y, int length, int width, TCHAR text[]);
	int stateinitial(char(*st)[BoardSize], char(*end)[BoardSize]);
	int moveinitial(char(*state)[BoardSize], AREA& site);
	int InitialPage(char(*start)[BoardSize], char(*end)[BoardSize]);
	int mainbg(char(*start)[BoardSize], char(*state)[BoardSize], char(*end)[BoardSize]);
	int mainoperate(void);
	int Gomyself(char(*state)[BoardSize], char(*end)[BoardSize]);
	void winshow(void);

	int processShow(vector<unsigned long long>& routeResult);
	int resultDataShow(clock_t time, int expandNum, int generateNum, vector<unsigned long long> routeResult);
	int searchTreeShow(vector<AStarTreeNote>& TreeList, unsigned long long  end);
	int searchTreeShowIn(vector<AStarTreeNote>& TreeList, unsigned long long  end);
	int searchTreeShowNode(int x, int y, AStarTreeNote& node, unsigned long long  end);
	int resultNone(void);
};

/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
int Simple_show(unsigned long long& in);
int arrayclear(char(*array)[BoardSize]);
bool answerExist(char(*arr1)[BoardSize], char(*arr2)[BoardSize]);
int TreePrint(vector<AStarTreeNote>& TreeList);


