#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "Point.h"
#include "heapSort.h"

int const SORT_BY_X = 0;
int const SORT_BY_Y = 1;
int const SORT_BY_INDEX = 2;

//給予一個點陣列和其長度，算出其中所有點的rank值
void ranking(Point* arr, int len) {
	
	if (len == 1) return;

	heapSort(arr, len, SORT_BY_X);

	int left_len = len / 2;
	int right_len = len - left_len;
	Point* left_arr = arr;
	Point* right_arr = arr + left_len;

	ranking(left_arr, left_len);
	ranking(right_arr, right_len);

	heapSort(left_arr, left_len, SORT_BY_Y);
	heapSort(right_arr, right_len, SORT_BY_Y);

	int i = 0, j;
	for (j = 0; j < right_len; j++) {
		while (i < left_len && left_arr[i].y < right_arr[j].y)
			i++;
		right_arr[j].rank += i;
	}

}

int main()
{
	//讀取並產生點陣列
	std::ifstream input("test1.txt");
	std::string line;
	std::getline(input, line);
	std::istringstream iss(line);

	Point* arr = new Point[2000];

	double temp0, temp1;
	int len = 0;
	
	while (iss >> temp0 && iss >> temp1) 
		arr[len++] = Point(temp0, temp1, 0, len);

	//計算ranking
	ranking(arr, len);

	//排序後輸出
	heapSort(arr, len, SORT_BY_INDEX);
	int max_rank = INT_MIN;
	int min_rank = INT_MAX;
	double total_rank = 0;
	for (int i = 0; i < len; i++) {
		arr[i].print();
		if (max_rank < arr[i].rank)
			max_rank = arr[i].rank;
		if (min_rank > arr[i].rank)
			min_rank = arr[i].rank;
		total_rank += arr[i].rank;
	}

	std::cout << std::endl;
	std::cout << "所有點的個數: " << len << std::endl;
	std::cout << "最大rank: " << max_rank << std::endl;
	std::cout << "最小rank: " << min_rank << std::endl; //最小rank一定是零阿!
	std::cout << "平均rank: " << total_rank / (double)len << std::endl;
	std::cout << std::endl;

	system("Pause");
}
