#define _CRT_SECURE_NO_WARNINGS


#include "Achivment_Card.h"

#include "../../Parser.h"

#include "../system/resources.h"

void Achivment_Card::update()
{
	achivment->setPosition(picture->getGlobalBounds().getCenter());
	achivment->move(sf::Vector2f(-achivment->getGlobalBounds().size.x / 2, 190));

	member_name->setPosition(achivment->getGlobalBounds().getCenter());
	member_name->move(sf::Vector2f(-member_name->getGlobalBounds().size.x / 2, 10));
}

void Achivment_Card::update_resource(const std::variant<sf::Texture*, sf::Font*>& res)
{
	achivment->setFont(Core::resource_manager.get_font(Fonts::base));
	member_name->setFont(Core::resource_manager.get_font(Fonts::base));

	picture->setTexture(*std::get<sf::Texture*>(res));
}

sf::FloatRect Achivment_Card::get_component_bounds()
{
	return body.getGlobalBounds();
}

sf::FloatRect Achivment_Card::get_component_render_bounds()
{
	return get_component_bounds();
}

sf::Drawable* Achivment_Card::as_drawable()
{
	return this;
}

void Achivment_Card::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body);
	target.draw(*picture);
	target.draw(*achivment);
	target.draw(*member_name);

}

Achivment_Card::Achivment_Card()
{
	Core::resource_manager.add_font("resources\\fonts\\clacon2.ttf", Fonts::base);

	fnt = Core::resource_manager.get_font(Fonts::base);

	type_of_resource = Resource_Types::Texture;

	body.setSize(sf::Vector2f(380, 576));
	body.setFillColor(sf::Color(102, 102, 255));
	body.setOutlineColor(sf::Color::White);
	body.setOutlineThickness(-2);
	body.setPosition(sf::Vector2f(0, 0));

	picture = new sf::Sprite(txr);
	picture->setPosition(sf::Vector2f(10, 10));
	picture->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(360, 360)));

	
	
	achivment = new sf::Text(fnt, "", 276);
	achivment->setScale(sf::Vector2f(0.2, 0.2));
	achivment->setFillColor(sf::Color::White);

	member_name = new sf::Text(fnt, "", 276);
	member_name->setScale(sf::Vector2f(0.1, 0.1));
	member_name->setFillColor(sf::Color::White);
}

Achivment_Card::~Achivment_Card()
{
	delete member_name;
	delete achivment;
	delete picture;
}
