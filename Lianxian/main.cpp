#include "maze.hpp"
#include <queue>
#include <stack>
#include <ctime>
#include <algorithm>
using namespace std;

set < vector<vector<char>>> Map::state;
stack<Map> list;
pair<int, int> dir[4] = { { 1,0 } ,{ -1,0 },{ 0,1 },{ 0,-1 } };
bool cmp(Block &ba, Block&bb) {
	return ba.face < bb.face;
}
void solve(Map & puzzle) {
	puzzle.startGameMustGo();
	puzzle.show();
	int lay = 0;
	clock_t t1=0, t2= 0;
	Map::state.insert(puzzle.hasBlock);
	while (list.size() > 0) {
		Map temp = list.top();
		//cout << "=======================" << endl;
		//temp.show();
		//cout << temp.str << endl;
		/*if (temp.layer >= 70) {
			temp.show();
		}*/
		while (!temp.unique()) {}
//		temp.show();
		if (lay < temp.layer) {
			t1 = clock();
			lay = temp.layer;
			cout << "µÚ"<<lay << "²ã >> " << t1 - t2 << endl;
			/*temp.show();
			if(lay>80)
			cout << temp.str << endl;*/
			t2 = t1;
		}
		list.pop();
		if (temp.win()) {
			cout << "win" << endl;
			cout << temp.str << endl;
			cout << temp.moves.size() << temp.endpots.size() << endl;
			temp.show();
			return;
		}
		//vector<Block> sortFace;
		//for (auto iter : temp.moves)sortFace.push_back(iter);
		//sort(sortFace.begin(), sortFace.end(), cmp);
		for (auto iter : temp.moves) {
			for (int j = 0; j < 4; ++j) {
				int newx = iter.x + dir[j].first;
				int newy = iter.y + dir[j].second;
				if (newx < puzzle.col && newy < puzzle.row && newx >= 0 && newy >= 0
					&& (temp.hasBlock[newx][newy] == '.'|| temp.hasBlock[newx][newy] == (temp.hasBlock[iter.x][iter.y]-32))) {
					Map nextMap(temp);
					nextMap.moves.erase(iter);
					if (temp.hasBlock[newx][newy] != (temp.hasBlock[iter.x][iter.y] - 32)) {
						nextMap.moves.insert(Block(newx, newy, iter.color));
					}
					else {
						nextMap.endpots.erase(Block(newx,newy, iter.color));
					}
					//nextMap.show();
					nextMap.hasBlock[newx][newy] = iter.color;
					//nextMap.show();
					string sss = "";
					nextMap.str += "\n";
					nextMap.str += to_string(iter.x) + "," + to_string(iter.y) + "-->" + to_string(newx) + "," + to_string(newy);
					nextMap.layer++;
					if (Map::state.find(nextMap.hasBlock) == Map::state.end()&&nextMap.hasResult()
					&&!nextMap.deadCorner()
						//&& !nextMap.deadMove()
						&& !nextMap.hasDeadPoint()
						) {
						//cout << newx << ", " << newy << endl;
						//nextMap.show();
						//cout << nextMap.hasResult() << endl;
						//nextMap.show();
						//cout << "dead cornor >> " << nextMap.deadCorner() << endl;
						list.push(nextMap);
						Map::state.insert(nextMap.hasBlock);
					// method 2
						
					}
				}
			}
		}
		
	}
	cout << "can't solve" << endl;
}

int main() {
	
	Map maze;
	maze.show();

	//cout << maze.deadMove() << endl;
	/*vector<int> cccc;
	vector<Block> sortFace;
	while (!maze.unique()) {

	}
	maze.show();
	for (auto iter : maze.moves)sortFace.push_back(iter);
	sort(sortFace.begin(), sortFace.end(), cmp);
	for (auto it : sortFace) {
		cout << it.x << " ," << it.y <<" "<<it.face << endl;
	}*/
//	maze.isVisited = maze.hasBlock;
	//cout << maze.deadCorner() << endl;
	//cout << maze.hasPath(3, 1, 4, 4, 'g') << endl;;
	//cccc.push_back(1);
	//vector<int> ddd = cccc;
	//ddd[0] = 333;
	//cout << cccc[0] << endl;
//	cout << maze.isConnected(0, 3, 1, 1, maze.hasBlock[0][3]) << endl;;
//	cout << maze.moves.size() << endl;
//	cout << maze.hasResult() << endl;

	list.push(maze);
	clock_t t22, t23;
	t22 = clock();
	solve(maze);
	t23 = clock();
	cout << t23 - t22 << endl;
	getchar();

}
