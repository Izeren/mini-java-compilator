#include "Classes.h"


//CType:
//-------------------------------------------------------------------------------------------------

CType::CType(CIdExp* _name) {
	name = std::unique_ptr<CIdExp>(_name);
	isPrimitive = false;
}

CType::CType(enums::TPrimitiveType _type) {
	isPrimitive = true;
	type = _type;
}

CType::CType() : CType(NULL) {};

void CType::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CField:
//-------------------------------------------------------------------------------------------------

CField::CField(CType* _type, CIdExp* _id) {
	type = std::unique_ptr<CType>(_type);
	id = std::unique_ptr<CIdExp>(_id);
}
CField::CField() : CField(NULL, NULL) {};

void CField::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CFieldList:
//-------------------------------------------------------------------------------------------------

CFieldList::CFieldList(CField* _field, CFieldList* _nextFields) {
	field = std::unique_ptr<CField>(_field);
	nextFields = std::unique_ptr<CFieldList>(_nextFields);
}

CFieldList::CFieldList() {};

void CFieldList::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CArgument:
//-------------------------------------------------------------------------------------------------

CArgument::CArgument(CType *_type, CIdExp *_id) {
	type = std::unique_ptr<CType>(_type);
	id = std::unique_ptr<CIdExp>(_id);
}

CArgument::CArgument() {}

void CArgument::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CArgumentList:
//-------------------------------------------------------------------------------------------------

CArgumentList::CArgumentList(CArgument* _argument, CArgumentList* _nextArguments)
{
	argument = std::unique_ptr<CArgument>(_argument);
	nextArguments = std::unique_ptr<CArgumentList>(_nextArguments);
}

CArgumentList::CArgumentList()
{}

void CArgumentList::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CMethod:
//-------------------------------------------------------------------------------------------------

CMethod::CMethod(CType* _returnType, CIdExp* _name, CArgumentList* _arguments, CCompoundStm* _statements, bool _isPublic)
{
	returnType = std::unique_ptr<CType>(_returnType);
	name = std::unique_ptr<CIdExp>(_name);
	arguments = std::unique_ptr<CArgumentList>(_arguments);
	statements = std::unique_ptr<CCompoundStm>(_statements);
	isPublic = _isPublic;
}

CMethod::CMethod() : CMethod(NULL, NULL) {};

void CMethod::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CMethodList:
//-------------------------------------------------------------------------------------------------

CMethodList::CMethodList(CMethod* _method, CMethodList* _nextMethods) {
	method = std::unique_ptr<CMethod>(_method);
	nextMethods = std::unique_ptr<CMethodList>(_nextMethods);
}

CMethodList::CMethodList() {};

void CMethodList::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CClass:
//-------------------------------------------------------------------------------------------------

CClass::CClass(CIdExp* _id, CIdExp* _parentClass, CFieldList* _fields, CMethodList* _methods) {
	id = std::unique_ptr<CIdExp>(_id);
	parentClass = std::unique_ptr<CIdExp>(_parentClass);
	fields = std::unique_ptr<CFieldList>(_fields);
	methods = std::unique_ptr<CMethodList>(_methods);
}

CClass::CClass() : CClass(NULL) {};

void CClass::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CClassList:
//-------------------------------------------------------------------------------------------------

CClassList::CClassList(CClass* _cclass, CClassList* _nextClasses) {
	cclass = std::unique_ptr<CClass>(_cclass);
	nextClasses = std::unique_ptr<CClassList>(_nextClasses);
}

CClassList::CClassList() {};

void CClassList::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CMainMethod:
//-------------------------------------------------------------------------------------------------

void CMainMethod::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CMainMethod::CMainMethod() {}

CMainMethod::CMainMethod(CType* _returnType, CArgumentList* _arguments, CCompoundStm* _statements) {
	returnType = std::unique_ptr<CType>(_returnType);
	arguments = std::unique_ptr<CArgumentList>(_arguments);
	statements = std::unique_ptr<CCompoundStm>(_statements);
}


//CMainClass:
//-------------------------------------------------------------------------------------------------

void CMainClass::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CMainClass::CMainClass() {}

CMainClass::CMainClass(CIdExp* _id, CMainMethod* _mainMethod) {
	id = std::unique_ptr<CIdExp>(_id);
	mainMethod = std::unique_ptr<CMainMethod>(_mainMethod);
}


//CProgram:
//-------------------------------------------------------------------------------------------------

void CProgram::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CProgram::CProgram() {}

CProgram::CProgram(CMainClass* _mainClass, CClassList* _classList) {
	mainClass = std::unique_ptr<CMainClass>(_mainClass);
	classList = std::unique_ptr<CClassList>(_classList);
}