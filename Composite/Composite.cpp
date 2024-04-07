#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 *  ������� ��������������, ���������� ������� � ����������� ��������� ��� ������������� �������� �� �������� � ������.
 *  ��������� �������� ������������ ���������� �������������� � ��������� �������.
	������� ���������� �������� �������, ������� ����� �������� �� ����������� � ������� ��������, �������� ����������� �������,
 *  ������ ������� ���������� ����� ����� ������� ����� �������.
 *
 * ���� �� ����� �������� ����������� - �������� �������� �� ������������� �����, �������� �� ��� � �������� ��� ��������� ��������.
 * ��� ���������� ���� ���� ����� Component ������ ������� ��� ����� ������ �������� ������ ��� ������� Composite � Leaf.
 * ������ ����� Component ������������� ��� ���� �������� ���������� �� ���������, � ��������� Composite � Leaf �������� ��.
 *
 * ����������:
 * - ���������� �������� �������, ��������� �� ����������� � ��������� ��������.
 * - �������� ����������� �������.
 * - ��������� ���������� ����� ����� �����������.
 * - ������������ �������� ������ �������
*/

/*
 Component
	- ��������� ��������� ��� ����������� ��������;
	- ������������� ���������� ���������� �������� �� ���������, ����� ��� ���� �������;
	- ��������� ��������� ��� ������� � �������� � ���������� ���;
	- ���������� ��������� ��� ������� � �������� ���������� � ����������� ��������� � ��� ������������� ��������� ���.
 */

class Component abstract {
protected:
	string name;
	int price;
	static int totalPrice;

public:
	Component(string name) {
		this->name = name;
	}
	Component(string name, int price) {
		this->name = name;
		this->price = price;
	}

	virtual void Add(Component* c) abstract;
	virtual void Remove(Component* c) abstract;
	virtual void Display(int depth) abstract;
	virtual int GetTotalPrice() abstract;
};
int Component::totalPrice = 0;

/*
 * Composite
 *  - ���������� ��������� �����������, � ������� ���� �������;
	- ������ ����������-�������;
	- ��������� ����������� � ���������� ��������� �������� � ���������� ������ Component;
*/

class Composite : public Component {
	vector<Component*> components;

public:
	Composite(string name) :Component(name) {	}
	Composite(string name, int price) :Component(name, price) {	}

	void Add(Component* component) override {
		components.push_back(component);
	}
	void Remove(Component* component) override {
		auto iter = find(components.begin(), components.end(), component);
		components.erase(iter);
	}
	void Display(int depth) override {
		string s(depth, '-');
		cout << s + name << " = " << price << "$" << endl;
		totalPrice += price;

		for (Component* component : components) {
			component->Display(depth + 2);
		}
	}
	int GetTotalPrice() override {
		return totalPrice;
	}
};
/*
 * Leaf
	- ������������ �������� ���� ���������� � �� ����� ��������;
	- ���������� ��������� ����������� �������� � ����������;
 */
class Leaf : public Component {
public:
	Leaf(string name) : Component(name) {	}
	Leaf(string name, int price) : Component(name, price) {	}

	void Add(Component* c) override {
		cout << "Cannot add to file\n";
	}
	void Remove(Component* c) override {
		cout << "Cannot remove from file\n";
	}
	void Display(int depth) override {
		string s(depth, '-');
		cout << s + name << " = " << price << "$" << endl;
		totalPrice += price;

	}
	int GetTotalPrice() override {
		return totalPrice;
	}
};

int main() {
	setlocale(LC_CTYPE, "Russian");

	Component* root = new Composite("������");

	Component* comp = new Composite("��������", 250);
	comp->Add(new Leaf("�����: ������ ����", 110));

	Component* comp2 = new Composite("���������� ������", 50);
	comp2->Add(new Leaf("10-20 �������� ���� ������������� ���", 35));
	comp->Add(comp2);
	comp->Add(new Leaf("������ �����", 150));


	Component* comp4 = new Composite("���� ���������", 80);
	Component* comp5 = new Composite("���������", 100);
	comp5->Add(new Leaf("������� ����� �������� �����", 10));
	comp4->Add(comp5);
	comp->Add(comp4);

	comp4->Add(new Leaf("������� ��������������", 200));
	comp->Add(new Leaf("����� � ������ � �������� �����", 150));



	// ��������� 1
	Component* comp8 = new Composite("��������� 1", 250);
	Component* comp9 = new Composite("10 ������", 350);
	Component* comp10 = new Composite("�����", 90);
	Component* comp11 = new Composite("���� �������", 50);
	comp11->Add(new Leaf("���������", 100));
	comp8->Add(comp9);
	comp8->Add(comp10);
	comp8->Add(comp11);

	Component* comp12 = new Composite("������� ������� �����������", 270);
	comp8->Add(comp12);



	// ��������� 2
	Component* comp13 = new Composite("��������� 2", 250);
	Component* comp14 = new Composite("20 ������", 750);
	comp13->Add(comp14);

	comp14->Add(new Leaf("����� ������� �����", 150));
	comp14->Add(new Leaf("����� ���������� � ���� ��� ����", 150));
	comp13->Add(new Leaf("�����", 90));
	comp13->Add(new Leaf("������ �����", 150));



	// ������������ ���������
	Component* comp15 = new Composite("������������ ���������", 250);
	Component* comp16 = new Composite("10 ������������ ������", 375);
	Component* comp17 = new Composite("��������� �� ������ �����", 10000);
	comp16->Add(comp17);
	comp15->Add(comp16);

	comp17->Add(new Leaf("��������� 2.2���", 50));
	comp17->Add(new Leaf("��������� �� 80��", 20));
	comp17->Add(new Leaf("����������� ������ 1024��", 30));

	comp16->Add(new Leaf("������� ����� ������� �����", 50));

	Component* comp18 = new Composite("�����", 90);
	comp15->Add(comp18);

	comp18->Add(new Leaf("����� ������������ ��������", 20));

	// ��������
	Component* comp19 = new Composite("��������", 250);
	Component* comp20 = new Composite("�������� �������", 550);
	Component* comp21 = new Composite("����", 20);
	comp19->Add(comp20);
	comp19->Add(comp21);

	comp21->Add(new Leaf("4 �����", 80));
	comp19->Add(new Leaf("�����������", 180));
	comp19->Add(new Leaf("����������", 40));

	root->Add(comp);
	root->Add(comp8);
	root->Add(comp13);
	root->Add(comp15);
	root->Add(comp19);
	root->Display(1);
	cout << "����� �����: " << root->GetTotalPrice() << "$\n";

	system("pause");
}