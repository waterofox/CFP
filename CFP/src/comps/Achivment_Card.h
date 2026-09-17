#pragma once
#include <foxAndDot-SDK/Components/Entity.h>

class Achivment_Card : public Scene_Component, public sf::Drawable
{

	static inline sf::Font fnt;
	static inline sf::Texture txr;

	sf::Sprite* picture;

	sf::RectangleShape sub_card;
	sf::RectangleShape sub_card_shadow;

	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& res) override;
	
	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds() override;
	
	sf::Drawable* as_drawable() override;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


public:

	sf::RectangleShape body;

	sf::Text* achivment;
	sf::Text* member_name;
	sf::Text* condition;

	Achivment_Card();
	~Achivment_Card();
};

