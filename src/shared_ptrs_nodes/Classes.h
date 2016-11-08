#pragma once

#include "INode.h"
#include "Statements.h"
#include "Expressions.h"


//CClassList:
//-------------------------------------------------------------------------------------------------

class CClassList : public INode {
public:
	CClassList(CClass* _cclass, CClassList* _nextClasses = NULL);
	CClassList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CClass> cclass;
	std::unique_ptr<CClassList> nextClasses;
};


//CClass:
//-------------------------------------------------------------------------------------------------

class CClass : public INode {
public:
	CClass(const std::string &_name, CIdExp* _parentClass = NULL, CFieldList* _fields = NULL, CMethodList* _methods = NULL);
	CClass();
	void Accept(IVisitor &visitor) override;

	std::string name;
	std::unique_ptr<CIdExp> parentClass;
	std::unique_ptr<CFieldList> fields;
	std::unique_ptr<CMethodList> methods;
};


//CFieldList:
//-------------------------------------------------------------------------------------------------

class CFieldList : public INode {
public:
	CFieldList(CField* _field, CFieldList* _nextFields = NULL);
	CFieldList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CField> field;
	std::unique_ptr<CFieldList> nextFields;
};


//CField:
//-------------------------------------------------------------------------------------------------

class CField : public INode {
public:
	CField(CType* _type, CIdExp* _id);
	CField();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CType> type;
	std::unique_ptr<CIdExp> id;
};


//CType:
//-------------------------------------------------------------------------------------------------

class CType : public INode {
public:
	CType(const std::string &_name);
	CType();
	void Accept(IVisitor &visitor) override;

	std::string name;
};


//CMethodList:
//-------------------------------------------------------------------------------------------------

class CMethodList : public INode {
public:
	CMethodList(CMethod* _method, CMethodList* _nextMethods = NULL);
	CMethodList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CMethod> method;
	std::unique_ptr<CMethodList> nextMethods;
};


//CMethod:
//-------------------------------------------------------------------------------------------------

class CMethod : public INode {
public:
	CMethod(CType* _returnType, const std::string &_name, CArgumentList* _arguments = NULL, CCompoundStm* _statements = NULL);
	CMethod();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CType> returnType;
	std::string name;
	std::unique_ptr<CArgumentList> arguments;
	std::unique_ptr<CCompoundStm> statements;
};


//CArgumentList:
//-------------------------------------------------------------------------------------------------

class CArgumentList : public INode {
public:
	CArgumentList(CArgument* _argument, CArgumentList* _argumentList);
	CArgumentList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CArgument> argument;
	std::unique_ptr<CArgumentList> argumentList;
};


//CArgument:
//-------------------------------------------------------------------------------------------------

class CArgument : public INode {
public:
	CArgument(CType *_type, CIdExp *_id);
	CArgument();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CType> type;
	std::unique_ptr<CIdExp> id;
};