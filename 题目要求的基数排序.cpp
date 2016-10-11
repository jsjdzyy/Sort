#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <queue>
#include <fstream>
#define MAX 1000000
typedef int keytype;
using namespace std;
//���������ݽṹ
typedef struct records {
	keytype key;
}LIST[MAX];
LIST A;
clock_t start, stop;
double duration;
//ʵ�ֽ���
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
//�������7����������
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
//�������A[max]
void CreateNumber(int n) {
	srand(n);
	for (int i = 1; i <= n; i++) {
		A[i].key = rand() % 1000;
	}
}
//���A[max]
void PrintList(int n, LIST A) {
	for (int i = 1; i <= n; i++) {
		cout << right << setw(10) << A[i].key;
	}
}
int main(int argc, const char * argv[]) {
	system("color f1");
	cout << "**-------------------------------------------------------**" << endl;
	cout << "   �������������Ԫ�����ɷ�ʽ��" << endl;
	cout << "                               1--�ֶ�����(��0��־��β��������1--999)" << endl;
	cout << "                               2--ϵͳ�������" << endl;
	cout << "**-------------------------------------------------------**" << endl;
	int size, way, num, i = 0;
	bool flag = false;
	do {
		cout << "��ѡ���������ݷ�ʽ��";
		cin >> way;
		while (way != 1 && way != 2) {
			cout << "ֻ����1��2��������Ԫ�ط�ʽ��" << endl;
			cout << "������ѡ��";
			cin >> way;
		}
		switch (way) {
		case 1:
			cout << "�����������Ԫ�أ�";
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
				cout << "�޷���" << e << "��Ԫ������" << endl;
				system("pause");
				return 0;
			}
			size = i;
			break;
		case 2:
			cout << "���������ݹ�ģ��";
			cin >> size;
			while (size == 0) {
				cout << "�������޷�ʵ�ֶ�0��Ԫ������" << endl;
				cout << "�������������ݹ�ģ��";
				cin >> size;
			}
			CreateNumber(size);
			break;
		default:
			break;
		}
		cout << "Ԫ�������ɳɹ�������" << size << "��Ԫ�أ�" << endl;
		cout << "**---------------------**" << endl;
		cout << "������ʹ�û�������" << endl;
		cout << "**---------------------**" << endl;
		start = clock();
		RadixSort(size, A);
		stop = clock();
		cout << "������Ϊ��" << endl;
		PrintList(size, A);
		duration = (static_cast <double>(stop - start)) / CLK_TCK;
		cout << endl << "���������" << endl;
		cout << "������ʱ��" << setprecision(20) << duration << "��" << endl;
		cout << "��ѡ�����or�˳���";
		char ch;
		cin >> ch;
		while (ch != 'Y'&&ch != 'y' && ch != 'N' && ch != 'n') {
			cout << "ֻ���ܡ�Y����y����N����n���ĸ���ĸ��" << endl;
			cout << "������ѡ��";
			cin >> ch;
		}
		if (ch == 'y' || ch == 'Y') flag = true;
		else if (ch == 'N' || ch == 'n') flag = false;
	} while (flag);
	system("pause");
	return 0;
}