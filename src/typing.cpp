#include "typing.hpp"

std::string tradeResultToString(TradeResult result) {
    switch (result) {
    case TradeResult::Passout: return "Passout";
    case TradeResult::Misere: return "Misere";
    default: return "Unknown result";
    }
}
