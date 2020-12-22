#include <SFML/Graphics.hpp>

class SFML
{
public:
	sf::RenderWindow window;
	sf::Event event;
	sf::Image img;
	sf::Image n_img;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;
	sf::Text text;
	sf::Vector2u v;
	sf::RectangleShape x_bar_big;
	sf::RectangleShape y_bar_big;
	sf::RectangleShape x_bar_small;
	sf::RectangleShape y_bar_small;
	unsigned int img_size_x, img_size_y, box_size, win_size_x, win_size_y, max_box_size, move_pixels, text_char_size, mouse_pressed_x, mouse_pressed_y, click_bar_offset_x, click_bar_offset_y;
	float pixel_division = 1 / (float)box_size, origin_x, origin_y;
	bool print_text, red, green, blue, alpha, y_pos, x_pos, mouse_down, clicked_x_bar, clicked_y_bar, x_bar, y_bar;
public:
	SFML(char *path);
	void user_input();
	void draw_text();
	void set_origin_from_bar_x();
	void set_origin_from_bar_y();
	void set_box_s();
	void set_origins();
	void show_hide_bar_x();
	void show_hide_bar_y();
	void set_bar_x();
	void set_bar_y();
	void set_sprite();
	void render();
	void update();
};
