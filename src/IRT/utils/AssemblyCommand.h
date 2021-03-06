//
// Created by izeren on 4/27/17.
//
#pragma once

#include <vector>
#include <map>
#include <memory>

#include "../utils/Temporary.h"
#include "Label.h"


#define REG IRT::CTemp

#define AssemblyCommands std::vector<std::shared_ptr<AssemblyCode::AssemblyCommand>>

namespace AssemblyCode {
    class RegisterInfo;

    class AssemblyCommand {
    public:
        virtual std::vector<IRT::CTemp> GetIn( ) const = 0;

        virtual std::vector<IRT::CTemp> GetOut( ) const = 0;

        virtual std::string ToString( ) const = 0;

        virtual void colorToRegisterChange(std::map<std::string, int>& tempToColorMap,
                                           AssemblyCode::RegisterInfo& registerInfo) = 0;

        virtual void processMemoryTemps(std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                        AssemblyCommands& newAssemblyCommands,
                                        std::map<std::string, int>& spilledToOffset,
                                        IRT::CTemp& beginSP) = 0;
    };


    class AddRegRegCommand : public AssemblyCommand {
    public:
        std::vector<IRT::CTemp> GetIn( ) const override;

        AddRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand );

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands,
                                 std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp& beginSP) override;

    private:
        REG leftOperand;
        REG rightOperand;

    };


    class SubRegRegCommand : public AssemblyCommand {
    public:
        std::vector<IRT::CTemp> GetIn( ) const override;

        SubRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand );

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        REG rightOperand;

    };

    class MulRegRegCommand : public AssemblyCommand {
    public:
        std::vector<IRT::CTemp> GetIn( ) const override;

        MulRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand );

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        REG rightOperand;

    };

    class DivRegRegCommand : public AssemblyCommand {
    public:
        std::vector<IRT::CTemp> GetIn( ) const override;

        DivRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand );

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        REG rightOperand;

    };

    class MoveRegRegCommand : public AssemblyCommand {
    public:
        MoveRegRegCommand( REG _target, REG _source );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        std::string getTarget() const;

        std::string getSource() const;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG source;
        REG target;
    };

    class MoveRegConstCommand : public AssemblyCommand {
    public:

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        MoveRegConstCommand( const IRT::CTemp &target, int source );

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        int source;
    };

    class MoveRegMemCommand : public AssemblyCommand {
    public:

        std::vector<IRT::CTemp> GetIn( ) const override;

        MoveRegMemCommand( const IRT::CTemp &target, const IRT::CTemp &sourse );

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        REG source;
    };

    class LabelCommand : public AssemblyCommand {
    public:

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        LabelCommand( const std::string &label );

        std::string getLabel() const;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        std::string label;
    };

    class NameCommand : public AssemblyCommand {
    public:
        NameCommand( const IRT::CTemp &target, const std::string &name );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        std::string name;
    };


    class CallCommand : public AssemblyCommand {
    public:
        CallCommand( const IRT::CLabel &address, const std::vector<IRT::CTemp> &arguments );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        IRT::CLabel address;
        std::vector<IRT::CTemp> arguments;
    };

    class AbstractJumpCommand : public AssemblyCommand {
    public:

        AbstractJumpCommand(const std::string &label);

        std::string getLabel() const;
    protected:
        std::string label;
    };

    class JumpCommand : public AbstractJumpCommand {
    public:
        JumpCommand( const std::string &label );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    };


    class CJumpLessCommand : public AbstractJumpCommand {
    public:
        CJumpLessCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand, const std::string &label );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        REG rightOperand;
    };

    class CJumpEqualCommand : public AbstractJumpCommand {
    public:
        CJumpEqualCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand, const std::string &label );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        REG rightOperand;
    };

    class CJumpNotEqualCommand : public AbstractJumpCommand {
    public:
        CJumpNotEqualCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand, const std::string &label );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        REG rightOperand;
    };

    class AddRegConstCommand : public AssemblyCommand {
    public:
        AddRegConstCommand( const IRT::CTemp leftOperand, int constant );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        int constant;

    };

    class MoveMemFromRegPlusConstToReg : public AssemblyCommand {
    public:
        MoveMemFromRegPlusConstToReg( const IRT::CTemp &target, const IRT::CTemp &source, int constant );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        REG source;
        int constant;

    };

    class MoveMemFromConstCommand : public AssemblyCommand {
    public:
        MoveMemFromConstCommand( const IRT::CTemp &target, int constant );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        int constant;

    };

    class MoveRegToMemByRegPlusConst : public AssemblyCommand {
    public:
        MoveRegToMemByRegPlusConst( const IRT::CTemp &target, int constant, const IRT::CTemp &source );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        int constant;
        REG source;

    };

    class MoveRegToMemByConst : public AssemblyCommand {
    public:
        MoveRegToMemByConst( int constant, const IRT::CTemp &source );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        int constant;
        REG source;
    };


    class MoveRegToMemByReg : public AssemblyCommand {
    public:
        MoveRegToMemByReg( const IRT::CTemp &target, const IRT::CTemp &source );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        REG source;
    };


    class MoveRegFromMemToMemByReg : public AssemblyCommand {
    public:
        MoveRegFromMemToMemByReg( const IRT::CTemp &target, const IRT::CTemp &source );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        REG source;
    };

    class SubRegConstCommand : public AssemblyCommand {
    public:
        SubRegConstCommand( const IRT::CTemp leftOperand, int rightConst );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG leftOperand;
        int rightConst;

    };


    class MoveToRegFromMemByReg : public AssemblyCommand {
    public:
        MoveToRegFromMemByReg( const IRT::CTemp &leftOperand, const IRT::CTemp &address );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        REG target;
        REG source;

    };

    class CommentCommand : public AssemblyCommand {
    public:

        CommentCommand( const std::string &comment );

        std::vector<IRT::CTemp> GetIn( ) const override;

        std::vector<IRT::CTemp> GetOut( ) const override;

        std::string ToString( ) const override;

        void colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                    AssemblyCode::RegisterInfo &registerInfo ) override;

        void processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 AssemblyCommands &newAssemblyCommands, std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp &beginSP ) override;

    private:
        std::string comment;
    };

};

#undef REG
#undef AssemblyCommands