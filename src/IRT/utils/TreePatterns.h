//
// Created by izeren on 4/25/17.
//
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include "../nodes/INode.h"
#include "../utils/Temporary.h"
#include "AssemblyCommand.h"


using ChildrenTemps = std::vector<std::pair<IRT::CTemp, const IRT::INode *>>;
using AssemblyCommands = std::vector<AssemblyCode::AssemblyCommand>;

namespace IRT {

    class TreePattern {
    public:
        TreePattern( );

        virtual ~TreePattern( );

        virtual std::shared_ptr<IRT::INode> GetPatternRepresentation( );

        virtual std::string GetStringRepresentation( );

        virtual bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                        AssemblyCommands &commands ) = 0;

    protected:
        std::shared_ptr<IRT::INode> treeRepresentation;
        std::string stringRepresentation;
    };

    class RegPlusRegPattern : public TreePattern {

    public:
        RegPlusRegPattern( );

        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class RegMinusRegPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;

        RegMinusRegPattern( );
    };

    class RegMulRegPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;

        RegMulRegPattern( );
    };

    class RegModRegPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;

        RegModRegPattern( );
    };

    class ConstPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class MemPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class RegPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class LabelPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class NamePattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class ExpPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class CallPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

    class MoveRegRegPattern : public TreePattern {
    public:
        bool TryToGenerateCode( const INode *tree, const CTemp &dest, ChildrenTemps &children,
                                AssemblyCommands &commands ) override;
    };

};
