/*
 * @author  : gonzalez
 * @time    : 2022.3.28-2022.3...
 * @function: ʵ����Ĺ��ܺ�������
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

//@function : AStarEightDigital��Ĭ�Ϲ��캯��
AStarEightDigital::AStarEightDigital()
{
	;//��ʱ�����蹹��
}

//@function : AStar�㷨�е�ʼĩ״̬���캯��
int AStarEightDigital::setup(char(*s)[BoardSize], char(*e)[BoardSize])
{
	//״̬�����ʼ��
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			start[i][j] = s[i][j];
			end[i][j] = e[i][j];
		}
	}

	//���ȶ��г�ʼ��
	AStarQueNote note;
	note.Queprice = 0;
	GraphChangeData(start, note.Quelayout);
	setInspire(note);
	OpenStorage.push_back(note);

	//�������б��ʼ��
	AStarTreeNote root;
	root.FatherNote = 0;
	root.Find = false;
	root.Treeinspire = note.Queinspire;
	root.Treeprice = 0;
	root.Treelayout = note.Quelayout;
	TreeList.push_back(root);

	return FINE;
}

//@function : unsigned long long ת���� char�Ϳ��ӻ�����
int AStarEightDigital::DataChangeGraph(unsigned long long &in, char(*arry)[BoardSize])
{
	unsigned long long data = in;
	char temp;
	//����ת�ַ�
	for(int i= BoardSize-1;i>=0;i--)
		for (int j = BoardSize - 1; j >= 0; j--) {
			temp = '0' + data % 10;
			arry[i][j] = char(temp);
			data = data / 10;
		}
	return FINE;
}

//@function : char�Ϳ��ӻ����� ת���� unsigned long long
int AStarEightDigital::GraphChangeData(char(* arry)[BoardSize], unsigned long long& in)
{
	unsigned long long data = 0;
	//�ַ�ת����
	for(int i=0;i<BoardSize;i++)
		for (int j = 0; j < BoardSize; j++) {
			data = data * 10;
			data = data + (int)(arry[i][j] - '0');
		}
			
	in = data;
	return FINE;
}


/*������Ӱ���㷨�ؼ����ص�����ʽ����������*/

//@function : ����λ����������Ϊ����ʽ����ֵ
#ifdef OUFOFPOSITION
int AStarEightDigital::setInspire(AStarQueNote& in)
{
	char st[BoardSize][BoardSize];
	DataChangeGraph(in.Quelayout,st);
	int price = 0;
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			if (st[i][j] != '0')//������������
				if (st[i][j] != end[i][j])
					price++;

	in.Queinspire = price;
	
	return FINE;
}
#endif // OUFOFPOSITION

//@function : �������ӵ���Ŀ��λ�õľ������Ϊ����ʽ����ֵ�������ٷ���
#ifdef DISTANCETOTARGET
int AStarEightDigital::setInspire(AStarQueNote& in)
{
	char st[BoardSize][BoardSize];
	DataChangeGraph(in.Quelayout, st);
	int price = 0;
	char TempState;
	for(int i=0;i<BoardSize;i++)
		for (int j = 0; j < BoardSize; j++)
			if (st[i][j] != '0') {//������Ϊ���ӵ����
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

//@function : �������ӵ���Ŀ��λ�õ�ֱ�߾���(ŷ�Ͼ���)��Ϊ����ʽ����ֵ
#ifdef EULERDISTANCE
int AStarEightDigital::setInspire(AStarQueNote& in)
{
	char st[BoardSize][BoardSize];
	DataChangeGraph(in.Quelayout, st);
	int price = 0;
	char TempState;
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			if (st[i][j] != '0') {//������Ϊ���ӵ����
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
				price += int(sqrt((ti - i) * (ti - i) + (tj - j) * (tj - j)));//ŷʽ����
			}
	in.Queinspire = price;
	return FINE;
}
#endif//EULERDISTANCE

//@function : ϵ�������پ��뷨
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


//@function : �ҵ�open�����е���Сֵ
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

//@function : �ҵ�����true;δ�ҵ�����false
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

//@function : �ҵ�����true;δ�ҵ�����false
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

//@function : ���а�����A*�㷨�е������ƶ�
int AStarEightDigital::AStarMove(char(*arry)[BoardSize], AStarTreeNote&father)
{	
	//�½���ʼ��
	unsigned long long num;
	GraphChangeData(arry, num);
	AStarQueNote quenote;	
	quenote.Queprice = father.Treeprice + 1;
	quenote.Quelayout = num;
	setInspire(quenote);                                       //��ȡ����ʽ����ֵ
	AStarTreeNote treenote;
	treenote.FatherNote = father.Treelayout;
	treenote.Treeprice = quenote.Queprice;
	treenote.Treelayout = num;
	treenote.Treeinspire = quenote.Queinspire;
	treenote.Find = false;
	
	//����open/close��������������ݷֱ�ִ������
	int site;
	if (FindOpen(num, site)) {                                 //OpenStorage�д�����ֵͬ
		if (quenote.Queprice + quenote.Queinspire < OpenStorage[site].Queprice + OpenStorage[site].Queinspire){
			OpenStorage[site].Queprice = quenote.Queprice;     //��ʾ��С��f(n)ֵ
			OpenStorage[site].Queinspire = quenote.Queprice;   //��ʾ��С��f(n)ֵ
			TreeList.push_back(treenote);                      //����������
		}
	}
	else if (FindClose(num, site)) {                           //CloseStorage�д�����ֵͬ
		if (quenote.Queprice+quenote.Queinspire >= CloseStorage[site].Queprice + CloseStorage[site].Queinspire)
			;
		else {
			CloseStorage.erase(CloseStorage.begin() + site);   //ɾ��close��ԭ���
			TreeList.push_back(treenote);                      //������������
			OpenStorage.push_back(quenote);                    //�µĽ�С�������open������
		}

	}
	else {                                                     //����������ֵͬ
		OpenStorage.push_back(quenote);
		TreeList.push_back(treenote);
	}

	return FINE;
}

//@function : ��������vector���ҵ���Ӧ���
int AStarEightDigital::FindFather(AStarQueNote& node, AStarTreeNote& father)
{
	for (int i = 0; i < (int)TreeList.size(); i++) {
		if(TreeList[i].Treelayout==node.Quelayout)                  //����һ��
			if(TreeList[i].Treeprice==node.Queprice)                //����ֵһ��
				if (TreeList[i].Treeinspire == node.Queinspire) {   //��������ֵһ��
					TreeList[i].Find = true;                        //�Ѿ�������
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

//@function : "A*"�㷨
int AStarEightDigital::AStar(void)
{
	AStarQueNote temp;
	AStarTreeNote FatherNode;
	unsigned long long EndState;                          //���״̬��Ϣ
	GraphChangeData(end, EndState);                       //�����Ϣ״̬ת��

	while (true) {
		if (OpenStorage.size() == 0)                      //δ�ҵ���·��
			return FAIL;
		int MinNum = 0;

		//������Сֵ�ĸ���
		int site;
		FindOpenMin(site);
		int value = OpenStorage[site].Queinspire + OpenStorage[site].Queprice;
		for (int i = 0; i < (int)OpenStorage.size(); i++) {
			if (OpenStorage[i].Queinspire + OpenStorage[i].Queprice <= value)
				MinNum++;
		}

		//��ʼ��չ
		for (int i = 1; i <= MinNum; i++) {

			//open-->close
			int popsite;
			FindOpenMin(popsite);
			temp = OpenStorage[popsite];
			OpenStorage.erase(OpenStorage.begin() + popsite);
			CloseStorage.push_back(temp);
			FindFather(temp, FatherNode);                 //�ҵ��������еĸõ�����Ӧ�ĵ�

			if (temp.Quelayout == EndState)               //�ҵ����
				return FINE;

			//begin to extend
			char st[BoardSize][BoardSize];
			char move;
			int ZeroSite[2] = { 0,0 };
			DataChangeGraph(temp.Quelayout, st);
			for(int i= 0;i<BoardSize;i++)                 //�ҵ��ո�λ��
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

//@function : �����·��
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
					break; //����forѭ��
				}
			}
		if (lastSite == startShow) {
			routeResult.push_back(lastSite);
			break;//����whileѭ��
		}
	}

	return FINE;
}

//@function : ������ɽ����
int AStarEightDigital::generateGet(int& get)
{
	get = TreeList.size();
	return FINE;
}

//@function : �����չ�����
int AStarEightDigital::expandGet(int& get)
{
	int num = 0;
	for (int i = 0; i < (int)TreeList.size(); i++){
		if (TreeList[i].Find)
			num++;
	}
	get = num - 1;//��ֹ��㲻����չ���
	return FINE;
}



/**********************************************************************/
/*@author    : */
/*@time      : */
/*@function  : */
/**********************************************************************/
//@function:��ʾһ���������������
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

//@function : �����ʼ��������
int arrayclear(char(*array)[BoardSize])
{
	for (int i = 0; i < BoardSize; i++)
		for (int j = 0; j < BoardSize; j++)
			array[i][j] = '*';
	return FINE;
}

//@function : �ж��Ƿ���ڽ��-->start��end������������
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
		if (list1[i] != 0) {//�ո񲻼��
			Temp = list1[i];
			for (int j = 0; j < i; j++) {
				if (list1[j] > Temp)
					num1++;
			}
		}
	}
	for (int i = 0; i < (int)list2.size(); i++) {
		if (list2[i] != 0) {//�ո񲻼��
			Temp = list2[i];
			for (int j = 0; j < i; j++) {
				if (list2[j] > Temp)
					num2++;
			}
		}
	}

	if (num1 % 2 == num2 % 2)      //��ż��һ��
		return true;
	else                           //��ż�Բ�ͬ
		return false;

}

//@function : cmd��ʾ��������������ӻ����治��������
int TreePrint(vector<AStarTreeNote>& TreeList)
{
	cout << "������ΪΪ��" << endl;
	cout << "********************************************************" << endl;
	for (int i = 0; i < (int)TreeList.size(); i++) {
		cout << "���׽��Ϊ ��" << TreeList[i].FatherNote << endl;

		cout << "�Ƿ���չ ��" << boolalpha << TreeList[i].Find << endl;
		cout << "���ۺ���ֵ ��" << TreeList[i].Treeprice << endl;
		cout << "��������ֵ ��" << TreeList[i].Treeinspire << endl;
		cout << "�ý����Ϣ ��" << endl;
		Simple_show(TreeList[i].Treelayout);
		cout << "----------------------" << endl;
	}

	return FINE;
}

