#include "QuestionTree.h"
#include <iostream>
#include <math.h>
using std::cout;
using std::max;

//int QuestionTree::getSize() const {
//	return size;
//}

QuestionNode* QuestionTree::getRoot() const {
	return root;
};

//void QuestionTree::setRoot(QuestionNode* root) { this->root = root; };

bool QuestionTree::Insert(Question& data) {
	int tempSize = size;
	root = InsertAVL(root, data);
	return tempSize != size;
};

bool QuestionTree::Delete(int id) {
	int tempSize = size;
	root = DeleteAVL(root, id);
	return tempSize != size;
}

QuestionNode* QuestionTree::Search(int id) {
	return SearchRecursive(root, id);
}

//void QuestionTree::Print2DUntil(QuestionNode* root, int space) {
//	if (root == NULL)
//		return;
//	space += 7;
//
//	Print2DUntil(root->right, space);
//	cout << '\n';
//
//	for (int i = 4; i < space; i++)
//		cout << " ";
//	cout << root->question.getID() << " (" << root->height << ") " << "\n";
//
//	Print2DUntil(root->left, space);
//}

QuestionTree::QuestionTree() { this->root = nullptr; }

QuestionTree::~QuestionTree() {
	FreeAllMemories(root);
}

int QuestionTree::getHeight(QuestionNode* node) {
	if (node == nullptr) return 0;

	return node->height;
}

int QuestionTree::getBalance(QuestionNode* node) {
	if (node == nullptr) return 0;

	//cout << getHeight(node->left) << ' ' << getHeight(node->right) << '\n';

	return getHeight(node->left) - getHeight(node->right);
}

void QuestionTree::FreeAllMemories(QuestionNode* root) {
	if (root == nullptr) return;

	if (root->left != nullptr) {
		FreeAllMemories(root->left);
	}

	if (root->right != nullptr) {
		FreeAllMemories(root->right);
	}

	delete root;
}

QuestionNode* QuestionTree::LeftRotate(QuestionNode* node) {
	QuestionNode* rightNode = node->right;
	QuestionNode* rightLeftNode = rightNode->left;

	rightNode->left = node;
	node->right = rightLeftNode;

	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	rightNode->height = max(getHeight(rightNode->left), getHeight(rightNode->right)) + 1;

	return rightNode;
}

QuestionNode* QuestionTree::RightRotate(QuestionNode* node) {
	QuestionNode* leftNode = node->left;
	QuestionNode* leftRightNode = leftNode->right;

	leftNode->right = node;
	node->left = leftRightNode;

	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	leftNode->height = max(getHeight(leftNode->left), getHeight(leftNode->right)) + 1;

	return leftNode;
}

QuestionNode* QuestionTree::LeftRightRotate(QuestionNode* node) {
	node->left = LeftRotate(node->left);

	return RightRotate(node);
}

QuestionNode* QuestionTree::RightLeftRotate(QuestionNode* node) {
	node->right = RightRotate(node->right);

	return LeftRotate(node);
}

QuestionNode* QuestionTree::FindMinID(QuestionNode* node) {
	QuestionNode* currNode = node;

	while (currNode->left != nullptr) {
		currNode = currNode->left;
	}

	return currNode;
}

QuestionNode* QuestionTree::InsertAVL(QuestionNode* node, Question& currQuestion) {
	if (node == nullptr) {
		++size;
		return new QuestionNode(currQuestion);
	}

	int currQuestionId = currQuestion.getID();

	if (currQuestionId < node->question.getID()) {
		node->left = InsertAVL(node->left, currQuestion);
	}
	else if (currQuestionId > node->question.getID()) {
		node->right = InsertAVL(node->right, currQuestion);
	}
	else {
		// ---- them dong thong bao keyID bi trung ----//
		return node;
	}

	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	//cout << node->height << '\n';
	//cout << node->height << '\n';
	int balance = getBalance(node);

	if (balance > 1) { // lech trai
		if (currQuestionId < node->left->question.getID()) { // lech trai trai
			return RightRotate(node);
		}
		else { // lech trai phai
			return LeftRightRotate(node);
		}
	}
	else if (balance < -1) { // lech phai
		if (currQuestionId > node->right->question.getID()) {
			return LeftRotate(node);
		}
		else { // lech phai trai
			return RightLeftRotate(node);
		}
	}

	return node;
}

QuestionNode* QuestionTree::DeleteAVL(QuestionNode*& node, int id) {
	if (node == nullptr) {
		return nullptr;
	}

	if (id < node->question.getID()) {
		DeleteAVL(node->left, id);
	}
	else if (id > node->question.getID()) {
		DeleteAVL(node->right, id);
	}
	else {
		// ---- them dong thong bao keyID dc xoa ----//
		if ((node->right == nullptr) || (node->left == nullptr)) { // nhieu nhat 1 node con
			QuestionNode* tempNode = (node->left != nullptr) ? node->left : node->right;

			if (tempNode == nullptr) { // khong co ca 2 node con
				tempNode = node;
				node = nullptr;
			}
			else { // co 1 node con
				*node = *tempNode;
			}

			--size;
			delete tempNode;
		}
		else { // co 2 node con
			QuestionNode* minIdNode = FindMinID(node->right);

			node->question = minIdNode->question;
			node->right = DeleteAVL(node->right, minIdNode->question.getID());
		}
	}

	if (node == nullptr) {
		return nullptr;
	}

	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

	int balance = getBalance(node);

	if (balance > 1) { // lech trai
		if (getBalance(node->left) >= 0) { // lech trai Trai
			return RightRotate(node);
		}
		else { // lech trai phai
			return LeftRightRotate(node);
		}
	}
	else if (balance < -1) {
		if (getBalance(node->right) <= 0) { // lech phai phai
			return LeftRotate(node);
		}
		else { // lech phai trai
			return RightLeftRotate(node);
		}
	}

	return node;
}

QuestionNode* QuestionTree::SearchRecursive(QuestionNode* node, int id) {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->question.getID() == id) {
		return node;
	}

	if (id < node->question.getID()) {
		return SearchRecursive(node->left, id);
	}

	return SearchRecursive(node->right, id);
}