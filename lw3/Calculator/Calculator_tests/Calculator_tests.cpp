#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Calculator/Calculator.h"

using namespace std;

SCENARIO("Id validation")
{
	ostringstream output;
	Calculator calc(cin, output);
	CHECK(calc.IdentifierValidation("") == false);
	CHECK(calc.IdentifierValidation("1") == false);
	CHECK(calc.IdentifierValidation("A1") == true);
	CHECK(calc.IdentifierValidation("_abc1") == true);
	CHECK(calc.IdentifierValidation("abc_") == true);
	CHECK(calc.IdentifierValidation("a") == true);
}

SCENARIO("GetCommand")
{
	ostringstream output;

	WHEN("var")
	{
		std::istringstream input("var\n");
		Calculator calc(input, output);
		optional<Command> command = calc.GetCommand();
		REQUIRE(command);
		CHECK(*command == Command::Var);
	}
	WHEN("let")
	{
		std::istringstream input("let\n");
		Calculator calc(input, output);
		optional<Command> command = calc.GetCommand();
		REQUIRE(command);
		CHECK(*command == Command::Let);
	}
	WHEN("fn")
	{
		std::istringstream input("fn\n");
		Calculator calc(input, output);
		optional<Command> command = calc.GetCommand();
		REQUIRE(command);
		CHECK(*command == Command::Function);
	}
	WHEN("print")
	{
		std::istringstream input("print\n");
		Calculator calc(input, output);
		optional<Command> command = calc.GetCommand();
		REQUIRE(command);
		CHECK(*command == Command::Print);
	}
	WHEN("printvars")
	{
		std::istringstream input("printvars\n");
		Calculator calc(input, output);
		optional<Command> command = calc.GetCommand();
		REQUIRE(command);
		CHECK(*command == Command::PrintVariables);
	}
	WHEN("printfns")
	{
		std::istringstream input("printfns\n");
		Calculator calc(input, output);
		optional<Command> command = calc.GetCommand();
		REQUIRE(command);
		CHECK(*command == Command::PrintFunctions);
	}
}

SCENARIO("AddVariable and IsIdExists")
{
	ostringstream output;
	istringstream input;
	Calculator calc(input, output);
	CHECK(calc.CreateVariable("abc") == true);
	CHECK(calc.IsIdExists("abc") != nullopt);

	WHEN("This id invalid")
	{
		CHECK(calc.CreateVariable("1abc") == false);
	}
	WHEN("This id exists")
	{
		CHECK(calc.CreateVariable("abc") == false);
	}
}

SCENARIO("AddFunction and IsIdExists")
{
	istringstream input;
	ostringstream output;
	Calculator calc(input, output);
	calc.AddVariableValue("ABCD", "1");
	CHECK(calc.CreateFunction("abc", "ABCD") == true);
	CHECK(calc.IsIdExists("abc") != nullopt);

	WHEN("This id1 invalid")
	{
		CHECK(calc.CreateFunction("1abc", "abc") == false);
	}
	WHEN("This id2 invalid")
	{
		CHECK(calc.CreateFunction("abc1", "1abc") == false);
	}
	WHEN("This id exists")
	{
		CHECK(calc.CreateFunction("abc", "asd2") == false);
	}
	WHEN("id1 == id2")
	{
		CHECK(calc.CreateFunction("abc1", "abc1") == false);
	}

	WHEN("APlusB=a+b -> right")
	{
		calc.AddVariableValue("a", "1");
		calc.AddVariableValue("b", "2");
		CHECK(calc.CreateFunction("APlusB", "a+b") == true);
	}
}

SCENARIO("ParsingId")
{
	ostringstream output;
	double number;
	Calculator calc(cin, output);
	CHECK(calc.IdentifyId("abc", number) == ParsingResult::Identifier);
	CHECK(calc.IdentifyId("12.00", number) == ParsingResult::Number);
	CHECK(number == 12.00);
}

SCENARIO("AddVariableValue")
{
	WHEN("Variable not created")
	{
		ostringstream output;
		Calculator calc(cin, output);
		REQUIRE(calc.AddVariableValue("abc", "1"));
		calc.PrintVariables();
		CHECK(output.str() == "Variable saved successfully!\n"
			"The variable was successfully assigned a new value!\n"
			"abc:1.00\n");
	}
	WHEN("Variable was created")
	{
		ostringstream output;
		Calculator calc(cin, output);
		REQUIRE(calc.AddVariableValue("abc", "1"));
		REQUIRE(calc.AddVariableValue("abc", "50"));
		calc.PrintVariables();
		CHECK(output.str() == "Variable saved successfully!\n"
			"The variable was successfully assigned a new value!\n"
			"The variable was successfully assigned a new value!\n"
			"abc:50.00\n");
	}
	WHEN("Assign a function value to a variable")
	{
		ostringstream output;
		Calculator calc(cin, output);
		REQUIRE(calc.AddVariableValue("a", "1"));
		REQUIRE(calc.AddVariableValue("b", "1"));
		calc.CreateFunction("APlusB", "a+b");
		REQUIRE(calc.AddVariableValue("ab", "APlusB"));
		calc.Print("ab");
		CHECK(output.str() == "Variable saved successfully!\n"
			"The variable was successfully assigned a new value!\n"
			"Variable saved successfully!\n"
			"The variable was successfully assigned a new value!\n"
			"Function saved successfully!\n"
			"Variable saved successfully!\n"
			"Variable changed successfully!\n"
			"2.00\n");
	}
}