//
// Created by izeren on 4/27/17.
//

#include <cassert>
#include "AssemblyCommand.h"
#include "../register_allocation/RegisterAllocation.h"

std::shared_ptr<AssemblyCode::AssemblyCommand> createLoad(IRT::CTemp& target, int offset, IRT::CTemp& beginSP) {
    return std::make_shared<AssemblyCode::MoveMemFromRegPlusConstToReg>(target, beginSP, -offset);
}

std::shared_ptr<AssemblyCode::AssemblyCommand> createStore(IRT::CTemp& source, int offset, IRT::CTemp& beginSP) {
    return std::make_shared<AssemblyCode::MoveRegToMemByRegPlusConst>(beginSP, -offset, source);
}

void leftRightProcessMemoryTemps(AssemblyCommands &newAssemblyCommands,
                                 std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp& beginSP,
                                 std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 IRT::CTemp& leftOperand,
                                 IRT::CTemp& rightOperand,
                                 bool shouldLoadLeft = true,
                                 bool shouldStoreLeft = true) {

    assert(shouldLoadLeft || shouldStoreLeft);

    std::string leftName = leftOperand.ToString();
    std::string rightName = rightOperand.ToString();

    auto leftFind = spilledToOffset.find(leftOperand.ToString());
    auto rightFind = spilledToOffset.find(rightOperand.ToString());

    if (rightFind != spilledToOffset.end()) {
        IRT::CTemp rightTemp;
        newAssemblyCommands.push_back(createLoad(rightTemp, rightFind->second, beginSP));

        rightName = rightTemp.ToString();
    }

    if (leftFind != spilledToOffset.end()) {
        IRT::CTemp leftTemp;
        if (shouldLoadLeft) {
            newAssemblyCommands.push_back( createLoad( leftTemp, leftFind->second, beginSP ));
        }
        leftName = leftTemp.ToString( );

        newAssemblyCommands.push_back(thisShared);

        if (shouldStoreLeft) {
            newAssemblyCommands.push_back( createStore( leftTemp, leftFind->second, beginSP ));
        }
    } else {
        newAssemblyCommands.push_back(thisShared);
    }

    leftOperand.setName(leftName);
    rightOperand.setName(rightName);
}

void onlyRightProcessMemoryTemps(AssemblyCommands &newAssemblyCommands,
                                 std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp& beginSP,
                                 std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 IRT::CTemp& rightOperand) {

    std::string rightName = rightOperand.ToString();

    auto rightFind = spilledToOffset.find(rightOperand.ToString());

    if (rightFind != spilledToOffset.end()) {
        IRT::CTemp rightTemp;
        newAssemblyCommands.push_back(createLoad(rightTemp, rightFind->second, beginSP));

        rightName = rightTemp.ToString();
    }

    newAssemblyCommands.push_back(thisShared);

    rightOperand.setName(rightName);
}

void onlyLeftProcessMemoryTemps(AssemblyCommands &newAssemblyCommands,
                                 std::map<std::string, int> &spilledToOffset,
                                 IRT::CTemp& beginSP,
                                 std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                 IRT::CTemp& leftOperand,
                                 bool shouldLoadLeft = true,
                                 bool shouldStoreLeft = true) {

    std::string leftName = leftOperand.ToString();

    auto leftFind = spilledToOffset.find(leftOperand.ToString());

    if (leftFind != spilledToOffset.end()) {
        IRT::CTemp leftTemp;
        if (shouldLoadLeft) {
            newAssemblyCommands.push_back( createLoad( leftTemp, leftFind->second, beginSP ));
        }
        leftName = leftTemp.ToString();

        newAssemblyCommands.push_back(thisShared);

        if (shouldStoreLeft) {
            newAssemblyCommands.push_back( createStore( leftTemp, leftFind->second, beginSP ));
        }
    } else {
        newAssemblyCommands.push_back(thisShared);
    }

    leftOperand.setName(leftName);
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<IRT::CTemp> AssemblyCode::MoveRegRegCommand::GetIn( ) const {
    return { source };
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegRegCommand::GetOut( ) const {
    return { target };
}

AssemblyCode::MoveRegRegCommand::MoveRegRegCommand(
        IRT::CTemp _target, IRT::CTemp _source
) : source( _source ), target( _target ) { }

std::string AssemblyCode::MoveRegRegCommand::ToString( ) const {
    return "mov " + target.ToString( ) + " " + source.ToString( ) + "\n";
}

std::string AssemblyCode::MoveRegRegCommand::getTarget() const {
    return target.ToString();
}

std::string AssemblyCode::MoveRegRegCommand::getSource() const {
    return source.ToString();
}

void AssemblyCode::MoveRegRegCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                             AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(source, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
}

void AssemblyCode::MoveRegRegCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                          AssemblyCommands &newAssemblyCommands,
                                                          std::map<std::string, int> &spilledToOffset,
                                                          IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, target, source, false);

}

//----------------------------------------------------------------------------------------------------------------------

std::vector<IRT::CTemp> AssemblyCode::AddRegRegCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

std::vector<IRT::CTemp> AssemblyCode::AddRegRegCommand::GetOut( ) const {
    return { leftOperand };
}

std::string AssemblyCode::AddRegRegCommand::ToString( ) const {
    return "add " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\n";
}

AssemblyCode::AddRegRegCommand::AddRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand )
        : leftOperand( leftOperand ), rightOperand( rightOperand ) { }

void AssemblyCode::AddRegRegCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                            AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(rightOperand, tempToColorMap, registerInfo);
}

void AssemblyCode::AddRegRegCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                         AssemblyCommands &newAssemblyCommands,
                                                         std::map<std::string, int> &spilledToOffset,
                                                         IRT::CTemp& beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, leftOperand, rightOperand);
}


//----------------------------------------------------------------------------------------------------------------------
std::vector<IRT::CTemp> AssemblyCode::SubRegRegCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

AssemblyCode::SubRegRegCommand::SubRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand )
        : leftOperand( leftOperand ), rightOperand( rightOperand ) { }

std::vector<IRT::CTemp> AssemblyCode::SubRegRegCommand::GetOut( ) const {
    return { leftOperand };
}

std::string AssemblyCode::SubRegRegCommand::ToString( ) const {
    return "sub " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\n";
}

void AssemblyCode::SubRegRegCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                            AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(rightOperand, tempToColorMap, registerInfo);
}

void AssemblyCode::SubRegRegCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                         AssemblyCommands &newAssemblyCommands,
                                                         std::map<std::string, int> &spilledToOffset,
                                                         IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, leftOperand, rightOperand);

}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MulRegRegCommand::MulRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand )
        : leftOperand( leftOperand ), rightOperand( rightOperand ) { }

std::vector<IRT::CTemp> AssemblyCode::MulRegRegCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

std::vector<IRT::CTemp> AssemblyCode::MulRegRegCommand::GetOut( ) const {
    return { leftOperand };
}

std::string AssemblyCode::MulRegRegCommand::ToString( ) const {
    return "imul " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\n";
}

void AssemblyCode::MulRegRegCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                            AssemblyCode::RegisterInfo &registerInfo ) {

    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(rightOperand, tempToColorMap, registerInfo);

}

void AssemblyCode::MulRegRegCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                         AssemblyCommands &newAssemblyCommands,
                                                         std::map<std::string, int> &spilledToOffset,
                                                         IRT::CTemp &beginSP ) {
    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, leftOperand, rightOperand);


}

//----------------------------------------------------------------------------------------------------------------------
std::vector<IRT::CTemp> AssemblyCode::DivRegRegCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

std::vector<IRT::CTemp> AssemblyCode::DivRegRegCommand::GetOut( ) const {
    return { leftOperand };
}

std::string AssemblyCode::DivRegRegCommand::ToString( ) const {
    return "idiv " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\n";
}

AssemblyCode::DivRegRegCommand::DivRegRegCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand )
        : leftOperand( leftOperand ), rightOperand( rightOperand ) { }

void AssemblyCode::DivRegRegCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                            AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(rightOperand, tempToColorMap, registerInfo);

}

void AssemblyCode::DivRegRegCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                         AssemblyCommands &newAssemblyCommands,
                                                         std::map<std::string, int> &spilledToOffset,
                                                         IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, leftOperand, rightOperand);

}

//----------------------------------------------------------------------------------------------------------------------
std::vector<IRT::CTemp> AssemblyCode::MoveRegConstCommand::GetIn( ) const {
    return { };
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegConstCommand::GetOut( ) const {
    return { target };
}

std::string AssemblyCode::MoveRegConstCommand::ToString( ) const {
    return "mov " + target.ToString( ) + " " + std::to_string( source ) + "\n";
}

AssemblyCode::MoveRegConstCommand::MoveRegConstCommand( const IRT::CTemp &target, int source ) : target( target ),
                                                                                                 source( source ) { }

void AssemblyCode::MoveRegConstCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                               AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);

}

void AssemblyCode::MoveRegConstCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                            AssemblyCommands &newAssemblyCommands,
                                                            std::map<std::string, int> &spilledToOffset,
                                                            IRT::CTemp &beginSP ) {

    onlyLeftProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, target, false);

}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MoveRegMemCommand::MoveRegMemCommand( const IRT::CTemp &target, const IRT::CTemp &source ) : target(
        target ), source( source ) { }

std::vector<IRT::CTemp> AssemblyCode::MoveRegMemCommand::GetIn( ) const {
    return { source };
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegMemCommand::GetOut( ) const {
    return { target };
}

std::string AssemblyCode::MoveRegMemCommand::ToString( ) const {
    return "mov " + target.ToString( ) + " [" + source.ToString( ) + "]\n";
}

void AssemblyCode::MoveRegMemCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                             AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(source, tempToColorMap, registerInfo);

}

void AssemblyCode::MoveRegMemCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                          AssemblyCommands &newAssemblyCommands,
                                                          std::map<std::string, int> &spilledToOffset,
                                                          IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, target, source, false);

}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::LabelCommand::LabelCommand( const std::string &label ) : label( label ) { }

std::vector<IRT::CTemp> AssemblyCode::LabelCommand::GetIn( ) const {
    return { };
}

std::vector<IRT::CTemp> AssemblyCode::LabelCommand::GetOut( ) const {
    return { };
}

std::string AssemblyCode::LabelCommand::ToString( ) const {
    return label + ":\n";
}

std::string AssemblyCode::LabelCommand::getLabel() const {
    return label;
}

void AssemblyCode::LabelCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                        AssemblyCode::RegisterInfo &registerInfo ) {

}

void AssemblyCode::LabelCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                     AssemblyCommands &newAssemblyCommands,
                                                     std::map<std::string, int> &spilledToOffset,
                                                     IRT::CTemp &beginSP ) {

    newAssemblyCommands.push_back(thisShared);

}

//----------------------------------------------------------------------------------------------------------------------
std::vector<IRT::CTemp> AssemblyCode::NameCommand::GetIn( ) const {
    return { };
}

AssemblyCode::NameCommand::NameCommand( const IRT::CTemp &target, const std::string &name ) : target( target ),
                                                                                              name( name ) { }

std::vector<IRT::CTemp> AssemblyCode::NameCommand::GetOut( ) const {
    return { target };
}

std::string AssemblyCode::NameCommand::ToString( ) const {
    return "mov " + target.ToString( ) + " \"" + name + "\"\n";
}

void AssemblyCode::NameCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                       AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
}

void AssemblyCode::NameCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                    AssemblyCommands &newAssemblyCommands,
                                                    std::map<std::string, int> &spilledToOffset, IRT::CTemp &beginSP ) {

    onlyLeftProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, target);

}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::CallCommand::CallCommand( const IRT::CTemp &address, const std::vector<IRT::CTemp> &arguments )
        : address( address ), arguments( arguments ) { }

std::vector<IRT::CTemp> AssemblyCode::CallCommand::GetIn( ) const {
    std::vector<IRT::CTemp> in;
    in.push_back( address );
//    for ( auto argument : arguments ) {
//        in.push_back( argument );
//    }
    return in;
}

std::vector<IRT::CTemp> AssemblyCode::CallCommand::GetOut( ) const {
    return { };
}

std::string AssemblyCode::CallCommand::ToString( ) const {
    std::string command = "call (" + address.ToString( ) + ") ";
    for ( auto argument : arguments ) {
        command += argument.ToString( ) + " ";
    }
    return command + "\n";
}

void AssemblyCode::CallCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                       AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(address, tempToColorMap, registerInfo);
    for ( auto argTemp : arguments) {
        AssemblyCode::colorToRegisterChange( argTemp, tempToColorMap, registerInfo );
    }
}

void AssemblyCode::CallCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                    AssemblyCommands &newAssemblyCommands,
                                                    std::map<std::string, int> &spilledToOffset, IRT::CTemp &beginSP ) {

    onlyRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP, thisShared, address);

}

//----------------------------------------------------------------------------------------------------------------------
std::string AssemblyCode::AbstractJumpCommand::getLabel() const {
    return label;
}

AssemblyCode::AbstractJumpCommand::AbstractJumpCommand(const std::string& label) : label(label) {

}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::JumpCommand::JumpCommand( const std::string &label ) : AbstractJumpCommand( label ) { }

std::vector<IRT::CTemp> AssemblyCode::JumpCommand::GetIn( ) const {
    return { };
}

std::vector<IRT::CTemp> AssemblyCode::JumpCommand::GetOut( ) const {
    return { };
}

std::string AssemblyCode::JumpCommand::ToString( ) const {
    return "jmp " + label + "\n";
}

void AssemblyCode::JumpCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                       AssemblyCode::RegisterInfo &registerInfo ) {

}

void AssemblyCode::JumpCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                    AssemblyCommands &newAssemblyCommands,
                                                    std::map<std::string, int> &spilledToOffset, IRT::CTemp &beginSP ) {

    newAssemblyCommands.push_back(thisShared);

}

//----------------------------------------------------------------------------------------------------------------------
std::vector<IRT::CTemp> AssemblyCode::CJumpLessCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

std::vector<IRT::CTemp> AssemblyCode::CJumpLessCommand::GetOut( ) const {
    return { };
}

std::string AssemblyCode::CJumpLessCommand::ToString( ) const {
    return "cmp " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\njl " + label + "\n";
}

AssemblyCode::CJumpLessCommand::CJumpLessCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand,
                                                  const std::string &label ) : AbstractJumpCommand( label ),
                                                                               leftOperand( leftOperand ),
                                                                               rightOperand( rightOperand ) { }

void AssemblyCode::CJumpLessCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                            AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(rightOperand, tempToColorMap, registerInfo);
}

void AssemblyCode::CJumpLessCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                         AssemblyCommands &newAssemblyCommands,
                                                         std::map<std::string, int> &spilledToOffset,
                                                         IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, leftOperand, rightOperand, /* load left */ true, /* store left */ false);

}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::CJumpEqualCommand::CJumpEqualCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand,
                                                    const std::string &label ) : leftOperand( leftOperand ),
                                                                                 rightOperand( rightOperand ),
                                                                                 AbstractJumpCommand( label ) { }

std::vector<IRT::CTemp> AssemblyCode::CJumpEqualCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

std::vector<IRT::CTemp> AssemblyCode::CJumpEqualCommand::GetOut( ) const {
    return { };
}

std::string AssemblyCode::CJumpEqualCommand::ToString( ) const {
    return "cmp " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\nje " + label + "\n";

}

void AssemblyCode::CJumpEqualCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                             AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(rightOperand, tempToColorMap, registerInfo);
}

void AssemblyCode::CJumpEqualCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                          AssemblyCommands &newAssemblyCommands,
                                                          std::map<std::string, int> &spilledToOffset,
                                                          IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, leftOperand, rightOperand, /* load left */ true, /* store left */ false);

}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::CJumpNotEqualCommand::CJumpNotEqualCommand( const IRT::CTemp leftOperand, const IRT::CTemp rightOperand,
                                                          const std::string &label ) : leftOperand( leftOperand ),
                                                                                       rightOperand( rightOperand ),
                                                                                       AbstractJumpCommand( label ) { }

std::vector<IRT::CTemp> AssemblyCode::CJumpNotEqualCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

std::vector<IRT::CTemp> AssemblyCode::CJumpNotEqualCommand::GetOut( ) const {
    return { };
}

std::string AssemblyCode::CJumpNotEqualCommand::ToString( ) const {
    return "cmp " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\njne " + label + "\n";
}

void AssemblyCode::CJumpNotEqualCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                                AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(rightOperand, tempToColorMap, registerInfo);

}

void AssemblyCode::CJumpNotEqualCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                             AssemblyCommands &newAssemblyCommands,
                                                             std::map<std::string, int> &spilledToOffset,
                                                             IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, leftOperand, rightOperand, /* load left */ true, /* store left */ false);

}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::AddRegConstCommand::AddRegConstCommand( const IRT::CTemp leftOperand, int constant ) : leftOperand(
        leftOperand ), constant( constant ) { }

std::vector<IRT::CTemp> AssemblyCode::AddRegConstCommand::GetIn( ) const {
    return { };
}

std::vector<IRT::CTemp> AssemblyCode::AddRegConstCommand::GetOut( ) const {
    return { leftOperand };
}

std::string AssemblyCode::AddRegConstCommand::ToString( ) const {
    return "add " + leftOperand.ToString( ) + " " + std::to_string( constant ) + "\n";
}

void AssemblyCode::AddRegConstCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                              AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);
}

void AssemblyCode::AddRegConstCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                           AssemblyCommands &newAssemblyCommands,
                                                           std::map<std::string, int> &spilledToOffset,
                                                           IRT::CTemp &beginSP ) {

    onlyLeftProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, leftOperand, /* load left */ true, /* store left */ true);

}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MoveMemFromRegPlusConstToReg::MoveMemFromRegPlusConstToReg( const IRT::CTemp &target,
                                                                          const IRT::CTemp &source, int constant )
        : target( target ), source( source ), constant( constant ) { }

std::vector<IRT::CTemp> AssemblyCode::MoveMemFromRegPlusConstToReg::GetIn( ) const {
    return { source };
}

std::vector<IRT::CTemp> AssemblyCode::MoveMemFromRegPlusConstToReg::GetOut( ) const {
    return { target };
}

std::string AssemblyCode::MoveMemFromRegPlusConstToReg::ToString( ) const {
    if (constant > 0) {
        return "mov " + target.ToString( ) + " [" + source.ToString( ) + " + " + std::to_string( constant ) + "]\n";
    } else {
        return "mov " + target.ToString( ) + " [" + source.ToString( ) + " - " + std::to_string( abs(constant) ) + "]\n";
    }
}

void AssemblyCode::MoveMemFromRegPlusConstToReg::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                                        AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(source, tempToColorMap, registerInfo);
}

void AssemblyCode::MoveMemFromRegPlusConstToReg::processMemoryTemps(
        std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared, AssemblyCommands &newAssemblyCommands,
        std::map<std::string, int> &spilledToOffset, IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, target, source, /* load left */ false, /* store left */ true);
}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MoveMemFromConstCommand::MoveMemFromConstCommand( const IRT::CTemp &target, int constant ) : target(
        target ), constant( constant ) { }

std::vector<IRT::CTemp> AssemblyCode::MoveMemFromConstCommand::GetIn( ) const {
    return {};
}

std::vector<IRT::CTemp> AssemblyCode::MoveMemFromConstCommand::GetOut( ) const {
    return {target};
}

std::string AssemblyCode::MoveMemFromConstCommand::ToString( ) const {
    return "mov " + target.ToString( ) + " [" + std::to_string( constant ) + "]\n";
}

void AssemblyCode::MoveMemFromConstCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                                   AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
}

void
AssemblyCode::MoveMemFromConstCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                           AssemblyCommands &newAssemblyCommands,
                                                           std::map<std::string, int> &spilledToOffset,
                                                           IRT::CTemp &beginSP ) {

    onlyLeftProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, target, /* load left */ false, /* store left */ true);

}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MoveRegToMemByRegPlusConst::MoveRegToMemByRegPlusConst( const IRT::CTemp &target, int constant,
                                                                      const IRT::CTemp &source ) : target( target ),
                                                                                                   constant( constant ),
                                                                                                   source( source ) { }

std::vector<IRT::CTemp> AssemblyCode::MoveRegToMemByRegPlusConst::GetIn( ) const {
    return {source};
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegToMemByRegPlusConst::GetOut( ) const {
    return {target};
}

std::string AssemblyCode::MoveRegToMemByRegPlusConst::ToString( ) const {
    if (constant > 0) {
        return "mov [" + target.ToString( ) + " + " + std::to_string( constant ) + "] " + source.ToString( ) + "\n";
    } else {
        return "mov [" + target.ToString( ) + " - " + std::to_string( abs(constant) ) + "] " + source.ToString( ) + "\n";
    }
}

void AssemblyCode::MoveRegToMemByRegPlusConst::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                                      AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(source, tempToColorMap, registerInfo);
}

void
AssemblyCode::MoveRegToMemByRegPlusConst::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                              AssemblyCommands &newAssemblyCommands,
                                                              std::map<std::string, int> &spilledToOffset,
                                                              IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, target, source, /* load left */ false, /* store left */ true);

}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MoveRegToMemByConst::MoveRegToMemByConst( int constant, const IRT::CTemp &source ) : constant( constant ),
                                                                                                   source( source ) { }

std::vector<IRT::CTemp> AssemblyCode::MoveRegToMemByConst::GetIn( ) const {
    return {source};
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegToMemByConst::GetOut( ) const {
    return {};
}

std::string AssemblyCode::MoveRegToMemByConst::ToString( ) const {
    return "mov [" + std::to_string( constant ) + "] " + source.ToString() + "\n";
}

void AssemblyCode::MoveRegToMemByConst::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                               AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(source, tempToColorMap, registerInfo);
}

void AssemblyCode::MoveRegToMemByConst::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                            AssemblyCommands &newAssemblyCommands,
                                                            std::map<std::string, int> &spilledToOffset,
                                                            IRT::CTemp &beginSP ) {

    onlyRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, source);

}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MoveRegToMemByReg::MoveRegToMemByReg( const IRT::CTemp &target, const IRT::CTemp &source ) : target(
        target ), source( source ) { }

std::vector<IRT::CTemp> AssemblyCode::MoveRegToMemByReg::GetIn( ) const {
    return {source};
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegToMemByReg::GetOut( ) const {
    return {target};
}

std::string AssemblyCode::MoveRegToMemByReg::ToString( ) const {
    return "mov [" + target.ToString() + "] " + source.ToString() + "\n";
}

void AssemblyCode::MoveRegToMemByReg::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                             AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(source, tempToColorMap, registerInfo);

}

void AssemblyCode::MoveRegToMemByReg::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                          AssemblyCommands &newAssemblyCommands,
                                                          std::map<std::string, int> &spilledToOffset,
                                                          IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, target, source, /* load left */ false, /* store left */ true);
}


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MoveRegFromMemToMemByReg::MoveRegFromMemToMemByReg( const IRT::CTemp &target, const IRT::CTemp &source )
        : target( target ), source( source ) { }

std::vector<IRT::CTemp> AssemblyCode::MoveRegFromMemToMemByReg::GetIn( ) const {
    return {source};
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegFromMemToMemByReg::GetOut( ) const {
    return {target};
}

std::string AssemblyCode::MoveRegFromMemToMemByReg::ToString( ) const {
    return "mov [" + target.ToString() + "] [" + source.ToString() + "]\n";
}

void AssemblyCode::MoveRegFromMemToMemByReg::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                                    AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(target, tempToColorMap, registerInfo);
    AssemblyCode::colorToRegisterChange(source, tempToColorMap, registerInfo);

}

void
AssemblyCode::MoveRegFromMemToMemByReg::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                            AssemblyCommands &newAssemblyCommands,
                                                            std::map<std::string, int> &spilledToOffset,
                                                            IRT::CTemp &beginSP ) {

    leftRightProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, target, source, /* load left */ false, /* store left */ true);

}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::SubRegConstCommand::SubRegConstCommand( const IRT::CTemp leftOperand, int rightConst ) : leftOperand(
        leftOperand ), rightConst( rightConst ) { }

std::vector<IRT::CTemp> AssemblyCode::SubRegConstCommand::GetIn( ) const {
    return { leftOperand };
}

std::vector<IRT::CTemp> AssemblyCode::SubRegConstCommand::GetOut( ) const {
    return { leftOperand };
}

std::string AssemblyCode::SubRegConstCommand::ToString( ) const {
    return "sub " + leftOperand.ToString() + " " + std::to_string(rightConst);
}

void AssemblyCode::SubRegConstCommand::colorToRegisterChange( std::map<std::string, int> &tempToColorMap,
                                                              AssemblyCode::RegisterInfo &registerInfo ) {
    AssemblyCode::colorToRegisterChange(leftOperand, tempToColorMap, registerInfo);

}

void AssemblyCode::SubRegConstCommand::processMemoryTemps( std::shared_ptr<AssemblyCode::AssemblyCommand> thisShared,
                                                           AssemblyCommands &newAssemblyCommands,
                                                           std::map<std::string, int> &spilledToOffset,
                                                           IRT::CTemp &beginSP ) {

    onlyLeftProcessMemoryTemps(newAssemblyCommands, spilledToOffset, beginSP,
                                thisShared, leftOperand, /* load left */ true, /* store left */ true);

}
