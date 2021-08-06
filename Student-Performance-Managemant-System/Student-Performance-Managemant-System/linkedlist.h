/*filename:linkedlist.h
description:����ģ���������*/

#pragma once
#include <cstdlib>
using namespace std;
template <class T>
struct node
{
	T data;
	node<T>* next;
	node<T>() { data=T(); next = NULL; }
	node<T>(T& t) { data = T(t); next = NULL; }
};

template <class T>
class linkedlist
{
private:
	node<T>* head;
	node<T>* current;
	inline void deepCopy(const linkedlist<T>& original);//���
public:
	linkedlist();
	linkedlist(const linkedlist<T>& aplist);
	~linkedlist();

	void push(node<T>* newNode);//�������м�����
	node<T>* getFirst();//���head
	inline node<T>* getNext();//���current��һ�����
	node<T>* getByIndex(int index);//����������ý��
	bool remove(node<T>* n);//�Ƴ��ڵ�
	bool isEmpty() const;//�ж������Ƿ�Ϊ��
	void sort(bool (*compare)(node<T>&, node<T>&));//��������˳���ɺ���ָ�����
	void makeEmpty();//�������
	int size();//����������

	linkedlist<T>& operator=(const linkedlist<T>& rlist);
};

template <class T>
linkedlist<T>::linkedlist() {
	head = current = NULL;
}

template <class T>
linkedlist<T>::linkedlist(const linkedlist<T>& aplist) {
	deepCopy(aplist);
}

template <class T>
linkedlist<T>::~linkedlist() {
	makeEmpty();
}

template <class T>
void linkedlist<T>::push(node<T>* newNode) {
	current = NULL;
	node<T>* tail = head;
	newNode->next = NULL;
	if (tail == NULL) {
		head = newNode;
	}
	else {
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = newNode;
	}
}

template <class T>
node<T>* linkedlist<T>::getFirst() {
	if (head == NULL) {
		return NULL;
	}
	current = head;
	return head;
}

template <class T>
node<T>* linkedlist<T>::getNext() {
	if (current == NULL)
		return NULL;
	if (current->next == NULL) {
		current = NULL;
		return NULL;
	}
	current = current->next;
	return current;
}

template <class T>
node<T>* linkedlist<T>::getByIndex(int index) {
	if (index >= size()) {
		return NULL;
	}
	current = head;
	while (index > 0) {
		current = current->next;
		index--;
	}
	return current;
}

template <class T>
bool linkedlist<T>::remove(node<T>* n) {
	current = NULL;
	if (head == NULL)
		return false;
	node<T>* tmp = head;
	if (head == n) {
		head = tmp->next;
		delete tmp;
		return true;
	}
	while (tmp->next != NULL) {
		if (tmp->next == n) {
			node<T>* ptr = tmp->next;
			tmp->next = ptr->next;
			delete ptr;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

template <class T>
bool linkedlist<T>::isEmpty() const {
	return head == NULL;
}

template <class T>
void linkedlist<T>::sort(bool (*compare)(node<T>&, node<T>&)) {
	if (head == NULL || head->next == NULL)
		return;
	node<T>* p = head->next, * pstart = new node<T>(), * pend = head;
	pstart->next = head;
	while (p != NULL) {
		node<T>* tmp = pstart->next, * pre = pstart;
		while (tmp != p && compare(*p, *tmp)) {//p>=tmp:��С����
			tmp = tmp->next;
			pre = pre->next;
		}
		if (tmp == p) pend = p;
		else {
			pend->next = p->next;
			p->next = tmp;
			pre->next = p;
		}
		p = pend->next;
	}
	head = pstart->next;
	delete pstart;
	return;
}

template <class T>
void linkedlist<T>::makeEmpty() {
	while (head != NULL) {
		current = head;
		head = head->next;
		delete current;
	}
	current = NULL;
}

template <class T>
int linkedlist<T>::size() {
	int size = 0;
	node<T>* tmp = head;
	while (tmp != NULL) {
		size++;
		tmp = tmp->next;
	}
	return size;
}

template <class T>
void linkedlist<T>::deepCopy(const linkedlist<T>& original) {
	head = current = NULL;
	if (original.head == NULL)
		return;

	node<T>* copy = head = new node<T>;
	node<T>* origin = original.head;
	copy->data = origin->data;
	if (origin == original.current)
		current = copy;

	while (origin->next != NULL) {
		copy->next = new node<T>;
		origin = origin->next;
		copy = copy->next;
		copy->data = origin->data;
		if (origin == original.current)
			current = copy;
	}
	copy->next = NULL;
}

template <class T>
linkedlist<T>& linkedlist<T>::operator=(const linkedlist<T>& rlist) {
	if (this == &rlist)
		return *this;
	makeEmpty();
	deepCopy(rlist);
	return *this;
}
