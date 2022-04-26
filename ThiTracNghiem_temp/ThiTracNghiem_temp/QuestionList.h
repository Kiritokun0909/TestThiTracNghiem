#pragma once
#include "Question.h"

class QuestionList
{
private:
	int size = 0;
	int capacity = 0;
	Question** list = nullptr;
public:
	QuestionList(int capacity);

	bool IsFull();
	bool IsEmpty();
	void Clear();

	bool PushBack(Question* question);
	bool PopBack();
	bool InsertAt(Question* question, int position);
	bool DeleteAt(int position);

	int getSize();
	int getCapacity();

	void setCapacity(int capacity);

	Question** getList() const;
	QuestionList();
	~QuestionList();
};

