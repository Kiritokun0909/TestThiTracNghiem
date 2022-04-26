#include "Question.h"

Question::Question(const string& subjectId, const string& problem, string abcd[], char answer) {
	id = autoId;
	autoId++;

	this->subjectId = subjectId;
	this->problem = problem;
	for (short int i = 0; i < 4; ++i) {
		this->abcd[i] = abcd[i];
	}
	this->answer = answer;
}

Question::Question(Question* question) {
	*this = *question;
}

int Question::getAutoID() const {
	return autoId;
}

int Question::getID() const {
	return id;
}

string Question::getSubjectID() const {
	return this->subjectId;
}

string Question::getProblem() const {
	return this->problem;
}

string* Question::getABCD() const {
	string* tempABCD = new string[4];
	for (short int i = 0; i < 4; ++i) {
		tempABCD[i] = abcd[i];
	}
	return tempABCD;
}

char Question::getAnswer() const {
	return this->answer;
}

void Question::setAutoID(int id) {
	autoId = id;
}

void Question::setID(int id) {
	this->id = id;
}

void Question::setSubjectID(const string& SubjecId) {
	this->subjectId = subjectId;
}

void Question::setProblem(const string& problem) {
	this->problem = problem;
}

bool Question::setABCD(const string& abcd, int choose) {
	if (choose < 1 || choose > 4) {
		return 0;
	}
	this->abcd[choose - 1] = abcd;
	return 1;
}

bool Question::setABCD(const string& abcd, char choose) {
	if (choose >= 'a' && choose <= 'd') {
		choose -= 32;
	}
	if (choose >= 'A' && choose <= 'D') {
		int selectedNumber = choose - 'A';
		this->abcd[selectedNumber] = abcd;
		return 1;
	}
	return 0;
}

bool Question::setAnswer(char answer) {
	if (answer >= 'a' && answer <= 'd') {
		answer -= 32;
	}
	if (answer >= 'A' && answer <= 'D') {
		this->answer = answer;
		return 1;
	}
	return 0;
}

bool Question::setAnswer(int _answer) {
	this->answer = _answer - '0' + 'A';
	return setAnswer(_answer);
}

Question::Question() {
};

Question::~Question() {
};

