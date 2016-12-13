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

std::map<enums::TPrimitiveType, std::string> CType::typeNames = {
	{enums::TPrimitiveType::INT, "int"},
	{enums::TPrimitiveType::BOOLEAN, "boolean"},
	{enums::TPrimitiveType::INT_ARRAY, "int[]"},
	{enums::TPrimitiveType::STRING_ARRAY, "String[]"}
};

std::string CType::toString() const {
	if( this->isPrimitive ) {
        return CType::typeNames[this->type];
    } else {
        if( this->name == nullptr ) {
            return "";
        } else {
            return this->name->name;
        }
    }
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

CFieldList::CFieldList() {
	fields = std::vector<std::unique_ptr<CField> >();
}

void CFieldList::Add(CField* _field) {
	fields.push_back(std::unique_ptr<CField>(_field));
}

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

CArgumentList::CArgumentList() {
	arguments = std::vector<std::unique_ptr<CArgument> >();
}

CArgumentList::CArgumentList(CArgument* _argument) {
	arguments = std::vector<std::unique_ptr<CArgument> >();
	arguments.push_back(std::unique_ptr<CArgument>(_argument));
}

void CArgumentList::Add(CArgument* _argument) {
	arguments.push_back(std::unique_ptr<CArgument>(_argument));
}

void CArgumentList::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CMethod:
//-------------------------------------------------------------------------------------------------

CMethod::CMethod(CType* _returnType, IExpression* _returnExp, CIdExp* _name, CArgumentList* _arguments, CFieldList* _vars, CCompoundStm* _statements, bool _isPublic)
{
	returnType = std::unique_ptr<CType>(_returnType);
	returnExp = std::unique_ptr<IExpression>(_returnExp);
	name = std::unique_ptr<CIdExp>(_name);
	arguments = std::unique_ptr<CArgumentList>(_arguments);
	statements = std::unique_ptr<CCompoundStm>(_statements);
	vars = std::unique_ptr<CFieldList>(_vars);
	isPublic = _isPublic;
}

CMethod::CMethod() : CMethod(NULL, NULL, NULL) {};

void CMethod::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CMethodList:
//-------------------------------------------------------------------------------------------------

CMethodList::CMethodList() {
	methods = std::vector<std::unique_ptr<CMethod> >();
}

void CMethodList::Add(CMethod* _method) {
	methods.push_back(std::unique_ptr<CMethod>(_method));
}

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

CClassList::CClassList() {
	classes = std::vector<std::unique_ptr<CClass> >();
}

void CClassList::Add(CClass* cClass) {
	classes.push_back(std::unique_ptr<CClass>(cClass));
}

void CClassList::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CMainMethod:
//-------------------------------------------------------------------------------------------------

void CMainMethod::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CMainMethod::CMainMethod() {}

CMainMethod::CMainMethod(CType* _returnType, CIdExp* _args, CFieldList* _vars, CCompoundStm* _statements) {
	returnType = std::unique_ptr<CType>(_returnType);
	args = std::unique_ptr<CIdExp>(_args);
	statements = std::unique_ptr<CCompoundStm>(_statements);
	vars = std::unique_ptr<CFieldList>(_vars);

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