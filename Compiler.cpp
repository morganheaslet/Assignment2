#include "Compiler.h"

Compiler::Compiler()
{
	listLocation = 0;
}

Compiler::Compiler(std::string inputFileName, std::string outputFileName)
{
	outputFile = outputFileName;
	inputFile = inputFileName;
}

void Compiler::CreateTokenList()
{
	std::fstream iFile;
	std::string sourceString;
	Token tempToken;
	Lexer ourLexer;

	iFile.open(inputFile);

	if (!iFile.is_open())
	{
		std::cout << "File not found.\n";
	}
	else
	{
		while (!iFile.eof())
		{
			if (ourLexer.lineEmpty())
			{
				getline(iFile, sourceString);
				ourLexer.getLine(sourceString);
			}

			tempToken = ourLexer.getToken();
			ourLexer.clearToken();

			if (tempToken.getLexeme() != "")
			{
				tokenList.push_back(tempToken);
				tempToken.changeLexeme("");
				tempToken.changeType(UNKNOWN);
			}			
		}
	}
}

void Compiler::ParseTokenList()
{
	//oFile.open(outputFile, std::ios_base::app);
	oFile.open(outputFile);
	iter = tokenList.begin();

	Rat18F();
}

void Compiler::OutputTokenList()
{
	Token tempToken;
	for (iter = tokenList.begin(); iter != tokenList.end(); iter++)
	{
		std::cout << iter->getLexeme() << " " << iter->GetTypeString() << std::endl;
	}
}

void Compiler::Rat18F()
{
	if (printFunctions)
		oFile << "\t<Opt Function Definitions>   $$  <Opt Declaration List>  <Statement List>  $$\n";

		while (iter->getLexeme() != "$$")
		{
			oFile << iter->printToken();
			OptFuncDef();
		}
		iter++;
		oFile << iter->printToken();
		OptDeclarationList();
		StatementList();

		if (iter->getLexeme() == "$$")
			oFile << "\tSuccessfully parsed.";
		else
			Error("Rat18F");
}

void Compiler::OptFuncDef()
{
	if (printFunctions)
		oFile << "\t<Function Definitions>     |  <Empty>\n";

	if (iter->getLexeme() == "function")
		FuncDef();
}

void Compiler::FuncDef()
{
	if (printFunctions)
		oFile << "\t<Function> | <Function> <Function Definitions>\n";
	
	while (iter->getLexeme() == "function")
	{
		iter++;
		oFile << iter->printToken();
		Function();
	}
}

void Compiler::Function()
{
	if (printFunctions)
		oFile << "\tfunction  <Identifier>(<Opt Parameter List>)  <Opt Declaration List>  <Body>\n";

	oFile << iter->printToken();
	if (iter->GetTypeString() == "IDENTIFIER")
	{
		iter++;
		oFile << iter->printToken();
		if (iter->getLexeme() == "(")
		{
			iter++;
			oFile << iter->printToken();
			OptParameterList();

			if (iter->getLexeme() != ")")
				Error("Function");
			else
			{
				iter++;
				oFile << iter->printToken();
			}
		}		
		
		if(iter->getLexeme() == "int" || iter->getLexeme() == "real" || iter->getLexeme() == "boolean")
			OptDeclarationList();

		if (iter->getLexeme() == "{")
			Body();
		else
			Error("Function");
	}
	else
		Error("Function");
}

void Compiler::OptParameterList()
{
	if (printFunctions)
		oFile << "\t<Parameter List> | <Empty>\n";
	
	if (iter->GetTypeString() == "IDENTIFIER")
	{
		ParameterList();
	}
}
void Compiler::ParameterList()
{
	if (printFunctions)
		oFile << "\t<Parameter>    |     <Parameter> , <Parameter List>\n";

	Parameter();
	
	if (iter->GetTypeString() == "IDENTIFIER")
		ParameterList();
}
void Compiler::Parameter()
{
	if (printFunctions)
		oFile << "\t<IDs > : <Qualifier> \n";

	while (iter->GetTypeString() == "IDENTIFIER")
	{
		IDs();
	}

	if (iter->getLexeme() == ":")
	{
		iter++;
		oFile << iter->printToken();
		if (iter->getLexeme() == "int" || iter->getLexeme() == "boolean" || iter->getLexeme() == "real")
			Qualifier();
		else
			Error("Parameter");
	}	
	else
		Error("Parameter");
}
void Compiler::Qualifier()
{
	if (printFunctions)
		oFile << "\tint     |    boolean    |  real \n";
	current_type = iter->getLexeme();
	iter++;
	oFile << iter->printToken();
}
void Compiler::Body()
{
	if (printFunctions)
		oFile << "\t{  < Statement List>  }\n";

	iter++;
	oFile << iter->printToken();
	iter->printToken();
	
	while (iter->getLexeme() != "}")
	{
		StatementList();
	}
	iter++;
	oFile << iter->printToken();
}
void Compiler::OptDeclarationList()
{
	if (printFunctions)
		oFile << "\t<Declaration List>   |    <Empty>\n";

	if (iter->getLexeme() == "int" || iter->getLexeme() == "boolean" || iter->getLexeme() == "real")
		DeclarationList();
}
void Compiler::DeclarationList()
{
	if (printFunctions)
		oFile << "\t<Declaration> ;     |      <Declaration> ; <Declaration List>\n";

	while (iter->getLexeme() == "int" || iter->getLexeme() == "boolean" || iter->getLexeme() == "real")
	{
		Declaration();
		if (iter->getLexeme() == ";")
		{
			iter++;
			oFile << iter->printToken();
		}
		else
			Error("DeclarationList");

	}
}
void Compiler::Declaration()
{
	if (printFunctions)
		oFile << "\t<Qualifier > <IDs>    \n";

	if (iter->getLexeme() == "int" || iter->getLexeme() == "boolean" || iter->getLexeme() == "real")
		Qualifier();
	else
		Error("Declaration");

	if (iter->GetTypeString() == "IDENTIFIER")
		IDs();
	else
		Error("Declaration");
}
void Compiler::IDs()
{
	if (printFunctions)
		oFile << "\t<Identifier>    | <Identifier>, <IDs>\n";

	if (iter->GetTypeString() == "IDENTIFIER")
	{
		iter->setType( current_type );
		get_address(*iter);
		iter++;
		oFile << iter->printToken();
		IDs();
	}
}
void Compiler::StatementList()
{
	if (printFunctions)
		oFile << "\t<Statement>   | <Statement> <Statement List> \n";


	Statement();

	if(iter->getLexeme() == "{" || iter->GetTypeString() == "IDENTIFIER" || iter->getLexeme() == "If" || iter->getLexeme() == "return"
		|| iter->getLexeme() == "put" || iter->getLexeme() == "get" || iter->getLexeme() == "while")
	{
		StatementList();
	}
}
void Compiler::Statement()
{
	if (printFunctions)
		oFile << "\t<Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While>\n";

	if (iter->getLexeme() == "{")
		Compound();
	else if (iter->GetTypeString() == "IDENTIFIER")
		Assign();
	else if (iter->getLexeme() == "if")
		If();
	else if (iter->getLexeme() == "return")
		Return();
	else if (iter->getLexeme() == "put")
		Print();
	else if (iter->getLexeme() == "get")
		Scan();
	else if (iter->getLexeme() == "while")
		While();
	else
		Error("Statement");
} 
void Compiler::Compound()
{
	if (printFunctions)
		oFile << "\t {  <Statement List>  } \n";

	iter++;
	oFile << iter->printToken();

	StatementList();
	
	if (iter->getLexeme() == "}")
		iter++;
	else
		Error("Compound");
}
void Compiler::Assign()
{
	if (printFunctions)
		oFile << "\t<Identifier> = <Expression> ;\n";
	//saved token
	Token saved_token = *iter;

	iter++;
	if (iter->getLexeme() == "=")
	{
		iter++;
		oFile << iter->printToken();
		Expression();
		get_instr("POPM", std::to_string(get_address(saved_token)) );
	}
	else
		Error("Assign");

	if (iter->getLexeme() == ";")
	{
		iter++;
		oFile << iter->printToken();
	}
	else
		Error("Assign");
}
void Compiler::If()
{
	if (printFunctions)
		oFile << "\tif  ( <Condition>  ) <Statement>   ifend    |	if (<Condition>) <Statement>   else  <Statement>  ifend \n";

	current_address = current_instruction_address;
	iter++;
	oFile << iter->printToken();

	if (iter->getLexeme() == "(")
	{
		iter++;
		oFile << iter->printToken();
		Condition();
		
		if (iter->getLexeme() != ")")
			Error("If");
		else
		{
			Statement();
			back_patch(current_instruction_address);
			if (iter->getLexeme() != "ifend" || iter->getLexeme() != "else")
				Error("If");
			else
			{
				if (iter->getLexeme() == "else")
				{
					iter++;
					oFile << iter->printToken();
					Statement();
				}
			}
		}
	}
	else
		Error("If");
	oFile << iter->printToken();

}
void Compiler::Return()
{
	if (printFunctions)
		oFile << "\treturn ; |  return <Expression> ;\n";

	iter++;
	oFile << iter->printToken();

	if (iter->getLexeme() == ";")
	{
		iter++;
		oFile << iter->printToken();
	}
	else if (iter->GetTypeString() == "IDENTIFIER" || iter->GetTypeString() == "REAL" || iter->GetTypeString() == "DIGIT"
		|| iter->getLexeme() == "true" || iter->getLexeme() == "false" || iter->getLexeme() == "(")
	{
		Expression();
	}
	else
		Error("Return");

	if (iter->getLexeme() == ";")
	{
		iter++;
		oFile << iter->printToken();
	}
	else
		Error("Return");
}
void Compiler::Print()
{
	if (printFunctions)
		oFile << "\tput ( <Expression>);\n";
	get_instr("STDOUT", "NULL");
	iter++;
	oFile << iter->printToken();
	if (iter->getLexeme() == "(")
	{
		iter++;
		oFile << iter->printToken();
		Expression();
	}
	else
		Error("Print");

	if (iter->getLexeme() != ")")
		Error("Print");

	iter++;
	oFile << iter->printToken();

	if (iter->getLexeme() != ";")
		Error("Print");

	iter++;
	oFile << iter->printToken();
}
void Compiler::Scan()
{
	if (printFunctions)
		oFile << "\tget ( <IDs> );\n";
	get_instr("STDIN", "NULL");
	iter++;
	oFile << iter->printToken();

	if (iter->getLexeme() == "(")
	{
		iter++;
		oFile << iter->printToken();
		get_instr("POPM", std::to_string(get_address(*iter)) );
		IDs();
	}
	else
		Error("Scan");

	if (iter->getLexeme() != ")")
		Error("Scan");

	iter++;
	oFile << iter->printToken();


	if (iter->getLexeme() != ";")
		Error("Scan");

	iter++;
	oFile << iter->printToken();

}
void Compiler::While()
{
	if (printFunctions)
		oFile << "\twhile ( <Condition>  )  <Statement>  whileend\n";
	if (printFunctions)
		oFile << "\tENTERING WHILE";

	current_address = current_instruction_address;
	get_instr("LABEL", "NULL");

	iter++;
	oFile << iter->printToken();
	if (iter->getLexeme() == "(")
	{
		iter++;
		oFile << iter->printToken();
		Condition();
	}
	else
		Error("While");

	if (iter->getLexeme() != ")")
		Error("While");

	iter++;
	oFile << iter->printToken();
	Statement();
	get_instr("JUMP", std::to_string(current_address));
	back_patch(current_instruction_address);


	if (iter->getLexeme() != "whileend")
		Error("While");

	iter++;
	oFile << iter->printToken();
}
void Compiler::Condition()
{
	if (printFunctions)
		oFile << "\t<Expression>  <Relop>   <Expression>\n";

	if (iter->GetTypeString() == "IDENTIFIER" || iter->GetTypeString() == "DIGIT" || iter->GetTypeString() == "REAL" ||
		iter->getLexeme() == "true" || iter->getLexeme() == "false")
	{
		Expression();
	}
	else
		Error("Condition");

	if (iter->GetTypeString() == "OPERATOR")
		Relop();
	else
		Error("Condition");

	if (iter->GetTypeString() == "IDENTIFIER" || iter->GetTypeString() == "DIGIT" || iter->GetTypeString() == "REAL" ||
		iter->getLexeme() == "true" || iter->getLexeme() == "false")
	{
		Expression();
	}
	else
		Error("Condition");
}
void Compiler::Relop()
{
	if (printFunctions)
		oFile << "\t==   |   ^=    |   >     |   <    |   =>    |   =<  \n";
	std::string op = iter->getLexeme();
	iter++;
	get_instr("PUSHM", std::to_string(get_address(*iter)));
	iter--;
	if (op == "==") {
		get_instr("EQU", "NULL");
		jump_stack.push(current_instruction_address);
		get_instr("JUMPZ", "NULL");
	}
	else if (op == "^=") {
		get_instr("NEQ", "NULL");
		jump_stack.push(current_instruction_address);
		get_instr("JUMPZ", "NULL");
	}
	else if (op == ">") {
		get_instr("GRT", "NULL");
		jump_stack.push(current_instruction_address);
		get_instr("JUMPZ", "NULL");
	}
	else if (op == "<") {
		get_instr("LES", "NULL");
		jump_stack.push(current_instruction_address);
		get_instr("JUMPZ", "NULL");
	}
	else if (op == "=>") {
		get_instr("GEQ", "NULL");
		jump_stack.push(current_instruction_address);
		get_instr("JUMPZ", "NULL");
	}
	else if (op == "=<") {
		get_instr("LEQ", "NULL");
		jump_stack.push(current_instruction_address);
		get_instr("JUMPZ", "NULL");
	}


	iter++;
	oFile << iter->printToken();
}
void Compiler::Expression()
{
	if (printFunctions)
		oFile << "\t<Expression> + <Term>    | <Expression>  - <Term>    |    <Term>\n";

	while (iter->GetTypeString() == "IDENTIFIER" || iter->GetTypeString() == "DIGIT" || iter->GetTypeString() == "REAL" ||
		iter->getLexeme() == "true" || iter->getLexeme() == "false" || iter->getLexeme() == "+" || iter->getLexeme() == "-"
		|| iter->getLexeme() == "(")
	{
		if (iter->getLexeme() == "+")
		{
			iter++;
			oFile << iter->printToken();
			get_instr("ADD", "NULL");
		}
		else if (iter->getLexeme() == "-")
		{
			iter++;
			oFile << iter->printToken();
			get_instr("SUB", "NULL");
		}
		else
			Term();
	}
}
void Compiler::Term()
{
	if (printFunctions)
		oFile << "\t<Term>  *  <Factor>     |   <Term>  /  <Factor>     |     <Factor>\n";

	while (iter->GetTypeString() == "IDENTIFIER" || iter->GetTypeString() == "DIGIT" || iter->GetTypeString() == "REAL" ||
		iter->getLexeme() == "true" || iter->getLexeme() == "false" || iter->getLexeme() == "*" || iter->getLexeme() == "/"
		|| iter->getLexeme() == "(")
	{
		if (iter->getLexeme() == "*")
		{

			iter++;
			oFile << iter->printToken();
			get_instr("MUL", "NULL");
		}
		else if(iter->getLexeme() == "/")
		{

			iter++;
			oFile << iter->printToken();
			get_instr("DIV", "NULL");
		}
		else
			Factor();
	}
}
void Compiler::Factor()
{
	if (printFunctions)
		oFile << "\t<Primary>    |    <Primary>\n";

	Primary();
}
void Compiler::Primary() 
{
	if (printFunctions)
		oFile << "\t<Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |   <Real> | true | false \n";
	
	if (iter->getLexeme() == "(")
	{
		iter++;
		Expression();
		if (iter->getLexeme() == ")")
		{
			iter++;
			oFile << iter->printToken();
		}
		else
			Error("Primary");
	}
	else if (iter->GetTypeString() == "DIGIT" || iter->GetTypeString() == "REAL" || iter->getLexeme() == "true" ||
		iter->getLexeme() == "false")
	{
		if (iter->GetTypeString() == "DIGIT")
			get_instr("PUSHI", iter->getLexeme());
		iter++;
		oFile << iter->printToken();
	}
	else if (iter->GetTypeString() == "IDENTIFIER")
	{
		if (iter->getLexeme() == "(")
		{
			IDs();
			if (iter->getLexeme() == ")")
			{
				iter++;
				oFile << iter->printToken();
			}
			else
				Error("Primary");
		}
		else
		{
			
			iter++;
			oFile << iter->printToken();
		}
	}
	else
		Error("Primary");
}
void Compiler::Empty()
{
	if (printFunctions)
		oFile << "\n";
}
void Compiler::Error(std::string error)
{
	if (printFunctions) 
	{
		oFile << "ERROR - INVALID SYNTAX\n";
		oFile << iter->printToken();
		oFile << "thas caused an error on line " << iter->getLineNum() << ".\n";
	}
}

void Compiler::PrintInstructionTable() 
{
	int size = instructionTable.size();

	oFile << "\nADDRESS\tOP\tOPERAND\n";
	for (int i = 0; i < size; i++) 
	{
		oFile << instructionTable[i].address << "\t" << instructionTable[i].op << "\t";
		if (instructionTable[i].oprnd != "NULL")
			oFile << instructionTable[i].oprnd << "\n";
		else
			oFile << "\n";
	}
}

void Compiler::PrintSymbolTable() 
{
	int size = symbolTable.size();

	oFile << "\nIDENTIFIER\tMEMORY LOCATION\tTYPE\n";
	for (int i = 0; i < size; i++)
	{
		oFile << symbolTable[i].identifier << "\t\t"
			<< symbolTable[i].memoryLocation << "\t"
			<< symbolTable[i].type << "\n";
	}
}

void Compiler::get_instr(std::string op, std::string oprnd)
{
	Instruction_Table currentInstruction;
	currentInstruction.address = current_instruction_address;
	currentInstruction.op = op;
	currentInstruction.oprnd = oprnd;
	instructionTable.push_back(currentInstruction);
	current_instruction_address++;
}

int Compiler::get_address(Token thisToken) 
{
	std::string identifier = thisToken.getLexeme();
	int size = symbolTable.size();
	int location = 0;
	for (int i = 0; i < size; i++) 
	{
		if (identifier == symbolTable[i].identifier)
			location = symbolTable[i].memoryLocation;
	}
	if (location == 0) {
		Symbol newSymbol;
		newSymbol.identifier = thisToken.getLexeme();
		newSymbol.memoryLocation = current_memory_location;
		newSymbol.type = thisToken.getSymbolType();

		symbolTable.push_back(newSymbol);
		location = current_memory_location;
		current_memory_location++;

		return location;
	}
	else {
		return location;
	}
}

void Compiler::back_patch(int instr_address) 
{
	int patch_address = jump_stack.top();
	jump_stack.pop();
	instructionTable[patch_address-1].oprnd = std::to_string(instr_address);

}
