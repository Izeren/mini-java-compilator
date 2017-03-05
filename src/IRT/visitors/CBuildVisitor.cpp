//
// Created by izeren on 3/4/17.
//

#include "../../shared_ptrs_nodes/Expressions.h"
#include "CBuildVisitor.h"
#include "../../bison.hpp"

void CBuildVisitor::Visit( CIdExp &exp ) {

}

void CBuildVisitor::Visit( CIdPtrExp &exp ) {

}

void CBuildVisitor::Visit( CNumExp &exp ) {

}

void CBuildVisitor::Visit( COpExp &exp ) {

}

void CBuildVisitor::Visit( CLogExp &exp ) {

}

void CBuildVisitor::Visit( CLogOpExp &exp ) {

}

void CBuildVisitor::Visit( CCompExp &exp ) {

}

void CBuildVisitor::Visit( CUnarMinusExp &exp ) {

}

void CBuildVisitor::Visit( CGetLengthExp &exp ) {

}

void CBuildVisitor::Visit( CGetFieldExp &exp ) {

}

void CBuildVisitor::Visit( CCallMethodExp &exp ) {

}

void CBuildVisitor::Visit( CExpList &exp ) {

}

void CBuildVisitor::Visit( CNegativeExpression &exp ) {

}

void CBuildVisitor::Visit( CArrayExpression &exp ) {

}

void CBuildVisitor::Visit( CThisExpression &exp ) {

}

void CBuildVisitor::Visit( CByIndexExpression &exp ) {

}

void CBuildVisitor::Visit( CNewIdentifier &exp ) {

}

void CBuildVisitor::Visit( CAssignStm &stm ) {

}

void CBuildVisitor::Visit( CAssignSubscriptStm &stm ) {

}

void CBuildVisitor::Visit( CCompoundStm &stm ) {

}

void CBuildVisitor::Visit( CPrintStm &stm ) {

}

void CBuildVisitor::Visit( CSimpleStm &stm ) {

}

void CBuildVisitor::Visit( CIfStm &stm ) {

}

void CBuildVisitor::Visit( CWhileStm &stm ) {

}

void CBuildVisitor::Visit( CType &stm ) {

}

void CBuildVisitor::Visit( CField &stm ) {

}

void CBuildVisitor::Visit( CFieldList &stm ) {

}

void CBuildVisitor::Visit( CArgument &stm ) {

}

void CBuildVisitor::Visit( CArgumentList &stm ) {

}

void CBuildVisitor::Visit( CMethod &stm ) {

}

void CBuildVisitor::Visit( CMethodList &stm ) {

}

void CBuildVisitor::Visit( CClass &stm ) {

}

void CBuildVisitor::Visit( CClassList &stm ) {

}

void CBuildVisitor::Visit( CMainMethod &stm ) {

}

void CBuildVisitor::Visit( CMainClass &stm ) {

}

void CBuildVisitor::Visit( CProgram &stm ) {

}

std::unique_ptr<const MethodToIRTMap> CBuildVisitor::GetMethodFromIrtMap() {
    return std::unique_ptr<const MethodToIRTMap>();
}

IRT::enums::TOperationType CBuildVisitor::operatorAst2Irt( enums::TOperation type ) const {
    return IRT::enums::TOperationType::MOD;
}

void CBuildVisitor::updateSubtreeWrapper( IRT::ISubtreeWrapper *wrapper ) {

}

void CBuildVisitor::updateSubtreeWrapper( std::unique_ptr<IRT::ISubtreeWrapper> wrapper ) {

}

std::string CBuildVisitor::GetMethodFullName( const std::string &className, const std::string &methodName ) {
    return std::__cxx11::string();
}

template<class InputIteratorArguments, class InputIteratorLocals, class InputIteratorFields>
void CBuildVisitor::buildNewFrame( const std::string &className, const std::string &methodName,
                                   InputIteratorArguments argumentsLeftIt, InputIteratorArguments argumentsRightIt,
                                   InputIteratorLocals localsLeftIt, InputIteratorLocals localsRightIt,
                                   InputIteratorFields fieldsLeftIt, InputIteratorFields fieldsRightIt ) {

}

void CBuildVisitor::buildNewFrame( const CMethod *declaration ) {

}

void CBuildVisitor::buildNewFrame( const CMainClass *mainClass ) {

}
