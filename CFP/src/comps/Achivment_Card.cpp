#define _CRT_SECURE_NO_WARNINGS


#include "Achivment_Card.h"

#include "../../Parser.h"

#include "../system/resources.h"

void Achivment_Card::update()
{
	achivment->setPosition(sf::Vector2f(
		picture->getGlobalBounds().getCenter().x,
		picture->getGlobalBounds().position.y + picture->getGlobalBounds().size.y + 20));
	achivment->move(sf::Vector2f(-achivment->getGlobalBounds().size.x / 2, 0));

	member_name->setPosition(sf::Vector2f(
		achivment->getGlobalBounds().getCenter().x,
		achivment->getGlobalBounds().position.y + achivment->getGlobalBounds().size.y + 20));
	member_name->move(sf::Vector2f(-member_name->getGlobalBounds().size.x / 2, 0));

	condition->setPosition(sf::Vector2f(
		sub_card.getGlobalBounds().getCenter().x,
		sub_card.getPosition().y + sub_card.getSize().y + 40));
	condition->move(sf::Vector2f(-condition->getGlobalBounds().size.x / 2, 0));
}

void Achivment_Card::update_resource(const std::variant<sf::Texture*, sf::Font*>& res)
{
	achivment->setFont(Core::resource_manager.get_font(Fonts::base));
	member_name->setFont(Core::resource_manager.get_font(Fonts::base));
	condition->setFont(Core::resource_manager.get_font(Fonts::base));


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
	target.draw(sub_card_shadow);
	target.draw(sub_card);

	target.draw(*picture);

	target.draw(*achivment);
	target.draw(*member_name);
	target.draw(*condition);


}

Achivment_Card::Achivment_Card()
{
	Core::resource_manager.add_font("resources\\fonts\\clacon2.ttf", Fonts::base);

	fnt = Core::resource_manager.get_font(Fonts::base);

	type_of_resource = Resource_Types::Texture;

	body.setSize(sf::Vector2f(570, 864));
	body.setFillColor(sf::Color(102, 102, 255));
	body.setPosition(sf::Vector2f(0, 0));

	sub_card.setSize(sf::Vector2f(399,604.8));
	sub_card.setFillColor(sf::Color::White);
	sub_card.setPosition(sf::Vector2f(85.5, 85.5));

	sub_card_shadow.setSize(sub_card.getSize());
	sub_card_shadow.setFillColor(sf::Color::Black);
	sub_card_shadow.setPosition(sub_card.getPosition());
	sub_card_shadow.move(sf::Vector2f(12, 12));

	picture = new sf::Sprite(txr);
	picture->setPosition(sub_card.getPosition());
	picture->move(sf::Vector2f(19.5,19.5));
	picture->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(360, 360)));


	achivment = new sf::Text(fnt, "", 276);
	achivment->setScale(sf::Vector2f(0.2, 0.2));
	achivment->setFillColor(sf::Color::Black);

	member_name = new sf::Text(fnt, "", 276);
	member_name->setScale(sf::Vector2f(0.15, 0.15));
	member_name->setFillColor(sf::Color::Black);

	condition = new sf::Text(fnt, "", 276);
	condition->setScale(sf::Vector2f(0.1, 0.1));
	condition->setFillColor(sf::Color::White);
}

Achivment_Card::~Achivment_Card()
{
	delete member_name;
	delete achivment;
	delete condition;
	delete picture;
}
