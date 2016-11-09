#include "CConvertVisitor.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

//std::unordered_map<TOperation, std::string> operationNames = {}

CConvertVisitor::CConvertVisitor() {
	//lastVisited = 0;
}



//Expressions:
//-------------------------------------------------------------------------------------------------

void CConvertVisitor::Visit(CIdExp &exp) {
	this->code += exp.name;
}

void CConvertVisitor::Visit(CIdPtrExp &exp) {
	this->code += exp.name;
}

void CConvertVisitor::Visit(CNumExp &exp) {
	this->code += std::to_string(exp.number);
}

void CConvertVisitor::Visit(COpExp &exp) {
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += " " + COpExp::stringOperations[exp.operation] + " ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CLogExp &exp) {
	if (exp.variable) {
		this->code += "true";
	}
	else {
		this->code += "false";
	}
}

void CConvertVisitor::Visit(CLogOpExp &exp) {
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += " " + exp.stringOperations[exp.operation] + " ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CCompExp &exp) {
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += " " + exp.stringOperations[exp.operation] + " ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CUnarMinusExp &exp) {
	this->code += "- ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CGetLengthExp &exp) {
	exp.array->Accept(*this);
	this->code += ".length";
}

void CConvertVisitor::Visit(CGetFieldExp &exp) {
	exp.classOwner->Accept(*this);
	this->code += "."
	exp.field->Accept(*this);
}

void CConvertVisitor::Visit(CCallMethodExp &exp) {
	exp.classOwner->Accept(*this);
	this->code += "."
	exp.methodName->Accept(*this);
	this->code += "("
	exp.args->Accept(*this);
	this->code += ")"
}

void CConvertVisitor::Visit(CExpList &exp) {
	exp.exp->Accept(*this);
	if (exp.expList) {
		exp.expList->Accept(*this);
	}
}

void CConvertVisitor::Visit(CNegativeExpression &exp) {
	this->code += "!(";
	exp.expression->Accept(*this);
	this->code += ")"
}

void CConvertVisitor::Visit(CArrayExpression &exp) {
	this->code += " new int[";
	exp.lengthExpression->Accept(*this);
	this->code += "]"
}

void CConvertVisitor::Visit(CThisExpression &exp) {
	this->code += "this";
}

void CConvertVisitor::Visit(CByIndexExpression &exp)
{
	exp.arrayExpression->Accept(*this);
	this->code += "[";
	exp.indexExpression->Accept(*this);
	this->code += "]";
}



//Statements:
//-------------------------------------------------------------------------------------------------

void CConvertVisitor::Visit(CAssignStm &stm) {
	if (stm.leftExpression) {
		stm.leftExpression->Accept(*this);
	}
	this->code += " = ";
	if (stm.rightExpression) {
		stm.rightExpression->Accept(*this);
	}
}

void CConvertVisitor::Visit(CAssignSubscriptStm &stm) {
	if (stm.idExpression) {
		stm.idExpression->Accept(*this);
	}
	this->code += "[";
	if (stm.offset) {
		stm.offset->Accept(*this);
	}
	this->code += "] = ";
	if (stm.valueExpression) {
		stm.valueExpression->Accept(*this);
	}
}

void CConvertVisitor::Visit(CCompoundStm &stm) {
	if (stm.leftStatement) {
		stm.leftStatement->Accept(*this);
	}
	if (stm.rightStatement) {
		stm.rightStatement->Accept(*this);
	}
}

void CConvertVisitor::Visit(CPrintStm &stm) {

	this->code += "System.out.println(";
	if (stm.expression) {
		stm.expression->Accept(*this);
	}
	this->code += ")";

}

void CConvertVisitor::Visit(CSimpleStm &stm) {
	if (stm.statement) {
		stm.statement->Accept(*this);
		this->code += ";\n";
	}
}

void CConvertVisitor::Visit(CIfStm &stm) {
	this->code += "if (";
	if (stm.conditionExpression) {
		stm.conditionExpression->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.positiveStatement) {
		stm.positiveStatement->Accept(*this);
	}
	this->code += "}\n";
	if (stm.negativeStatement) {
		this->code += "else {\n";
		stm.negativeStatement->Accept(*this);
		this->code += "}\n";
	}
}

void CConvertVisitor::Visit(CWhileStm &stm) {
	this->code += "while (";
	if (stm.conditionExpression) {
		stm.conditionExpression->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.statement) {
		stm.statement->Accept(*this);
	}
	this->code += "}\n";
}



//Classes:
//-------------------------------------------------------------------------------------------------

void CConvertVisitor::Visit(CType &stm) {
	this->code += stm.name  + " ";
}

void CConvertVisitor::Visit(CField &stm) {
	stm.type->Accept(*this);
	stm.id->Accept(*this);
	this->code += ";\n";
}

void CConvertVisitor::Visit(CFieldList &stm) {
	if (stm.field) {
		stm.field->Accept(*this);
	}
	if (stm.nextFields) {
		stm.nextFields->Accept(*this);
	}
}

void CConvertVisitor::Visit(CArgument &stm) {
	stm.type->Accept(*this);
	stm.id->Accept(*this);
	this->code += ";\n";
}

void CConvertVisitor::Visit(CArgumentList &stm) {
	if (stm.argument) {
		stm.argument->Accept(*this);
	}
	if (stm.nextArguments) {
		stm.nextArguments->Accept(*this);
	}
}

void CConvertVisitor::Visit(CMethod &stm) {
	if (stm.isPublic) {
		this->code += "public";
	} else {
		this->code += "private";
	}
	stm.returnType->Accept(*this);
	this->code += stm.name;
	this->code += "(";
	if (stm.arguments) {
		stm.arguments->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.statements) {
		stm.statements->Accept(*this);
	}
	this->code += "}\n\n";
}

void CConvertVisitor::Visit(CMethodList &stm) {
	if (stm.method) {
		stm.method->Accept(*this);
	}
	if (stm.nextMethods) {
		stm.nextMethods->Accept(*this);
	}
}

void CConvertVisitor::Visit(CClass &stm) {
	stm.id->Accept(*this);
	if (stm.parentClass) {
		this->code += " : ";
		stm.parentClass->Accept(*this);
	}
	this->code += " {\n";
	if (stm.fields) {
		stm.fields->Accept(*this);
	}
	if (stm.methods) {
		stm.methods->Accept(*this);
	}
	this->code += "}\n\n";
}

void CConvertVisitor::Visit(CClassList &stm) {
	if (stm.cclass) {
		stm.cclass->Accept(*this);
	}
	if (stm.nextClasses) {
		stm.nextClasses->Accept(*this);
	}
}

void CConvertVisitor::Visit(CMainMethod &stm) {
	stm.returnType->Accept(*this);
	this->code += "main";
	this->code += "(";
	if (stm.arguments) {
		stm.arguments->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.statements) {
		stm.statements->Accept(*this);
	}
	this->code += "}\n\n";
}

void CConvertVisitor::Visit(CMainClass &stm) {
	stm.id->Accept(*this);
	this->code += " {\n";
	if (stm.mainMethod) {
		stm.mainMethod->Accept(*this);
	}
	this->code += "}\n\n";
}

void CConvertVisitor::Visit(CProgram &stm) {
	stm.mainClass->Accept(*this);
	if (stm.classList) {
		stm.classList->Accept(*this);
	}
}


std::string CConvertVisitor::GetResult() {
	return code;
}