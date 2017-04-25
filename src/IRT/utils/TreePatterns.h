//
// Created by izeren on 4/25/17.
//
#pragma once

#include <memory>
#include <string>

#include "../nodes/INode.h"


namespace IRT {

    class TreePattern {
    public:
        TreePattern();
        virtual ~TreePattern( );
        virtual std::shared_ptr<IRT::INode> GetPatternRepresentation();
        virtual std::string GetStringRepresentation();

    protected:
        std::shared_ptr<IRT::INode> treeRepresentation;
        std::string stringRepresentation;
    };

    class RegPlusRegToRegPattern : public TreePattern {

    public:
        RegPlusRegToRegPattern( );
    };

    class RegMinusRegToRegPattern : public TreePattern {
    public:
        RegMinusRegToRegPattern( );
    };

    class RegMulRegToRegPattern : public TreePattern {
    public:
        RegMulRegToRegPattern( );
    };

    class RegModRegToRegPattern :public TreePattern {
    public:
        RegModRegToRegPattern( );
    };

    class RegPlusConstToRegPattern : public  TreePattern {
    public:
        RegPlusConstToRegPattern( );
    };

    class ConstPlusRegToRegPattern : public  TreePattern {
    public:
        ConstPlusRegToRegPattern( );
    };

    class ConstToRegPattern : public TreePattern {
    public:
        ConstToRegPattern( );
    };

    class RegMinusConstToRegPattern : public TreePattern {
    public:
        RegMinusConstToRegPattern( );
    };

    class MemFromRegPlusConstToRegPattern : public TreePattern {
    public:
        MemFromRegPlusConstToRegPattern( );
    };

    class MemFromConstPlusRegToRegPattern : public TreePattern {
    public:
        MemFromConstPlusRegToRegPattern( );
    };

    class MemFromConstToRegPattern : public TreePattern {
    public:
        MemFromConstToRegPattern( );
    };

    class MemFromRegToRegPattern : public TreePattern {
    public:
        MemFromRegToRegPattern( );
    };

    class MoveFromMemFromRegPlusConstToRegPattern : public TreePattern {
    public:
        MoveFromMemFromRegPlusConstToRegPattern( );
    };

    class MoveFromMemFromConstPlusRegToRegPattern : public TreePattern {
    public:
        MoveFromMemFromConstPlusRegToRegPattern( );
    };

    class MoveFromMemFromConstToRegPattern : public TreePattern {
    public:
        MoveFromMemFromConstToRegPattern( );
    };

    class MoveFromMemFromRegToRegPattern : public TreePattern {
    public:
        MoveFromMemFromRegToRegPattern( );
    };

    class MoveFromMemFromRegToMemToRegPattern : public TreePattern {
    public:
        MoveFromMemFromRegToMemToRegPattern( );
    };


};
