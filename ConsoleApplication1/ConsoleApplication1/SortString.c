#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include "SortString.h"


static char filename[] = "d:\\�����\\1 ����\\������ ������������� � ����������������(��������)\\������������_28\\lab_28\\��� ������ 28\\dict0.txt";

// ������������ ����� ����� � �������
#define MAX_LEN_WORD 80
// ������������ ���������� ����
#define MAX_WORDS 20000

// �����, ����������� �� ����� 
char words[MAX_WORDS][MAX_LEN_WORD + 1];
// ���������� ���� � �������
int n = 0;

// ������ ��� ���������� 
char a[MAX_WORDS][MAX_LEN_WORD + 1];

int getNextDelim(FILE* fp, char token[]);
int getNextWord(FILE* fp, char token[]);

int LoadWords(char* filename) {
	// ������� ����
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fin = fopen(filename, "rt");
	if (fin == NULL) {
		// ���� ���� �� ������ ������� - �������� �� ����
		printf("File %s doesn't opened!\n", filename);
		return 0;
	}

	char token[MAX_LEN_WORD + 1];
	// ���� �� ����� �����
	while (!feof(fin)) {
		// ���� ���� ����������� - ����� ���
		while (getNextDelim(fin, token)) {
		}
		// ���� ���� ����� - ����� ���
		if (getNextWord(fin, token)) {
			if (n < MAX_WORDS) {
				strcpy(words[n], token);
				n++;
			}
			else {
				printf("Words are more than elements in array!!\n", filename);
				fclose(fin);
				return 0;
			}
		}
	}
	// ��������� ���� � �������
	fclose(fin);
	return 1;
}

// ���������� 0 - ���� ch - �� �����.
// ���������� 1 - ���� ch - �����.
// ��������� �������� ��� ��������� ���� (� ������ < 128)
// � ��� ������� ���� �� ��������� ANSI

int isalpha_my(unsigned char ch) {

	if (isalpha(ch))
		return 1;

	// ANSI ���������!!!
	if (ch >= 192 && ch <= 223)
		return 1;
	if (ch >= 224 && ch <= 255)
		return 1;

	return 0;
}

// ���������� 1 - ����  �� ����� �������� �����������.
// � ���� ������ � token ������������ ������, ���������� 
// ���� �����������.
// ���� � ����� ��� �� ����������� - ���������� 0.
// � ���� ������ ��������� token ������������.

int getNextDelim(FILE* fp, char token[])
{
	int ch = getc(fp);
	if (ch == EOF) {
		return 0;
	}
	if (isalpha_my((unsigned char)ch)) {
		ungetc(ch, fp);
		return 0;
	}
	token[0] = (unsigned char)ch;
	token[1] = '\0';
	return 1;
}

// ���������� 1 - ����  �� ����� ��������� �����.
// � ���� ������ � token ������������ ������, ���������� 
// ��� �����. ������������� ��� ����� �� ����� MAX_LEN_WORD ��������.
// ���� � ����� �� ���� ����� - ���������� 0.
// � ���� ������ token �������� ������ ������.

int getNextWord(FILE* fp, char token[])
{
	int i = 0;
	int ch;
	while (((ch = getc(fp)) != EOF) && (i < MAX_LEN_WORD)) {
		if (!isalpha_my((unsigned char)(ch))) {
			break;
		}
		token[i++] = ch;
	}
	ungetc(ch, fp);
	token[i] = '\0';
	if (i == 0)
		return 0;
	return 1;
}

void fillArrayStrings() {

	for (int i = 0; i < n; i++) {
		strcpy(a[i], words[i]);
	}

}

int isSortedStrings() {
	for (int i = 0; i < n - 1; i++) {
		if (strcmp(a[i], a[i + 1]) > 0) {
			return 0;
		}
	}
	return 1;
}

void SelectionSortStrings() {
	for (int i = 0; i < n - 1; i++) {

		int iMin = i;
		for (int j = i + 1; j < n; j++) {
			if (strcmp(a[j], a[iMin]) < 0) {
				iMin = j;
			}
		}

		if (i != iMin) {
			char tmp[MAX_LEN_WORD + 1];
			strcpy(tmp, a[i]);
			strcpy(a[i], a[iMin]);
			strcpy(a[iMin], tmp);
		}
	}
}

void QuickSortStrings() {
	qsort(a, n, sizeof(a[0]), strcmp);
}

int BinarySearchStrings(char value) {
	int left = 0;
	int right = n - 1;

	while (left <= right) {
		int middle = (left + right) / 2;

		if (a[middle] == value) {
			return 1;
		}
		else if (a[middle] < value) {
			left = middle + 1;
		}
		else if (a[middle] > value) {
			right = middle - 1;
		}
	}
	return 0;
}

int LinearSearchStrings(char value) {
	for (int i = 0; i < n; i++) {
		if (a[i] == value) {
			return 1;
		}
	}
	return 0;
}

void BubbleSortStrings() {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp(a[j], a[j + 1]) > 0) {
				char tmp[MAX_LEN_WORD + 1];
				strcpy(tmp, a[j]);
				strcpy(a[j], a[j + 1]);
				strcpy(a[j + 1], tmp);
			}
		}
	}
}

void InsertSortStrings() {
	int i, j;
	char k[MAX_LEN_WORD + 1];

	for (i = 1; i < n; i++) {
		strcpy(k, a[i]);
		j = i - 1;
		while (j >= 0 && strcmp(a[j], k) > 0) {
			strcpy(a[j + 1], a[j]);
			j = j - 1;
		}
		strcpy(a[j + 1], k);
	}
}

void MergeStrings(int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	char** L = (char**)malloc(n1 * sizeof(char*));
	char** R = (char**)malloc(n2 * sizeof(char*));

	for (i = 0; i < n1; i++) {
		L[i] = (char*)malloc((MAX_LEN_WORD + 1) * sizeof(char));
		strcpy(L[i], a[left + i]);
	}
	for (j = 0; j < n2; j++) {
		R[j] = (char*)malloc((MAX_LEN_WORD + 1) * sizeof(char));
		strcpy(R[j], a[mid + 1 + j]);
	}

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (strcmp(L[i], R[j]) <= 0) {
			strcpy(a[k], L[i]);
			i++;
		}
		else {
			strcpy(a[k], R[j]);
			j++;
		}
		k++;
	}

	while (i < n1) {
		strcpy(a[k], L[i]);
		i++;
		k++;
	}

	while (j < n2) {
		strcpy(a[k], R[j]);
		j++;
		k++;
	}

	for (i = 0; i < n1; i++) {
		free(L[i]);
	}
	free(L);

	for (j = 0; j < n2; j++) {
		free(R[j]);
	}
	free(R);
}

void MergeSortStrings(int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		MergeSortStrings(left, mid);
		MergeSortStrings(mid + 1, right);

		MergeStrings(left, mid, right);
	}
}