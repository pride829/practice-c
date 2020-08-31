#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

void swap(double* a, double* b) {
	double t = *a;
	*a = *b;
	*b = t;
}

void merge_sort_recursive(double* front, double* end) {

	if (!(front < end)) return;

	double* i, * j;
	i = front - 1;
	j = front;
	while (j != end) {
		if (*j > *end) {
			j++;
		}
		else {
			i++;
			swap(i, j);
			j++;
		}
	}
	i++;
	swap(i, end);
	
	merge_sort_recursive(front, i-1);
	merge_sort_recursive(i + 1, end);
}

void merge_sort(double* front, double* end) {
	merge_sort_recursive(front, end);
}

void insertion_sort(double* arr, int n) {

	for (int j = 1; j < n; j++) {
		int i;
		for (i = 0; i < j && arr[i] < arr[j]; i++);
		int t_pos = i;
		double t_value = arr[j];
		for (i = j; i > t_pos; i--)
			arr[i] = arr[i - 1];
		arr[i] = t_value;
	}
	return;
}


void main()
{

	double arr0[2000], arr1[2000];
	std::ifstream input("test1.txt");
	std::string line;
	std::getline(input, line);
	std::istringstream iss(line);

	int q = 0;
	while (iss >> arr0[q]) {
		arr1[q] = arr0[q];
		q++;
	}

	std::cout << "Quick sort:" << std::endl << std::endl;
	merge_sort(arr0, &arr0[q-1]);

	std::cout << "所有數的個數: " << q << std::endl << std::endl;
	std::cout << "最大的數: " << arr0[q - 1] << std::endl << std::endl;
	std::cout << "最小的數: " << arr0[0] << std::endl << std::endl;

	for (int i = 0; i < q; i++)
		std::cout << std::setw(5) << arr0[i] << " ";

	std::cout << std::endl << std::endl;


	std::cout << "Insertion sort:" << std::endl << std::endl;
	insertion_sort(arr1, q);

	std::cout << "所有數的個數: " << q << std::endl << std::endl;
	std::cout << "最大的數: " << arr1[q - 1] << std::endl << std::endl;
	std::cout << "最小的數: " << arr1[0] << std::endl << std::endl;

	for (int i = 0; i < q; i++)
		std::cout << std::setw(5) << arr1[i] << " ";

	std::cout << std::endl << std::endl;

	system("PAUSE");
	return;
}




