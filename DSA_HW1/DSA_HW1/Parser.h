#ifndef _PARSER_HEADER_INCLUDED_
#define _PARSER_HEADER_INCLUDED_

#include <iostream>
#include <fstream>
#include "Operator.h"
#include "Vector.h"
#include "String.h"
#include "Stack.h"

class Parser
{
public:
	Parser(const char*, const char*);

	const String& getPostfix() const { return m_postfixExpr; }
	void printResult() const { printf("%.*f", 5, m_result); }

private:
	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;

	void setPath(char*&, const char*);
	void allocate(char*&, size_t) const;

	bool isDigit(char) const;
	bool isOperator(char, const Vector<Operator>&, size_t) const;

	int toDigit(char) const;
	double toNum(const String&) const;

	double calc(double, char, double) const;

	void extractOperators(Vector<Operator>&) const;
	void extractExpression(Vector<String>&) const;

	String generatePostfix(const Vector<String>&, size_t) const;
	double calculateExpression(const Vector<String>&, size_t) const;

private:
	Vector<Operator> m_operators;
	Vector<String> m_prefixExpr;
	String m_postfixExpr;
	double m_result;

	char* m_exprFile;
	char* m_oprtrsFile;
};

#endif // !_PARSER_HEADER_INCLUDED_
