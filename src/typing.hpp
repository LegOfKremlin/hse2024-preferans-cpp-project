#ifndef TYPIING_HPP_
#define TYPIING_HPP_

#include <string>

enum class Move {
    Bidding,
    Passout,
    Misere,
};

enum class TradeResult {
    Passout,
    Misere,
    MisereWithoutTalon,
    Pass,
    SixSpades,
    SixClubs,
    SixDiamonds,
    SixHearts,
    SixNoTrump,
    SevenSpades,
    SevenClubs,
    SevenDiamonds,
    SevenHearts,
    SevenNoTrump,
    EightSpades,
    EightClubs,
    EightDiamonds,
    EightHearts,
    EightNoTrump,
    NineSpades,
    NineClubs,
    NineDiamonds,
    NineHearts,
    NineNoTrump,
    TenSpades,
    TenClubs,
    TenDiamonds,
    TenHearts,
    TenNoTrump,
    NineSpadesWithoutTalon,
    NineNoTrumpWithoutTalon,
    TenSpadesWithoutTalon,
    TenNoTrumpWithoutTalon
};

std::string tradeResultToString(TradeResult result);

int tradeResultToBidNumber(TradeResult result);

#endif // TYPIING_HPP_