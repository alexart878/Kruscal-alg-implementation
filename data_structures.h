#pragma once

//vector
template <typename T>
class Vector
{
private:

	T* arr;
	size_t v_size;
	size_t v_cap;

public:

	Vector() {
		arr = 0;
		v_size = 0;
		v_cap = 0;
	}

	Vector(size_t size) {
		arr = new T[size];
		v_size = size;
		v_cap = size;
	}

	Vector(const Vector<T>& v) {
		v_size = v.v_size;
		v_cap = v.v_cap;
		for (size_t i = 0; i < v_size; i++) arr[i] = v.arr[i];
	}

	~Vector() {
		delete[] arr;
	}

	size_t size() { return v_size; };

	void reserve(size_t cap) {
		if (arr == 0) {
			v_size = 0;
			v_cap = 0;
		}

		T* buffer = new T[cap];
		size_t l_size = cap < v_size ? cap : v_size;
		for (size_t i = 0; i < l_size; i++) buffer[i] = arr[i];
		v_cap = cap;
		delete[] arr;
		arr = buffer;
	}

	void resize(size_t size) {
		reserve(size);
		v_size = size;
	}

	void push_back(T val) {
		if (v_size >= v_cap) reserve(v_cap + 5);
		arr[v_size++] = val;
	}

	void pop_back() {
		v_size--;
	}

	T& operator[](size_t index) {
		return arr[index];
	}
};

//queue
template <typename T>
class Queue 
{
private:
	struct qnode {
		T data;
		qnode* next;
		qnode(T d)
		{
			data = d;
			next = nullptr;
		}
	};

public:
	qnode* front;
	qnode* rear;

	Queue() { front = rear = nullptr; }

	void enQueue(T x) {
		qnode* temp = new qnode(x);

		if (!rear) {
			front = rear = temp;
			return;
		}

		rear->next = temp;
		rear = temp;
	}

	void deQueue() {
		if (!front) return;

		qnode* temp = front;
		front = front->next;

		if (!front) rear = nullptr;
		delete (temp);
	}

	size_t size() {
		if (front == NULL) return 0; else {
			size_t size = 1;
			qnode* temp = front;

			while (temp->next != nullptr) {
				temp = temp->next;
				size++;
			}
			return size;
		}
	}

	bool is_empty() {
		if (front) return false;
		return true;
	}
};