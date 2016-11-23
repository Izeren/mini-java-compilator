#include <iostream>

#include "SymbolInfo.h"

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

VariableInfo::VariableInfo( const std::string & _name, std::shared_ptr<TypeInfo> _type )
	:name( _name ), type( _type )
{}

void VariableInfo::Print( std::ofstream& out )
{
	out << "\t" << "\t" << "\t" << "name: " << name << "\n";
	out << "\t" << "\t" << "\t" << "type: ";
	type->Print( out );
	out << "\n";
}

MethodInfo::MethodInfo( const std::string & _name, bool _isPublic, std::shared_ptr<TypeInfo> _returnType )
	:name( _name ), isPublic( _isPublic ), returnType( _returnType )
{}

void MethodInfo::AddVariable( std::shared_ptr<VariableInfo> variableInfo )
{
	variables.emplace( variableInfo->name, variableInfo );
}

void MethodInfo::Print( std::ofstream& out )
{
	out << "\t" << "\t" << "name: " << name << " " << "\n";
	if( returnType ) {
		out << "\t" << "\t" << "returnType: ";
		returnType->Print( out ); 
		out << "\n";
	}
	out << "\t" << "\t" << "isPublic: " << isPublic << " " << "\n";
	for( auto elem : variables ) {
		out << "\t" << "\t" << "variable: {" << "\n";
		(elem.second)->Print( out );
		out << "\t" << "\t" << "} " << "\n";
	}
}

ClassInfo::ClassInfo( const std::string & _name )
	:name( _name )
{}

void ClassInfo::AddField( std::shared_ptr<VariableInfo> fieldInfo )
{
	fields.emplace( fieldInfo->name, fieldInfo );
}

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
	for( auto elem : fields ) {
		out << "\t" << "field: {" << "\n";
		(elem.second)->Print( out );
		out << "\t" << "} " << "\n";
	}
	for( auto elem : methods ) {
		out << "\t" << "method: {" << "\n";
		(elem.second)->Print( out );
		out << "\t" << "} " << "\n";
	}
}

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
