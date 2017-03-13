//
// Created by izeren on 3/4/17.
//
#pragma once

#include "../../shared_ptrs_nodes/INode.h"
#include "../../shared_ptrs_nodes/Expressions.h"
#include "../../shared_ptrs_nodes/Statements.h"
#include "../../shared_ptrs_nodes/Classes.h"

#include "../../shared_ptrs_visitors/IVisitor.h"

#include "../utils/SubtreeWrapper.h"
#include "../utils/Frame.h"

#include "../../symbol_table/SymbolInfo.h"
#include <map>
#include <utility>

using MethodToIRTMap = std::map<std::string, std::unique_ptr<const IRT::CStatement>>;
using FramesMap = std::map<std::string, std::unique_ptr<const IRT::CFrame>>;

class CBuildVisitor : public IVisitor {
public:
    CBuildVisitor( const SymbolTable *table )
            : symbolTable( table ), treesOfMethods( std::move(std::unique_ptr<MethodToIRTMap>(new MethodToIRTMap()))) {}


	void Visit( CIdExp &exp ) override;
	void Visit( CIdPtrExp &exp ) override;
	void Visit( CNumExp &exp ) override;
	void Visit( COpExp &exp ) override;
	void Visit( CLogExp &exp ) override;
	void Visit( CLogOpExp &exp ) override;
	void Visit( CCompExp &exp ) override;
	void Visit( CUnarMinusExp &exp ) override;
	void Visit( CGetLengthExp &exp ) override;
	void Visit( CGetFieldExp &exp ) override;
	void Visit( CCallMethodExp &exp ) override;
	void Visit( CExpList &exp ) override;
	void Visit( CNegativeExpression &exp ) override;
	void Visit( CArrayExpression &exp ) override;
	void Visit( CThisExpression &exp ) override;
	void Visit( CByIndexExpression &exp ) override;
	void Visit( CNewIdentifier &exp ) override;

	void Visit( CAssignStm &stm ) override;
	void Visit( CAssignSubscriptStm &stm ) override;
	void Visit( CCompoundStm &stm ) override;
	void Visit( CPrintStm &stm ) override;
	void Visit( CSimpleStm &stm ) override;
	void Visit( CIfStm &stm ) override;
	void Visit( CWhileStm &stm ) override;

	void Visit( CType &stm ) override;
	void Visit( CField &stm ) override;
	void Visit( CFieldList &stm ) override;
	void Visit( CArgument &stm ) override;
	void Visit( CArgumentList &stm ) override;
	void Visit( CMethod &stm ) override;
	void Visit( CMethodList &stm ) override;
	void Visit( CClass &stm ) override;
	void Visit( CClassList &stm ) override;
	void Visit( CMainMethod &stm ) override;
	void Visit( CMainClass &stm ) override;
	void Visit( CProgram &stm ) override;

	std::unique_ptr<const MethodToIRTMap> GetMethodFromIrtMap();

private:

    IRT::enums::TOperationType operatorAst2Irt( enums::TOperation type ) const;

    IRT::enums::TOperationType logOperatorAst2Irt( enums::TLogicalOperation type ) const;

    void updateSubtreeWrapper( IRT::ISubtreeWrapper *wrapper );

    void updateSubtreeWrapper( std::unique_ptr<IRT::ISubtreeWrapper> wrapper );

    std::string GetMethodFullName( const std::string &className, const std::string &methodName );

    template<class InputIteratorArguments, class InputIteratorLocals, class InputIteratorFields>
    void buildNewFrame( const std::string &className, const std::string &methodName,
                        InputIteratorArguments argumentsLeftIt, InputIteratorArguments argumentsRightIt,
                        InputIteratorLocals localsLeftIt, InputIteratorLocals localsRightIt,
                        InputIteratorFields fieldsLeftIt, InputIteratorFields fieldsRightIt );

    void buildNewFrame( const CMethod *declaration );

    void buildNewFrame( const CMainClass *mainClass );

    std::unique_ptr<IRT::ISubtreeWrapper> wrapper;

    const SymbolTable *symbolTable;

    std::string currentClassName;
    FramesMap frames;
    IRT::CFrame *currentFrame;

    std::string nameOfMethodParentClass;

    std::unique_ptr<MethodToIRTMap> treesOfMethods;
};

