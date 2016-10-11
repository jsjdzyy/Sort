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
//�������1��ֱ�Ӳ�������
void InsertSort(int n, LIST A) {
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = i; j>0; j--) {
			if (A[j].key<A[j - 1].key) swap(A[j], A[j - 1]);
		}
	}
}
//�۰���Ҵ�����λ��
int BinSearch(LIST A, int low, int high, keytype k) {
	if (low>high) return low;
	else {
		int mid = (low + high) / 2;
		if (k<A[mid].key) return BinSearch(A, low, mid - 1, k);
		else if (k>A[mid].key) return BinSearch(A, mid + 1, high, k);
		else return mid;
	}
}
//�������2���۰��������
void BinInsertSort(int n, LIST A) {
	A[0].key = -1;
	for (int i = 1; i <= n; i++) {
		int j = BinSearch(A, 1, i, A[i].key);
		keytype temp;
		temp = A[i].key;
		for (int k = i; k>j; k--) {
			A[k].key = A[k - 1].key;
		}
		A[j].key = temp;
	}
}
//�������3����������
void BubbleSort(int n, LIST A) {
	for (int i = 1; i<n; i++) {
		for (int j = n; j >= i + 1; j--) {
			if (A[j].key<A[j - 1].key) {
				swap(A[j], A[j - 1]);
			}
		}
	}
}
int FindPivot(int i, int j) {
	keytype firstkey = A[i].key;
	int k;
	for (k = i + 1; k <= j; k++) {
		if (A[k].key>firstkey) return k;
		else if (firstkey>A[k].key) return i;
	}
	return 0;
}
int Partition(int i, int j, keytype pivot) {
	int x, y;
	do {
		for (x = i; A[x].key<pivot; x++);
		for (y = j; A[y].key >= pivot; y--);
		if (x<y) swap(A[x], A[y]);
	} while (x <= y);
	return x;
}
//�������4������
void QuickSort(int i, int j) {
	keytype pivot;
	int k, pivotindex;
	pivotindex = FindPivot(i, j);
	if (pivotindex != 0) {
		pivot = A[pivotindex].key;
		k = Partition(i, j, pivot);
		QuickSort(i, k - 1);
		QuickSort(k, j);
	}
}
//�������5��ѡ������
void SelectSort(int n, LIST A) {
	keytype lowkey;
	int i, j, lowindex;
	for (i = 1; i<n; i++) {
		lowindex = i;
		lowkey = A[i].key;
		for (j = i + 1; j <= n; j++) {
			if (A[j].key<lowkey) {
				lowkey = A[j].key;
				lowindex = j;
			}
		}
		swap(A[i], A[lowindex]);
	}
}
//��������
void PushUp(int first, int last) {
	int r = first;
	while (r <= last / 2) {
		if (r == last / 2 && last % 2 == 0) {
			if (A[r].key<A[2 * r].key) {
				swap(A[r], A[2 * r]);
			}
			r = last;
		}
		else if (A[r].key<A[2 * r].key && A[2 * r].key >= A[2 * r + 1].key) {
			swap(A[r], A[2 * r]);
			r = 2 * r;
		}
		else if (A[r].key<A[2 * r + 1].key && A[2 * r + 1].key>A[2 * r].key) {
			swap(A[r], A[2 * r + 1]);
			r = 2 * r + 1;
		}
		else {
			r = last;
		}
	}
}
//�������6������
void HeapSort(int n, LIST A) {
	int i;
	for (i = n / 2; i >= 1; i--) {
		PushUp(i, n);
	}
	for (i = n; i >= 2; i--) {
		swap(A[1], A[i]);
		PushUp(1, i - 1);
	}
}
int Radix(int k, int p) {
	int power = 1;
	for (int i = 1; i <= p - 1; i++) {
		power = power * 10;
	}
	return (k % (power * 10)) / power;
}
//��figure
int FindFigure(int n) {
	int figure = 1;
	for (int i = 1; i<100; i++) {
		if (pow(10, i) <= n && pow(10, i + 1)>n)  return i + 1;
	}
	return figure;
}
//�������7����������
void RadixSort(int n, LIST A) {
	int figure = FindFigure(n);
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
		A[i].key = rand() % (10 * n);
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
	cout << "   ��������ʵ�����¹��ܣ�" << endl;
	cout << "                           1--ֱ�Ӳ�������" << endl;
	cout << "                           2--�۰��������" << endl;
	cout << "                           3--��������" << endl;
	cout << "                           4--��������" << endl;
	cout << "                           5--ѡ������" << endl;
	cout << "                           6--������" << endl;
	cout << "                           7--��������" << endl;
	cout << "**-------------------------------------------------------**" << endl;
	cout << "**-------------------------------------------------------**" << endl;
	cout << "   �������������Ԫ�����ɷ�ʽ��" << endl;
	cout << "                               1--�ֶ�����(��0��־��β��)" << endl;
	cout << "                               2--ϵͳ�������" << endl;
	cout << "**-------------------------------------------------------**" << endl;
	int size,way,num,i=0;
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
			cout << "�޷���"<<e<<"��Ԫ������" << endl;
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
	ofstream output("A.txt",ios::ate);
	for (int i = 1; i <= size; i++) {
		output <<right<<setw(10)<<A[i].key;
		if (i % 15 == 0) output << endl;
	}
	output << endl<<"����ǰԪ����ȫ��д�룡"<<endl;
	output.close();
	bool flag = false;
	int times=0;
	ofstream output3("����ʱ��.txt",ios::app);
	do {
		cout << "��ѡ���������";
		int choose;
		cin >> choose;
		output << "��������Ԫ�ظ���"<<size<<"��";
		output3 << "����"<<setw(3)<<++times<<"������";
		switch (choose) {
		case 1:
			cout << "**----------------------**" << endl;
			cout << "  ������ʹ��ֱ�Ӳ�������" << endl;
			cout << "**---------------------**" << endl;
			output3 << "����ʹ��ֱ�Ӳ�������";
			start = clock();
			InsertSort(size, A);
			stop = clock();
			break;
		case 2:
			cout << "**---------------------**" << endl;
			cout << "������ʹ���۰��������" << endl;
			cout << "**---------------------**" << endl;
			output3 << "����ʹ���۰��������";
			start = clock();
			BinInsertSort(size, A);
			stop = clock();
			break;
		case 3:
			cout << "**---------------------**" << endl;
			cout << "������ʹ����������" << endl;
			cout << "**---------------------**" << endl;
			output3 << "����ʹ����������";
			start = clock();
			BubbleSort(size, A);
			stop = clock();
			break;
		case 4:
			cout << "**---------------------**" << endl;
			cout << "������ʹ�ÿ�������" << endl;
			cout << "**---------------------**" << endl;
			output3 << "����ʹ�ÿ�������";
			start = clock();
			QuickSort(1, size);
			stop = clock();
			break;
		case 5:
			cout << "**---------------------**" << endl;
			cout << "������ʹ��ѡ������" << endl;
			cout << "**---------------------**" << endl;
			output3 << "����ʹ��ѡ������";
			start = clock();
			SelectSort(size, A);
			stop = clock();
			break;
		case 6:
			cout << "**---------------------**" << endl;
			cout << "������ʹ�ö�����" << endl;
			cout << "**---------------------**" << endl;
			output3 << "����ʹ�ö�����";
			start = clock();
			HeapSort(size, A);
			stop = clock();
			break;
		case 7:
			cout << "**---------------------**" << endl;
			cout << "������ʹ�û�������" << endl;
			cout << "**---------------------**" << endl;
			output3 << "����ʹ�û�������";
			start = clock();
			RadixSort(size, A);
			stop = clock();
			break;
		default:
			break;
		}
		cout << "������Ϊ��" << endl;
		PrintList(size, A);
		duration = (static_cast <double>(stop - start)) / CLK_TCK;
		cout << endl << "���������" << endl;
		cout << "������ʱ��" << setprecision(20) << duration << "��" << endl;
		output3<< "������ʱ��" << setprecision(20) << duration << "��" << endl;
		output.open("A.txt",ios::app);
		output << "����" << setw(3) << times << "������"<<endl;
		for (int i = 1; i <= size; i++) {
			output << right << setw(10) << A[i].key;
			if (i % 15 == 0) output << endl;
		}
		output << endl << "�����Ԫ��д����ϣ�" << endl;
		output.close();
		ifstream output2;
		output2.open("A.txt",ios::in);
		for (int i = 1; i <=size; i++) {
			output2 >> A[i].key;
		}
		output2.close();
		cout << "��ѡ�����or�˳���" ;
		char ch;
		cin >> ch;
		while (ch!='Y'&&ch!='y' && ch!='N' && ch!='n') {
			cout << "ֻ���ܡ�Y����y����N����n���ĸ���ĸ��" << endl;
			cout << "������ѡ��";
			cin>>ch;
		}
		if (ch == 'y' || ch == 'Y') flag = true;
		else if (ch == 'N' || ch == 'n') flag = false;
	} while (flag);
	system("pause");
	return 0;
}