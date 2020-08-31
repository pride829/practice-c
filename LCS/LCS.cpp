#include <iostream>
#include <string>

int const LEFT_UP = 0;
int const LEFT = 1;
int const UP = 2;

std::string s1, s2;
int** length;
int** dir;

void print_LCS(int i, int j)
{
	if (i == 0 || j == 0) return;

	if (dir[i][j] == LEFT_UP){
		print_LCS(i - 1, j - 1);
		//std::cout << i << "," << j << ":" << s2[j] << std::endl;
		std::cout << s1[i];
	}
	else if (dir[i][j] == LEFT)
		print_LCS(i, j - 1);
	else if (dir[i][j] == UP)
		print_LCS(i - 1, j);
}

void LCS()
{
	int len1 = (signed)s1.length() - 1;
	int len2 = (signed)s2.length() - 1;


	length = new int* [len1 + 1];
	dir = new int* [len1 + 1];

	for (int i = 0; i < len1 + 1; i++) {
		length[i] = new int[len2 + 1];
		dir[i] = new int[len2 + 1];
	}

	for (int i = 0; i <= len1; i++) 
		length[i][0] = 0;
	for (int j = 0; j <= len2; j++) 
		length[0][j] = 0;

	for (int i = 1; i <= len1; i++)
		for (int j = 1; j <= len2; j++)
			if (s1[i] == s2[j])
			{
				length[i][j] = length[i - 1][j - 1] + 1;
				dir[i][j] = LEFT_UP;
			}
			else
			{
				if (length[i - 1][j] < length[i][j - 1])
				{
					length[i][j] = length[i][j - 1];
					dir[i][j] = LEFT;
				}
				else
				{
					length[i][j] = length[i - 1][j];
					dir[i][j] = UP;
				}
			}

	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++)
			if (i == 0 && j == 0)
				std::cout << "  ";
			else if (i == 0)
				std::cout << s2[j] << " ";
			else if (j == 0)
				std::cout << s1[i] << " ";
			else
			std::cout << length[i][j] << " ";
		
		std::cout << std::endl;
	}
	
	std::cout << std::endl;

	/*
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++)
			std::cout << dir[i][j] << " ";

		std::cout << std::endl;
	}
	*/
	std::cout << "LCS的長度為：" << length[len1][len2] << std::endl;
	std::cout << "LCS = ";
	print_LCS(len1, len2);
	std::cout << std::endl;
}


int main() {

	std::cin >> s1 >> s2;

	/*
	s1 = "MZJAWXU";
	s2 = "XMJYAUZ";
	*/

	s1 = " " + s1;
	s2 = " " + s2;

	LCS();

	system("PAUSE");

}