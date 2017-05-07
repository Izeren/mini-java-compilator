//
// Created by izeren on 4/27/17.
//

#include "AssemblyCommand.h"

std::vector<IRT::CTemp> AssemblyCode::MoveRegRegCommand::GetIn( ) const {
    return { source };
}

std::vector<IRT::CTemp> AssemblyCode::MoveRegRegCommand::GetOut( ) const {
    return { target };
}

AssemblyCode::MoveRegRegCommand::MoveRegRegCommand(
        const IRT::CTemp &_target, const IRT::CTemp &_source
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

AssemblyCode::AddRegRegCommand::AddRegRegCommand( const IRT::CTemp &leftOperand, const IRT::CTemp &rightOperand )
        : leftOperand( leftOperand ), rightOperand( rightOperand ) { }


//----------------------------------------------------------------------------------------------------------------------
std::vector<IRT::CTemp> AssemblyCode::SubRegRegCommand::GetIn( ) const {
    return { leftOperand, rightOperand };
}

AssemblyCode::SubRegRegCommand::SubRegRegCommand( const IRT::CTemp &leftOperand, const IRT::CTemp &rightOperand )
        : leftOperand( leftOperand ), rightOperand( rightOperand ) { }

std::vector<IRT::CTemp> AssemblyCode::SubRegRegCommand::GetOut( ) const {
    return { leftOperand };
}

std::string AssemblyCode::SubRegRegCommand::ToString( ) const {
    return "sub " + leftOperand.ToString( ) + " " + rightOperand.ToString( ) + "\n";
}

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::MulRegRegCommand::MulRegRegCommand( const IRT::CTemp &leftOperand, const IRT::CTemp &rightOperand )
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

AssemblyCode::DivRegRegCommand::DivRegRegCommand( const IRT::CTemp &leftOperand, const IRT::CTemp &rightOperand )
        : leftOperand( leftOperand ), rightOperand( rightOperand ) { }

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


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::CallCommand::CallCommand( const IRT::CTemp &address, const std::vector<IRT::CTemp> &arguments )
        : address( address ), arguments( arguments ) { }

std::vector<IRT::CTemp> AssemblyCode::CallCommand::GetIn( ) const {
    std::vector<IRT::CTemp> in;
    in.push_back( address );
    for ( auto argument : arguments ) {
        in.push_back( argument );
    }
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

//----------------------------------------------------------------------------------------------------------------------
std::string AssemblyCode::AbstractJumpCommand::getLabel() const {
    return label;
}

AssemblyCode::AbstractJumpCommand::AbstractJumpCommand(const std::string &label) : label(label) {}

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

AssemblyCode::CJumpLessCommand::CJumpLessCommand( const IRT::CTemp &leftOperand, const IRT::CTemp &rightOperand,
                                                  const std::string &label ) : leftOperand( leftOperand ),
                                                                               rightOperand( rightOperand ),
                                                                               AbstractJumpCommand( label ) { }

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::CJumpEqualCommand::CJumpEqualCommand( const IRT::CTemp &leftOperand, const IRT::CTemp &rightOperand,
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

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::CJumpNotEqualCommand::CJumpNotEqualCommand( const IRT::CTemp &leftOperand, const IRT::CTemp &rightOperand,
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


//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::AddRegConstCommand::AddRegConstCommand( const IRT::CTemp &leftOperand, int constant ) : leftOperand(
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
    return "mov " + target.ToString( ) + " [" + source.ToString( ) + " + " + std::to_string( constant ) + "]\n";
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
    return "mov [" + target.ToString( ) + " + " + std::to_string( constant ) + "] " + source.ToString() + "\n";
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

//----------------------------------------------------------------------------------------------------------------------
AssemblyCode::SubRegConstCommand::SubRegConstCommand( const IRT::CTemp &leftOperand, int rightConst ) : leftOperand(
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
