#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int const TOP = 0;
int const DOWN = 1;
int const LEFT = 2;
int const RIGHT = 3;
int n;
int m;
int map[500][500];
bool visited[500][500];
//NodeTraversing紀錄了經過的點、其和原點的距離、其hop、還有與hop的方向 
class NodeTraversing
{
public:
	NodeTraversing(int x, int y, int parent);
	int x, y, parent;
private:
};

NodeTraversing::NodeTraversing(int x, int y, int parent)
{
	this->x = x;
	this->y = y;
	this->parent = parent;
}

int main()
{
	ifstream input("test4.txt");

	string line;

	getline(input, line);
	istringstream is(line);

	n = 0, m = 0;
	is >> n >> m;


	//initiallizing


	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			map[j][i] = 0;
			visited[j][i] = 0;
		}
	}
	int j = 0;
	int i = 0;
	while (getline(input, line))
	{
		for (int i = 0; i < n; i++)
			map[i][j] = (int)line[i] - '0';
		for (int i = 0; i < n; i++)
			cout << map[i][j];
		cout << endl;
		j++;
	}
	cout << endl;


	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			cout << "x " << j << " y " << i << " " << map[j][i] << " ";
		}
		cout << endl;
	}

	int src_x, src_y, dst_x, dst_y;

	cin >> src_x >> src_y >> dst_x >> dst_y;

	cout << dst_x << " " << dst_y << endl;
	if (src_x >= n || src_y >= m || dst_x >= n || dst_y >= m) {
		cout << "輸入有誤" << endl;
		system("PAUSE");
		return -1;
	}

	//BFS(src_x,src_y,dst_x,dst_y);
		//產生一個queue用來處理BFS演算法
	std::vector<NodeTraversing> traversing_queue;
	traversing_queue.push_back(NodeTraversing(src_x, src_y, 0));

	int q = 0;

	//當尚未抵達終點以及traversing_queue沒有被用完時
	while (!(traversing_queue[q].x == dst_x && traversing_queue[q].y == dst_y)) {

		if (map[dst_x][dst_y] == 1) {
			cout << "unreachable node" << endl;
			break;
		}
		if (visited[traversing_queue[q].x][traversing_queue[q].y] == 0)
		{
			int now_x = traversing_queue[q].x;
			int now_y = traversing_queue[q].y;
			visited[now_x][now_y] = 1;
			cout << now_x << "  " << now_y << endl;
			//搜尋上下左右
			if (now_y - 1 >= 0 && map[now_x][now_y - 1] == 0 && visited[now_x][now_y - 1] == 0) {
				traversing_queue.push_back(NodeTraversing(now_x, now_y - 1, q));
				cout << "push " << now_x << " " << now_y - 1 << endl;
			}


			if (now_y + 1 < m && map[now_x][now_y + 1] == 0 && visited[now_x][now_y + 1] == 0) {
				traversing_queue.push_back(NodeTraversing(now_x, now_y + 1, q));
				cout << "push " << now_x << " " << now_y + 1 << endl;
			}
			if (now_x - 1 >= 0 && map[now_x - 1][now_y] == 0 && visited[now_x - 1][now_y] == 0)
			{
				traversing_queue.push_back(NodeTraversing(now_x - 1, now_y, q));
				cout << "push " << now_x - 1 << " " << now_y << endl;
			}

			if (now_x + 1 < n && map[now_x + 1][now_y] == 0 && visited[now_x + 1][now_y] == 0) {
				traversing_queue.push_back(NodeTraversing(now_x + 1, now_y, q));
				cout << "push " << now_x + 1 << " " << now_y << endl;
			}



		}
		q++;

	}

	cout << traversing_queue[q].x << "  " << traversing_queue[q].y << "is finale" << endl;
	if (q >= traversing_queue.size()) {
		std::cout << "No available path.";
		return 0;
	}

	std::vector<NodeTraversing> traversing_stack;

	NodeTraversing now_node = traversing_queue[q];

	//queue中的順序是顛倒的，因此將其推入stack最後再輸出
	while (!(now_node.x == src_x && now_node.y == src_y)) {

		cout << traversing_queue[q].x << " " << traversing_queue[q].y << endl;
		traversing_stack.push_back(now_node);
		now_node = traversing_queue[now_node.parent];

	}

	traversing_stack.push_back(now_node);

	//輸出所有經過的點
	while (!traversing_stack.empty()) {

		now_node = traversing_stack.back();
		traversing_stack.pop_back();

		std::cout << "(" << now_node.x << ", " << now_node.y << ") ";
		map[now_node.y][now_node.x] = -1;

	}

	std::cout << std::endl;


	//輸出整張圖
	for (int j = 0; j < m; j++) {

		for (int i = 0; i < n; i++)
			if (map[i][j] == -1)
				cout << '*';
			else
				cout << map[i][j];

		cout << endl;

	}

	system("PAUSE");

	return 0;
}

