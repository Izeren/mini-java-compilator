#include <iostream>

#include "SymbolInfo.h"


//TypeInfo:
//-------------------------------------------------------------------------------------------------

TypeInfo::TypeInfo( enums::TPrimitiveType _type )
	:isPrimitive( true ), type( _type )
{}

TypeInfo::TypeInfo( const std::string& _className )
	: isPrimitive( false ), className( _className )
{}

void TypeInfo::Print( std::ofstream & out )
{
	if( isPrimitive ) {
		out << CType::typeNames[type];
	} else {
		out << className;
	}
}

bool operator==(const TypeInfo& left, const TypeInfo& right) {
	if ( left.isPrimitive ) {
		if( right.isPrimitive ) {
			return left.type == right.type;
		} else {
			return false;
		}
	} else {
		if( right.isPrimitive ) {
			return false;
		} else {
			return left.className == right.className;
		}
	}
}

bool operator!=(const TypeInfo& left, const TypeInfo& right) {
	return !( left == right );
}


//VariableInfo:
//-------------------------------------------------------------------------------------------------

VariableInfo::VariableInfo( const std::string & _name, std::shared_ptr<TypeInfo> _type )
	:name( _name ), type( _type )
{}

void VariableInfo::Print( std::ofstream& out )
{
	out << "\t" << "\t" << "\t" << "\t" << "name: " << name << "\n";
	out << "\t" << "\t" << "\t" << "\t" << "type: ";
	type->Print( out );
	out << "\n";
}


//VariablesInfo:
//-------------------------------------------------------------------------------------------------

VariablesInfo::VariablesInfo()
{}

void VariablesInfo::Print( std::ofstream & out )
{
	if( !variables.empty() ) {
		for( auto elem : variables ) {
			out << "\t" << "\t" << "\t" << "variable: {" << "\n";
			(elem.second)->Print( out );
			out << "\t" << "\t" << "\t" << "} " << "\n";
		}
	}
}

void VariablesInfo::AddVariable( std::shared_ptr<VariableInfo> variableInfo )
{
	variables.emplace( variableInfo->name, variableInfo );
	variableNames.push_back( variableInfo->name );
}


//MethodInfo:
//-------------------------------------------------------------------------------------------------

MethodInfo::MethodInfo( const std::string & _name, bool _isPublic, std::shared_ptr<TypeInfo> _returnType )
	:name( _name ), isPublic( _isPublic ), returnType( _returnType )
{}

void MethodInfo::Print( std::ofstream& out )
{
	out << "\t" << "\t" << "name: " << name << " " << "\n";
	if( returnType ) {
		out << "\t" << "\t" << "returnType: ";
		returnType->Print( out ); 
		out << "\n";
	}
	out << "\t" << "\t" << "isPublic: " << isPublic << " " << "\n";
	out << "\t" << "\t" << "arguments: {" << "\n";
	arguments->Print( out );
	out << "\t" << "\t" << "} " << "\n";
	out << "\t" << "\t" << "fields: {" << "\n";
	fields->Print( out );
	out << "\t" << "\t" << "} " << "\n";
}


//ClassInfo:
//-------------------------------------------------------------------------------------------------

ClassInfo::ClassInfo( const std::string & _name )
	:name( _name )
{}

void ClassInfo::AddMethod( std::shared_ptr<MethodInfo> methodInfo )
{
	methods.emplace( methodInfo->name, methodInfo );
}

void ClassInfo::Print( std::ofstream& out )
{
	out << "\t" << "name: " << name << "\n";
	if( baseClass != "" ) {
		out << "\t" << "base: " << baseClass << "\n";
	}
	out << "\t" << "fields: {" << "\n";
	fields->Print( out );
	out << "\t" << "} " << "\n";
	for( auto elem : methods ) {
		out << "\t" << "method: {" << "\n";
		(elem.second)->Print( out );
		out << "\t" << "} " << "\n";
	}
}


//SymbolTable:
//-------------------------------------------------------------------------------------------------

void SymbolTable::AddClass( std::shared_ptr<ClassInfo> classInfo )
{
	classes.emplace( classInfo->name, classInfo );
}

void SymbolTable::Print( std::ofstream& out )
{
	for( auto elem : classes ) {
		out << "class: {" << "\n";
		(elem.second)->Print( out );
		out << "}" << "\n";
	}
}


//CError:
//-------------------------------------------------------------------------------------------------

const std::string CError::FUNCTION_REDEFINITION = "Function redefined.";
const std::string CError::VARIABLE_REDEFINITION = "Variable redefined.";
const std::string CError::CLASS_REDEFINITION = "Class redefined.";
const std::string CError::AST_ERROR = "AST construction error.";
const std::string CError::IS_NOT_CALLABLE = "Object is not callable.";
CError::CError( const std::string & _message, const PositionInfo& position )
	:message(_message), position(position)
{}

CError::CError(const std::string &_message)
	:message(_message), position(PositionInfo())
{}

std::string & CError::GetMessage()
{
	return message;
}

PositionInfo CError::GetPosition() {
	return position;
}

std::string CError::GetTypeErrorMessage(const TypeInfo &expected, const TypeInfo &got) {
    std::string errorMessage = "";
	errorMessage += "Type mismatch, expected: ";
	if( expected.isPrimitive ) {
		errorMessage += CType::typeNames[expected.type];
	} else {
		errorMessage += expected.className;
	}
	errorMessage += " got: ";
	if( got.isPrimitive ) {
		errorMessage += CType::typeNames[got.type];
	} else {
		errorMessage += got.className;
	}
	errorMessage += ".";
	return errorMessage;
}

std::string CError::GetUndeclaredErrorMessage(const std::string& name) {
    std::string errorMessage = "The object named: " + name + " is undeclared in this scope.";
	return errorMessage;
}

std::string CError::GetHasNoMemberErrorMessage(const std::string &className, const std::string &fieldName) {
    std::string errorMessage = "Class: " + className + " has no member: " + fieldName + ".";
	return errorMessage;
}

std::string CError::GetUndeclaredVariableErrorMessage( const std::string& variableName) {
    return  "Variable " + variableName + " undeclared.";
}

std::string CError::GetNotInitializedVariableErrorMessage( const std::string& variableName) {
    return "Variable " + variableName + " not initialized but has been used.";
}

std::string CError::GetNumberOfArgsMessage(unsigned long expected, unsigned long got) {
	 std::string errorMessage = "";
	errorMessage += "Wrong number of arguments, expected: ";
    errorMessage += std::to_string( expected );
	errorMessage += " got: ";
    errorMessage += std::to_string( got );
	errorMessage += ".";
	return errorMessage;
}


