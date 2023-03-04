/*
 * @author    : gonzalez
 * @time      : 2022.5.2-2022.5.9
 * @function  : AlphaBeta �ڲ�ʵ�ֺ���
 */


#include"minimaxAlphaBeta_head.h"

#define DIRECTIONINNER 8   //8�������ϵĽڵ������չ
//#define DIRECTIONOUTER 16

using namespace std;

//******************************************************************���⺯��******************************************************************
//@function:�����̸�ֵ
bool copyBoard(char(*chessTemp)[BOARDLENGHT + BOARDADD], char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	for (int i = 0; i < BOARDWIDTH + BOARDADD; i++)
		for (int j = 0; j < BOARDLENGHT + BOARDADD; j++)
			chessTemp[i][j] = chessBoard[i][j];
	return true;
}

//@function:����sort�ıȽ�
bool compareAscend(NODESCORE& lhs, NODESCORE& rhs)//����
{
	return lhs.score < rhs.score;
}
bool compareDecend(NODESCORE& lhs, NODESCORE& rhs)//����
{
	return lhs.score > rhs.score;
}


//******************************************************************���ں���******************************************************************

//@function  :  �����̽��г�ʼ������-->1��0��*��
//@notice    :  Ϊ���캯��
searchAlphaBeta::searchAlphaBeta(char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	for (int i = 0; i <= BOARDWIDTH; i++) {
		for (int j = 0; j <= BOARDLENGHT; j++) {
			board[i][j] = chessBoard[i][j];
		}
	}
}

//@function  :  ����ĳ���ַ����Ļ����÷�
int searchAlphaBeta::getScoreFromString(string& get)
{
	string dealWith = get;
	int len = 6;                                           //������Ԫ�����ʽ���м���

	//����������length>=6�Ĵ�
	if ((int)get.size() < len - 1)                         // С���������������
		return 0;
	else if ((int)get.size() == len - 1)                   // �������Ȼ����
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

//@function  :  ���������ڲ�����
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

//@function  :  ������������
void searchAlphaBeta::toneUpAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site, char sort)
{
	int beforeValue = 0;
	int afterValue = 0;

	beforeValue = toneUpAssessIn(chessBoard, site);

	chessBoard[site.rowSite][site.colSite] = sort;         //���
	afterValue = toneUpAssessIn(chessBoard, site);
	chessBoard[site.rowSite][site.colSite] = NONECHESS;    //��ԭ

	site.score = afterValue - beforeValue;

	return;
}

//@function:�ж���Χ�Ƿ��������
bool searchAlphaBeta::chessAround(int row, int col , char (* chess)[BOARDLENGHT + BOARDADD])
{
#ifdef DIRECTIONINNER
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			if ((i >= 1 && i <= BOARDWIDTH) && (j >= 1 && j <= BOARDLENGHT) && (i != row || j != col)) {
				if(chess[i][j]!='*')
					return true;  //��������
			}
		}
	}
	return false;                 //����������
#endif 
}

//@function  :  ���ۺ����жԲ�ͬ��������ز�ͬ�÷�
//@notice    :  ʹ����Ԫ���������
int searchAlphaBeta::eachGet(string& extract)
{

	/*-----------------------------------------------����-----------------------------------------------*/
	//��Ӯ
	if (extract == "******")
		return 0;
	else if (extract == "111111" || extract == "*11111" || extract == "11111*"
		|| extract == "111110" || extract == "011111")
		return -10000000;
	//�ڻ���&�ڳ���
	else if (extract == "*1111*" || 
		extract == "1*111*"|| extract == "11*11*" || extract == "111*1*" || extract == "1111**" ||
		extract == "1*1111" || extract == "11*111"  ||extract == "111*11" || extract == "1111*1" ||
		extract == "*11110" || extract == "1*1110" || extract == "11*110" || extract == "111*10" || extract == "1111*0" ||
		extract == "0*1111" || extract == "01*111" || extract == "011*11" || extract == "0111*1" || extract == "01111*")
		return -100000;
	//�ڻ���
	else if (extract == "**111*" || extract == "*1*11*" || extract == "*11*1*" || extract == "*111**")
		return -8000;
	//������
	else if (extract == "**1110" || extract == "*1*110" || extract == "*11*10" || extract == "*111*0" ||
		extract == "1**110" || extract == "1*1*10" || extract == "1*11*0" ||
		extract == "11**10" || extract == "11*1*0" ||
		extract == "111**0" ||
		extract == "0**111" || extract == "0*1*11" || extract == "0*11*1" || extract == "0*111*" ||
		extract == "01**11" || extract == "01*1*1" || extract == "01*11*" ||
		extract == "011**1" || extract == "011*1*" ||
		extract == "0111**")
		return -50;
	//�ڻ��
	else if (extract == "***11*" || extract == "**1*1*" || extract == "**11**" ||
		extract == "*1**1*" || extract == "*1*1**" ||
		extract == "*11***")
		return -50;
	//���߶�
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
	//�ڻ�һ
	else if (extract == "****1*" || extract == "***1**" ||
		extract == "**1***" ||
		extract == "*1****")
		return -3;

	/*-----------------------------------------------����-----------------------------------------------*/
	//��Ӯ
	else if (extract == "000000" || extract == "*00000" || extract == "00000*"
		|| extract == "000001" || extract == "100000")
		return 1000000;
	//�׻���
	else if (extract == "*0000*")
		return 50000;
	//�׳���
	else if(extract == "0*000*" || extract == "00*00*" || extract == "000*0*" || extract == "0000**" ||
		extract == "0*0000" || extract == "00*000" || extract == "000*00" || extract == "0000*0" ||
		extract == "*00001" || extract == "0*0001" || extract == "00*001" || extract == "000*01" || extract == "0000*1" ||
		extract == "1*0000" || extract == "10*000" || extract == "100*00" || extract == "1000*0" || extract == "10000*")
		return 400;
	//�׻���
	else if (extract == "**000*" || extract == "*0*00*" || extract == "*00*0*" || extract == "*000**")
		return 400;
	//������
	else if (extract == "**0001" || extract == "*0*001" || extract == "*00*01" || extract == "*000*1" ||
		extract == "0**001" || extract == "0*0*01" || extract == "0*00*1" ||
		extract == "00**01" || extract == "00*0*1" ||
		extract == "000**1" ||
		extract == "1**000" || extract == "1*0*00" || extract == "1*00*0" || extract == "1*000*" ||
		extract == "10**00" || extract == "10*0*0" || extract == "10*00*" ||
		extract == "100**0" || extract == "100*0*" ||
		extract == "1000**")
		return 20;
	//�׻��
	else if (extract == "***00*" || extract == "**0*0*" || extract == "**00**" ||
		extract == "*0**0*" || extract == "*0*0**" ||
		extract == "*00***")
		return 20;
	//���߶�
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
	//�׻�һ
	else if (extract == "****0*" || extract == "***0**" ||
		extract == "**0***" ||
		extract == "*0****")
		return 1;
	else
		return 0;

}

//@function:������ս���������޸ĵص��ֵ
int searchAlphaBeta::alphabetaGetBack(void)
{
	return alphabetaAlgorithm(board, 0, INT_MIN, INT_MAX);//�������ӵ�
}

//@function:��߽�
bool searchAlphaBeta::findBorder(char(*chessBoard)[BOARDLENGHT + BOARDADD], BORDER& bor)
{
	//�Ͻ�
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
	//���
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
	//�½�
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
	//�ҽ�
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

//@function:ȫ����������
int searchAlphaBeta::assessBoardValue(char(*chessBoard)[BOARDLENGHT + BOARDADD])
{
	int ValueGet = 0;
	int eachLength = 6;

	//N->S(�ϵ���)
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
	//W->E(����)
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
	//NW->SE(���ϵ�����)
	for (int ter = 5; ter <= BOARDWIDTH; ter++) {
		int xST = 1;
		int yST = ter;
		if (ter == 5) {//����
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
		if (ter == BOARDLENGHT - 5) {//����
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
	//SW->NE(���µ�����)
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

//@function:�ҵ����ŵ�̽����㣨�ֲ�����+��̬����+��֦��
bool searchAlphaBeta::seekBestPoint(char(*chessBoard)[BOARDLENGHT + BOARDADD], char chessClass, vector<NODESCORE>& result)
{
	vector<NODESCORE>Total;
	BORDER bor;
	char chessTemp[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };
	copyBoard(chessTemp, chessBoard);
	findBorder(chessTemp, bor);//�޶��߽���ٱ���

	//��չ���н��
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			if (chessBoard[i][j] == NONECHESS && chessAround(i, j, chessBoard)) {//�������н����-->����chessAround��λ��������뿼��
				NODESCORE node;
				node.rowSite = i;
				node.colSite = j;
				toneUpAssess(chessBoard, node, chessClass);//��������
				Total.push_back(node);
			}
		}
	}
	//���н�������
	if (chessClass == BLACKCHESS)       //��������-->���ڼ�֦
		sort(Total.begin(), Total.end(), compareAscend);
	else if (chessClass == WHITECHESS)  //���彵��-->���ڼ�֦
		sort(Total.begin(), Total.end(), compareDecend);

	//���и�ֵ����
	for (int i = 0; (i < (int)Total.size() && i + 1 <= EACHSEARCH); i++)
		result.push_back(Total[i]);

	return true;

}

//@function:��һ������������
bool searchAlphaBeta::searchThreeMust(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& get, char chessSort)
{
	//----------initiate----------
	int row = get.rowSite;
	int col = get.colSite;
	int tempRow = 0;
	int tempCol = 0;
	string  score = "";
	for (int i = 0; i < 3; i++)//��������
		score += chessSort;
	score += NONECHESS;
	string TEMP = "";

	//----------operate----------
	//����
	for (int i = 1; (i <= 4 && col + i <= BOARDLENGHT); i++) {
		tempRow = row;
		tempCol = col + i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//����
	for (int i = 1; (i <= 4 && col - i >= 1); i++) {
		tempRow = row;
		tempCol = col - i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//����
	for (int i = 1; (i <= 4 && row - i >= 1); i++) {
		tempRow = row - i;
		tempCol = col;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//����
	for (int i = 1; (i <= 4 && row + i <=BOARDWIDTH); i++) {
		tempRow = row + i;
		tempCol = col;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//����
	for (int i = 1; (i <= 4 && row - i >= 1&& col - i >= 1); i++) {
		tempRow = row - i;
		tempCol = col - i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//����
	for (int i = 1; (i <= 4 && row + i <=BOARDWIDTH && col - i >= 1); i++) {
		tempRow = row + i;
		tempCol = col - i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//����
	for (int i = 1; (i <= 4 && row - i >= 1 && col + i <= BOARDLENGHT); i++) {
		tempRow = row - i;
		tempCol = col + i;
		TEMP += chessBoard[tempRow][tempCol];
	}
	if (TEMP == score)
		return true;
	else
		TEMP = "";
	//����
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

//@function:��һ�������������л�������(��Ԫ��)
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

//@function:��һ��������������
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
	chessBoard[row][col] = chessSort;     //�޸�

	//----------------------operate----------------------
	//W-E
	string beforeWE = "";
	for (int i = stCol; i <= enCol; i++)
		beforeWE += chessBoard[row][i];
	if (fiveMust(beforeWE, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //��ԭ
		return true;
	}

	//N-S
	string beforeNS = "";
	for (int i = stRow; i <= enRow; i++)
		beforeNS += chessBoard[i][col];
	if (fiveMust(beforeNS, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //��ԭ
		return true;
	}

	//SW-NE
	string beforeSWNE = "";
	int leftTopDis = min(row - stRow, col - stCol);
	int rightDownDis = min(enRow - row, enCol - col);
	for (int i = row - leftTopDis, j = col - leftTopDis; (i <= row + rightDownDis && j <= col + rightDownDis); i++, j++)
		beforeSWNE += chessBoard[i][j];
	if (fiveMust(beforeSWNE, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //��ԭ
		return true;
	}

	//NW-SE
	string beforeNWSE = "";
	int leftDownDis = min(enRow - row, col - stCol);
	int rightTopDis = min(row - stRow, enCol - col);
	for (int i = row + leftDownDis, j = col - leftDownDis; (i >= row - rightTopDis && j <= col + rightTopDis); i--, j++)
		beforeNWSE += chessBoard[i][j];
	if (fiveMust(beforeNWSE, chessSort)) {
		chessBoard[row][col] = NONECHESS;  //��ԭ
		return true;
	}

	chessBoard[row][col] = NONECHESS;      //��ԭ
	return false;
}

//@function:��һ������,������ڱ����壬�򷵻ر������λ��-->��԰����ӽ�
bool searchAlphaBeta::firstLayerAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], int& feeBack)
{
	char chessClass = WHITECHESS;
	BORDER bor;
	char chessTemp[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };
	copyBoard(chessTemp, chessBoard);
	findBorder(chessTemp, bor); //�޶��߽���ٱ���

	//����������������
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			//�������н����-->����chessAround��λ��������뿼��
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
	//����������������
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			//�������н����-->����chessAround��λ��������뿼��
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
	//�����������
	for (int i = bor.top; i <= bor.down; i++) {
		for (int j = bor.left; j <= bor.right; j++) {
			//�������н����-->����chessAround��λ��������뿼��
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

//@function:����alpha-beta����-->�Ż���������-->ÿ�ν�����10�����ŵ�
int searchAlphaBeta::alphabetaAlgorithm(char(*chessBoard)[BOARDLENGHT + BOARDADD], int layer, int alpha, int beta)
{

	//==================================lastLayerBack==================================
	if (layer == EXPLORELAYER)
		return assessBoardValue(chessBoard);                                           //ȫ������

	//=====================================Initiate====================================
	vector<NODESCORE> choenChess;
	int nextValue = 0;
	int thisAlpha = alpha;
	int thisBeta = beta;
	char chessTemp[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { 0 };//���¿���
	copyBoard(chessTemp, chessBoard);

	//=====================================Operate=====================================
	//---------------------------------------MIN---------------------------------------
	if (layer % 2 == 1) {
		seekBestPoint(chessTemp, BLACKCHESS, choenChess);                              //Ѱ������Ϻõ�case������չ
		for (int i = 0; i < (int)choenChess.size(); i++) {
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = BLACKCHESS;      //�ӽڵ�Ϊ����
			nextValue = alphabetaAlgorithm(chessTemp, layer + 1, thisAlpha, thisBeta); //���µݹ�
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = NONECHESS;       //��ԭ��ԭ����
			thisBeta = min(nextValue, thisBeta);                                       //ȡminֵ
			if (thisAlpha >= thisBeta)                                                 //alpha��֦
				break;
		}
		return thisBeta;
	}
	//---------------------------------------MAX---------------------------------------
	else {
		if (layer == 0) {
			int MustSite = 0;
			if (firstLayerAssess(chessBoard, MustSite))                                //��һ������
				return MustSite;
		}
		int goChess = 0;
		seekBestPoint(chessTemp, WHITECHESS, choenChess);                              //Ѱ������Ϻõ�case������չ
		for (int i = 0; i < (int)choenChess.size(); i++) {
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = WHITECHESS;      //�ӽڵ�Ϊ����
			nextValue = alphabetaAlgorithm(chessTemp, layer + 1, thisAlpha, thisBeta); //���µݹ�
			chessTemp[choenChess[i].rowSite][choenChess[i].colSite] = NONECHESS;       //��ԭ��ԭ����
			if (layer == 0) {                                                          //��0����������
				if (nextValue > thisAlpha)
					goChess = choenChess[i].rowSite * 100 + choenChess[i].colSite;
			}
			thisAlpha = max(nextValue, thisAlpha);                                     //ȡmaxֵ
			if (thisAlpha >= thisBeta)                                                 //beta��֦
				break;
		}
		if (layer == 0)
			return goChess;
		else
			return thisAlpha;
	}
}
