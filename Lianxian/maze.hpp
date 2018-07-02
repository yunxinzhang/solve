#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
using namespace std;
static set<char> colourset;
static pair<int, int> dir2[4] = { { 1,0 } ,{ -1,0 },{ 0,1 },{ 0,-1 } };
class Block {
public:
	int x, y;
	int face;
	char color;
	bool operator<(const Block &p)const {
		if (x <p.x || (x==p.x && y>p.y))
			return true;
		else
			return false;
	}
	bool operator==(const Block &p)const {
		if (x==p.x && y==p.y &&color == p.color)
			return true;
		else
			return false;
	}
	Block() {}
	Block(int x, int y, char c) :x(x), y(y), color(c) { face = 0; }
};
class Map {
public:
	static set<vector<vector<char>>> state;
	set<Block> moves;
	set<Block> endpots;
	int row;
	int col;
	vector<vector<char>> hasBlock;
	vector<vector<char>> isVisited;
	set<pair<int, int>> locs;
	int layer;
	string str;
	void findEnd(int x, int y, int &x1 , int& y1) {
		for (int i = 0; i < col; ++i) {
			for (int j = 0; j < row; ++j) {
				if (hasBlock[i][j] == hasBlock[x][y] - 32) {
					x1 = i;
					y1 = j;
					return;
				}
			}
		}
	}
	void startGameMustGo() {
		for (auto it : moves) {
			if (it.x == 0 && it.y == 1 && hasBlock[0][0] == '.' && hasBlock[1][0]) {
				it.x = 1;
				it.y = 0;
				hasBlock[0][0] = it.color;
				hasBlock[1][0] = it.color;
			}
			if (it.x == 1 && it.y == 0 && hasBlock[0][0] == '.' && hasBlock[0][1]) {
				it.x = 0;
				it.y = 1;
				hasBlock[0][0] = it.color;
				hasBlock[0][1] = it.color;
			}

			if (it.x == 0 && it.y == col-2 && hasBlock[0][col-1] == '.' && hasBlock[1][col-1]) {
				it.x = 1;
				it.y = col-1;
				hasBlock[0][col-1] = it.color;
				hasBlock[1][col - 1] = it.color;
			}
			if (it.x == 1 && it.y == col-1 && hasBlock[0][col-1] == '.' && hasBlock[0][col-2]) {
				it.x = 0;
				it.y = col-2;
				hasBlock[0][col-1] = it.color;
				hasBlock[0][col - 2] = it.color;
			}

			if (it.x == row-2 && it.y == 0 && hasBlock[row-1][0] == '.' && hasBlock[row-1][1]) {
				it.x = row-1;
				it.y = 1;
				hasBlock[row-1][0] = it.color;
				hasBlock[row - 1][1] = it.color;
			}
			if (it.x == row-1 && it.y == 1 && hasBlock[row-1][0] == '.' && hasBlock[row-2][0]) {
				it.x = row-2;
				it.y = 0;
				hasBlock[row-1][0] = it.color;
				hasBlock[row - 2][0] = it.color;
			}

			if (it.x == row - 2 && it.y == col-1 && hasBlock[row-1][col-1] == '.' && hasBlock[row-1][col-2]) {
				it.x = row - 1;
				it.y = col-2;
				hasBlock[row - 1][col-1] = it.color;
				hasBlock[row - 1][col - 2] = it.color;
			}
			if (it.x == row - 1 && it.y == col-2 && hasBlock[row-1][col-1] == '.' && hasBlock[row-2][col-1]) {
				it.x = row - 2;
				it.y = col-1;
				hasBlock[row - 1][col-1] = it.color;
				hasBlock[row - 2][col - 1] = it.color;
			}
		}
		for (auto it : endpots) {
			if (it.x == 0 && it.y == 1 && hasBlock[0][0] == '.' && hasBlock[1][0]) {
				it.x = 1;
				it.y = 0;
				hasBlock[0][0] = '#';
				hasBlock[1][0] = it.color;
			}
			if (it.x == 1 && it.y == 0 && hasBlock[0][0] == '.' && hasBlock[0][1]) {
				it.x = 0;
				it.y = 1;
				hasBlock[0][0] = '#';
				hasBlock[0][1] = it.color;
			}

			if (it.x == 0 && it.y == col - 2 && hasBlock[0][col - 1] == '.' && hasBlock[1][col - 1]) {
				it.x = 1;
				it.y = col - 1;
				hasBlock[0][col - 1] = '#';
				hasBlock[1][col - 1] = it.color;
			}
			if (it.x == 1 && it.y == col - 1 && hasBlock[0][col - 1] == '.' && hasBlock[0][col - 2]) {
				it.x = 0;
				it.y = col - 2;
				hasBlock[0][col - 1] = '#';
				hasBlock[0][col - 2] = it.color;
			}

			if (it.x == row - 2 && it.y == 0 && hasBlock[row - 1][0] == '.' && hasBlock[row - 1][1]) {
				it.x = row - 1;
				it.y = 1;
				hasBlock[row - 1][0] = '#';
				hasBlock[row - 1][1] = it.color;
			}
			if (it.x == row - 1 && it.y == 1 && hasBlock[row - 1][0] == '.' && hasBlock[row - 2][0]) {
				it.x = row - 2;
				it.y = 0;
				hasBlock[row - 1][0] = '#';
				hasBlock[row - 2][0] = it.color;
			}

			if (it.x == row - 2 && it.y == col - 1 && hasBlock[row - 1][col - 1] == '.' && hasBlock[row - 1][col - 2]) {
				it.x = row - 1;
				it.y = col - 2;
				hasBlock[row - 1][col - 1] = '#';
				hasBlock[row - 1][col - 2] = it.color;
			}
			if (it.x == row - 1 && it.y == col - 2 && hasBlock[row - 1][col - 1] == '.' && hasBlock[row - 2][col - 1]) {
				it.x = row - 2;
				it.y = col - 1;
				hasBlock[row - 1][col - 1] = '#';
				hasBlock[row - 2][col - 1] = it.color;
			}
		}
	}
	bool hasPath(int x, int y, int x1, int y1, char c) {
		//cout << x << ", " << y << "  :: " << x1 << " , " << y1 << endl;
		if (x == x1 && y == y1) {
			return true;
		}
		isVisited[x][y] =c;
		for (int i = 0; i < 4; ++i) {
			int newx = x + dir2[i].first;
			int newy = y + dir2[i].second;
			//cout << dir2[i].first << " , " << dir2[i].second << endl;
			//cout << newx << " >> " << newy << endl;
			if (newx < row && newx >= 0 && newy < col && newy >= 0 &&
				(isVisited[newx][newy]=='.'||isVisited[newx][newy]==isVisited[x][y]-32)) {
				//cout << newx << " >> " << newy << endl;
				if( hasPath(newx, newy, x1, y1, c))return true;
			}
		}
		return false;
	}
	bool hasDeadPoint() {
		getLocs();
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if (hasBlock[i][j] == '.' && deadPoint(i, j))return true;
			}
		}
		return false;
	}
	bool deadPoint(int x, int y) {
		int cnt = 0;
		for (int i = 0; i < 4; ++i) {
			int newx = x + dir2[i].first;
			int newy = y + dir2[i].second;
			
			if (newx >= 0 && newx < row && newy >= 0 && newy < col ) {
				if (hasBlock[newx][newy] == '.')return false;
				else {
					if (locs.find(pair<int, int>(newx, newy)) != locs.end()) {
						++cnt;
					}
				}
			}
		}
		if (cnt <= 1)return true;
		return false;
	}
	void getLocs() {
		locs.clear();
		for (auto it : moves) {
			locs.insert(pair<int, int>(it.x, it.y));
		}
		for (auto it : endpots) {
			locs.insert(pair<int, int>(it.x, it.y));
		}
	}

	bool isConnected(int x, int y, int x1, int y1, char c) {
		isVisited = hasBlock;
		//show();
		return hasPath(x, y, x1, y1, c);
	}
	bool hasResult() {
		for (auto it : moves) {
			//cout << it.x << "," << it.y << endl;
			int x1=-1, y1=-1;
			findEnd(it.x, it.y, x1, y1);
			//cout << x1 << "," << y1 << endl;
			if (!isConnected(it.x, it.y, x1, y1, hasBlock[it.x][it.y])) {
				return false;
			}
		}
		return true;
	}
	Map() {
		str = "";
		layer = 0;
		ifstream fin("map.txt");
		if (!fin) { cout << " read map failed ."; }
		string str; char c;
		fin >> str;
		fin >> row >> col;
		for (int i = 0; i < row; ++i) {
			vector<char> v;
			for (int j = 0; j < col; ++j) {
				v.push_back('.');
			}
			hasBlock.push_back(v);
		}
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				fin >> c;
				if (c == 'x')continue;
				
				else  {
					if (colourset.find(c) == colourset.end()) {
						hasBlock[i][j] = c;
						moves.insert(Block(i, j, c));
					}
					else {
						endpots.insert(Block(i, j, c));
						hasBlock[i][j] = c-32;
					}
					
					colourset.insert(c);
				}
			}
		}
		fin.close();
	}
	void show() {
		cout << "=======================" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cout << hasBlock[i][j] << "\t";
			}
			cout << endl;
		}
	}
	void calc_faces() {
		
	}
	bool deadMove() {
		for (auto it : moves) {
			if (deadMove(it.x, it.y))return true;
		}
		for (auto it : endpots) {
			if (deadMove(it.x, it.y))return true;
		}
		return false;
	}
	// 移动点
	bool deadMove(int x ,int y) {
		for (int i = 0; i < 4; ++i) {
			int newx = x + dir2[i].first;
			int newy = y + dir2[i].second;
			if(newx>=0 && newx<row && newy>=0 && newy<col)
			if (hasBlock[newx][newy] == '.' || hasBlock[x][y] == (hasBlock[newx][newy] + 32) 
				|| hasBlock[x][y] == (hasBlock[newx][newy] - 32)) {
				return false;
			}
		}
		return true;
	}
	// 空地路径点
	
	void safeLine() {

	}
	bool unique() {
		int total = 0;
		for (auto iter : moves) {
			int ind = 0;
			int cnt = 0;
			for (int i = 0; i < 4; ++i) {
				int newx = iter.x + dir2[i].first;
				int newy = iter.y + dir2[i].second;
				if (newx >= 0 && newx < row && newy >= 0 && newy < col
					&& (hasBlock[newx][newy]=='.'|| hasBlock[newx][newy]==(hasBlock[iter.x][iter.y]-32))) {
					cnt++;
					ind = i;
				}
			}
			iter.face = cnt;
			if (cnt == 1) {
				++total;
				
				int newx = iter.x + dir2[ind].first;
				int newy = iter.y + dir2[ind].second;
				//cout << newx << "," << newy << endl;
				moves.erase(iter);
				if (hasBlock[newx][newy] != (hasBlock[iter.x][iter.y] - 32))
					moves.insert(Block(newx, newy, iter.color));
				else
					endpots.erase(Block(newx, newy, iter.color));
				hasBlock[newx][newy] = iter.color;
				/*if (iter.x == 0 && iter.y == 0 && newx == 1 && newy == 0) {
					cout << 3333 << endl;
					show();
					cout << 3333 << endl;
				}*/
				str += "\n";
				str += to_string(iter.x) + "," + to_string(iter.y) + "-->" + to_string(newx) + "," + to_string(newy);
				layer++;
			}
		}
		for (auto iter : endpots) {
			int ind = 0;
			int cnt = 0;
			for (int i = 0; i < 4; ++i) {
				int newx = iter.x + dir2[i].first;
				int newy = iter.y + dir2[i].second;
				if (newx >= 0 && newx < row && newy >= 0 && newy < col
					&& (hasBlock[newx][newy] == '.' || hasBlock[newx][newy] == (hasBlock[iter.x][iter.y] + 32))) {
					cnt++;
					ind = i;
				}
			}
			iter.face = cnt;
			if (cnt == 1) {
				++total;
				int newx = iter.x + dir2[ind].first;
				int newy = iter.y + dir2[ind].second;
				//cout << newx << "," << newy << endl;
				endpots.erase(iter);
				if (hasBlock[newx][newy] != (hasBlock[iter.x][iter.y] + 32))
					endpots.insert(Block(newx, newy, iter.color));
				else
					moves.erase(Block(newx, newy, iter.color));
				hasBlock[newx][newy] = iter.color-32;
				hasBlock[iter.x][iter.y] = '#';
				
				str += "\n";
				str += to_string(iter.x) + "," + to_string(iter.y) + "-->" + to_string(newx) + "," + to_string(newy);
				layer++;
			}
		}
		return total == 0;
	}
	bool deadCorner() {
		if (hasBlock[0][1] != '.' && hasBlock[1][1] != '.'&&hasBlock[1][0] == '.' && hasBlock[0][0] == '.') {
			for (auto it : moves) {
				if (it.x == 0 && it.y == 1) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == 0 && it.y == 1) {
					return false;
				}
			}
			return true;
		}
		if (hasBlock[1][0] != '.' && hasBlock[1][1] != '.'&&hasBlock[0][0] == '.' && hasBlock[0][1] == '.') {
			for (auto it : moves) {
				if (it.x == 1 && it.y == 0) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == 1 && it.y == 0) {
					return false;
				}
			}
			return true;
		}
		if (hasBlock[0][col-2] != '.' && hasBlock[1][col-2] != '.'&&hasBlock[1][col-1] == '.' && hasBlock[0][col-1] == '.') {
			for (auto it : moves) {
				if (it.x == 0 && it.y == col-2) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == 0 && it.y == col - 2) {
					return false;
				}
			}
			return true;
		}
		
		if (hasBlock[1][col-2] != '.' && hasBlock[1][col-1] != '.'&&hasBlock[0][col-2] == '.' && hasBlock[0][col-1] == '.') {
			for (auto it : moves) {
				if (it.x == 1 && it.y == col-1) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == 1 && it.y == col - 1) {
					return false;
				}
			}
			return true;
		}
		if (hasBlock[row-1][1] != '.' && hasBlock[row-2][1] != '.'&&hasBlock[row-1][0] == '.' && hasBlock[row-2][0] == '.') {
			for (auto it : moves) {
				if (it.x == row-1 && it.y == 1) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == row - 1 && it.y == 1) {
					return false;
				}
			}
			return true;
		}
		if (hasBlock[row-2][0] != '.' && hasBlock[row-2][1] != '.'&&hasBlock[row-1][0] == '.' && hasBlock[row-1][1] == '.') {
			for (auto it : moves) {
				if (it.x == row-2 && it.y == 0) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == row - 2 && it.y == 0) {
					return false;
				}
			}
			return true;
		}
		if (hasBlock[row-2][col-2] != '.' && hasBlock[row-1][col-2] != '.'&&hasBlock[row-2][col-1] == '.' && hasBlock[row-1][col-1] == '.') {
			for (auto it : moves) {
				if (it.x == row-1 && it.y == col-2) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == row - 1 && it.y == col - 2) {
					return false;
				}
			}
			return true;
		}
		if (hasBlock[row-2][col-2] != '.' && hasBlock[row-2][col-1] != '.'&&hasBlock[row-1][col-1] == '.' && hasBlock[row-1][col-2] == '.') {
			for (auto it : moves) {
				if (it.x == row-2 && it.y == col-1) {
					return false;
				}
			}
			for (auto it : endpots) {
				if (it.x == row - 2 && it.y == col - 1) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	// 应该是可以 moves的size 为0
	bool win() {
		for (int i = 0; i < row ; ++i) {
			for (int j = 0; j < col; ++j) {
				if (hasBlock[i][j] == '.')return false;
			}
		}
		if (moves.size() > 0 || endpots.size()>0)return false;
		return true;
	}
};