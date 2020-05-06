#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;

class Point;
class Rectangle;
class ListNode;
class MyList;

class Point {
public:
	friend class Rectangle;
	Point() :x(0), y(0) {};
	Point(int x, int y):x(x),y(y){}
	void setX(int x);
	void setY(int y);
	int getX ()const;
	int getY()const;
	double getDistance(const Point& temp)const;
	void printDistanceWith(const Point& temp)const;
private:
	int x, y;
};

class Rectangle {
public:
	Rectangle(int x1, int y1, int x2, int y2);
	Rectangle(const Point& x, const Point& y);
	int getPerimeter()const;
	int getArea()const;
	void print()const;
private:
	Point upperLeft, lowerRight;
};

class ListNode {
public:
	friend class MyList;
	ListNode(const Rectangle& temp) :data(temp) {
		next = NULL;
	}
private:
	ListNode* next;
	Rectangle data;
};

class MyList {
public:
	MyList() {
		pHead = NULL;
		number = 0;
	}
	void append(const Rectangle& temp);
	Rectangle pop(int i);
	void print();
	~MyList();
private:
	ListNode* pHead;
	int number;
	int compare(const ListNode* p, const ListNode* q);
};


int main() {
	//1
	cout << "Test1:" << endl;
	Point p1, p2(3, -4);
	p1.printDistanceWith(p2);
	cout << "Test1 end!" << endl << endl;

	//2
	cout << "Test2:" << endl;
	Rectangle r1(p1, p2);
	r1.print();
	cout << "Test2 end!" << endl << endl;

	//3
	cout << "Test3:" << endl;
	Rectangle a(0, 2, 2, 0), b(0, 4, 9, 0), c(0, 6, 6, 0), d(0, 7, 7, 0);
	MyList list;
	list.append(a);
	list.append(b);
	list.append(c);
	list.append(d);
	list.print();
	cout << "After pop:" << endl;
	list.pop(1);
	list.print();
	cout << "Test3 end!" << endl;

	return 0;
}


void Point::setX(int x) {
	this->x = x;
}
void Point::setY(int y) {
	this->y = y;
}
int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}
double Point::getDistance(const Point& temp) const {
	int x2, y2;
	x2=temp.getX();
	y2 = temp.getY();
	double distance = pow(x - x2,2 )+pow( y - y2,2);
	distance = sqrt(distance);
	return distance;
}
void Point::printDistanceWith(const Point& temp) const {
	int x2, y2;
	x2 = temp.getX();
	y2 = temp.getY();
	double distance = getDistance(temp);
	printf("(%d,%d)*(%d,%d) = %.2lf\n", x, y, x2, y2, distance);

}

Rectangle::Rectangle(int x1, int y1, int x2, int y2) {
	if (x1<x2 && y1>y2) {
		upperLeft.setX(x1);
		upperLeft.setY(y1);
		lowerRight.setX(x2);
		lowerRight.setY(y2);

	}
	else {
		cout << " Input Error!" << endl;
	}
}
Rectangle::Rectangle(const Point& a, const Point& b){
	if (a.getX() < b.getX() && a.getY() > b.getY()) {
		upperLeft = a;
		lowerRight = b;
	}
	else {
		cout << " Input Error!" << endl;
	}

}
int Rectangle::getPerimeter() const{
	int x1, x2, y1, y2;

	x1=upperLeft.getX();
	y1 = upperLeft.getY();

	x2 = lowerRight.getX();	
	y2= lowerRight.getY();

	return 2 * (x2 - x1) + 2 * (y1 - y2);
}
int Rectangle::getArea() const {
	int x1, x2, y1, y2;

	x1 = upperLeft.getX();
	y1 = upperLeft.getY();

	x2 = lowerRight.getX();
	y2 = lowerRight.getY();

	return (x2 - x1) * (y1 - y2);
}
void Rectangle::print() const {
	int x1, x2, y1, y2;

	x1 = upperLeft.getX();
	y1 = upperLeft.getY();

	x2 = lowerRight.getX();
	y2 = lowerRight.getY();

	printf("vertices: (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n"
		, x1, y1, x2, y1, x2, y2, x1, y2);
	cout << "perimeter: " << getPerimeter() << endl;
	cout << "area : " << getArea() << endl;
}


int MyList::compare(const ListNode* p, const ListNode* q) {
	int val = 0;

	if (p->data.getArea() > q->data.getArea())val = 1;
	else if (p->data.getArea() < q->data.getArea())val = -1;
	else {
		if (p->data.getPerimeter() > q->data.getPerimeter())val = 1;
		else if (p->data.getPerimeter() < q->data.getPerimeter())val = -1;
		else val = 0;
	}
	return val;
}
void MyList::append(const Rectangle& temp) {
	ListNode* pTempNode = new ListNode(temp);
	number++;

	if (!pHead) {//空字符串
		pHead = pTempNode;
		return;
	}

	if (compare(pHead, pTempNode) == 1) {//放在第一个
		pTempNode->next = pHead;
		pHead = pTempNode;
		return;
	}

	ListNode* pNode1 = pHead;
	ListNode* pNode2 = NULL;

	while (pNode1 != NULL && compare(pNode1, pTempNode) != 1) {//放在中间或最后
		pNode2 = pNode1;
		pNode1 = pNode1->next;
	}
	
	pTempNode->next = pNode1;
	pNode2->next = pTempNode;
	
	return;

}
Rectangle MyList::pop(int i) {
	if (i==1) {//第一个
		Rectangle tempRec = pHead->data;
		auto tempList = pHead->next;
		delete pHead;
		pHead = tempList;
		number--;
		return tempRec;
	}

	ListNode* pNode1 = pHead;
	ListNode* pNode2 = NULL;
	for (int j = 1; j < i; j++) {//中间或者最后
		pNode2 = pNode1;
		pNode1 = pNode1->next;
	}
	Rectangle tempRec = pNode1->data;
	pNode2->next = pNode1->next;
	delete pNode1;
	number--;
	return tempRec;
}
void MyList::print() {
	if (number < 3) {
		cout << "Error!" << endl;
		return;
	}

	ListNode* pNode1 = pHead;
	for (int j = 0; j < number - 3; j++) 
		pNode1 = pNode1->next;

	ListNode* p1 = pNode1;
	ListNode* p2 = p1->next;
	ListNode* p3 = p2->next;

	cout << 1 << endl;
	p3->data.print();
	cout << endl<<2 << endl;
	p2->data.print();
	cout <<endl<< 3 << endl;
	p1->data.print();
	
}
MyList::~MyList() {
	ListNode* p1 = pHead;
	ListNode* p2 = NULL;
	for (int i = 0; i < number; i++) {
		p2 = p1;
		p1 = p1->next;
		delete p2;
	}
}

