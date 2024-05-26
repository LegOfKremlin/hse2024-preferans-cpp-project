#ifndef TYPIING_HPP_
#define TYPIING_HPP_

namespace godot
{

    enum class Move {
        Bidding,
        Passout,
        Misere,
    };

    enum class TradeResult {
        Passout,
        Misere,
        MisereWithoutTalon,
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

} // namespace godot

#endif // TYPIING_HPP_
