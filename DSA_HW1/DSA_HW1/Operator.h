#ifndef _OPERATOR_HEADER_INCLUDED_
#define _OPERATOR_HEADER_INCLUDED_

struct Operator
{
	Operator()
		: m_symbol('\0')
		, m_op('\0')
		, m_assoc('\0')
	{}

	Operator(char symbol, char op, char assoc)
		: m_symbol(symbol)
		, m_op(op)
		, m_assoc(assoc)
	{}

	char m_symbol;
	char m_op;
	char m_assoc;
};

#endif // !_OPERATOR_HEADER_INCLUDED_


