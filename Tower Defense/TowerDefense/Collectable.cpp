#include "Collectable.h"
Collectable::Collectable(float x, float y, Game* game) :
	Actor("res/icono_recolectable.png", x, y, 40, 40, game) {

	animation = new Animation("res/recolectable.png", width, height,
		256, 32, 3, 8, true, game);

}

void Collectable::update()
{
	animation->update();
}

void Collectable::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}