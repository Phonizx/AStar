#pragma once

#ifndef CELL_H
#define CELL_H

 
// manca solo la gestione del parent 
class Cell {
public:
	Cell();
	Cell(int, int);
	void setType(char c);
	char getType() const;

	int get_f() const;
	int get_g() const;
	int get_h() const;

	int get_x() const ;
	int get_y() const;

	void set_f(int);
	void set_g(int);
	void set_h(int);

	bool isStart();
	bool isGoal();
	bool isUnwalkable();
	bool isCell();

	Cell& operator=(Cell);
	bool operator==(Cell);
	Cell(const Cell& c);

	Cell* get_parent() const;
	void set_parent(Cell*);	

private:
	int x = 0, y = 0;
	int f = 0, g = 0, h = 0;
	Cell *parent = nullptr;
	char typeNode = 'c';
};

Cell& Cell::operator=(Cell c)
{
	this->x = c.get_x();
	this->y = c.get_y();

	this->f = c.get_f();
	this->g = c.get_g();
	this->h = c.get_h();
	this->parent = c.get_parent();
	this->typeNode = c.getType();

	return *this;
}

Cell::Cell(const Cell& c)
{
	this->x = c.get_x();
	this->y = c.get_y();
	this->f = c.get_f();
	this->g = c.get_g();
	this->h = c.get_h();
	this->parent = c.get_parent();
	this->typeNode = c.getType();
 
}

bool Cell::operator==(Cell c)
{
	if (x == c.get_x() && y == c.get_y())
		return true;
	else
		return false;
}
 
Cell::Cell() { }

Cell::Cell(int _x, int _y)
{
	x = _x;
	y = _y;
}
void Cell::setType(char c) { typeNode = c; }

char Cell::getType() const { return typeNode; }

int Cell::get_f() const { return f; }
int Cell::get_g() const { return g; }
int Cell::get_h() const { return h; }
int Cell::get_x() const { return x; }
int Cell::get_y() const { return y; }

void Cell::set_f(int value) { f = value; }
void Cell::set_g(int value) { g = value; }
void Cell::set_h(int value) { h = value; }


  
Cell* Cell::get_parent() const { return parent; }
void Cell::set_parent(Cell *c) { parent = c; }


bool Cell::isCell() { return (typeNode == 'c') ? true : false; }
bool Cell::isGoal() { return (typeNode == 'g') ? true : false; }
bool Cell::isStart() { return (typeNode == 's') ? true : false; }
bool Cell::isUnwalkable() { return (typeNode == 'x') ? true : false; }


#endif
