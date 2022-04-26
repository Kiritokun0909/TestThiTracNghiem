#pragma once
#include <string>
using std::string;
static int autoId = 1;
class Question {
private:
	int id = 0;
	string subjectId{};
	string problem{};
	string abcd[4]{};
	char answer{};

public:
	Question(const string& subjectId, const string& problem, string abcd[], char answer);
	Question(Question* question);

	int getAutoID() const;
	int getID() const;
	string getSubjectID() const;
	string getProblem() const;
	string* getABCD() const;
	char getAnswer() const;

	void setAutoID(int id);
	void setID(int id);
	void setSubjectID(const string& subjectId);
	void setProblem(const string& problem);
	bool setABCD(const string& abcd, int choose);
	bool setABCD(const string& abcd, char choose);
	bool setAnswer(char Answer);
	bool setAnswer(int Answer);

	Question();
	~Question();
};

