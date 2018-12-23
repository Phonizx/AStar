#pragma once

#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>

#include "Cell.h"
#include <math.h>
#include <vector>
#include <queue>

using namespace std;



struct Comp {
	bool operator()(const Cell& a, const Cell& b)
	{
		return a.get_f() > b.get_f();
	}
};


class AStar {

public:
	AStar();
	void print();

	int manhattan_dist(Cell a, Cell b);
	float euclidean_dist(Cell a, Cell b);

	bool testerNode(int, int);
	vector<Cell> get_adjacentes(Cell);
	void path_finding(Cell, Cell);
	void print_path(Cell);
	
	ostream& operator<<(ostream&);
	Cell** getGrid();

	typedef Cell (*punt)[6];
	punt get_grid() {return grid;}

private:
	Cell grid[6][6];
	int row = 6;
	int col = 6;

	priority_queue<Cell, vector<Cell>, Comp> openSet;
	vector<Cell> closedSet;

	bool find_inOpen(Cell);
	bool find_inClosed(Cell);

};



ostream& operator<<(ostream& os,AStar a)
{
	AStar::punt tmpGrid = a.get_grid();

 		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				os << tmpGrid[i][j].getType() << " ";
			}
			os << "\n";
		}
		os << "\n\n";
	return os;
}
bool AStar::find_inClosed(Cell c)
{
	for (Cell t : closedSet)
		if (t == c)
			return true;
	return false;
}
bool AStar::find_inOpen(Cell c)
{
	auto tmp = openSet;
	bool flag = false;
	while (tmp.size() > 0 && !flag)
	{
		Cell n = tmp.top();
		if (n == c)
			flag = true;
		else
			tmp.pop();
	}
	return flag;
}

AStar::AStar() // caricamento di testing 
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j<col; j++)
		{
			Cell node(i, j);
			node.setType('c');

			if (i == 0 && j == 0) { // start
				node.setType('s');
			}
			if (i == 5 && j == 5) // target
				node.setType('g');
			grid[i][j] = node;
		}
	// creazione  ostacoli
	grid[0][1].setType('x');
	grid[1][1].setType('x');
	grid[2][1].setType('x');
	grid[3][1].setType('x');
	grid[4][1].setType('x');
}

void AStar::print_path(Cell t)
{
	Cell tmp = *t.get_parent();
	cout << "padre di : " << tmp.getType() << endl;
	cout << tmp.get_x() << " "  << tmp.get_y() << endl;
}

void AStar::path_finding(Cell start, Cell goal)
{
	grid[goal.get_x()][goal.get_y()] = goal;
	Cell current;
	start.set_parent(&start);
	closedSet.push_back(start);
	openSet.push(start);
	while (openSet.size() > 0)
	{
		current = openSet.top();

		cout << "Analyzed: " << current.get_x() << "  " << current.get_y() << endl;

		closedSet.push_back(current);
		openSet.pop();

		if (current == goal)
		{
			cout << "Printing path ... " << endl;
			break;
		}
		grid[current.get_x()][current.get_y()].setType('$');  // colored
		vector<Cell> tmpAdj = get_adjacentes(current);
		if (tmpAdj.empty())
			cout << "Path non trovato";
		for (Cell adj : tmpAdj)
		{ 
			if (find_inClosed(adj))
				continue;
			if (find_inOpen(adj))
			{
				int tmpG = current.get_g() + adj.get_g();
				if (tmpG < adj.get_g()) {//  DA TESTARE CON L'EURISTICA 
					adj.set_parent(&current);
					grid[adj.get_x()][adj.get_y()] = adj;
				}
				//l'adiacente è gia presente nella lista open
			}
			else
			{
				//cout << "Adiacente Evaluating: " << adj.get_x() << "  " << adj.get_y() << endl;
				adj.set_g(10);
				adj.set_h(manhattan_dist(adj, goal));
				adj.set_f(adj.get_g() + adj.get_h());
				adj.set_parent(&current);
				grid[adj.get_x()][adj.get_y()] = adj;
				
				// stampe per il controllo del parent  [da fixare]
//				cout << "parent di adj(" << grid[adj.get_x()][adj.get_y()].get_x() << "," << grid[adj.get_x()][adj.get_y()].get_y() << "): "
//					<< grid[adj.get_x()][adj.get_y()].get_parent()->get_x() << " "
//					<< grid[adj.get_x()][adj.get_y()].get_parent()->get_y() << "\n";

				openSet.push(adj);

			}
		}
		
	}

	
}
vector<Cell> AStar::get_adjacentes(Cell c)
{
	vector<Cell> adj_list;
	int x = c.get_x();
	int y = c.get_y();

	if (y + 1 < col) // destra
		if (!grid[x][y + 1].isUnwalkable())
			adj_list.push_back(grid[x][y + 1]);
	if (y - 1>0)
		if (!grid[x][y - 1].isUnwalkable())
			adj_list.push_back(grid[x][y - 1]); //sinistra
	if (x + 1 < row) // sotto
		if (!grid[x + 1][y].isUnwalkable())
			adj_list.push_back(grid[x + 1][y]);
	if (x - 1 > 0) // sopra
		if (!grid[x - 1][y].isUnwalkable())
			adj_list.push_back(grid[x - 1][y]);
	return adj_list;
}

void AStar::print()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << "[h:" << grid[i][j].get_h() << " ," << grid[i][j].get_f() << "] ";
		}
		cout << "\n";
	}
	cout << "\n\n";
	 
}

float AStar::euclidean_dist(Cell a, Cell b) {
	float radix = (pow((a.get_x() - b.get_x()), 2) + pow((a.get_y() - b.get_y()), 2));
	return sqrt(radix);
}

int AStar::manhattan_dist(Cell a, Cell b)
{
	return abs(a.get_x() - b.get_x()) + abs(a.get_y() - b.get_y());
}

// funzione di test per valutare il tipo di cella {cell,start, goal, wall} 
bool AStar::testerNode(int r, int c)
{
	return grid[r][c].isStart();
}
#endif // !ASTAR_H
