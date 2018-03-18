#include "Parser.h"

Parser::Parser(const char* exprFile, const char* oprtrsFile)
{
	if (!exprFile || !oprtrsFile)
	{
		throw std::runtime_error("Invalid file path(s) has/have been passed.\n");
	}
	else
	{
		setPath(m_exprFile, exprFile);
		setPath(m_oprtrsFile, oprtrsFile);

		extractOperators(m_operators);
		extractExpression(m_prefixExpr);
		size_t exprLen = m_prefixExpr.getSize();

		m_postfixExpr = generatePostfix(m_prefixExpr, exprLen);
		m_result = calculateExpression(m_prefixExpr, exprLen);
	}
}

void Parser::setPath(char*& dest, const char * filePath)
{
	if (!filePath)
	{
		throw std::runtime_error("Invalid file name has been passed.\n");
	}
	else
	{
		allocate(dest, strlen(filePath) + 1);
		strcpy(dest, filePath);
	}
}

void Parser::allocate(char*& dest, size_t size) const
{
	dest = new char[size];
}

bool Parser::isDigit(char c) const
{
	return c >= '0' && c <= '9';
}

bool Parser::isOperator(char c,	const Vector<Operator>& operators, size_t size) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (c == operators[i].m_symbol)
		{
			return true;
		}
	 }

	return false;
}

int Parser::toDigit(char c) const
{
	return c - '0';
}

double Parser::toNum(const String& str) const
{
	double res = 0,
		   end = 0;
	size_t len = str.getSize();
	
	(str[0] != '-') ? end = 0 : end = 1;

	int n = 0;
	for (int i = len - 1; i >= end; --i)
	{
		res += toDigit(str[i])*pow(10, n);
		++n;
	}

	return (end == 0) ? res : res *= -1;
}

double Parser::calc(double num1, char sym, double num2) const
{
	char op = '\0';
	size_t size = m_operators.getSize();
	
	for (size_t i = 0; i < size; ++i)
	{
		if (sym == m_operators[i].m_symbol)
		{
			op = m_operators[i].m_op;
			break;
		}
	}

	switch (op)
	{
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			if (num2 == 0) 
			{ 
				throw std::logic_error("Cannot divide by zero.\n"); 
			}
			return num1 / num2;

		default:
			throw std::runtime_error("Invalid operator.\n"); //should never reach this line
	}
}

void Parser::extractOperators(Vector<Operator>& operators) const
{
	if (!m_oprtrsFile)
	{
		throw std::runtime_error("No such file with operators\n");
	}
	else
	{
		std::ifstream in;
		in.open(m_oprtrsFile);
		if (!in) 
		{ 
			throw std::runtime_error("A problem occured while opening the file with operators.\n"); 
		}
		
		const size_t lineLen = 7;
		char buff[lineLen];

		while (!in.eof())
		{
			in.getline(buff, sizeof(buff) - 1);
			Operator op(buff[0], buff[2], buff[4]);
			operators.push_back(op);
		}

		in.close();
	}
}

void Parser::extractExpression(Vector<String>& expression) const
{
	if (!m_exprFile)
	{
		throw std::runtime_error("No such file with an expression.\n");
	}
	else
	{
 		std::ifstream in;
		in.open(m_exprFile);
		if (!in) 
		{ 
			throw std::runtime_error("A problem occured while opening the file with the expression.\n"); 
		}

		char c = '\0';

		while (!in.eof())
		{
			c = in.get();
			if (isOperator(c, m_operators, m_operators.getSize()))
			{
				String op;
				op += c;
				expression.push_back(op);
			}
			else if (c == '-' || isDigit(c))
			{
				String num;
				size_t numCnt = 0;

				if (c == '-')
				{
					if (!isDigit(in.peek())) 
					{ 
						throw std::runtime_error("Error\n"); 
					}
				}

				num += c;

				while (isDigit(in.peek()))
				{
					c = in.get();
					num += c;
				}

				expression.push_back(num);
			}
			else
			{
				throw std::runtime_error("Error.\n");
			}

			while (c != ' ' && !in.eof()) { c = in.get(); }  //eat whitespaces
		}

		in.close();
	}
}

String Parser::generatePostfix(const Vector<String>& expression, size_t exprLen) const
{
	Stack<String> st;
	st.push(expression[exprLen - 1]);
	int cnt = exprLen - 2;

	String opnd1, opnd2, res;
	while (cnt >= 0)
	{
		if (isDigit(expression[cnt][0]) || (expression[cnt][0] == '-' && expression[cnt][1] != '\n'))
		{
			st.push(expression[cnt]);
		}
		else
		{
			if (st.getSize() < 2)
			{
				throw std::runtime_error("Error\n"); 
			}

			opnd1 = st.getTop();
			st.pop();
			opnd2 = st.getTop();
			st.pop();

			res = opnd1;
			res += ' ';
			res += opnd2;
			res += ' ';
			res += expression[cnt];

			st.push(res);
		}

		--cnt;
	}

	if (st.getSize() != 1) 
	{ 
		throw std::runtime_error("Error\n"); 
	}

	return st.getTop();
}

double Parser::calculateExpression(const Vector<String>& expression, size_t exprLen) const
{
	Stack<double> st;
	st.push(toNum(expression[exprLen - 1]));
	int cnt = exprLen - 2;

	while (cnt >= 0)
	{
		if (isDigit(expression[cnt][0]) || (expression[cnt][0] == '-' && expression[cnt][1] != '\n'))
		{
			st.push(toNum(expression[cnt]));
		}
		else
		{
			if (st.getSize() < 2) { throw std::runtime_error("Error\n"); }

			double opnd1 = st.getTop();
			st.pop();
			double opnd2 = st.getTop();
			st.pop();

			double res = calc(opnd1, expression[cnt][0], opnd2);
			st.push(res);
		}

		--cnt;
	}

	if (st.getSize() != 1) 
	{ 
		throw std::runtime_error("Error\n"); 
	}

	return st.getTop();
}