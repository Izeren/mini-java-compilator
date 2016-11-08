#include "Classes.h"

//CClassList:
//-------------------------------------------------------------------------------------------------

CClassList::CClassList(CClass* _cclass, CClassList* _nextClasses) {
	cclass = std::unique_ptr<CClass>(_cclass);
	nextClasses = std::unique_ptr<CClassList>(_nextClasses);
}

CClassList::CClassList() {};

void CClassList::Accept(IVisitor &visitor) override {
	visitor.Visit(*this);
}


//CClass:
//-------------------------------------------------------------------------------------------------

CClass::CClass(const std::string &_name, CIdExp* _parentClass, CFieldList* _fields, CMethodList* _methods) {
	name = _name;
	parentClass = std::unique_ptr<CIdExp>(_parentClass);
	fields = std::unique_ptr<CFieldList>(_fields);
	methods = std::unique_ptr<CMethodList>(_methods);
}

CClass::CClass() : CClass(NULL) {};

void CClass::Accept(IVisitor &visitor) override {
	visitor.Visit(*this);
}


//CFieldList:
//-------------------------------------------------------------------------------------------------

CFieldList::CFieldList(CField* _field, CFieldList* _nextFields) {
	field = std::unique_ptr<CField>(_field);
	nextFields = std::unique_ptr<CFieldList>(_nextFields);
}

CFieldList::CFieldList() {};

void CFieldList::Accept(IVisitor &visitor) override {
	visitor.Visit(*this);
}


//CField:
//-------------------------------------------------------------------------------------------------

CField::CField(CType* _type, CIdExp* _id) {
	type = std::unique_ptr<CType>(_type);
	id = std::unique_ptr<CIdExp>(_id);
}
CField::CField() : CField(NULL, NULL) {};

void CField::Accept(IVisitor &visitor) override {
	visitor.Visit(*this);
}


//CType:
//-------------------------------------------------------------------------------------------------

CType::CType(const std::string &_name) {
	name = _name;
}

CType::CType() : CType(NULL) {};

void CType::Accept(IVisitor &visitor) override {
	visitor.Visit(*this);
}


//CMethodList:
//-------------------------------------------------------------------------------------------------

CMethodList::CMethodList(CMethod* _method, CMethodList* _nextMethods) {
	method = std::unique_ptr<CMethod>(_method);
	nextMethods = std::unique_ptr<CMethodList>(_nextMethods);
}

CMethodList::CMethodList() {};

void CMethodList::Accept(IVisitor &visitor) override {
	visitor.Visit(*this);
}


//CMethod:
//-------------------------------------------------------------------------------------------------

CMethod::CMethod(CType* _returnType, const std::string &_name, CArgumentList* _arguments, CCompoundStm* _statements) {
	returnType = std::unique_ptr<CType>(_returnType);
	name = _name;
	arguments = std::unique_ptr<CArgumentList>(_arguments);
	statements = std::unique_ptr<CCompoundStm>(_statements);
}

CMethod::CMethod() : CMethod(NULL, NULL) {};

void CMethod::Accept(IVisitor &visitor) override {
	visitor.Visit(*this);
}


//CArgumentList:
//-------------------------------------------------------------------------------------------------

CArgumentList::CArgumentList(CArgument* _argument, CArgumentList* _argumentList)
{
	argument = std::unique_ptr<CArgument>(_argument);
	argumentList = std::unique_ptr<CArgumentList>(_argumentList);
}

CArgumentList::CArgumentList()
{}

void CArgumentList::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}


//CArgumentList:
//-------------------------------------------------------------------------------------------------

CArgument::CArgument(CType *_type, CIdExp *_id)
{
	type = std::unique_ptr<CType>(_type);
	id = std::unique_ptr<CIdExp>(_id);
}

CArgument::CArgument()
{}

void CArgument::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}
