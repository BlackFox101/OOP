#pragma once
#include <map>
#include <string>
#include <optional>

using namespace std;

enum class ParsingResult
{
	Number,
	Identifier,
	InvalidIdentifier
};

enum class OperandType
{
	Variable,
	Function
};

enum class Operation
{
	Plus = '+',
	Minus = '-',
	Multiply = '*', 
	Divide = '/'
};

struct Variable
{
	double number;
};

struct AdditionalFunctionOperand
{
	Operation operation;
	string identifier;
};

struct Function
{
	string id1;
	optional<Operation> operation;
	optional<string> id2;
};

enum class Command
{
	Var,
	Let,
	Function,
	Print,
	PrintVariables,
	PrintFunctions
};

class Calculator
{
public:
	Calculator(istream& input, ostream& output);

	optional<Command> GetCommand() const;
	bool PerformCommand(Command command);

	bool CreateVariable(const string& id);
	bool CreateFunction(const string& id1, const string& id2);
	bool AddVariableValue(const string& id1, const string& id2);

	void Print(const string& id) const;
	void PrintVariables() const;
	void PrintFunctions() const;

	optional<OperandType> IsIdExists(const string& id) const; // TODO переименовать
	bool IdentifierValidation(const string& str) const; // TODO статический 
	ParsingResult IdentifyId(const string& str, double& number) const; // TODO не понятный,
private:
	map<string, optional<Variable>> m_vars;
	map<string, Function> m_funcs;

	istream& m_input;
	ostream& m_output; 

	optional<double> GetVariableValue(const string& id) const;
	optional<Function> GetFunction(const string& id) const;
	optional<double> Calculate(optional<double> x, optional<double> y, Operation operation) const;
	bool DefiningOperator(const string& str, optional<Operation>& oper) const;
	bool AreIdsEqual(const string& id1, const string& id2) const;
	optional<double> CalculateFunction(const Function& function) const;
	optional<double> CalculateFunction(const string& id) const;
	bool CheckingIdsCorrectness(const string& id1, const string& id2) const;
};

