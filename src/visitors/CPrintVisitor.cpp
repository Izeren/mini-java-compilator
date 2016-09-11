#include "CPrintVisitor.h"
#include ""
#include <iostream>

CPrintVisitor::CPrintVisitor() {
	currentId = 0;
}

IVisitorResult CPrintVisitor::Visit(CPrintStm *stm) {

	CPrintResults result = stm->Accept(this);


}

IVisitorResult Visit(CCompoundStm *stm);

IVisitorResult Visit(COpExp *exp);

IVisitorResult Visit(CNumExp *exp);

IVisitorResult Visit(CIdExp *exp);

IVisitorResult Visit(CAssignStm *exp);

