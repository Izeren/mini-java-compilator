#include "CTypeCheckerVisitor.h"
#include "../symbol_table/SymbolInfo.h"
#include "../shared_ptrs_nodes/Statements.h"
#include "../shared_ptrs_nodes/Expressions.h"
#include "../shared_ptrs_nodes/Classes.h"
#include <exception>



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
    if (exp.isInstance) {
        std::pair<VariableInfo*, bool> variableInfo = getVariableInfo(exp);

        bool isLocalVariable = variableInfo.second;
        VariableInfo* variableInfoPtr = variableInfo.first;

        if (variableInfoPtr == nullptr) {
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        }

        if (isLocalVariable && exp.isInstance && !variableInfoPtr->isInitialized) {
            errors.push_back( CError(CError::NOT_INITIALIZED_VARIABLE, exp.position) );
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
    //Только запоминаем тип
	lastCalculatedType = enums::TPrimitiveType::INT;
}

void CTypeCheckerVisitor::Visit( COpExp &exp ) 
{
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
	lastCalculatedType = enums::TPrimitiveType::BOOLEAN;
}

void CTypeCheckerVisitor::Visit( CLogOpExp &exp ) 
{
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
            errors.push_back( CError( errorMessage, exp.position ) );
            lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
            return;
        }

		auto fieldInfo = variablesInfo->variables[fieldName];
		lastCalculatedType = *(fieldInfo->type);
	} else {
		errors.push_back( CError( CError::AST_ERROR, exp.position ) );
        lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
	}
}

void CTypeCheckerVisitor::Visit( CCallMethodExp &exp ) 
{
	if( exp.args && exp.methodName) {
        std::string identifierName = currentClass->name;
        if ( exp.classOwner ) {
            identifierName = exp.classOwner->name;
        }
		auto classIterator = table->classes.find(identifierName);
		if( classIterator == table->classes.end() ) {
			errors.push_back( CError( CError::IS_NOT_CALLABLE, exp.position ) );
			return;
		}
		auto methodName = exp.methodName->name;
		auto methods = table->classes[identifierName]->methods;
		if( methods.find( methodName ) == methods.end() ) {
			errors.push_back( CError( CError::GetHasNoMemberErrorMessage( identifierName, methodName ), exp.position ) );
			return;
		}
		auto methodInfo = methods[methodName];
		auto expectedNumberOfArguments = methodInfo->arguments->variables.size();
        auto gotNumberOfArguments = exp.args->exps.size();
        if( expectedNumberOfArguments != gotNumberOfArguments ) {
			auto errorMessage = CError::GetNumberOfArgsMessage( expectedNumberOfArguments, gotNumberOfArguments );
			errors.push_back( CError( errorMessage, exp.position) );
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
    lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
}

void CTypeCheckerVisitor::Visit( CNegativeExpression &exp ) 
{
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
	if ( exp.lengthExpression ) {
		exp.lengthExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
	}
	if( lastCalculatedType != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
	}
}

void CTypeCheckerVisitor::Visit( CThisExpression &exp ) 
{
    if( exp.identifier ) {
        auto currentClassFields = currentClass->fields;
        auto fieldName = exp.identifier->name;
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
	}
}

void CTypeCheckerVisitor::Visit( CNewIdentifier &exp ) 
{
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
    if( stm.leftExpression && stm.rightExpression ) {
        bool isVisible = checkVariableVisibility( stm.leftExpression->name );
        if( !isVisible ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( stm.leftExpression->name );
            errors.push_back( CError( errorMessage, stm.leftExpression->position ) );
            return;
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
	    	auto errorMessage = CError::GetTypeErrorMessage( leftType, lastCalculatedType.type );
		    errors.push_back( CError( errorMessage, stm.position) );
            return;
	    }

        //success
        std::pair<VariableInfo*, bool> variableInfo = getVariableInfo(*stm.leftExpression);

        VariableInfo* variableInfoPtr = variableInfo.first;

        if (variableInfoPtr == nullptr) {
            lastCalculatedType = enums::TPrimitiveType::ERROR_TYPE;
            return;
        } else {
            variableInfoPtr->isInitialized = true;
        }

        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CAssignSubscriptStm &stm ) 
{
    if( stm.idExpression && stm.offset && stm.valueExpression ) {
        auto variableName = stm.idExpression->name;
        bool isVisible = checkVariableVisibility( variableName );
        if( !isVisible ) {
            errors.push_back( CError( CError::GetUndeclaredErrorMessage( variableName ), stm.position ) );
            return;
        }
        stm.offset->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( lastCalculatedType != enums::TPrimitiveType::INT ) {
            auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
            errors.push_back( CError( errorMessage, stm.offset->position) );
            return;
        }
        stm.valueExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
        if( lastCalculatedType != enums::TPrimitiveType::INT ) {
            auto errorMessage = CError::GetTypeErrorMessage( enums::TPrimitiveType::INT, lastCalculatedType );
            errors.push_back( CError( errorMessage, stm.valueExpression->position) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position) );
    }
}

void CTypeCheckerVisitor::Visit( CCompoundStm &stm ) 
{
    if( stm.leftStatement and stm.rightStatement ) {
        stm.leftStatement->Accept( *this );
        stm.rightStatement->Accept( *this );
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CPrintStm &stm ) 
{
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
    lastCalculatedType = enums::TPrimitiveType::VOID;
}

void CTypeCheckerVisitor::Visit( CIfStm &stm ) 
{
	if( stm.conditionExpression && stm.positiveStatement && stm.negativeStatement ) {
		stm.conditionExpression->Accept( *this );
        if( lastCalculatedType == enums::TPrimitiveType::ERROR_TYPE ) {
            return;
        }
		if( lastCalculatedType.type != enums::TPrimitiveType::BOOLEAN ) {
			auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::BOOLEAN), lastCalculatedType.type );
			errors.push_back( CError( errorMessage, stm.position ) );
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
    if( stm.name ) {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CField &stm ) 
{
    if( stm.id && stm.type ) {
        bool isVisibleType = checkClassVisibility( stm.id->name );
        if( !isVisibleType ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( stm.id->name );
            errors.push_back( CError( errorMessage, stm.position ) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CFieldList &stm ) 
{
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

void CTypeCheckerVisitor::Visit( CArgument &stm )  {
    if( stm.id && stm.type ) {
        bool isVisibleType = checkClassVisibility( stm.id->name );
        if( !isVisibleType ) {
            auto errorMessage = CError::GetUndeclaredErrorMessage( stm.id->name );
            errors.push_back( CError( errorMessage, stm.position ) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CArgumentList &stm ) 
{
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
    if( stm.name && stm.arguments && stm.returnExp && stm.returnType && stm.statements && stm.vars ) {
        currentMethod = table->classes[currentClass->name]->methods[stm.name->name];
        stm.name->Accept( *this );
        stm.arguments->Accept( *this );
        stm.statements->Accept( *this );
        stm.vars->Accept( *this );
        stm.returnExp->Accept( *this );
        TypeInfo expectedType = stm.returnType->isPrimitive ? TypeInfo(stm.returnType->type) : TypeInfo(stm.returnType->name->name);
        if( !stm.returnType->isPrimitive ) {
            bool isVisibleClass = checkClassVisibility( stm.returnType->name->name );
            if( !isVisibleClass ) {
                auto errorMessage = CError::GetUndeclaredErrorMessage( stm.returnType->name->name );
                errors.push_back( CError( errorMessage, stm.returnType->position) );
                return;
            }
        }
        //TODO: lastCalculatedType is not defined
        if( lastCalculatedType != expectedType ) {
            auto errorMessage = CError::GetTypeErrorMessage( expectedType, lastCalculatedType );
			errors.push_back( CError( errorMessage, stm.returnExp->position ) );
            return;
        }
        lastCalculatedType = enums::TPrimitiveType::VOID;
        currentMethod = nullptr;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CMethodList &stm ) 
{
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
    if( stm.id && stm.fields && stm.methods ) {
        stm.id->Accept( *this );
        stm.fields->Accept( *this );
        stm.methods->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CClassList &stm ) 
{
    bool areAllClassBuilt = true;
    for (int index = 0; index < stm.classes.size(); ++index) {
        auto curClass = stm.classes[index].get();
        if( !curClass ) {
            areAllClassBuilt = false;
            break;
        }
        curClass->Accept( *this );
    }
    if( areAllClassBuilt ) {
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CMainMethod &stm ) 
{
    if( stm.vars ) {
        stm.vars->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    }
    if( stm.statements ) {
        stm.vars->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    }
}

void CTypeCheckerVisitor::Visit( CMainClass &stm ) 
{
    if( stm.id ) {
        stm.id->Accept( *this );
        lastCalculatedType = enums::TPrimitiveType::VOID;
    } else {
        errors.push_back( CError( CError::AST_ERROR, stm.position ) );
    }
}

void CTypeCheckerVisitor::Visit( CProgram &stm ) 
{
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

bool CTypeCheckerVisitor::checkVariableVisibility( const std::string& variableName ) {
    if( currentClass == nullptr || currentMethod == nullptr ) {
        return false;
    }
    auto methodVariables = currentMethod->arguments->variables;
    if(methodVariables.find( variableName ) != methodVariables.end() ) {
        return true;
    }
    auto methodFields = currentMethod->fields->variables;
    if(methodVariables.find( variableName ) != methodVariables.end() ) {
        return true;
    }
    auto classVariables = currentClass->fields->variables;
    return classVariables.find(variableName ) != classVariables.end();
}

bool CTypeCheckerVisitor::checkMethodVisibility(const std::string &methodName) {
    if (currentClass == nullptr) {
        return false;
    }
    auto classMethods = currentClass->methods;
    return classMethods.find(methodName ) != classMethods.end();
}

bool CTypeCheckerVisitor::checkClassVisibility(const std::string &className) {
    return table->classes.find(className ) != table->classes.end();
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