#ifndef _PLAYER_COLOR_H_
#define _PLAYER_COLOR_H_

#include <vector>
#include <SFML/Graphics.hpp>

class PlayerColor {
  public:
    std::vector<sf::Color> shades;

    static const PlayerColor Red;
    static const PlayerColor Blue;

    PlayerColor(int shades[]);

    /** Apply the player color to a generic sprite sheet */
    void apply(sf::Texture *sprite_sheet) const;

  private:
    static const PlayerColor Mask;
};

#endif /* _PLAYER_COLOR_H_ */
