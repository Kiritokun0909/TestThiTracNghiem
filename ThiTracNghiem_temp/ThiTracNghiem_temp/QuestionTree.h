#pragma once

#include "QuestionNode.h"

class QuestionTree {
private:
	QuestionNode* root;
	int size = 0;

public:
	QuestionTree();
	~QuestionTree();

	//int getSize() const;
	QuestionNode* getRoot() const;
	//void setRoot(QuestionNode *root);

	bool Insert(Question& data); // tra ve 1 neu tim thay va 0 neu khong thay 
	bool Delete(int id); // tra ve 1 neu tim thay va 0 neu khong thay 

	QuestionNode* Search(int id); // tra ve Node can tim neu thay va nullptr neu khong thay

	//void Print2DUntil(QuestionNode* root, int space);

private:
	int getHeight(QuestionNode* node);
	int getBalance(QuestionNode* node);

	void FreeAllMemories(QuestionNode* root);

	QuestionNode* LeftRotate(QuestionNode* node);
	QuestionNode* RightRotate(QuestionNode* node);
	QuestionNode* LeftRightRotate(QuestionNode* node);
	QuestionNode* RightLeftRotate(QuestionNode* node);

	QuestionNode* FindMinID(QuestionNode* node);

	QuestionNode* InsertAVL(QuestionNode* node, Question& data);
	QuestionNode* DeleteAVL(QuestionNode*& node, int id);

	QuestionNode* SearchRecursive(QuestionNode* node, int id);
};