#include "QuestionList.h"

QuestionList::QuestionList(int capacity) {
	this->capacity = capacity;
	list = new Question * [capacity];
}

int QuestionList::getSize() {
	return this->size;
}

int QuestionList::getCapacity() {
	return this->capacity;
}

bool QuestionList::IsFull() {
	return size == capacity;
}

bool QuestionList::IsEmpty() {
	return size == 0;
}

void QuestionList::Clear() {
	for (int i = 0; i < size; ++i) {
		delete list[i];
	}

	delete[] list;
	size = 0;
}

bool QuestionList::PushBack(Question* question) {
	if (IsFull()) {
		return 0;
	}

	list[size] = new Question(question);
	size++;

	return 1;
}

bool QuestionList::PopBack() {
	if (size == 0) {
		return 0;
	}

	delete list[size - 1];
	size--;
	return 1;
}

bool QuestionList::InsertAt(Question* question, int position) {
	if (IsFull()) {
		return 0;
	}

	if (position < 0 || position > size) {
		return 0;
	}

	for (int i = size - 1; i >= position; --i) {
		list[i + 1] = list[i];
	}

	size++;
	list[position] = question;
	return 1;
}

bool QuestionList::DeleteAt(int position) {
	if (IsEmpty()) {
		return 0;
	}

	if (position < 0 || position > size) {
		return 0;
	}

	for (int i = position; i < size - 1; ++i) {
		list[i] = list[i + 1];
	}

	size--;
	return 0;
}

void QuestionList::setCapacity(int capacity) {
	while (capacity < this->size) {
		PopBack();
	}
}

Question** QuestionList::getList() const {
	return list;
}

QuestionList::QuestionList() {
}

QuestionList::~QuestionList() {

	for (int i = 0; i < size; ++i) {
		delete list[i];
	}

	delete[]list;
}