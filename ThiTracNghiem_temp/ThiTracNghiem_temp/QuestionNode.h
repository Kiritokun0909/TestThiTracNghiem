#pragma once 
#include "Question.h"
#include <iostream>
class QuestionNode {
public:
	Question question;
	QuestionNode* left = nullptr, * right = nullptr;
	int height = 1;

	QuestionNode(Question question);
	QuestionNode();
	~QuestionNode();
};