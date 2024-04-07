#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 *  Паттерн проектирования, объединяет объекты в древовидную структуру для представления иерархии от частного к целому.
 *  Позволяет клиентам единообразно трактовать индивидуальные и составные объекты.
	Паттерн определяет иерархию классов, которые могут состоять из примитивных и сложных объектов, упрощает архитектуру клиента,
 *  делает процесс добавления новых видов объекта более простым.
 *
 * Одна из целей паттерна компоновщик - избавить клиентов от необходимости знать, работают ли они с листовым или составным объектом.
 * Для достижения этой цели класс Component должен сделать как можно больше операций общими для классов Composite и Leaf.
 * Обычно класс Component предоставляет для этих операций реализации по умолчанию, а подклассы Composite и Leaf замещают их.
 *
 * Результаты:
 * - определяет иерархии классов, состоящие из примитивных и составных объектов.
 * - упрощает архитектуру клиента.
 * - облегчает добавление новых видов компонентов.
 * - способствует созданию общего дизайна
*/

/*
 Component
	- объявляет интерфейс для компонуемых объектов;
	- предоставляет подходящую реализацию операций по умолчанию, общую для всех классов;
	- объявляет интерфейс для доступа к потомкам и управления ими;
	- определяет интерфейс для доступа к родителю компонента в рекурсивной структуре и при необходимости реализует его.
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
 *  - определяет поведение компонентов, у которых есть потомки;
	- хранит компоненты-потомки;
	- реализует относящиеся к управлению потомками операции в интерфейсе класса Component;
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
	- представляет листовые узлы композиции и не имеет потомков;
	- определяет поведение примитивных объектов в композиции;
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

	Component* root = new Composite("Здание");

	Component* comp = new Composite("Приемная", 250);
	comp->Add(new Leaf("Стиль: теплые тона", 110));

	Component* comp2 = new Composite("Журнальный столик", 50);
	comp2->Add(new Leaf("10-20 журналов типа «компьютерный мир»", 35));
	comp->Add(comp2);
	comp->Add(new Leaf("Мягкий диван", 150));


	Component* comp4 = new Composite("Стол секретаря", 80);
	Component* comp5 = new Composite("Компьютер", 100);
	comp5->Add(new Leaf("Большой объем жесткого диска", 10));
	comp4->Add(comp5);
	comp->Add(comp4);

	comp4->Add(new Leaf("Офисный инструментарий", 200));
	comp->Add(new Leaf("Кулер с теплой и холодной водой", 150));



	// Аудитория 1
	Component* comp8 = new Composite("Аудитория 1", 250);
	Component* comp9 = new Composite("10 столов", 350);
	Component* comp10 = new Composite("Доска", 90);
	Component* comp11 = new Composite("Стол учителя", 50);
	comp11->Add(new Leaf("Компьютер", 100));
	comp8->Add(comp9);
	comp8->Add(comp10);
	comp8->Add(comp11);

	Component* comp12 = new Composite("Плакаты великих математиков", 270);
	comp8->Add(comp12);



	// Аудитория 2
	Component* comp13 = new Composite("Аудитория 2", 250);
	Component* comp14 = new Composite("20 столов", 750);
	comp13->Add(comp14);

	comp14->Add(new Leaf("Столы черного цвета", 150));
	comp14->Add(new Leaf("Столы выставлены в овал или круг", 150));
	comp13->Add(new Leaf("Доска", 90));
	comp13->Add(new Leaf("Мягкий диван", 150));



	// Компьютерная аудитория
	Component* comp15 = new Composite("Компьютерная аудитория", 250);
	Component* comp16 = new Composite("10 компьютерных столов", 375);
	Component* comp17 = new Composite("Компьютер на каждом столе", 10000);
	comp16->Add(comp17);
	comp15->Add(comp16);

	comp17->Add(new Leaf("Процессор 2.2ГРц", 50));
	comp17->Add(new Leaf("Винчестер на 80ГБ", 20));
	comp17->Add(new Leaf("Оперативная память 1024МБ", 30));

	comp16->Add(new Leaf("Розетка возле каждого стола", 50));

	Component* comp18 = new Composite("Доска", 90);
	comp15->Add(comp18);

	comp18->Add(new Leaf("Набор разноцветных маркеров", 20));

	// Столовая
	Component* comp19 = new Composite("Столовая", 250);
	Component* comp20 = new Composite("Кофейный автомат", 550);
	Component* comp21 = new Composite("Стол", 20);
	comp19->Add(comp20);
	comp19->Add(comp21);

	comp21->Add(new Leaf("4 стула", 80));
	comp19->Add(new Leaf("Холодильник", 180));
	comp19->Add(new Leaf("Умывальник", 40));

	root->Add(comp);
	root->Add(comp8);
	root->Add(comp13);
	root->Add(comp15);
	root->Add(comp19);
	root->Display(1);
	cout << "Общая сумма: " << root->GetTotalPrice() << "$\n";

	system("pause");
}