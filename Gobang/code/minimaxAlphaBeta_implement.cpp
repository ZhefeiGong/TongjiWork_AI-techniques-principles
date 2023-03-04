/*
 * @author    : gonzalez
 * @time      : 2022.5.2-2022.5.9
 * @function  : AlphaBeta 内部实现函数
 */


#include"minimaxAlphaBeta_head.h"

#define DIRECTIONINNER 8   //8个方向上的节点进行拓展
//#define DIRECTIONOUTER 16

using namespace std;

//******************************************************************类外函数******************************************************************
//@function:新棋盘赋值
bool copyBoard(char(*chessTemp)[BOARDLENGHT + BOARDADD], char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	for (int i = 0; i < BOARDWIDTH + BOARDADD; i++)
		for (int j = 0; j < BOARDLENGHT + BOARDADD; j++)
			chessTemp[i][j] = chessBoard[i][j];
	return true;
}

//@function:用于sort的比较
bool compareAscend(NODESCORE& lhs, NODESCORE& rhs)//升序
{
	return lhs.score < rhs.score;
}
bool compareDecend(NODESCORE& lhs, NODESCORE& rhs)//降序
{
	return lhs.score > rhs.score;
}


//******************************************************************类内函数******************************************************************

//@function  :  对棋盘进行初始化操作-->1黑0白*空
//@notice    :  为构造函数
searchAlphaBeta::searchAlphaBeta(char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	for (int i = 0; i <= BOARDWIDTH; i++) {
		for (int j = 0; j <= BOARDLENGHT; j++) {
			board[i][j] = chessBoard[i][j];
		}
	}
}

//@function  :  计算某个字符串的滑动得分
int searchAlphaBeta::getScoreFromString(string& get)
{
	string dealWith = get;
	int len = 6;                                           //采用六元组的形式进行计算

	//产生或留下length>=6的串
	if ((int)get.size() < len - 1)                         // 小于六个点进行评估
		return 0;
	else if ((int)get.size() == len - 1)                   // 五个子依然考虑
		dealWith += NONECHESS; 

	int answer = 0;
	for (int st = 0; st <= ((int)dealWith.size() - len); st++) {
		string temp = "";
		for (int j = 0; j < len; j++) {
			temp = temp + dealWith[st + j];
		}
		answer += eachGet(temp);
	}
	return answer;
}

//@function  :  增益评估内部函数
int searchAlphaBeta::toneUpAssessIn(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site)
{

	//--------------------initialize--------------------
	int row = site.rowSite;
	int col = site.colSite;
	int extend = 6;
    
	int Value = 0;
	int stCol, enCol, stRow, enRow;
	stCol = max(1, col - extend + 1);
	enCol = min(BOARDLENGHT, col + extend - 1);
	stRow = max(1, row - extend + 1);
	enRow = min(BOARDWIDTH, row + extend - 1);


	//----------------------operate----------------------
	//W-E
	string beforeWE = "";
	for (int i = stCol; i <= enCol; i++)
		beforeWE += chessBoard[row][i];
    Value += getScoreFromString(beforeWE);

	//N-S
	string beforeNS = "";
	for (int i = stRow; i <= enRow; i++)
		beforeNS += chessBoard[i][col];
	Value += getScoreFromString(beforeNS);

	//SW-NE
	string beforeSWNE = "";
	int leftTopDis = min(row - stRow, col - stCol);
	int rightDownDis = min(enRow - row, enCol - col);
	for (int i = row - leftTopDis, j = col - leftTopDis; (i <= row + rightDownDis && j <= col + rightDownDis); i++, j++)
		beforeSWNE += chessBoard[i][j];
	Value += getScoreFromString(beforeSWNE);

	//NW-SE
	string beforeNWSE = "";
	int leftDownDis = min(enRow - row, col - stCol);
	int rightTopDis = min(row - stRow, enCol - col);
	for (int i = row + leftDownDis, j = col - leftDownDis; (i >= row - rightTopDis && j <= col + rightTopDis); i--, j++)
		beforeNWSE += chessBoard[i][j];
	Value += getScoreFromString(beforeNWSE);


	return Value;
}

//@function  :  增益评估函数
void searchAlphaBeta::toneUpAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site, char sort)
{
	int beforeValue = 0;
	int afterValue = 0;

	beforeValue = toneUpAssessIn(chessBoard, site);

	chessBoard[site.rowSite][site.colSite] = sort;         //添加
	afterValue = toneUpAssessIn(chessBoard, site);
	chessBoard[site.rowSite][site.colSite] = NONECHESS;    //复原

	site.score = afterValue - beforeValue;

	return;
}

//@function:判断周围是否存在棋子
bool searchAlphaBeta::chessAround(int row, int col , char (* chess)[BOARDLENGHT + BOARDADD])
{
#ifdef DIRECTIONINNER
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			if ((i >= 1 && i <= BOARDWIDTH) && (j >= 1 && j <= BOARDLENGHT) && (i != row || j != col)) {
				if(chess[i][j]!='*')
					return true;  //存在棋子
			}
		}
	}
	return false;                 //不存在棋子
#endif 
}

//@function  :  评价函数中对不同的情况返回不同得分
//@notice    :  使用六元组进行评估
int searchAlphaBeta::eachGet(string& extract)
{

	/*-----------------------------------------------黑棋-----------------------------------------------*/
	//黑赢
	if (extract == "******")
		return 0;
	else if (extract == "111111" || extract == "*11111" || extract == "11111*"
		|| extract == "111110" || extract == "011111")
		return -10000000;
	//黑活四&黑冲四
	else if (extract == "*1111*" || 
		extract == "1*111*"|| extract == "11*11*" || extract == "111*1*" || extract == "1111**" ||
		extract == "1*1111" || extract == "11*111"  ||extract == "111*11" || extract == "1111*1" ||
		extract == "*11110" || extract == "1*1110" || extract == "11*110" || extract == "111*10" || extract == "1111*0" ||
		extract == "0*1111" || extract == "01*111" || extract == "011*11" || extract == "0111*1" || extract == "01111*")
		return -100000;
	//黑活三
	else if (extract == "**111*" || extract == "*1*11*" || extract == "*11*1*" || extract == "*111**")
		return -8000;
	//黑眠三
	else if (extract == "**1110" || extract == "*1*110" || extract == "*11*10" || extract == "*111*0" ||
		extract == "1**110" || extract == "1*1*10" || extract == "1*11*0" ||
		extract == "11**10" || extract == "11*1*0" ||
		extract == "111**0" ||
		extract == "0**111" || extract == "0*1*11" || extract == "0*11*1" || extract == "0*111*" ||
		extract == "01**11" || extract == "01*1*1" || extract == "01*11*" ||
		extract == "011**1" || extract == "011*1*" ||
		extract == "0111**")
		return -50;
	//黑活二
	else if (extract == "***11*" || extract == "**1*1*" || extract == "**11**" ||
		extract == "*1**1*" || extract == "*1*1**" ||
		extract == "*11***")
		return -50;
	//黑眠二
	else if (extract == "***110" || extract == "**1*10" || extract == "**11*0" ||
		extract == "*1**10" || extract == "*1*1*0" ||
		extract == "*11**0" ||
		extract == "1***10" || extract == "1**1*0" ||
		extract == "1*1**0" ||
		extract == "0***11" || extract == "0**1*1" || extract == "0**11*" ||
		extract == "0*1**1" || extract == "0*1*1*" ||
		extract == "0*11**" ||
		extract == "01***1" || extract == "01**1*" ||
		extract == "011***")
		return -3;
	//黑活一
	else if (extract == "****1*" || extract == "***1**" ||
		extract == "**1***" ||
		extract == "*1****")
		return -3;

	/*-----------------------------------------------白棋-----------------------------------------------*/
	//白赢
	else if (extract == "000000" || extract == "*00000" || extract == "00000*"
		|| extract == "000001" || extract == "100000")
		return 1000000;
	//白活四
	else if (extract == "*0000*")
		return 50000;
	//白冲四
	else if(extract == "0*000*" || extract == "00*00*" || extract == "000*0*" || extract == "0000**" ||
		extract == "0*0000" || extract == "00*000" || extract == "000*00" || extract == "0000*0" ||
		extract == "*00001" || extract == "0*0001" || extract == "00*001" || extract == "000*01" || extract == "0000*1" ||
		extract == "1*0000" || extract == "10*000" || extract == "100*00" || extract == "1000*0" || extract == "10000*")
		return 400;
	//白活三
	else if (extract == "**000*" || extract == "*0*00*" || extract == "*00*0*" || extract == "*000**")
		return 400;
	//白眠三
	else if (extract == "**0001" || extract == "*0*001" || extract == "*00*01" || extract == "*000*1" ||
		extract == "0**001" || extract == "0*0*01" || extract == "0*00*1" ||
		extract == "00**01" || extract == "00*0*1" ||
		extract == "000**1" ||
		extract == "1**000" || extract == "1*0*00" || extract == "1*00*0" || extract == "1*000*" ||
		extract == "10**00" || extract == "10*0*0" || extract == "10*00*" ||
		extract == "100**0" || extract == "100*0*" ||
		extract == "1000**")
		return 20;
	//白活二
	else if (extract == "***00*" || extract == "**0*0*" || extract == "**00**" ||
		extract == "*0**0*" || extract == "*0*0**" ||
		extract == "*00***")
		return 20;
	//白眠二
	else if (extract == "***001" || extract == "**0*01" || extract == "**00*1" ||
		extract == "*0**01" || extract == "*0*0*1" ||
		extract == "*00**1" ||
		extract == "0***01" || extract == "0**0*1" ||
		extract == "0*0**1" ||
		extract == "1***00" || extract == "1**0*0" || extract == "1**00*" ||
		extract == "1*0**0" || extract == "1*0*0*" ||
		extract == "1*00**" ||
		extract == "10***0" || extract == "10**0*" ||
		extract == "100***")
		return 1;
	//白活一
	else if (extract == "****0*" || extract == "***0**" ||
		extract == "**0***" ||
		extract == "*0****")
		return 1;
	else
		return 0;

}

//@function:获得最终结果，返回修改地点的值
int searchAlphaBeta::alphabetaGetBack(void)
{
	return alphabetaAlgorithm(board, 0, INT_MIN, INT_MAX);//返回落子点
}

//@function:求边界
bool searchAlphaBeta::findBorder(char(*chessBoard)[BOARDLENGHT + BOARDADD], BORDER& bor)
{
	//上界
	bool gout = false;
	for (int i = 1; i <= BOARDWIDTH; i++) {
		for (int j = 1; j <= BOARDLENGHT; j++) {
			if (chessBoard[i + 1][j] != '*') {
				bor.top = i;
				gout = true;
			}
			if (gout)
				break;
		}
		if (gout)
			break;
	}
	//左界
	gout = false;
	for (int j = 1; j <= BOARDLENGHT; j++) {
		for (int i = 1; i <= BOARDLENGHT; i++) {
			if (chessBoard[i][j + 1] != '*') {
				bor.left = j;
				gout = true;
			}
			if (gout)
				break;
		}
		if (gout)
			break;
	}
	//下界
	gout = false;
	for (int i = BOARDWIDTH; i >= 1; i--) {
		for (int j = BOARDLENGHT; j >= 1; j--) {
			if (chessBoard[i - 1][j] != '*') {
				bor.down= i;
				gout = true;
			}
			if (gout)
				break;
		}
		if (gout)
			break;
	}
	//右界
	gout = false;
	for (int j = BOARDLENGHT; j >=1; j--) {
		for (int i = BOARDLENGHT; i >=1; i--) {
			if (chessBoard[i][j - 1] != '*') {
				bor.right = j;
				gout = true;
			}
			if (gout)
				break;
		}
		if (gout)
			break;
	}
	return true;
}

//@function:全局评估函数
int searchAlphaBeta::assessBoardValue(char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	int ValueGet = 0;
	int eachLength = 6;

	//N->S(上到下)
	for (int i = 1; i <= BOARDWIDTH; i++) {
		for (int j = 1; j <= BOARDLENGHT - eachLength + 1; j++) {
			string temp = "";
			for (int add = 0; add < eachLength; add++) {
				temp += chessBoard[i][j + add];
			}
			if (temp != "******")
				ValueGet += eachGet(temp);
		}
	}
	//W->E(左到右)
	for (int j = 1; j <= BOARDLENGHT; j++) {
		for (int i = 1; i <= BOARDWIDTH - eachLength + 1; i++) {
			string temp = "";
			for (int add = 0; add < eachLength; add++) {
				temp += chessBoard[i + add][j];
			}
			if (temp != "******")
				ValueGet += eachGet(temp);
		}
	}
	//NW->SE(左上到右下)
	for (int ter = 5; ter <= BOARDWIDTH; ter++) {
		int xST = 1;
		int yST = ter;
		if (ter == 5) {//特判
			string temp = "";
			for (int i = 0; i < eachLength - 1; i++) {
				temp += chessBoard[yST - i][xST + i];
			}
			temp += '*';
			if (temp != "******")
				ValueGet += eachGet(temp);
		}
		else
			for (; (xST <= BOARDLENGHT - eachLength + 1) && (yST >= eachLength); (xST++, yST--)) {
				string temp = "";
				for (int i = 0; i < eachLength; i++) {
					temp += chessBoard[yST - i][xST + i];
				}
				if (temp != "******")
					ValueGet += eachGet(temp);
			}
	}
	for (int ter = BOARDLENGHT - 5; ter >= 2; ter--) {
		int xST = ter;
		int yST = BOARDWIDTH;
		if (ter == BOARDLENGHT - 5) {//特例
			string temp = "";
			for (int i = 0; i < eachLength - 1; i++) {
				temp += chessBoard[yST - i][xST + i];
			}
			temp += '*';
			if (temp != "******")
				ValueGet += eachGet(temp);
		}
		else
			for (; (xST <= BOARDLENGHT - eachLength + 1) && (yST >= eachLength); (xST++, yST--)) {
				string temp = "";
				for (int i = 0; i < eachLength; i++) {
					temp += chessBoard[yST - i][xST + i];
				}
				if (temp != "******")
					ValueGet += eachGet(temp);
			}
	}
	//SW->NE(左下到右上)
	for (int ter = 5; ter <= BOARDLENGHT; ter++) {
		int xST = ter;
		int yST = BOARDWIDTH;
		if (ter == 5) {
			string temp = "";
			for (int i = 0; i < eachLength - 1; i++) {
				temp += chessBoard[yST - i][xST - i];
			}
			temp += '*';
			if (temp != "******")
				ValueGet += eachGet(temp);
		}
		else
			for (; (xST >= eachLength) && (yST >= eachLength); (xST--, yST--)) {
				string temp = "";
				for (int i = 0; i < eachLength; i++) {
					temp += chessBoard[yST - i][xST - i];
				}
				if (temp != "******")
					ValueGet += eachGet(temp);
			}
	}
	for (int ter = 5; ter <= BOARDWIDTH - 1; ter++) {
		int xST = BOARDLENGHT;
		int yST = ter;
		if (ter == 5) {
			string temp = "";
			for (int i = 0; i < eachLength - 1; i++) {
				temp += chessBoard[yST - i][xST - i];
			}
			temp += '*';
			if (temp != "******")
				ValueGet += eachGet(temp);
		}
		else
			for (; (xST >= eachLength) && (yST >= eachLength); (xST--, yST--)) {
				string temp = "";
				for (int i = 0; i < eachLength; i++) {
					temp += chessBoard[yST - i][xST - i];
				}
				if (temp != "******")
					ValueGet += eachGet(temp);
			}
	}

	return ValueGet;
}

//@function:找到较优的探索结点（局部搜索+静态启发+剪枝）
bool searchAlphaBeta::seekBestPoint(char(*chessBoard)[BOARDLENGHT + BOARDADD], char chessClass, vector<NODESCORE>& result)
{
	vector<NODESCORE>Total;
	BORDER bor;
	char chessTemp[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };
	copyBoard(chessTemp, chessBoard);
	findBorder(chessTemp, bor);//限定边界减少遍历

	//拓展所有结点
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			if (chessBoard[i][j] == NONECHESS && chessAround(i, j, chessBoard)) {//遍历所有解情况-->符合chessAround的位置情况纳入考虑
				NODESCORE node;
				node.rowSite = i;
				node.colSite = j;
				toneUpAssess(chessBoard, node, chessClass);//增益评估
				Total.push_back(node);
			}
		}
	}
	//进行降序排序
	if (chessClass == BLACKCHESS)       //黑棋升序-->易于剪枝
		sort(Total.begin(), Total.end(), compareAscend);
	else if (chessClass == WHITECHESS)  //白棋降序-->易于剪枝
		sort(Total.begin(), Total.end(), compareDecend);

	//进行赋值返回
	for (int i = 0; (i < (int)Total.size() && i + 1 <= EACHSEARCH); i++)
		result.push_back(Total[i]);

	return true;

}

//@function:第一层白棋活三特判
bool searchAlphaBeta::searchThreeMust(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& get, char chessSort)
{
	//----------initiate----------
	int row = get.rowSite;
	int col = get.colSite;
	int tempRow = 0;
	int tempCol = 0;
	string  score = "";
	for (int i = 0; i < 3; i++)//活三特判
		score += chessSort;
	score += NONECHESS;
	string TEMP = "";

	//----------operate----------
	//向右
	for (int i = 1; (i <= 4 && col + i <= BOARDLENGHT); i++) {
		tempRow = row;
		tempCol = col + i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//向左
	for (int i = 1; (i <= 4 && col - i >= 1); i++) {
		tempRow = row;
		tempCol = col - i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//向上
	for (int i = 1; (i <= 4 && row - i >= 1); i++) {
		tempRow = row - i;
		tempCol = col;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//向下
	for (int i = 1; (i <= 4 && row + i <=BOARDWIDTH); i++) {
		tempRow = row + i;
		tempCol = col;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//左上
	for (int i = 1; (i <= 4 && row - i >= 1&& col - i >= 1); i++) {
		tempRow = row - i;
		tempCol = col - i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//左下
	for (int i = 1; (i <= 4 && row + i <=BOARDWIDTH && col - i >= 1); i++) {
		tempRow = row + i;
		tempCol = col - i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//右上
	for (int i = 1; (i <= 4 && row - i >= 1 && col + i <= BOARDLENGHT); i++) {
		tempRow = row - i;
		tempCol = col + i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//右下
	for (int i = 1; (i <= 4 && row + i <=BOARDWIDTH && col + i <= BOARDLENGHT); i++) {
		tempRow = row + i;
		tempCol = col + i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";

	return false;

}

//@function:第一层五子连珠特判滑窗特判(五元组)
bool searchAlphaBeta::fiveMust(string& get, char chessSort)
{
	int len = get.size();
	int extend = 5;
	string  goal = "";
	if (len < extend)
		return false;
	for (int i = 1; i <= extend; i++)
		goal += chessSort;

	for (int i = 0; i <= len - extend; i++) {
		string temp = "";
		for (int j = 0; j < extend; j++)
			temp += get[i + j];
		if (temp == goal)
			return true;
	}

	return false;
}

//@function:第一层五子连珠特判
bool searchAlphaBeta::searchFiveMust(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site, char chessSort)
{
	//--------------------initialize--------------------
	int row = site.rowSite;
	int col = site.colSite;
	int extend = 5;
	int stCol, enCol, stRow, enRow;
	stCol = max(1, col - extend + 1);
	enCol = min(BOARDLENGHT, col + extend - 1);
	stRow = max(1, row - extend + 1);
	enRow = min(BOARDWIDTH, row + extend - 1);
	chessBoard[row][col] = chessSort;     //修改

	//----------------------operate----------------------
	//W-E
	string beforeWE = "";
	for (int i = stCol; i <= enCol; i++)
		beforeWE += chessBoard[row][i];
	if (fiveMust(beforeWE, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //复原
		return true;
	}

	//N-S
	string beforeNS = "";
	for (int i = stRow; i <= enRow; i++)
		beforeNS += chessBoard[i][col];
	if (fiveMust(beforeNS, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //复原
		return true;
	}

	//SW-NE
	string beforeSWNE = "";
	int leftTopDis = min(row - stRow, col - stCol);
	int rightDownDis = min(enRow - row, enCol - col);
	for (int i = row - leftTopDis, j = col - leftTopDis; (i <= row + rightDownDis && j <= col + rightDownDis); i++, j++)
		beforeSWNE += chessBoard[i][j];
	if (fiveMust(beforeSWNE, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //复原
		return true;
	}

	//NW-SE
	string beforeNWSE = "";
	int leftDownDis = min(enRow - row, col - stCol);
	int rightTopDis = min(row - stRow, enCol - col);
	for (int i = row + leftDownDis, j = col - leftDownDis; (i >= row - rightTopDis && j <= col + rightTopDis); i--, j++)
		beforeNWSE += chessBoard[i][j];
	if (fiveMust(beforeNWSE, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //复原
		return true;
	}

	chessBoard[row][col] = NONECHESS;      //复原
	return false;
}

//@function:第一层特判,如果存在必下棋，则返回必下棋局位置-->针对白棋视角
bool searchAlphaBeta::firstLayerAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], int& feeBack)
{
	char chessClass = WHITECHESS;
	BORDER bor;
	char chessTemp[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };
	copyBoard(chessTemp, chessBoard);
	findBorder(chessTemp, bor); //限定边界减少遍历

	//白棋五子连珠特判
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			//遍历所有解情况-->符合chessAround的位置情况纳入考虑
			if (chessBoard[i][j] == NONECHESS && chessAround(i, j, chessBoard)) {
				NODESCORE node;
				node.rowSite = i;
				node.colSite = j;
				if (searchFiveMust(chessBoard, node, WHITECHESS)) {
					feeBack = node.rowSite * 100 + node.colSite;
					return true;
				}
			}
		}
	}
	//黑棋五子连珠特判
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			//遍历所有解情况-->符合chessAround的位置情况纳入考虑
			if (chessBoard[i][j] == NONECHESS && chessAround(i, j, chessBoard)) {
				NODESCORE node;
				node.rowSite = i;
				node.colSite = j;
				if (searchFiveMust(chessBoard, node, BLACKCHESS)) {
					feeBack = node.rowSite * 100 + node.colSite;
					return true;
				}
			}
		}
	}
	//白棋活三特判
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			//遍历所有解情况-->符合chessAround的位置情况纳入考虑
			if (chessBoard[i][j] == NONECHESS && chessAround(i, j, chessBoard)) {
				NODESCORE node;
				node.rowSite = i;
				node.colSite = j;
				if (searchThreeMust(chessBoard, node, WHITECHESS)) {
					feeBack = node.rowSite * 100 + node.colSite;
					return true;
				}
			}
		}
	}

	return false;

}

//@function:进行alpha-beta搜索-->优化搜索个数-->每次仅搜索10个较优点
int searchAlphaBeta::alphabetaAlgorithm(char(*chessBoard)[BOARDLENGHT + BOARDADD], int layer, int alpha, int beta)
{

	//==================================lastLayerBack==================================
	if (layer == EXPLORELAYER)
		return assessBoardValue(chessBoard);                                           //全局评估

	//=====================================Initiate====================================
	vector<NODESCORE> choenChess;
	int nextValue = 0;
	int thisAlpha = alpha;
	int thisBeta = beta;
	char chessTemp[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };//重新开辟
	copyBoard(chessTemp, chessBoard);

	//=====================================Operate=====================================
	//---------------------------------------MIN---------------------------------------
	if (layer % 2 == 1) {
		seekBestPoint(chessTemp, BLACKCHESS, choenChess);                              //寻找情况较好的case进行拓展
		for (int i = 0; i < (int)choenChess.size(); i++) {
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = BLACKCHESS;      //子节点为黑棋
			nextValue = alphabetaAlgorithm(chessTemp, layer + 1, thisAlpha, thisBeta); //向下递归
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = NONECHESS;       //还原成原棋盘
			thisBeta = min(nextValue, thisBeta);                                       //取min值
			if (thisAlpha >= thisBeta)                                                 //alpha剪枝
				break;
		}
		return thisBeta;
	}
	//---------------------------------------MAX---------------------------------------
	else {
		if (layer == 0) {
			int MustSite = 0;
			if (firstLayerAssess(chessBoard, MustSite))                                //第一层特判
				return MustSite;
		}
		int goChess = 0;
		seekBestPoint(chessTemp, WHITECHESS, choenChess);                              //寻找情况较好的case进行拓展
		for (int i = 0; i < (int)choenChess.size(); i++) {
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = WHITECHESS;      //子节点为白棋
			nextValue = alphabetaAlgorithm(chessTemp, layer + 1, thisAlpha, thisBeta); //向下递归
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = NONECHESS;       //还原成原棋盘
			if (layer == 0) {                                                          //第0层的特殊情况
				if (nextValue > thisAlpha)
					goChess = choenChess[i].rowSite * 100 + choenChess[i].colSite;
			}
			thisAlpha = max(nextValue, thisAlpha);                                     //取max值
			if (thisAlpha >= thisBeta)                                                 //beta剪枝
				break;
		}
		if (layer == 0)
			return goChess;
		else
			return thisAlpha;
	}
}
