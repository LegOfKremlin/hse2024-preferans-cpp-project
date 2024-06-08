#include "typing.hpp"

std::string tradeResultToString(TradeResult result) {
    switch (result) {
    case TradeResult::Passout: return "pass";
    case TradeResult::Misere: return "misere";
    case TradeResult::MisereWithoutTalon: return "misere without talon";
    case TradeResult::SixSpades: return "six spades";
    case TradeResult::SixClubs: return "six clubs";
    case TradeResult::SixDiamonds: return "six diamonds";
    case TradeResult::SixHearts: return "six hearts";
    case TradeResult::SixNoTrump: return "six no trump";
    case TradeResult::SevenSpades: return "seven spades";
    case TradeResult::SevenClubs: return "seven clubs";
    case TradeResult::SevenDiamonds: return "seven diamonds";
    case TradeResult::SevenHearts: return "seven hearts";
    case TradeResult::SevenNoTrump: return "seven no trump";
    case TradeResult::EightSpades: return "eight spades";
    case TradeResult::EightClubs: return "eight clubs";
    case TradeResult::EightDiamonds: return "eight diamonds";
    case TradeResult::EightHearts: return "eight hearts";
    case TradeResult::EightNoTrump: return "eight no trump";
    case TradeResult::NineSpades: return "nine spades";
    case TradeResult::NineClubs: return "nine clubs";
    case TradeResult::NineDiamonds: return "nine diamonds";
    case TradeResult::NineHearts: return "nine hearts";
    case TradeResult::NineNoTrump: return "nine no trump";
    case TradeResult::TenSpades: return "ten spades";
    case TradeResult::TenClubs: return "ten clubs";
    case TradeResult::TenDiamonds: return "ten diamonds";
    case TradeResult::TenHearts: return "ten hearts";
    case TradeResult::TenNoTrump: return "ten no trump";
    case TradeResult::NineSpadesWithoutTalon: return "nine spades without talon";
    case TradeResult::NineNoTrumpWithoutTalon: return "nine no trump without talon";
    case TradeResult::TenSpadesWithoutTalon: return "ten spades without talon";
    case TradeResult::TenNoTrumpWithoutTalon: return "ten no trump without talon";
    }
}

int tradeResultToBidNumber(TradeResult result) {
    switch (result) {
    case TradeResult::SixSpades:
    case TradeResult::SixClubs:
    case TradeResult::SixDiamonds:
    case TradeResult::SixHearts:
    case TradeResult::SixNoTrump:
        return 6;
    case TradeResult::SevenSpades:
    case TradeResult::SevenClubs:
    case TradeResult::SevenDiamonds:
    case TradeResult::SevenHearts:
    case TradeResult::SevenNoTrump:
        return 7;
    case TradeResult::EightSpades:
    case TradeResult::EightClubs:
    case TradeResult::EightDiamonds:
    case TradeResult::EightHearts:
    case TradeResult::EightNoTrump:
        return 8;
    case TradeResult::NineSpades:
    case TradeResult::NineClubs:
    case TradeResult::NineDiamonds:
    case TradeResult::NineHearts:
    case TradeResult::NineNoTrump:
    case TradeResult::NineSpadesWithoutTalon:
    case TradeResult::NineNoTrumpWithoutTalon:
        return 9;
    case TradeResult::TenSpades:
    case TradeResult::TenClubs:
    case TradeResult::TenDiamonds:
    case TradeResult::TenHearts:
    case TradeResult::TenNoTrump:
    case TradeResult::TenSpadesWithoutTalon:
    case TradeResult::TenNoTrumpWithoutTalon:
        return 10;
    default:
        return 0;
    }
}