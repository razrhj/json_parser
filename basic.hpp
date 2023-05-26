#ifndef _BASIC_
#define _BASIC_

#include <string>

enum class ReturnState {
  Success,
  OpenFileFailed,
  ReadError,

  NotLeftBrace,
  NotRightBrace,
  NotLeftBracket,
  NotRightBracket,
  NotComma,
  NotColon,
  NotQuote,

  StartError,
  ObjectError,
  ArrayError,
  KVError,
  KeyError,
  ValueError,
  PrimaryError,
  WrongNumberFormat,
  WrongBooleanFormat,
  WrongNullFormat,
  WrongStringFormat

};

inline std::string ReturnStateEnumName(ReturnState type) {
  switch (type) {

  case ReturnState::Success:
    return "ReturnState::Success";
  case ReturnState::OpenFileFailed:
    return "ReturnState::OpenFileFailed";
  case ReturnState::ReadError:
    return "ReturnState::ReadError";
  case ReturnState::NotLeftBrace:
    return "ReturnState::NotLeftBrace";
  case ReturnState::NotRightBrace:
    return "ReturnState::NotRightBrace";
  case ReturnState::NotLeftBracket:
    return "ReturnState::NotLeftBracket";
  case ReturnState::NotRightBracket:
    return "ReturnState::NotRightBracket";
  case ReturnState::NotComma:
    return "ReturnState::NotComma";
  case ReturnState::NotColon:
    return "ReturnState::NotColon";
  case ReturnState::NotQuote:
    return "ReturnState::NotQuote";
  case ReturnState::StartError:
    return "ReturnState::StartError";
  case ReturnState::ObjectError:
    return "ReturnState::ObjectError";
  case ReturnState::ArrayError:
    return "ReturnState::ArrayError";
  case ReturnState::KVError:
    return "ReturnState::KVError";
  case ReturnState::KeyError:
    return "ReturnState::KeyError";
  case ReturnState::ValueError:
    return "ReturnState::ValueError";
  case ReturnState::PrimaryError:
    return "ReturnState::PrimaryError";
  case ReturnState::WrongNumberFormat:
    return "ReturnState::WrongNumberFormat";
  case ReturnState::WrongBooleanFormat:
    return "ReturnState::WrongBooleanFormat";
  case ReturnState::WrongNullFormat:
    return "ReturnState::WrongNullFormat";
  case ReturnState::WrongStringFormat:
    return "ReturnState::WrongStringFormat";
  default:
    return "ReturnState::None";
  }
}

#endif // !_BASIC_
