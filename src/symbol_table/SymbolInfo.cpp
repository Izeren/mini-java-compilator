#include <memory> 

#include "SymbolInfo.h"

VariableInfo::VariableInfo( const std::string & _name, const std::string & _type )
	:name(_name), type(_type)
{}

MethodInfo::MethodInfo( const std::string & _name )
	:name(_name)
{}

void MethodInfo::AddVariable( std::shared_ptr<VariableInfo> variableInfo )
{
	variables.emplace( variableInfo->name, variableInfo );
}

ClassInfo::ClassInfo( const std::string & _name )
	:name(_name)
{}

void ClassInfo::AddField( std::shared_ptr<VariableInfo> fieldInfo )
{
	fields.emplace( fieldInfo->name, fieldInfo );
}

void ClassInfo::AddMethod( std::shared_ptr<MethodInfo> methodInfo )
{
	methods.emplace( methodInfo->name, methodInfo );
}

void SymbolTable::AddClass( std::shared_ptr<ClassInfo> classInfo )
{
	classes.emplace( classInfo->name, classInfo );
}
