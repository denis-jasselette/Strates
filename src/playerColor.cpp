#include "playerColor.h"

const int nb_shades = 4;
int red_components[] = { 0xa40000, 0x7c0000, 0x5c0400, 0x440400 };
const PlayerColor PlayerColor::Red(red_components);
int blue_components[] = { 0x0c48cc, 0x0428a0, 0x001474, 0x00044c };
const PlayerColor PlayerColor::Blue(blue_components);
const PlayerColor PlayerColor::Mask = Red;

PlayerColor::PlayerColor(int shades[]) {
  for (int s = 0; s < nb_shades; s++) {
    int r = (shades[s] & 0xff0000) >> 16;
    int g = (shades[s] & 0x00ff00) >> 8;
    int b = (shades[s] & 0x0000ff);
    this->shades.push_back(sf::Color(r, g, b));
  }
}

void PlayerColor::apply(sf::Texture *sprite_sheet) const {
  sf::Image img = sprite_sheet->copyToImage();

  for (int i = 0; i < img.getSize().y; i++) {
    for (int j = 0; j < img.getSize().x; j++) {
      for (int s = 0; s < nb_shades; s++) {
        if (img.getPixel(j, i) == Mask.shades[s])
          img.setPixel(j, i, shades[s]);
      }
    }
  }

  sprite_sheet->update(img);
}
