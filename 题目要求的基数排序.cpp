#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <queue>
#include <fstream>
#define MAX 1000000
typedef int keytype;
using namespace std;
//排序表的数据结构
typedef struct records {
	keytype key;
}LIST[MAX];
LIST A;
clock_t start, stop;
double duration;
//实现交换
void swap(records &x, records &y) {
	records temp;
	temp = x;
	x = y;
	y = temp;
}
int Radix(int k, int p) {
	int power = 1;
	for (int i = 1; i <= p - 1; i++) {
		power = power * 10;
	}
	return (k % (power * 10)) / power;
}
//排序程序7，基数排序
void RadixSort(int n, LIST A) {
	int figure = 3;
	queue<records> P;
	queue<records> Q[10];
	records data;
	for (int i = 1; i <= n; i++) {
		P.push(A[i]);
	}
	for (int pass = 1; pass <= figure; pass++) {
		while (!P.empty()) {
			data = P.front();
			P.pop();
			int r = Radix(data.key, pass);
			Q[r].push(data);
		}
		for (int i = 0; i <= 9; i++) {
			while (!Q[i].empty()) {
				data = Q[i].front();
				Q[i].pop();
				P.push(data);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		A[i] = P.front();
		P.pop();
	}
}
//随机生成A[max]
void CreateNumber(int n) {
	srand(n);
	for (int i = 1; i <= n; i++) {
		A[i].key = rand() % 1000;
	}
}
//输出A[max]
void PrintList(int n, LIST A) {
	for (int i = 1; i <= n; i++) {
		cout << right << setw(10) << A[i].key;
	}
}
int main(int argc, const char * argv[]) {
	system("color f1");
	cout << "**-------------------------------------------------------**" << endl;
	cout << "   本程序接受如下元素生成方式：" << endl;
	cout << "                               1--手动输入(以0标志结尾！仅接受1--999)" << endl;
	cout << "                               2--系统随机生成" << endl;
	cout << "**-------------------------------------------------------**" << endl;
	int size, way, num, i = 0;
	bool flag = false;
	do {
		cout << "请选择生成数据方式：";
		cin >> way;
		while (way != 1 && way != 2) {
			cout << "只接受1、2两种生成元素方式！" << endl;
			cout << "请重新选择：";
			cin >> way;
		}
		switch (way) {
		case 1:
			cout << "请输入待排序元素：";
			cin >> num;
			try {
				while (num != 0) {
					i++;
					A[i].key = num;
					cin >> num;
				}
				if (i == 0) throw 0;
			}
			catch (int e) {
				cout << "无法对" << e << "个元素排序！" << endl;
				system("pause");
				return 0;
			}
			size = i;
			break;
		case 2:
			cout << "请输入数据规模：";
			cin >> size;
			while (size == 0) {
				cout << "本程序无法实现对0个元素排序！" << endl;
				cout << "请重新输入数据规模：";
				cin >> size;
			}
			CreateNumber(size);
			break;
		default:
			break;
		}
		cout << "元素已生成成功！共有" << size << "个元素！" << endl;
		cout << "**---------------------**" << endl;
		cout << "接下来使用基数排序！" << endl;
		cout << "**---------------------**" << endl;
		start = clock();
		RadixSort(size, A);
		stop = clock();
		cout << "排序结果为：" << endl;
		PrintList(size, A);
		duration = (static_cast <double>(stop - start)) / CLK_TCK;
		cout << endl << "排序结束！" << endl;
		cout << "共消耗时间" << setprecision(20) << duration << "秒" << endl;
		cout << "请选择继续or退出：";
		char ch;
		cin >> ch;
		while (ch != 'Y'&&ch != 'y' && ch != 'N' && ch != 'n') {
			cout << "只接受‘Y’‘y’‘N’‘n’四个字母！" << endl;
			cout << "请重新选择：";
			cin >> ch;
		}
		if (ch == 'y' || ch == 'Y') flag = true;
		else if (ch == 'N' || ch == 'n') flag = false;
	} while (flag);
	system("pause");
	return 0;
}