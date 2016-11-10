#pragma once

#include "INode.h"
#include "Statements.h"
#include "Expressions.h"
#include <string>
#include <map>

class IWrapper : public INode {};

//CType:
//-------------------------------------------------------------------------------------------------

class CType : public IWrapper {
public:
	static std::map<enums::TPrimitiveType, std::string> typeNames;
	CType(CIdExp* _name);
	CType(enums::TPrimitiveType _type);
	CType();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CIdExp> name;
	enums::TPrimitiveType type;
	bool isPrimitive;
};


//CField:
//-------------------------------------------------------------------------------------------------

class CField : public IWrapper {
public:
	CField(CType* _type, CIdExp* _id);
	CField();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CType> type;
	std::unique_ptr<CIdExp> id;
};


//CFieldList:
//-------------------------------------------------------------------------------------------------

class CFieldList : public IWrapper {
public:
	CFieldList(CField* _field, CFieldList* _nextFields = NULL);
	CFieldList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CField> field;
	std::unique_ptr<CFieldList> nextFields;
};


//CArgument:
//-------------------------------------------------------------------------------------------------

class CArgument : public IWrapper {
public:
	CArgument(CType *_type, CIdExp *_id);
	CArgument();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CType> type;
	std::unique_ptr<CIdExp> id;
};


//CArgumentList:
//-------------------------------------------------------------------------------------------------

class CArgumentList : public IWrapper {
public:
	CArgumentList(CArgument* _argument, CArgumentList* _nextArguments);
	CArgumentList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CArgument> argument;
	std::unique_ptr<CArgumentList> nextArguments;
};


//CMethod:
//-------------------------------------------------------------------------------------------------

class CMethod : public IWrapper {
public:
	CMethod(CType* _returnType, CIdExp* _name, CArgumentList* _arguments = NULL, CCompoundStm* _statements = NULL, bool _isPublic = true);
	CMethod();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CType> returnType;
	std::unique_ptr<CIdExp> name;
	std::unique_ptr<CArgumentList> arguments;
	std::unique_ptr<CCompoundStm> statements;
	bool isPublic;
};


//CMethodList:
//-------------------------------------------------------------------------------------------------

class CMethodList : public IWrapper {
public:
	CMethodList(CMethod* _method, CMethodList* _nextMethods = NULL);
	CMethodList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CMethod> method;
	std::unique_ptr<CMethodList> nextMethods;
};


//CClass:
//-------------------------------------------------------------------------------------------------

class CClass : public IWrapper {
public:
	CClass(CIdExp* _id, CIdExp* _parentClass = NULL, CFieldList* _fields = NULL, CMethodList* _methods = NULL);
	CClass();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CIdExp> id;
	std::unique_ptr<CIdExp> parentClass;
	std::unique_ptr<CFieldList> fields;
	std::unique_ptr<CMethodList> methods;
};


//CClassList:
//-------------------------------------------------------------------------------------------------

class CClassList : public IWrapper {
public:
	CClassList(CClass* _cclass, CClassList* _nextClasses = NULL);
	CClassList();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CClass> cclass;
	std::unique_ptr<CClassList> nextClasses;
};


//CMainMethod:
//-------------------------------------------------------------------------------------------------

class CMainMethod : public IWrapper {
public:
	void Accept(IVisitor &visitor) override;
	CMainMethod();
	CMainMethod(CType* _returnType, CArgumentList* _arguments, CCompoundStm* _statements);

	std::unique_ptr<CType> returnType;
	std::unique_ptr<CArgumentList> arguments;
	std::unique_ptr<CCompoundStm> statements;
};


//CMainClass:
//-------------------------------------------------------------------------------------------------

class CMainClass : public IWrapper {
public:
	void Accept(IVisitor &visitor) override;
	CMainClass();
	CMainClass(CIdExp* _id, CMainMethod* _mainMethod);

	std::unique_ptr<CIdExp> id;
	std::unique_ptr<CMainMethod> mainMethod;
};


//CProgram:
//-------------------------------------------------------------------------------------------------

class CProgram : public IWrapper {
public:
	void Accept(IVisitor &visitor) override;
	CProgram();
	CProgram(CMainClass* _class, CClassList* _classList);

	std::unique_ptr<CMainClass> mainClass;
	std::unique_ptr<CClassList> classList;
};