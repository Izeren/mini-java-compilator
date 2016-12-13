#include "CConvertVisitor.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "../symbol_table/SymbolInfo.h"

//std::unordered_map<TOperation, std::string> operationNames = {}

CConvertVisitor::CConvertVisitor() {
	//lastVisited = 0;
}



//Expressions:
//-------------------------------------------------------------------------------------------------

void CConvertVisitor::Visit(CIdExp &exp) {
	this->code += exp.position.GetStringPosition();
	this->code += exp.name;
}

void CConvertVisitor::Visit(CIdPtrExp &exp) {
	this->code += exp.position.GetStringPosition();
	this->code += exp.name;
}

void CConvertVisitor::Visit(CNumExp &exp) {
	this->code += exp.position.GetStringPosition();
	this->code += std::to_string(exp.number);
}

void CConvertVisitor::Visit(COpExp &exp) {
	
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += exp.position.GetStringPosition();
	this->code += " " + COpExp::stringOperations[exp.operation] + " ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CLogExp &exp) {
	this->code += exp.position.GetStringPosition();
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
	this->code += exp.position.GetStringPosition();
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
	if (exp.array) {
		exp.array->Accept(*this);
	}
	this->code += ".length";
}

void CConvertVisitor::Visit(CGetFieldExp &exp) {
	if (exp.classOwner) {
		exp.classOwner->Accept(*this);
	}
	this->code += ".";
	if (exp.field) {
		exp.field->Accept(*this);
	}
}

void CConvertVisitor::Visit(CCallMethodExp &exp) {
	if (exp.classOwner) {
		exp.classOwner->Accept(*this);
	}
	this->code += ".";
	if (exp.methodName) {
		exp.methodName->Accept(*this);
	}
	this->code += "(";
	if (exp.args) {
		exp.args->Accept(*this);
	}
	this->code += ")";
}

void CConvertVisitor::Visit(CExpList &stm) {
    bool is_first_exp = true;
	if (stm.exps.size()) {
		for (int index = 0; index < stm.exps.size(); ++index) {
			if (stm.exps[index].get()) {
                if( is_first_exp) {
                    is_first_exp = false;
                } else {
                    this->code += ", ";
                }
				stm.exps[index].get()->Accept(*this);
			}
		}
	}
}

void CConvertVisitor::Visit(CNegativeExpression &exp) {
	this->code += "!(";
	if (exp.expression) {
		exp.expression->Accept(*this);
	}
	this->code += ")";
}

void CConvertVisitor::Visit(CArrayExpression &exp) {
	this->code += " new int[";
	if (exp.lengthExpression) {
		exp.lengthExpression->Accept(*this);
	}
	this->code += "]";
}

void CConvertVisitor::Visit(CNewIdentifier &exp) 
{
	this->code += "new ";
	if (exp.identifier){
		exp.identifier->Accept(*this);
	} 
	this->code += "()";
}

void CConvertVisitor::Visit(CThisExpression &exp) {
	this->code += "this.";
	if( exp.identifier ) {
		exp.identifier->Accept( *this );
	}
}

void CConvertVisitor::Visit(CByIndexExpression &exp)
{
	if (exp.identifier) {
		exp.identifier->Accept(*this);
	}
	this->code += "[";
	if (exp.indexExpression) {
		exp.indexExpression->Accept(*this);
	}
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
	this->code += ";\n";
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
	this->code += ";\n";
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
	this->code += ");\n";

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
	if (stm.isPrimitive) {
		this->code += CType::typeNames[stm.type] + " ";
	} else {
		stm.name->Accept(*this);
		this->code += " ";
	}
}

void CConvertVisitor::Visit(CField &stm) {
	if (stm.type) {
		stm.type->Accept(*this);
	}
	if (stm.id) {
		stm.id->Accept(*this);
	}
	this->code += ";\n";
}

void CConvertVisitor::Visit(CFieldList &stm) {
	if (stm.fields.size()) {
		for (int index = 0; index < stm.fields.size(); ++index) {
			if (stm.fields[index].get()) {
				stm.fields[index].get()->Accept(*this);
			}
		}
	}
}

void CConvertVisitor::Visit(CArgument &stm) {
	if (stm.type){
		stm.type->Accept(*this);
	}
	if (stm.id) {
		stm.id->Accept(*this);
	}
}

void CConvertVisitor::Visit(CArgumentList &stm) {
    bool is_first_argument = true;
	if (stm.arguments.size()) {
		for (int index = 0; index < stm.arguments.size(); ++index) {
			if (stm.arguments[index].get()) {
                if( is_first_argument) {
                    is_first_argument = false;
                } else {
                    this->code += ", ";
                }
				stm.arguments[index].get()->Accept(*this);
			}
		}
	}
}

void CConvertVisitor::Visit(CMethod &stm) {
	if (stm.isPublic) {
		this->code += "public ";
	} else {
		this->code += "private ";
	}
	stm.returnType->Accept(*this);
	stm.name->Accept(*this);
	this->code += "(";
	if (stm.arguments) {
		stm.arguments->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.vars) {
		stm.vars->Accept(*this);
	}
	if (stm.statements) {
		stm.statements->Accept(*this);
	}
	if (stm.returnExp) {
		this->code += "return ";
		stm.returnExp->Accept(*this);
		this->code += ";\n";
	}
	this->code += "}\n\n";
}

void CConvertVisitor::Visit(CMethodList &stm) {
	if (stm.methods.size()) {
		for (int index = 0; index < stm.methods.size(); ++index) {
			if (stm.methods[index].get()) {
				stm.methods[index].get()->Accept(*this);
			}
		}
	}
}

void CConvertVisitor::Visit(CClass &stm) {
	this->code += "class ";
	if (stm.id) {
		stm.id->Accept(*this);
	}
	if (stm.parentClass) {
		this->code += " extends ";
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
	if (stm.classes.size()) {
		for (int index = 0; index < stm.classes.size(); ++index) {
			if (stm.classes[index].get()) {
				stm.classes[index].get()->Accept(*this);
			}
		}
	}
}

void CConvertVisitor::Visit(CMainMethod &stm) {
	if (stm.returnType) {
		stm.returnType->Accept(*this);
	}
	this->code += "public static void main";
	this->code += "(String[] ";
	if (stm.args) {
		stm.args->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.vars) {
		stm.vars->Accept(*this);
	}
	if (stm.statements) {
		stm.statements->Accept(*this);
	}
	this->code += "}\n\n";
}

void CConvertVisitor::Visit(CMainClass &stm) {
	this->code += "class ";
	if (stm.id) {
		stm.id->Accept(*this);
	}
	this->code += " {\n";
	if (stm.mainMethod) {
		stm.mainMethod->Accept(*this);
	}
	this->code += "}\n\n";
}

void CConvertVisitor::Visit(CProgram &stm) {
	if (stm.mainClass) {
		stm.mainClass->Accept(*this);
	}
	if (stm.classList) {
		stm.classList->Accept(*this);
	}
}


std::string CConvertVisitor::GetResult() {
	return code;
}