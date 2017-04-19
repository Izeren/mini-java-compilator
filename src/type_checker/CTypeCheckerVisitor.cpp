#include "CTypeCheckerVisitor.h"
#include "../symbol_table/SymbolInfo.h"
#include "../shared_ptrs_nodes/Statements.h"
#include "../shared_ptrs_nodes/Expressions.h"
#include "../shared_ptrs_nodes/Classes.h"
#include <exception>
#include <iostream>



std::vector<std::unordered_map<std::string, std::shared_ptr<VariableInfo>>*> CTypeCheckerVisitor::getSuperFields() {
    std::vector<std::unordered_map<std::string, std::shared_ptr<VariableInfo>>*> superFields;

    std::string super = currentClass->baseClass;
    while (super != "") {
        ClassInfo* superClass = table->classes[super].get();
        std::unordered_map<std::string, std::shared_ptr<VariableInfo>>* fields = &superClass->fields->variables;
        superFields.push_back(fields);

        super = superClass->baseClass;
    }

    return superFields;
};

//bool -- isLocalVariable
std::pair<VariableInfo*, bool> CTypeCheckerVisitor::getVariableInfo(CIdExp& exp) {
    std::pair<VariableInfo*, bool> errorResult(nullptr, false);

    if (exp.isInstance) {
        bool isLocalVariable = false;
        VariableInfo* variableInfoPtr = nullptr;

        if (!currentClass || !currentMethod) {
            return errorResult;
        }

        auto classFieldIterator = currentClass->fields->variables.find(exp.name);
        if (classFieldIterator != currentClass->fields->variables.end()) {
            variableInfoPtr = classFieldIterator->second.get();
        } else {
            auto superFields = getSuperFields();
            for (int i = 0; i < superFields.size(); ++i) {
                auto it = superFields[i]->find(exp.name);
                if (it != superFields[i]->end()) {
                    variableInfoPtr = it->second.get();
                    break;
                }
            }
        }

        auto methodArgumentIterator = currentMethod->arguments->variables.find(exp.name);
        if (methodArgumentIterator != currentMethod->arguments->variables.end()) {
            variableInfoPtr = methodArgumentIterator->second.get();
        }

        auto methodVariableIterator = currentMethod->fields->variables.find(exp.name);
        if (methodVariableIterator != currentMethod->fields->variables.end()) {
            variableInfoPtr = methodVariableIterator->second.get();
            isLocalVariable = true;
        }

        //success
        return std::pair<VariableInfo*, bool>(variableInfoPtr, isLocalVariable);
    } else {
        return errorResult;
    }
}

//Expressions visit methods
//---------------------------------------------------------------------------------------

void CTypeCheckerVisitor::Visit( CIdExp &exp ) 
{
    std::cout << "typechecker: cidexp\n";

    if (exp.isInstance) {
        std::pair<VariableInfo*, bool> variableInfo = getVariableInfo(exp);

        bool isLocalVariable = variableInfo.second;
        VariableInfo* variableInfoPtr = variableInfo.first;

        if (variableInfoPtr == nullptr) {
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            errors.push_back(CError(CError::GetUndeclaredVariableErrorMessage(exp.name), exp.position));
            return;
        }

        if (isLocalVariable && exp.isInstance && !variableInfoPtr->isInitialized) {
            errors.push_back( CError(CError::GetNotInitializedVariableErrorMessage(exp.name), exp.position) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        }

        //success
        lastCalculatedType = *variableInfoPtr->type;
    } else {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    }
}

//unused class for now
void CTypeCheckerVisitor::Visit( CIdPtrExp &exp ) 
{
    //Только запоминаем тип
	lastCalculatedType = enums::TPrimitiveType::INT_ARRAY;
}

void CTypeCheckerVisitor::Visit( CNumExp &exp ) 
{
    std::cout << "typechecker: cnumexp\n";
    //Только запоминаем тип
	lastCalculatedType = enums::TPrimitiveType::INT;
}

void CTypeCheckerVisitor::Visit( COpExp &exp ) 
{
    std::cout << "typechecker: copexp\n";
    //Посещаем левый операнд
	if( exp.leftOperand ){
		exp.leftOperand->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

    if( lastCalculatedType != enums::TPrimitiveType::INT ) {
        //Работаем только с int
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError ( errorMessage, exp.position ) );
		lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}

    //Посещаем правый операнд
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

	if( lastCalculatedType != enums::TPrimitiveType::INT ) {
        //Работаем только с int
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}

	lastCalculatedType = enums::TPrimitiveType::INT;
}

void CTypeCheckerVisitor::Visit( CLogExp &exp ) 
{
    std::cout << "typechecker: clogexp\n";
    lastCalculatedType = enums::TPrimitiveType::BOOLEAN;
}

void CTypeCheckerVisitor::Visit( CLogOpExp &exp ) 
{
    std::cout << "typechecker: clogopexp\n";

    if( exp.leftOperand ) {
		exp.leftOperand->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

	if( lastCalculatedType != enums::TPrimitiveType::BOOLEAN ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::BOOLEAN, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}

	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

	if( lastCalculatedType != enums::TPrimitiveType::BOOLEAN ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::BOOLEAN, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position));
		lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}
	lastCalculatedType = enums::TPrimitiveType::BOOLEAN;
}

void CTypeCheckerVisitor::Visit( CCompExp &exp ) 
{
    std::cout << "typechecker: CCompExp\n";

    if( exp.leftOperand ) {
		exp.leftOperand->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

	if( lastCalculatedType != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}

	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

	if( lastCalculatedType != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}

	lastCalculatedType = enums::TPrimitiveType::BOOLEAN;
}

void CTypeCheckerVisitor::Visit( CUnarMinusExp &exp ) 
{
    std::cout << "typechecker: CUnarMinusExp\n";

    if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

	if( lastCalculatedType != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}

	lastCalculatedType = enums::TPrimitiveType::INT;
}

void CTypeCheckerVisitor::Visit( CGetLengthExp &exp ) 
{
    std::cout << "typechecker: CGetLengthExp\n";

    if( exp.array ) {
		exp.array->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	} else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
    }

	if( lastCalculatedType != enums::TPrimitiveType::INT_ARRAY ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT_ARRAY, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
		return;
	}
	lastCalculatedType = enums::TPrimitiveType::INT;
}

//В грамматике нет такого варианта и у нас тут хрень какая-то
void CTypeCheckerVisitor::Visit( CGetFieldExp &exp ) 
{
    std::cout << "typechecker: CGetFieldExp\n";

    if( exp.classOwner && exp.field ) {
		std::string ownerName = exp.classOwner->id->name;
		std::string fieldName = exp.field->id->name;
		auto ownerIterator = table->classes.find(ownerName);
		if( ownerIterator == table->classes.end() ) {
			auto errorMessage = CError::GetUndeclaredErrorMessage( ownerName );
			errors.push_back( CError( errorMessage, exp.position ) );
			lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
			return;
		}
        auto ownerInfo = table->classes[ownerName];
        auto variablesInfo = ownerInfo->fields;
        auto fieldIterator = variablesInfo->variables.find(fieldName);
        if( fieldIterator == variablesInfo->variables.end() ) {
            auto errorMessage = CError::GetHasNoMemberErrorMessage( ownerName, fieldName );
            errors.push_back( CError( errorMessage, exp.field->position ) );
            lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
            return;
        }

		auto fieldInfo = variablesInfo->variables[fieldName];
		lastCalculatedType = *(fieldInfo->type);
	} else {
		errors.push_back( CError( CError::AST_ERROR, exp.field->position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
	}
}

void CTypeCheckerVisitor::Visit( CCallMethodExp &exp ) 
{
    std::cout << "typechecker: CCallMethodExp\n";

    if( exp.args && exp.methodName ) {
        std::string identifierName = currentClass->name;
        bool isThis = true;
        if ( exp.objectName ) {
            exp.objectName->Accept( *this );
            if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
                return;
            }
            identifierName = lastCalculatedType.className;
            isThis = false;
            if( lastCalculatedType.isPrimitive ) {
                errors.push_back( CError( CError::IS_NOT_CALLABLE, exp.position ) );
                lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
                return;
            }
        }

		auto methodName = exp.methodName->name;
        auto classInfo = table->classes[identifierName];
        std::cout << methodName << " " << classInfo->name << " " << isThis << "\n";
		if( !checkMethodVisibility( methodName, classInfo, isThis ) ) {
			errors.push_back( CError( CError::GetHasNoMemberErrorMessage( identifierName, methodName ), exp.methodName->position ) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
			return;
		}
		auto methodInfo = classInfo->methods[methodName];
		auto expectedNumberOfArguments = methodInfo->arguments->variables.size();
        auto gotNumberOfArguments = exp.args->exps.size();
        if( expectedNumberOfArguments != gotNumberOfArguments ) {
			auto errorMessage = CError::GetNumberOfArgsMessage( expectedNumberOfArguments, gotNumberOfArguments );
			errors.push_back( CError( errorMessage, exp.position) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
			return;
		}
        auto argumentsInfo = methodInfo->arguments;
        for( int index = 0; index < gotNumberOfArguments; ++index ) {
            auto argumentInfo = argumentsInfo->variables[argumentsInfo->variableNames[index]];
            if( exp.args->exps[index] ) {
                exp.args->exps[index]->Accept( *this );
                auto expectedArgumentType = *( argumentInfo->type );
                if( lastCalculatedType != expectedArgumentType ) {
                    auto errorMessage = CError::GetTypeErrorMessage(expectedArgumentType, lastCalculatedType);
                    errors.push_back( CError( errorMessage, exp.args->exps[index]->position ) );
                    lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
                    return;
                }
            }
		}
		lastCalculatedType = *( methodInfo->returnType );
	} else {
		errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
    }
}

void CTypeCheckerVisitor::Visit( CExpList &exp ) 
{
    std::cout << "typechecker: CExpList\n";

    lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
}

void CTypeCheckerVisitor::Visit( CNegativeExpression &exp ) 
{
    std::cout << "typechecker: CNegativeExpression\n";

    if( exp.expression ) {
        exp.expression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( lastCalculatedType != enums::TPrimitiveType::BOOLEAN ) {
            auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::BOOLEAN, lastCalculatedType );
            errors.push_back( CError( errorMessage, exp.position ) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::BOOLEAN;
    } else {
        errors.push_back( CError( CError::AST_ERROR, exp.position) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
    }
}

void CTypeCheckerVisitor::Visit( CArrayExpression &exp ) 
{
    std::cout << "typechecker: CArrayExpression\n";

    if ( exp.lengthExpression ) {
		exp.lengthExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	}
	if( lastCalculatedType != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
	}
    lastCalculatedType = enums::TPrimitiveType::INT_ARRAY;
}

void CTypeCheckerVisitor::Visit( CGetFieldByThisExpression &exp )
{
    std::cout << "typechecker: CGetFieldByThisExpression\n";

    if( exp.fieldIdentifier ) {
        auto currentClassFields = currentClass->fields;
        auto fieldName = exp.fieldIdentifier->name;
        if( currentClassFields->variables.find( fieldName ) == currentClassFields->variables.end() ) {
            auto errorMessage = CError::GetHasNoMemberErrorMessage( currentClass->name, fieldName );
            errors.push_back( CError( errorMessage, exp.position ) );
            return;
        }
        lastCalculatedType = *( currentClassFields->variables[fieldName]->type );
    } else {
        errors.push_back( CError( CError::AST_ERROR, exp.position) );
    }
}

void CTypeCheckerVisitor::Visit( CByIndexExpression &exp ) 
{
    std::cout << "typechecker: CByIndexExpression\n";

    if( exp.identifier) {
		exp.identifier->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	}
	if( exp.indexExpression ) {
		exp.indexExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	}
	if( lastCalculatedType != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
        return;
	}
    lastCalculatedType = enums::TPrimitiveType::INT;
}

void CTypeCheckerVisitor::Visit( CNewIdentifier &exp ) 
{
    std::cout << "typechecker: CNewIdentifier\n";

    if( exp.identifier ) {
        if( table->classes.find(exp.identifier->name) == table->classes.end() ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( exp.identifier->name );
            errors.push_back( CError( errorMessage, exp.position) );
            return;
        }
        lastCalculatedType = exp.identifier->name;
    } else {
        errors.push_back( CError( CError::AST_ERROR, exp.position ) );
    }
}



//Statements visit methods
//---------------------------------------------------------------------------------------

void CTypeCheckerVisitor::Visit( CAssignStm &stm ) 
{
    std::cout << "typechecker: CAssignStm\n";

    if( stm.leftExpression && stm.rightExpression ) {
        bool isVisible = checkVariableVisibility( stm.leftExpression->name, currentClass, currentMethod );
        if( !isVisible ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( stm.leftExpression->name );
            errors.push_back( CError( errorMessage, stm.leftExpression->position ) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        }

        std::pair<VariableInfo*, bool> variableInfo = getVariableInfo(*stm.leftExpression);

        VariableInfo* variableInfoPtr = variableInfo.first;

        if (variableInfoPtr == nullptr) {
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        } else {
            variableInfoPtr->isInitialized = true;
        }

        stm.leftExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        auto leftType = lastCalculatedType;
        stm.rightExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( leftType != lastCalculatedType ) {
	    	auto errorMessage = CError::GetTypeErrorMessage( leftType, lastCalculatedType );
		    errors.push_back( CError( errorMessage, stm.leftExpression->position ) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
	    }

        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CAssignSubscriptStm &stm ) 
{
    std::cout << "typechecker: CAssignSubscriptStm\n";

    if( stm.idExpression && stm.offset && stm.valueExpression ) {
        auto variableName = stm.idExpression->name;
        bool isVisible = checkVariableVisibility( variableName, currentClass, currentMethod );
        if( !isVisible ) {
            errors.push_back( CError( CError::GetUndeclaredErrorMessage( variableName ), stm.position ) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        }
        stm.offset->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( lastCalculatedType != enums::TPrimitiveType::INT ) {
            auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
            errors.push_back( CError( errorMessage, stm.offset->position) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        }
        stm.valueExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( lastCalculatedType != enums::TPrimitiveType::INT ) {
            auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
            errors.push_back( CError( errorMessage, stm.valueExpression->position) );
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position) );
    }
}

void CTypeCheckerVisitor::Visit( CCompoundStm &stm ) 
{
    std::cout << "typechecker: CCompoundStm\n";

    if( stm.leftStatement) {
        stm.leftStatement->Accept( *this );
    }

    if( stm.rightStatement ) {
        stm.rightStatement->Accept( *this );
    }
}

void CTypeCheckerVisitor::Visit( CPrintStm &stm ) 
{
    std::cout << "typechecker: CPrintStm\n";

    if( stm.expression ) {
        stm.expression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( lastCalculatedType != enums::TPrimitiveType::INT ) {
            auto errorMessage = CError::GetTypeErrorMessage(enums::TPrimitiveType::INT, lastCalculatedType);
            errors.push_back(CError(errorMessage, stm.position));
        }
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CSimpleStm &stm )
{
    std::cout << "typechecker: CSimpleStm\n";

    lastCalculatedType = enums::TPrimitiveType::VOID;
}

void CTypeCheckerVisitor::Visit( CIfStm &stm ) 
{
    std::cout << "typechecker: CIfStm\n";

    if( stm.conditionExpression && stm.positiveStatement && stm.negativeStatement ) {
		stm.conditionExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
		if( lastCalculatedType.type != enums::TPrimitiveType::BOOLEAN ) {
			auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::BOOLEAN, lastCalculatedType );
			errors.push_back( CError( errorMessage, stm.conditionExpression->position ) );
            return;
		}
        stm.positiveStatement->Accept( *this );
        stm.negativeStatement->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CWhileStm &stm ) 
{
    std::cout << "typechecker: CWhileStm\n";

    if( stm.conditionExpression && stm.statement ) {
		stm.conditionExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
		if( lastCalculatedType.type != enums::TPrimitiveType::BOOLEAN ) {
			auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::BOOLEAN), lastCalculatedType.type );
			errors.push_back( CError( errorMessage, stm.position ) );
            return;
		}
        stm.statement->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
	}
}


//Classes visit methods
//---------------------------------------------------------------------------------------

void CTypeCheckerVisitor::Visit( CType &stm ) 
{
	std::cout << "typechecker: type\n";
    if( stm.name ) {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CField &stm ) 
{
	std::cout << "typechecker: field\n";
    if( stm.id && stm.type ) {
        bool isVisibleType = checkTypeExisting(*stm.type);
        if( !isVisibleType ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( stm.type->toString() );
            errors.push_back( CError( errorMessage, stm.type->position ) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CFieldList &stm ) 
{
	std::cout << "typechecker: fieldlist\n";
    bool areAllFieldsBuilt = true;
    for (int index = 0; index < stm.fields.size(); ++index) {
        auto field = stm.fields[index].get();
        if( !field ) {
            areAllFieldsBuilt = false;
            break;
        }
        field->Accept( *this );
    }
    if( areAllFieldsBuilt ) {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CArgument &stm )  
{
	std::cout << "typechecker: arg\n";
    if( stm.id && stm.type ) {
        bool isVisibleType = checkTypeExisting(*stm.type);
        if( !isVisibleType ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( stm.type->toString() );
            errors.push_back( CError( errorMessage, stm.type->position ) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CArgumentList &stm ) 
{
	std::cout << "typechecker: arglist\n";
    bool areAllArgsBuilt = true;
    for (int index = 0; index < stm.arguments.size(); ++index) {
        auto argument = stm.arguments[index].get();
        if( !argument ) {
            areAllArgsBuilt = false;
            break;
        }
        argument->Accept( *this );
    }
    if( areAllArgsBuilt ) {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CMethod &stm ) 
{
	std::cout << "typechecker: method\n";
    if( stm.name && stm.arguments && stm.returnExp && stm.returnType && stm.statements && stm.vars ) {
        currentMethod = currentClass->methods[stm.name->name];
        std::cout << "current method was got from symbol table\n";
        stm.name->Accept( *this );
        stm.arguments->Accept( *this );
        stm.statements->Accept( *this );
        stm.vars->Accept( *this );
        stm.returnExp->Accept( *this );
        TypeInfo expectedType = stm.returnType->isPrimitive ? TypeInfo(stm.returnType->type) : TypeInfo(stm.returnType->name->name);

        bool isVisibleClass = checkTypeExisting(*stm.returnType);
        if( !isVisibleClass ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( stm.returnType->name->name );
            errors.push_back( CError( errorMessage, stm.returnType->position) );
            return;
        }

        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( lastCalculatedType != expectedType ) {
            auto errorMessage = CError::GetTypeErrorMessage( expectedType, lastCalculatedType );
			errors.push_back( CError( errorMessage, stm.returnExp->position ) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
    currentMethod = nullptr;
}

void CTypeCheckerVisitor::Visit( CMethodList &stm ) 
{
	std::cout << "typechecker: methodlist\n";
    bool areAllMethods = true;
    for (int index = 0; index < stm.methods.size(); ++index) {
        auto method = stm.methods[index].get();
        if( !method ) {
            areAllMethods = false;
            break;
        }
        method->Accept( *this );
    }
    if( areAllMethods ) {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CClass &stm ) 
{
	std::cout << "typechecker: class\n";
    if( stm.id && stm.fields && stm.methods ) {
        currentClass = table->classes[stm.id->name];
        std::cout << "Before cyclic check\n";
        bool isBadInherited = checkCyclicInheritance( currentClass, currentClass );
        std::cout << "Cyclic inheritance was checked for class: " << currentClass->name << "\n";
        if( isBadInherited ) {
            errors.push_back( CError( CError::CYCLIC_INHERITANCE, stm.parentClass->position ) );
            return;
        }
        stm.id->Accept( *this );
        stm.fields->Accept( *this );
        stm.methods->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
    currentClass = nullptr;
}

void CTypeCheckerVisitor::Visit( CClassList &stm ) 
{
	std::cout << "typechecker: classlist\n";
    bool areAllClassBuilt = true;
    for (int index = 0; index < stm.classes.size(); ++index) {;
        if( !stm.classes[index]) {
            areAllClassBuilt = false;
            break;
        }
        std::cout << "Accepting of class: \n";
        std::cout << stm.classes[index]->id->name;
        std::cout << "\nLet's begin\n";
        stm.classes[index]->Accept( *this );
    }
    if( areAllClassBuilt ) {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CMainMethod &stm )
{
	std::cout << "typechecker: mainmethod\n";
    currentMethod = currentClass->methods["main"];
    if( stm.vars ) {
        stm.vars->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    }
    if( stm.statements ) {
        stm.statements->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    }
}

void CTypeCheckerVisitor::Visit( CMainClass &stm ) 
{
	std::cout << "typechecker: mainclass\n";
    if( stm.id ) {
        currentClass = table->classes[stm.id->name];
        stm.id->Accept( *this );
        stm.mainMethod->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
    currentClass = nullptr;
}

void CTypeCheckerVisitor::Visit( CProgram &stm ) 
{
    std::cout << "typechecker: program\n";
    if( stm.mainClass ) {
        stm.mainClass->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.mainClass->position ) );
    }
    if( stm.classList ) {
        stm.classList->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    }
}

//Constructor for type checker.
CTypeCheckerVisitor::CTypeCheckerVisitor(std::shared_ptr<SymbolTable> table) : table( table ),
 lastCalculatedType( enums::TPrimitiveType::ERROR_TYPE ), currentMethod( nullptr ), currentClass( nullptr ) {}

bool CTypeCheckerVisitor::checkVariableVisibility( const std::string& variableName, std::shared_ptr<ClassInfo> classInfo,
std::shared_ptr<MethodInfo> methodInfo ) {
    //Nullptr for method info means that we try to find the variable in fields of base classes.
    if( methodInfo ) {
        auto methodVariables = methodInfo->arguments->variables;
        if (methodVariables.find(variableName) != methodVariables.end()) {
            return true;
        }
        auto methodFields = methodInfo->fields->variables;
        if (methodFields.find(variableName) != methodFields.end()) {
            return true;
        }
    }
    auto classVariables = classInfo->fields->variables;
    if( classVariables.find( variableName ) != classVariables.end() ) {
        if ( currentClass->baseClass != "" ) {
            return checkVariableVisibility( variableName, table->classes[classInfo->baseClass], nullptr );
        } else {
            return false;
        }
    } else {
        return true;
    }
}

bool CTypeCheckerVisitor::checkMethodVisibility(const std::string &methodName, std::shared_ptr<ClassInfo> clazz, bool isThis ) {
    //if we call the method using this, clazz should be equal nullptr, this way, current class will be checked
    auto classMethods = clazz->methods;
    bool isMethodExist = classMethods.find( methodName ) != classMethods.end();
    if( !isMethodExist ) {
        if ( clazz->baseClass != "" ) {
            return checkMethodVisibility( methodName, table->classes[clazz->baseClass], isThis );
        } else {
            return false;
        }
    } else {
        std::shared_ptr<MethodInfo> methodInfo = classMethods[methodName];
        if( !isThis) {
            return methodInfo->isPublic;
        } else {
            return true;
        }
    }
}

bool CTypeCheckerVisitor::checkTypeExisting(const CType &type) {
    if (type.isPrimitive) {
        return true;
    } else {
        return table->classes.find(type.name->name ) != table->classes.end();
    }
}

bool CTypeCheckerVisitor::checkCyclicInheritance(std::shared_ptr<ClassInfo> startClass,
                                                 std::shared_ptr<ClassInfo> currentClass) {
    if( currentClass->baseClass == "" ) {
        return false;
    }
    if( currentClass->baseClass == startClass->name )
    {
        return true;
    }
    return checkCyclicInheritance( startClass, table->classes[currentClass->baseClass]);
}

std::vector<CError> CTypeCheckerVisitor::GetErrors()
{
    return errors;
}