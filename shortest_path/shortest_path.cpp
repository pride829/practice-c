#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <stack>

//邊的資料結構
class Path{

public:

	int src, dst;
	double distance, width;
	std::string restrict;

	Path() {
		src = -1;
		dst = -1;
		distance = -1;
		width = -1;
		restrict = std::string();
	}

	Path(int src, int dst, double distance, double width, std::string restrict) {
		this->src = src;
		this->dst = dst;
		this->distance = distance;
		this->width = width;
		this->restrict = restrict;
	}

};

int main()
{
	std::ofstream myfile;
	myfile.open("t2_out.txt");

	//預設的載具最小寬度
	double const widths[] = {6, 4, 2, 1.5, 0.5};

	int src, dst, travel_way;

	std::cin >> src >> dst >> travel_way;

	travel_way -= 1;

	std::ifstream input("test1.txt");
	std::string line;
	std::getline(input, line);
	std::istringstream first_iss(line);

	int n = 0;
	first_iss >> n;

	if (n < src || n < dst || travel_way > 4) {
		std::cout << "鍵盤輸入有誤！" << std::endl;
		system("PAUSE");
		return 0;
	}

	std::vector<Path> all_paths(0);
	
	int q = 0;

	//讀取每一行路徑並放入向量中
	while (std::getline(input, line)) {

		int temp_src, temp_dst;
		double temp_distance, temp_width;
		std::string temp_restrict;

		std::istringstream iss(line);

		iss >> temp_src >> temp_dst >> temp_distance >> temp_width;

		if (!(iss >> temp_restrict))
			temp_restrict = std::string();
		
		//偵錯
		if (temp_src == temp_dst) {
			std::cout << "出現self-loop的邊。" << std::endl;
			system("PAUSE");
			return -1;
		}

		if (temp_distance <= 0 || temp_width <= 0) {
			std::cout << "出現距離或路幅為0或負數的邊。" << std::endl;
			system("PAUSE");
			return -1;
		}

		if (temp_src >= n || temp_dst >= n) {
			std::cout << "出現不合規定的節點編號。" << std::endl;
			system("PAUSE");
			return -1;
		}

		//如果該條道路無法通行則距離為無限大
		if (!temp_restrict.empty() && temp_restrict[travel_way] == '0')
			temp_distance = INT_MAX;
		
		if(temp_width < widths[travel_way])
			temp_distance = INT_MAX;


		all_paths.push_back(Path(temp_src, temp_dst, temp_distance, temp_width, temp_restrict));

	}

	int* all_distance = new int[n];
	Path* all_parent_paths = new Path[n];
	bool* distance_is_set = new bool[n];
	int set_count = 0;

	for (int i = 0; i < n; i++) {
		all_distance[i] = INT_MAX;
		distance_is_set[i] = false;
	}
	
	all_distance[src] = 0;

	//使用dijkstra演算法找出最短路徑
	while (set_count < n) {

		int closet_point = -1;
		int closet_distance = INT_MAX;

		//找出目前最短的點
		for (int i = 0; i < n; i++) {
			if (distance_is_set[i] == false && all_distance[i] < closet_distance) {
				closet_point = i;
				closet_distance = all_distance[i];
			}
		}

		if (closet_point == -1)
			break;

		distance_is_set[closet_point] = true;
		set_count++;

		//進行relaxtion
		for (int i = 0; i < all_paths.size(); i++) {
			if (all_paths[i].src == closet_point) {
				if (all_paths[i].distance + all_distance[closet_point] < all_distance[all_paths[i].dst]) {

					all_distance[all_paths[i].dst] = all_paths[i].distance + all_distance[closet_point];
					all_parent_paths[all_paths[i].dst] = all_paths[i];

				}
			}
		}
	}

	if (all_distance[dst] == INT_MAX) {
		std::cout << "Unreachable." << std::endl;
		system("PAUSE");
		return 0;
	}

	int next_dst = dst;
	int total_distance = 0;
	std::stack<Path> path_stack;

	//因為要從src開始print，因此建立一個stack堆疊paths
	while (next_dst != src) {

		path_stack.push(all_parent_paths[next_dst]);
		total_distance += all_parent_paths[next_dst].distance;
		next_dst = all_parent_paths[next_dst].src;

	}

	//輸出
	std::cout << "總長度: " << total_distance << std::endl;
	myfile << "總長度: " << total_distance << std::endl;



	while (!path_stack.empty()) {

		Path temp_path = path_stack.top();
		path_stack.pop();

		std::cout << "("
			<< temp_path.src
			<< ", "
			<< temp_path.dst
			<< ") "
			<< temp_path.distance << " "
			<< temp_path.width << " ";


		myfile << "("
			<< temp_path.src
			<< ", "
			<< temp_path.dst
			<< ") "
			<< temp_path.distance << " "
			<< temp_path.width << " ";

		if (!temp_path.restrict.empty()) {
			std::cout << temp_path.restrict;
			myfile << temp_path.restrict;
		}

		std::cout << std::endl;
		myfile << std::endl;
	}

	myfile.close();

	system("PAUSE");

	return 0;
}
