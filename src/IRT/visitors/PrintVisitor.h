#pragma once

#include "IVisitor.h"
#include "../nodes/INode.h"
#include "../nodes/Expressions.h"
#include "../nodes/Statements.h"

#include <string>
#include <vector>

namespace IRT {

    struct ChildrenAnswers {
        void PushBack(std::string description, int id);

        std::vector<std::string> descriptions;
        std::vector<int> ids;
    };

    class PrintVisitor : public IVisitor {
    public:

        PrintVisitor();

        virtual void Visit( const CEseqExpression &expression ) override;
        virtual void Visit( const CBinopExpression &expression ) override;
        virtual void Visit( const CConstExpression &expression ) override;
        virtual void Visit( const CTempExpression &expression ) override;
        virtual void Visit( const CNameExpression &expression ) override;
        virtual void Visit( const CCallExpression &expression ) override;
        virtual void Visit( const CMemExpression &expression ) override;
        virtual void Visit( const CExpressionList &expression ) override;

        virtual void Visit( const CMoveStatement &statement ) override;
        virtual void Visit( const CExpStatement &statement ) override;
        virtual void Visit( const CLabelStatement &statement ) override;
        virtual void Visit( const CJumpStatement &statement ) override;
        virtual void Visit( const CJumpConditionalStatement &statement ) override;
        virtual void Visit( const CSeqStatement &statement ) override;
        virtual void Visit( const CStatementList &statement ) override;

        std::string GetResult();

    private:
        ChildrenAnswers VisitChildren(std::vector<const INode*> children);
        void AddChildrenDescriptions(ChildrenAnswers answers);
        void AddChildrenIds(ChildrenAnswers answers);
        void AddChildrenAnswers(ChildrenAnswers answers);
        std::string ConstructLabel(std::string label, int id);
        void AddLabel(std::string label);
        void AddArrow(int child_id);

        int lastVisited;
        std::string description;
    };

}
