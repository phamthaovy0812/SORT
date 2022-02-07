#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int* readFile(ifstream& fread, int& n);
void WriteFile(ofstream& fwrite, int* a, int n);
//without compare
void flashSort(int* a, int n);
void mergeSort(int* a, int l, int r);
void Bubble_sort(int arr[], int n);
void Shaker_sort(int arr[], int n);
void Heap_sort(int arr[], int n);
void InsertionSort(int a[], int n);
void QuickSort(int a[], int n);
void counting_sort(int input[], int n);
void selection_sort(int a[], int n);
void radix_sort(int a[], int n);
void shell_sort(int a[], int n);
//with compare
void C_flashSort(int a[], int n, long long& comp);
void C_mergeSort(int* a, int l, int r, long long& comp);
void C_Bubble_sort(int arr[], int n, long long& count);
void C_Shaker_sort(int arr[], int n, long long& count);
void C_Heap_sort(int arr[], int n, long long& count);
void C_InsertionSort(int a[], int n, long long& compar);
void C_quickSort(int* a, int l, int r, long long& compar);
void C_counting_sort(int input[], int n, long long& compar);
void C_selection_sort(int a[], int n, long long& count_compare);
void C_radix_sort(int a[], int n, long long& count_compare);
void C_shell_sort(int a[], int n, long long& count_compare);
//
void out(int* a, int n);
void GenerateRandomData(int a[], int n);
bool checkStringNum(string a);
void cmd1(string mode, string algor, string inputFile, string paramet);
void cmd2(string mode, string algor, string size, string order, string paramet);
void cmd3(string mode, string algor, string size, string paramet);
void cmd4(string mode, string algor1, string algor2, string inputFile);
void cmd5(string mode, string algor1, string algor2, string size, string order);

/*	luoi nhap qua viet san lenh :)))
	cmd1 :
	a.exe -c flash-sort input.txt -both
	a.exe -a merge-sort input.txt -both
	a.exe -a quick-sort input.txt -both
	a.exe -a bubble-sort input.txt -both
	a.exe -a shaker-sort input.txt -both
	a.exe -a insertion-sort input.txt -both
	a.exe -a heap-sort input.txt -both
	a.exe -a selection-sort input.txt -both
	a.exe -a radix-sort input.txt -both
	a.exe -a shell-sort input.txt -both
	a.exe -a counting-sort input.txt -both

	cmd2:
	a.exe -a flash-sort 30000 -rand -both
	a.exe -a merge-sort 30000 -rand -both
	a.exe -a quick-sort 30000 -rand -both
	a.exe -a bubble-sort 30000 -rand -both
	a.exe -a shaker-sort 30000 -rand -both
	a.exe -a insertion-sort 30000 -rand -both
	a.exe -a heap-sort 30000 -rand -both
	a.exe -a selection-sort 30000 -rand -both
	a.exe -a radix-sort 30000 -rand -both
	a.exe -a shell-sort 30000 -rand -both
	a.exe -a counting-sort 30000 -rand -both
	cmd3 : a.exe -a merge-sort 20000 -both
	cmd4 : a.exe -a flash-sort merge-sort input.txt
	cmd5 : a.exe -c merge-sort radix-sort 50000 -nsorted
*/

int main(int argc, char** argv)
{
	if (argc == 6) {
		string s[5];
		for (int i = 1; i <= 5; i++)
			s[i - 1] = (string)argv[i];
		if (checkStringNum(s[2]))
			cmd2(s[0], s[1], s[2], s[3], s[4]);
		else
			cmd5(s[0], s[1], s[2], s[3], s[4]);
	}
	if (argc == 5) {
		string s[4];
		for (int i = 1; i <= 4; i++)
			s[i - 1] = (string)argv[i];
		if (checkStringNum(s[2]))
			cmd3(s[0], s[1], s[2], s[3]);
		else {
			if (s[3] == "-both" || s[3] == "-comp" || s[3] == "-time")
				cmd1(s[0], s[1], s[2], s[3]);
			else
				cmd4(s[0], s[1], s[2], s[3]);
		}
	}
	if (argc != 6 && argc != 5)
		cout << "error input!";
	return 0;
}

void HoanVi(int& a, int& b)
{
	int x = a;
	a = b;
	b = x;
}
void flashSort(int a[], int n)
{
	int minVal = a[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0; i < m; i++)
		l[i] = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i] < minVal)
			minVal = a[i];
		if (a[i] > a[max])
			max = i;
	}
	if (a[max] == minVal)
		return;
	double c1 = (double)(m - 1) / (a[max] - minVal);
	for (int i = 0; i < n; i++)
	{
		int k = int(c1 * (a[i] - minVal));
		++l[k];
	}
	for (int i = 1; i < m; i++)
		l[i] += l[i - 1];
	HoanVi(a[max], a[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (nmove < n - 1)
	{
		while (j > l[k] - 1)
		{
			j++;
			k = int(c1 * (a[j] - minVal));
		}
		flash = a[j];
		if (k < 0) break;
		while (j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	for (int i = 1; i < n; i++)
	{
		int v = i - 1;
		int key = a[i];
		while (a[v] > key && v >= 0)
		{
			a[v + 1] = a[v];
			v--;
		}
		a[v + 1] = key;
	}
}

void C_flashSort(int a[], int n, long long& comp)
{
	comp = 0;
	int minVal = a[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0; i < m; i++)
		l[i] = 0;
	for (int i = 1; ++comp && i < n; i++)
	{
		if (++comp && a[i] < minVal)
			minVal = a[i];
		if (++comp && a[i] > a[max])
			max = i;
	}
	if (++comp && a[max] == minVal)
		return;
	double c1 = (double)(m - 1) / (a[max] - minVal);
	for (int i = 0; ++comp && i < n; i++)
	{
		int k = int(c1 * (a[i] - minVal));
		++l[k];
	}
	for (int i = 1; ++comp && i < m; i++)
		l[i] += l[i - 1];
	HoanVi(a[max], a[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (++comp && nmove < n - 1)
	{
		while (++comp && j > l[k] - 1)
		{
			j++;
			k = int(c1 * (a[j] - minVal));
		}
		flash = a[j];
		if (++comp && k < 0) break;
		while (++comp && j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	for (int i = 1; ++comp && i < n; i++)
	{
		int v = i - 1;
		int key = a[i];
		while ((++comp && a[v] > key) && (++comp && v >= 0))
		{
			a[v + 1] = a[v];
			v--;
		}
		a[v + 1] = key;
	}
}

void merge(int* a, int l, int m, int r)
{
	int i = 0, j = 0, k = l;
	int part1 = m - l + 1;
	int part2 = r - m;

	int* L, * R;
	L = new int[part1];
	R = new int[part2];

	int h = 0, c = 0;
	while (true) {
		if (h < part1)
			L[h] = a[l + h];
		if (h < part2)
			R[h] = a[m + 1 + h];
		if (h == part1)
			c++;
		if (h == part2)
			c++;
		if (c == 2)break;
		h++;
	}

	while (i < part1 && j < part2)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < part1)
		a[k++] = L[i++];

	while (j < part2)
		a[k++] = R[j++];
}
void mergeSort(int* a, int l, int r)
{
	if (l < r) {
		int mid = l + (r - l) / 2;
		mergeSort(a, l, mid);
		mergeSort(a, mid + 1, r);
		merge(a, l, mid, r);
	}
}

void mergeCompare(int* a, int l, int m, int r, long long& comp)
{
	int i = 0, j = 0, k = l;
	int part1 = m - l + 1;
	int part2 = r - m;

	int* L, * R;
	L = new int[part1];
	R = new int[part2];

	int h = 0, c = 0;
	while (true) {
		if (++comp && h < part1)
			L[h] = a[l + h];
		if (++comp && h < part2)
			R[h] = a[m + 1 + h];
		if (++comp && h == part1)
			c++;
		if (++comp && h == part2)
			c++;
		if (++comp && c == 2)break;
		h++;
	}

	while ((++comp && i < part1) && (++comp && j < part2))
	{
		if (++comp && L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
		k++;
	}

	while (++comp && i < part1)
		a[k++] = L[i++];

	while (++comp && j < part2)
		a[k++] = R[j++];
}
void C_mergeSort(int* a, int l, int r, long long& comp)
{
	if (++comp && l < r) {
		int mid = l + (r - l) / 2;
		C_mergeSort(a, l, mid, comp);
		C_mergeSort(a, mid + 1, r, comp);
		mergeCompare(a, l, mid, r, comp);
	}
}

//Vy --BB-Shake-heap
//without compare

void Bubble_sort(int arr[], int n)
{
	for (int i = 0; i < n - 2; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (arr[j] < arr[j - 1])
			{

				swap(arr[j], arr[j - 1]);
			}
		}
	}
}


void Shaker_sort(int arr[], int n)
{
	int left = 0, right = n - 1, k = 0;
	while (left < right)
	{
		for (int i = right; i > left; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
				k = i;
			}
		}
		left = k;
		for (int i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				k = i;
			}
		}
		right = k;
	}
}

void Heapify(int arr[], int n, int i)
{
	int i_max = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && arr[i_max] < arr[left])
	{
		i_max = left;
	}
	if (right < n && arr[i_max] < arr[right])
	{
		i_max = right;
	}
	if (i_max != i)
	{
		swap(arr[i], arr[i_max]);
		Heapify(arr, n, i_max);
	}
}

void Heap_sort(int arr[], int n)
{

	for (int i = n / 2 - 1; i >= 0; i--)
	{
		Heapify(arr, n, i);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[i], arr[0]);
		Heapify(arr, i, 0);
	}
}

//with compare
void C_Bubble_sort(int arr[], int n, long long& count)
{
	count = 0;
	for (int i = 0; count++ >= 0 && i < n - 2; i++)
	{
		for (int j = n - 1; count++ >= 0 && j > i; j--)
		{
			if (count++ >= 0 && arr[j] < arr[j - 1])
			{

				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

void C_Shaker_sort(int arr[], int n, long long& count)
{
	count = 0;
	int left = 0, right = n - 1, k = 0;
	while (count++ >= 0 && left < right)
	{
		for (int i = right; count++ >= 0 && i > left; i--)
		{
			if (count++ >= 0 && arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
				k = i;
			}
		}
		left = k;
		for (int i = left; count++ >= 0 && i < right; i++)
		{
			if (count++ >= 0 && arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				k = i;
			}
		}
		right = k;
	}
}

void C_Heapify(int arr[], int n, int i, long long& count1)
{
	int i_max = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (count1 + 2 >= 0 && left < n && arr[i_max] < arr[left])
	{
		i_max = left;
	}
	if (count1 + 2 >= 0 && right < n && arr[i_max] < arr[right])
	{
		i_max = right;
	}
	if (count1++ >= 0 && i_max != i)
	{
		swap(arr[i], arr[i_max]);
		Heapify(arr, n, i_max);
	}
}

void C_Heap_sort(int arr[], int n, long long& count)
{
	count = 0;
	for (int i = n / 2 - 1; ++count && i >= 0; i--)
	{
		C_Heapify(arr, n, i, count);
	}
	for (int i = n - 1; ++count && i > 0; i--)
	{
		swap(arr[i], arr[0]);
		C_Heapify(arr, i, 0, count);
	}
}


//Tan 
//without compare
void InsertionSort(int a[], int n)
{

	for (int i = 1; i < n; i++)
	{
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}

}

int partition(int a[], int l, int r)
{
	HoanVi(a[l + (r - l) / 2], a[r]);
	int pivot = a[r];
	int i = (l - 1);

	for (int j = l; j <= r; j++)
	{

		if (a[j] < pivot)
		{
			i++;
			HoanVi(a[i], a[j]);
		}
	}
	HoanVi(a[i + 1], a[r]);
	return (i + 1);
}


void quickSort(int a[], int l, int r)
{
	if (l < r)
	{

		int mid = partition(a, l, r);

		quickSort(a, l, mid - 1);
		quickSort(a, mid + 1, r);
	}
}

void QuickSort(int a[], int n)
{
	if (n > 1)
		quickSort(a, 0, n - 1);
}

void counting_sort(int input[], int n)
{
	int* output;
	output = new int[n];
	int max = input[0];
	int min = input[0];

	for (int i = 1; i < n; i++)
	{
		if (input[i] > max)
			max = input[i];
		else if (input[i] < min)
			min = input[i];
	}

	int k = max - min + 1;

	int* count_array;
	count_array = new int[k];
	fill_n(count_array, k, 0);

	for (int i = 0; i < n; i++)
		count_array[input[i] - min]++;

	for (int i = 1; i < k; i++)
		count_array[i] += count_array[i - 1];

	for (int i = 0; i < n; i++)
	{
		output[count_array[input[i] - min] - 1] = input[i];
		count_array[input[i] - min]--;
	}


	for (int i = 0; i < n; i++)
		input[i] = output[i];

}

//with compare

void C_InsertionSort(int a[], int n, long long& compar)
{
	compar = 0;
	for (int i = 1; ++compar && i < n; i++)
	{

		int key = a[i];
		int j = i - 1;
		while (++compar && j >= 0 && ++compar && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}

}
int partition_count(int* a, int l, int r, long long& compar)
{
	HoanVi(a[l + (r - l) / 2], a[r]);
	int pivot = a[r];
	int i = (l - 1);

	for (int j = l; j <= r; j++)
	{
		++compar;
		if (++compar && a[j] < pivot)
		{
			i++;
			HoanVi(a[i], a[j]);
		}
	}
	HoanVi(a[i + 1], a[r]);
	return (i + 1);
}


void C_quickSort(int* a, int l, int r, long long& compar)
{

	if (++compar && l < r)
	{

		int mid = partition_count(a, l, r, compar);

		C_quickSort(a, l, mid - 1, compar);
		C_quickSort(a, mid + 1, r, compar);
	}
}


void C_counting_sort(int input[], int n, long long& compar)
{
	compar = 0;
	int* output;
	output = new int[n];
	int max = input[0];
	int min = input[0];

	for (int i = 1; ++compar && i < n; i++)
	{
		if (++compar && input[i] > max)
			max = input[i];
		else if (++compar && input[i] < min)
			min = input[i];
	}

	int k = max - min + 1;

	int* count_array;
	count_array = new int[k];
	for (int i = 0; ++compar && i < k; i++)
	{
		count_array[i] = 0;
	}
	for (int i = 0; ++compar && i < n; i++)
		count_array[input[i] - min]++;

	for (int i = 1; ++compar && i < k; i++)
		count_array[i] += count_array[i - 1];

	for (int i = 0; ++compar && i < n; i++)
	{
		output[count_array[input[i] - min] - 1] = input[i];
		count_array[input[i] - min]--;
	}


	for (int i = 0; ++compar && i < n; i++)
		input[i] = output[i];

}

//Huan
//without compare

void selection_sort(int a[], int n)
{
	int min, temp;
	for (int i = 0; i < n; i++)
	{
		min = i;
		temp = a[min];
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < temp)
			{
				min = j;
				temp = a[min];
			}
		}
		swap(a[min], a[i]);
	}
}

long long getMax(int a[], int n)
{
	long long max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > max) max = a[i];
	}
	return max;
}


void count_sort(int a[], int n, int digit)
{
	int* out = new int[n];

	int count[10] = { 0 };

	for (int i = 0; i < n; i++)
	{
		count[(a[i] / digit) % 10]++;
	}

	for (int i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}


	for (int i = n - 1; i >= 0; i--)
	{
		out[count[(a[i] / digit) % 10] - 1] = a[i];
		count[(a[i] / digit) % 10]--;
	}

	for (int i = 0; i < n; i++)
	{
		a[i] = out[i];
	}
}


// Ham Radix Sort 

void radix_sort(int a[], int n)
{

	long long max = getMax(a, n);

	for (int digit = 1; max / digit > 0; digit *= 10)
	{
		count_sort(a, n, digit);
	}
}
//Ham dem Radix Sort

// Ham Shell Sort

void shell_sort(int a[], int n)
{
	for (int h = n / 2; h > 0; h /= 2)
	{
		for (int i = h; i < n; i++)
		{
			int temp = a[i];
			int j;
			for (j = i; j >= h && a[j - h] > temp; j -= h)
				a[j] = a[j - h];

			a[j] = temp;
		}
	}
}


//with compare
//Ham dem Selection

void C_selection_sort(int a[], int n, long long& count_compare)
{

	count_compare = 0;

	int min, temp;
	for (int i = 0; ++count_compare && i < n; i++)
	{
		min = i;
		temp = a[min];
		for (int j = i + 1; ++count_compare && j < n; j++)
		{
			if (++count_compare && a[j] < temp)
			{
				min = j;
				temp = a[min];
			}
		}
		swap(a[min], a[i]);
	}
	count_compare;
}
long long CgetMax(int a[], int n, long long& count_compare)
{

	long long max = a[0];
	for (int i = 1; ++count_compare && i < n; i++)
	{
		if (++count_compare && a[i] > max)
		{
			max = a[i];
		}
	}
	return max;
}

void C_count_sort(int a[], int n, int digit, long long& count_compare)
{

	int* out = new int[n];

	int count[10] = { 0 };

	for (int i = 0; ++count_compare && i < n; i++)
	{
		count[(a[i] / digit) % 10]++;
	}

	for (int i = 1; ++count_compare && i < 10; i++)
	{
		count[i] += count[i - 1];
	}


	for (int i = n - 1; ++count_compare && i >= 0; i--)
	{
		out[count[(a[i] / digit) % 10] - 1] = a[i];
		count[(a[i] / digit) % 10]--;
	}

	for (int i = 0; ++count_compare && i < n; i++)
	{
		a[i] = out[i];
	}
}

void C_radix_sort(int a[], int n, long long& count_compare)
{

	count_compare = 0;

	int max = CgetMax(a, n, count_compare);

	for (int digit = 1; ++count_compare && max / digit > 0; digit *= 10)
	{
		C_count_sort(a, n, digit, count_compare);
	}
}

// Ham dem Shell Sort

void C_shell_sort(int a[], int n, long long& count_compare)
{

	count_compare = 0;

	for (int h = n / 2; ++count_compare && h > 0; h /= 2)
	{
		for (int i = h; ++count_compare && i < n; i++)
		{
			int temp = a[i];
			int j;
			for (j = i; ++count_compare && j >= h && ++count_compare && a[j - h] > temp; j -= h)
			{
				a[j] = a[j - h];
			}
			a[j] = temp;
		}
	}
}
//ham phu

void out(int* a, int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n-----------------------------------------------\n";
}

void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// increase function
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// discrease
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// pretty sort
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		swap(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// random
		GenerateRandomData(a, n);
		break;
	case 1:	// sorted
		GenerateSortedData(a, n);
		break;
	case 2:	// high to low
		GenerateReverseData(a, n);
		break;
	case 3:	// nearly sort
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

bool checkStringNum(string a)
{
	for (int i = 0; i < a.length(); i++)
		if (a[i] > '9' || a[i] < '0')
			return false;
	return true;
}
void copyArr(int* a, int* b, int n)
{
	for (int i = 0; i < n; i++)
		b[i] = a[i];
}
void WriteFile(ofstream& fwrite, int* a, int n)
{
	fwrite << n << '\n';
	for (int i = 0; i < n; i++)
		fwrite << a[i] << ' ';
}

int* readFile(ifstream& fread, int& n)
{
	int* a;
	fread >> n;
	a = new int[n];
	for (int i = 0; i < n; i++)
		fread >> a[i];
	return a;
}

void timeAndComp(int* a, int* b, int n, string arg2, double& time, long long& comp)
{
	clock_t start, end;
	start = clock();
	if (arg2 == "flash-sort") {
		cout << " Flash sort";
		flashSort(a, n);
		end = clock();
		C_flashSort(b, n, comp);
	}
	if (arg2 == "merge-sort") {
		cout << " Merge sort";
		mergeSort(a, 0, n - 1);
		end = clock();
		C_mergeSort(b, 0, n - 1, comp);
	}
	if (arg2 == "bubble-sort") {
		cout << " Bubble sort";
		Bubble_sort(a, n);
		end = clock();
		C_Bubble_sort(b, n, comp);
	}
	if (arg2 == "shaker-sort") {
		cout << " Shaker sort";
		Shaker_sort(a, n);
		end = clock();
		C_Shaker_sort(b, n, comp);
	}
	if (arg2 == "heap-sort") {
		cout << " Heap sort";
		Heap_sort(a, n);
		end = clock();
		C_Heap_sort(b, n, comp);
	}
	if (arg2 == "insertion-sort") {
		cout << " Insertion sort";
		InsertionSort(a, n);
		end = clock();
		C_InsertionSort(b, n, comp);
	}
	if (arg2 == "quick-sort") {
		cout << " Quick sort";
		QuickSort(a, n);
		end = clock();
		C_quickSort(b, 0, n - 1, comp);
	}
	if (arg2 == "counting-sort") {
		cout << " Counting  sort";
		counting_sort(a, n);
		end = clock();
		C_counting_sort(b, n, comp);
	}
	if (arg2 == "selection-sort") {
		cout << "Selection sort";
		selection_sort(a, n);
		end = clock();
		C_selection_sort(b, n, comp);
	}
	if (arg2 == "radix-sort") {
		cout << " Radix sort";
		radix_sort(a, n);
		end = clock();
		C_radix_sort(b, n, comp);
	}
	if (arg2 == "shell-sort") {
		cout << " Shell sort";
		shell_sort(a, n);
		end = clock();
		C_shell_sort(b, n, comp);
	}
	time = double(end - start) / double(CLOCKS_PER_SEC) * 1000;
}
void cmd1(string arg1, string arg2, string arg3, string arg4)
{
	ofstream fwrite;
	ifstream fread;
	int* a, * b;
	int n;
	fread.open(arg3);
	a = readFile(fread, n);
	fread.close();
	b = new int[n];
	copyArr(a, b, n);
	long long  comp = 0;
	double time;
	int type;
	if (arg1 == "-a")
		cout << "Algorithm Mode\n";
	if (arg1 == "-c") {
		cout << "\nThis case does not support comparison mode !!! \n";
		return;
	}
	cout << "Algorithm : ";
	timeAndComp(a, b, n, arg2, time, comp);
	cout << "\nInput file : " << arg3 << "\n";
	cout << "Input size : " << n << "\n";
	cout << "--------------------------------------\n";
	if (arg4 == "-time")
		cout << "Running time : " << fixed << time << "\tmili seconds.\n";
	if (arg4 == "-comp")
		cout << "Comparisions : " << comp << "\n";
	if (arg4 == "-both") {
		cout << "Running time : " << fixed << time << "\tmili seconds.\n";
		cout << "Comparisions : " << comp << "\n";
	}
	//ghi mang da sap xep vao file
	fwrite.open("output.txt");
	WriteFile(fwrite, a, n);
	fwrite.close();

}
void cmd2(string mode, string algor, string size, string order, string paramet)
{
	ofstream fwrite;
	int* a, * b;
	int n = stoi(size);
	a = new int[n];
	b = new int[n];
	long long comp = 0;
	double time;
	string inputOrder;
	int type;
	if (mode == "-a")
		cout << "ALGORITHM MODE\n";
	if (mode == "-c") {
		cout << "\nThis case does not support comparison mode !!! \n";
		return;
	}
	if (order == "-rand") {
		GenerateRandomData(a, n);
		copyArr(a, b, n);
		inputOrder = "Randomized data.\n";
	}
	if (order == "-nsorted") {
		GenerateNearlySortedData(a, n);
		copyArr(a, b, n);
		inputOrder = " Nearly sorted data.\n";
	}
	if (order == "-sorted") {
		GenerateSortedData(a, n);
		copyArr(a, b, n);
		inputOrder = "Sorted data.\n";
	}
	if (order == "-rev") {
		GenerateReverseData(a, n);
		copyArr(a, b, n);
		inputOrder = "Reverse sorted data.\n";
	}

	//ghi du lieu dau vao vao file
	fwrite.open("input.txt");
	WriteFile(fwrite, a, n);
	fwrite.close();
	cout << "Algorithm : ";
	timeAndComp(a, b, n, algor, time, comp);
	cout << "\nInput size : " << n << "\n";
	cout << "Input oder : " << inputOrder << "\n";
	cout << "--------------------------------------\n";
	if (paramet == "-time")
		cout << "Running time : " << fixed << time << "\tmili seconds.\n";
	if (paramet == "-comp")
		cout << "Comparisions : " << comp << "\n";

	if (paramet == "-both") {
		cout << "Running time : " << fixed << time << "\tmili seconds.\n";
		cout << "Comparisions : " << comp << "\n";
	}
}

void cmd3(string mode, string algor, string size, string paramet)
{
	/*
	mảng a_1,b_1 : kiểu random
	mảng a_2,b_2 : kiểu nearly sorted
	mảng a_3,b_3: kiểu sorted
	mảng a_4,b_4: kiểu reserved 
	comp_1,time_1: số lượng comparation và time của kiểu random
	comp_2,time_2: số lượng comparation và time của kiểu nearly sorted
	comp_3,time_3: số lượng comparation và time của kiểu sorted 
	comp_4,time_4: số lượng comparation và time của kiểu reserved 
	*/
	ofstream fwrite;
	int* a_1, * b_1, * a_2, * b_2, * a_3, * b_3, * a_4, * b_4;
	int n = stoi(size);
	a_1 = new int[n]; 
	b_1 = new int[n];
	a_2 = new int[n];
	b_2 = new int[n];
	a_3 = new int[n];
	b_3 = new int[n];
	a_4 = new int[n];
	b_4 = new int[n];
	long long comp_1 = 0;
	double time_1;
	long long comp_2 = 0;
	double time_2;
	long long comp_3 = 0;
	double time_3;
	long long comp_4 = 0;
	double time_4;
	int type;
	if (mode == "-a")
		cout << "ALGORITHM MODE\n";
	if (mode == "-c") 
	{
		cout << "\nThis case does not support comparison mode !!! \n";
		return;
	}
	
	GenerateRandomData(a_1, n);  // ghi vo file input1 
	copyArr(a_1, b_1, n);
	fwrite.open("input_1.txt");
	WriteFile(fwrite, a_1, n);
	fwrite.close();
	
	GenerateNearlySortedData(a_2, n); // ghi vo file input 2
	copyArr(a_2, b_2, n);
	fwrite.open("input_2.txt");
	WriteFile(fwrite, a_2, n);
	fwrite.close();
	
	GenerateSortedData(a_3, n); // ghi vo file input 3
	copyArr(a_3, b_3, n);
	fwrite.open("input_3.txt");
	WriteFile(fwrite, a_3, n);
	fwrite.close();
	
	GenerateReverseData(a_4, n); // ghi vo file input 4
	copyArr(a_4, b_4, n);
	fwrite.open("input_4.txt");
	WriteFile(fwrite, a_4, n);
	fwrite.close();

	cout << "Algorithm : " << algor << "\n";
	cout << "Input size: " << n << "\n\n";

	// kieu randomize data
	cout << "Input oder: " << "Randomize\n";
	cout << "---------------------------------------------\n";
	timeAndComp(a_1, b_1, n, algor, time_1, comp_1); 
	if (paramet == "-time")
		cout << "Running time : " << fixed << time_1 << "\tmili seconds.\n";
	if (paramet == "-comp")
		cout << "Comparisions : " << comp_1 << "\n";
	if (paramet == "-both") {
		cout << "Running time : " << fixed << time_1 << "\tmili seconds.\n";
		cout << "Comparisions : " << comp_1 << "\n";
	}
	cout << "\n";

	// kieu nearly data
	cout << "Input oder: " << " Nearly Sorted\n";
	cout << "\n---------------------------------------------\n";
	timeAndComp(a_2, b_2, n, algor, time_2, comp_2);
	if (paramet == "-time")
		cout << "Running time : " << fixed << time_2 << "\tmili seconds.\n";
	if (paramet == "-comp")
		cout << "Comparisions : " << comp_2 << "\n";
	if (paramet == "-both") {
		cout << "Running time : " << fixed << time_2 << "\tmili seconds.\n";
		cout << "Comparisions : " << comp_2 << "\n";
	}
	cout << "\n";

	// kieu sorted data
	cout << "Input oder: " << " Sorted\n";
	cout << "\n---------------------------------------------\n";
	timeAndComp(a_3, b_3, n, algor, time_3, comp_3);
	if (paramet == "-time")
		cout << "Running time : " << fixed << time_3 << "\tmili seconds.\n";
	if (paramet == "-comp")
		cout << "Comparisions : " << comp_3 << "\n";
	if (paramet == "-both") {
		cout << "Running time : " << fixed << time_3 << "\tmili seconds.\n";
		cout << "Comparisions : " << comp_3 << "\n";
	}
	cout << "\n";

	// kieu reserved data
	cout << "Input oder: " << " Reserved\n";
	cout << "\n---------------------------------------------\n";
	timeAndComp(a_4, b_4, n, algor, time_4, comp_4);
	if (paramet == "-time")
		cout << "Running time : " << fixed << time_4 << "\tmili seconds.\n";
	if (paramet == "-comp")
		cout << "Comparisions : " << comp_4 << "\n";
	if (paramet == "-both") {
		cout << "Running time : " << fixed << time_4 << "\tmili seconds.\n";
		cout << "Comparisions : " << comp_4 << "\n";
	}
	cout << "\n";
		
}

void cmd4(string mode, string algor1, string algor2, string inputFile)
{
	cout << "\n{\\_/}\n(-_-)\n/>ok\n";
}

void cmd5(string mode, string algor1, string algor2, string size, string order)
{
	//lay size
	ofstream fwrite;
	int n = stoi(size);

	int* a = new int[n];
	int* b = new int[n];
	int* c = new int[n];
	int* d = new int[n];

	double time1, time2;
	long long comp1 = 0, comp2 = 0;
	string inputOrder;

	//check mode
	if (mode == "-a") {
		cout << "\nThis case does not support algorithm mode (try '-c' ) !!! \n";
		return;
	}
	if (mode == "-c")
	{
		cout << "Comparision Mode:\n";
	}

	//tao mang
	if (order == "-rand") {
		GenerateRandomData(a, n);
		copyArr(a, b, n);
		copyArr(a, c, n);
		copyArr(a, d, n);
		inputOrder = "Randomized data.\n";
	}
	if (order == "-nsorted") {
		GenerateNearlySortedData(a, n);
		copyArr(a, b, n);
		copyArr(a, c, n);
		copyArr(a, d, n);
		inputOrder = " Nearly sorted data.\n";
	}
	if (order == "-sorted") {
		GenerateSortedData(a, n);
		copyArr(a, b, n);
		copyArr(a, c, n);
		copyArr(a, d, n);
		inputOrder = "Sorted data.\n";
	}
	if (order == "-rev") {
		GenerateReverseData(a, n);
		copyArr(a, b, n);
		copyArr(a, c, n);
		copyArr(a, d, n);
		inputOrder = "Reverse sorted data.\n";
	}

	//ghi mang dau vao da tao 
	fwrite.open("input.txt");
	WriteFile(fwrite, a, n);
	fwrite.close();
	//output ten thuat toan
	cout << "Algorithm : ";
	timeAndComp(a, b, n, algor1, time1, comp1);
	cout << "  |  ";
	timeAndComp(c, d, n, algor2, time2, comp2);
	cout << "\n";
	//output size,order
	cout << "Input size : " << n << "\n";
	cout << "Input oder : " << inputOrder << "\n";
	cout << "--------------------------------------\n";
	cout << "Running time: " << time1 << "\t   |   " << time2 << endl;
	cout << "Comparisions: " << comp1 << "\t   |   " << comp2 << endl;
}
