#include <iostream>
#include "Calculator.h"
#include <algorithm>
#include <cmath>
#include <regex>
#include <map>
#include <iomanip>

using namespace std;

Calculator::Calculator(istream& input, ostream& output) : m_input(input), m_output(output)
{
}

optional<Command> Calculator::GetCommand() const
{
	string str;
	m_input >> str;

	transform(str.begin(), str.end(), str.begin(), ::tolower);

	if (str == "var")
	{
		return Command::Var;
	}
	else if (str == "let")
	{
		return Command::Let;
	}
	else if (str == "fn")
	{
		return Command::Function;
	}
	else if (str == "print")
	{
		return Command::Print;
	}
	else if (str == "printvars")
	{
		return Command::PrintVariables;
	}
	else if (str == "printfns")
	{
		return Command::PrintFunctions;
	}

	return nullopt;
}

bool Calculator::PerformCommand(Command command)
{
	string str;
	string id1;
	string id2;
	switch (command)
	{
	case Command::Var:
		m_input >> str;
		return CreateVariable(str);
	case Command::Let:
		m_input >> str;

		if (str.find('=') == std::string::npos)
		{
			return false;
		}
		id1 = str.substr(0, str.find('='));
		id2 = str.substr(id1.length() + 1);
		if (id2.length() == 0)
		{
			m_output << "The second ID is not specified\n";
			return false;
		}
		return AddVariableValue(id1, id2);

	case Command::Function:
		m_input >> str;

		if (str.find('=') == std::string::npos)
		{
			return false;
		}
		id1 = str.substr(0, str.find('='));
		id2 = str.substr(id1.length() + 1);
		return CreateFunction(id1, id2);

	case Command::Print:
		m_input >> str;
		Print(str);
		break;
	case Command::PrintVariables:
		PrintVariables();
		break;
	case Command::PrintFunctions:
		PrintFunctions();
		break;
	default:
		break;
	}

	return true;
}

bool Calculator::AddVariableValue(const string& id1, const string& id2)
{
	if (!IsIdExists(id1))
	{
		CreateVariable(id1);
	}

	double number;
	ParsingResult ParsingResult = IdentifyId(id2, number);

	switch (ParsingResult)
	{
	case ParsingResult::Number:
		m_vars[id1] = { number };
		m_output << "The variable was successfully assigned a new value!\n";
		break;
	case ParsingResult::Identifier:
		if (!IdentifierValidation(id2))
		{
			m_output << "Invalid argument\n";
			return false;
		}
		auto isExist = IsIdExists(id2);
		if (isExist)
		{
			if (isExist == OperandType::Variable)
			{
				m_vars[id1] = m_vars[id2];
			}
			else
			{
				auto tempNumber = CalculateFunction(id2);
				m_vars[id1] = { *tempNumber };
			}

			m_output << "Variable changed successfully!\n";
			return true;
		}

		return false;
	}

	return true;
}

ParsingResult Calculator::IdentifyId(const string& str, double& number) const
{
	size_t pos;
	try
	{
		number = stod(str, &pos);
		if (pos != str.length())
		{
			return ParsingResult::Identifier;
		}
		return ParsingResult::Number;
	}
	catch (const invalid_argument&)
	{
		return ParsingResult::Identifier;;
	}
}

bool Calculator::CreateVariable(const string& id)
{
	if (!IdentifierValidation(id))
	{
		m_output << "Invalid argument'" << id << "'\n";
		return false;
	}
	if (IsIdExists(id))
	{
		m_output << "This identifier '" << id << "' already exists!\n";
		return false;
	}
	m_vars[id] = nullopt;
	m_output << "Variable saved successfully!\n";

	return true;
}

bool Calculator::IdentifierValidation(const string& str) const
{
	smatch result;
	regex regular("^[^0-9][A-Za-z0-9_]*");

	return regex_match(str, result, regular);
}

optional<OperandType> Calculator::IsIdExists(const string& id) const
{
	if (m_vars.find(id) != m_vars.end())
	{
		return OperandType::Variable;
	}
	if (m_funcs.find(id) != m_funcs.end())
	{
		return OperandType::Function;
	}

	return nullopt;
}

void Calculator::Print(const string& id) const
{
	if (m_vars.find(id) != m_vars.end())
	{
		optional<Variable> value = m_vars.at(id);

		if (value)
		{
			m_output << fixed << setprecision(2) << value->number << endl;;
		}
		else
		{
			m_output << "nan" << endl;
		}

		return;
	}

	if (m_funcs.find(id) != m_funcs.end())
	{
		auto value = CalculateFunction(m_funcs.at(id));
		if (value)
		{
			m_output << fixed << setprecision(2) << *value << endl;;
		}
		else
		{
			m_output << "nan" << endl;
		}
		return;
	}

	m_output << "This ID does not exist\n";
}

bool Calculator::DefiningOperator(const string& str, optional<Operation>& oper) const
{
	if (str.find('+') != std::string::npos)
	{
		oper = Operation::Plus;
		return true;
	}
	if (str.find('-') != std::string::npos)
	{
		oper = Operation::Minus;
		return true;
	}
	if (str.find('*') != std::string::npos)
	{
		oper = Operation::Multiply;
		return true;
	}
	if (str.find('/') != std::string::npos)
	{
		oper = Operation::Divide;
		return true;
	}

	oper = nullopt;
	return false;
}

bool Calculator::CheckingIdsCorrectness(const string& id1, const string& id2) const
{
	if (!IdentifierValidation(id2))
	{
		m_output << "Invalid argument '" << id2 << "'\n";
		return false;
	}
	if (!IsIdExists(id2))
	{
		m_output << "This identifier '" << id2 << "' is not exists!\n";
		return false;
	}

	return !AreIdsEqual(id1, id2);
}

bool Calculator::CreateFunction(const string& id1, const string& id2)
{
	if (!IdentifierValidation(id1))
	{
		m_output << "Invalid argument!\n";
		return false;
	}
	if (IsIdExists(id1))
	{
		m_output << "This identifier already exists!\n";
		return false;
	}

	optional<Operation> operation;
	if (DefiningOperator(id2, operation))
	{
		string tempId1 = id2.substr(0, id2.find((char)*operation));
		if (!CheckingIdsCorrectness(id1, tempId1))
		{
			return false;
		}

		string tempId2 = id2.substr(tempId1.length() + 1);
		if (!CheckingIdsCorrectness(id1, tempId2))
		{
			return false;
		}

		m_funcs[id1] = { tempId1, operation,  tempId2 };
		m_output << "Function saved successfully!\n";
	}
	else
	{
		if (!CheckingIdsCorrectness(id1, id2))
		{
			return false;
		}

		m_funcs[id1] = { id2, operation,  nullopt };
		m_output << "Function saved successfully!\n";
	}

	return true;
}

bool Calculator::AreIdsEqual(const string& id1, const string& id2) const
{
	if (id1 == id2)
	{
		m_output << "You can't assign a function to itself!\n";
		return true;
	}

	return false;
}

void Calculator::PrintVariables() const
{
	if (m_vars.empty())
	{
		m_output << "The list of functions is empty\n";
	}
	for (auto& it : m_vars)
	{
		m_output << it.first << ":";
		if (it.second)
		{
			m_output << fixed << setprecision(2) << it.second->number << endl;
		}
		else
		{
			m_output << "nan" << endl;
		}
	}
}

void Calculator::PrintFunctions() const
{
	if (m_funcs.empty())
	{
		m_output << "The list of functions is empty\n";
	}
	for (auto& it : m_funcs)
	{
		auto value = CalculateFunction(m_funcs.at(it.first));

		m_output << it.first << ":";
		m_output << fixed << setprecision(2) << *value << endl;
	}
}

optional<double> Calculator::CalculateFunction(const Function& function) const
{
	if (!function.operation)
	{
		return CalculateFunction(function.id1);
	}

	return Calculate(CalculateFunction(function.id1), CalculateFunction(*function.id2), *function.operation);
}

optional<double> Calculator::CalculateFunction(const string& id) const
{
	auto value = IsIdExists(id);
	if (value && value == OperandType::Variable)
	{
		return GetVariableValue(id);
	}

	return CalculateFunction(*GetFunction(id));
}

optional<double> Calculator::GetVariableValue(const string& id) const
{
	if (m_vars.find(id) != m_vars.end())
	{
		auto number = m_vars.at(id);
		if (number)
		{
			return number->number;
		}
		return nullopt;
	}
	
	return nullopt;
}

optional<Function> Calculator::GetFunction(const string& id) const
{
	if (m_funcs.find(id) != m_funcs.end())
	{
		return m_funcs.at(id);
	}

	return nullopt;
}

optional<double> Calculator::Calculate(optional<double> x, optional<double> y, Operation operation) const
{
	if (!x || !y)
	{
		return nullopt;
	}

	switch (operation)	
	{
	case Operation::Plus:
		return *x + *y;
	case Operation::Minus:
		return *x - *y;
	case Operation::Multiply:
		return *x * *y;
	case Operation::Divide:
		return *x / *y;
	}
}