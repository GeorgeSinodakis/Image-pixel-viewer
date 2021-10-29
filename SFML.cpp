#include "SFML.h"
#include <windows.h>
#include <iostream>

SFML::SFML(char *path)
{
	img_size_x = 0;
	img_size_y = 0;
	box_size = 1;
	win_size_x = (int)(GetSystemMetrics(SM_CXSCREEN) / 4 * 3);
	win_size_y = (int)(GetSystemMetrics(SM_CYSCREEN) / 4 * 3);
	max_box_size = 100;
	move_pixels = 3;
	text_char_size = 11;
	mouse_pressed_x = 0;
	mouse_pressed_y = 0;
	click_bar_offset_x = 0;
	click_bar_offset_y = 0;
	pixel_division = 1 / (float)box_size;
	origin_x = 0.5;
	origin_y = 0.5;
	print_text = true;
	red = true;
	green = true;
	blue = true;
	alpha = false;
	y_pos = false;
	x_pos = false;
	mouse_down = false;
	clicked_x_bar = false;
	clicked_y_bar = false;
	x_bar = false;
	y_bar = false;

	window.create(sf::VideoMode(win_size_x, win_size_y), "Image pixel viewer", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	if (!img.loadFromFile(path)) std::cout << "Unable to load image" << std::endl;
	v = img.getSize();
	img_size_x = v.x;
	img_size_y = v.y;

	n_img.create(win_size_x, win_size_y, sf::Color::White);

	texture.setRepeated(false);

	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	text.setFont(font);

	x_bar_big.setSize(sf::Vector2f(win_size_x, win_size_y * 0.02));
	x_bar_big.setPosition(sf::Vector2f(0, win_size_y - x_bar_big.getSize().y));
	x_bar_big.setFillColor(sf::Color(255, 255, 255, 0));

	y_bar_big.setSize(sf::Vector2f(x_bar_big.getSize().y, win_size_y));
	y_bar_big.setPosition(sf::Vector2f(win_size_x - x_bar_big.getSize().y, 0));
	y_bar_big.setFillColor(sf::Color(255, 255, 255, 0));

	x_bar_small.setFillColor(sf::Color(127, 127, 127, 0));

	y_bar_small.setFillColor(sf::Color(127, 127, 127, 0));
}

void SFML::user_input()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return;
		}
		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta < 0)
			{
				if (box_size + event.mouseWheel.delta >= 1)
				{
					float rects_x = (float)event.mouseWheel.x / (float)box_size,
					      rects_y = (float)event.mouseWheel.y / (float)box_size;
					box_size += event.mouseWheel.delta;
					origin_x -= (float)event.mouseWheel.x / (float)box_size - rects_x;
					origin_y -= (float)event.mouseWheel.y / (float)box_size - rects_y;
				}
				else
				{
					float rects_x = (float)event.mouseWheel.x / (float)box_size,
					      rects_y = (float)event.mouseWheel.y / (float)box_size;
					box_size = 1;
					origin_x -= (float)event.mouseWheel.x / (float)box_size - rects_x;
					origin_y -= (float)event.mouseWheel.y / (float)box_size - rects_y;
				}
			}
			else
			{
				if (box_size + event.mouseWheel.delta <= max_box_size)
				{
					float rects_x = (float)event.mouseWheel.x / (float)box_size,
					      rects_y = (float)event.mouseWheel.y / (float)box_size;
					box_size += event.mouseWheel.delta;
					origin_x -= (float)event.mouseWheel.x / (float)box_size - rects_x;
					origin_y -= (float)event.mouseWheel.y / (float)box_size - rects_y;
				}
				else
				{
					float rects_x = (float)event.mouseWheel.x / (float)box_size,
					      rects_y = (float)event.mouseWheel.y / (float)box_size;
					box_size = max_box_size;
					origin_x -= (float)event.mouseWheel.x / (float)box_size - rects_x;
					origin_y -= (float)event.mouseWheel.y / (float)box_size - rects_y;
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left && !mouse_down)
		{
			mouse_down = true;
			mouse_pressed_x = event.mouseButton.x;
			mouse_pressed_y = event.mouseButton.y;
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
		{
			mouse_down = false;
			clicked_x_bar = false;
			clicked_y_bar = false;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
		{
			if (box_size < 70)
			{
				float rects_x = (float)win_size_x / (float)box_size,
				      rects_y = (float)win_size_y / (float)box_size;
				box_size += 1;
				origin_x += (rects_x - (float)win_size_x / (float)box_size) / 2;
				origin_y += (rects_y - (float)win_size_y / (float)box_size) / 2;
			}
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
		{
			if (box_size > 1)
			{
				float rects_x = (float)win_size_x / (float)box_size,
				      rects_y = (float)win_size_y / (float)box_size;
				box_size -= 1;
				origin_x -= ((float)win_size_x / (float)box_size - rects_x) / 2;
				origin_y -= ((float)win_size_y / (float)box_size - rects_y) / 2;
			}
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
		{
			print_text = !print_text;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
		{
			red = !red;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
		{
			green = !green;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
		{
			blue = !blue;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
		{
			alpha = !alpha;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X)
		{
			x_pos = !x_pos;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y)
		{
			y_pos = !y_pos;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			origin_x -= move_pixels;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			origin_x += move_pixels;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			origin_y -= move_pixels;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			origin_y += move_pixels;
		}
	}
}

void SFML::draw_text()
{
	if (box_size < 50) return;

	text.setCharacterSize(text_char_size);

	int start_x = -(origin_x - (long)origin_x) / pixel_division,
	    start_y = -(origin_y - (long)origin_y) / pixel_division,
	    end_x = 0,
	    end_y = 0,
	    x_offset = (box_size - 30) / 2,
	    y_offset = 0,
	    acumm = 0;

	if (red) y_offset += text_char_size;
	if (green) y_offset += text_char_size;
	if (blue) y_offset += text_char_size;
	if (alpha) y_offset += text_char_size;
	if (x_pos) y_offset += text_char_size;
	if (y_pos) y_offset += text_char_size;

	if (y_offset < box_size) y_offset = (box_size - y_offset) / 2;

	if (img_size_x * box_size < win_size_x) end_x = img_size_x * box_size;
	else end_x = win_size_x;

	if (img_size_y * box_size < win_size_y) end_y = img_size_y * box_size;
	else end_y = win_size_y;

	sf::Color c;

	for (int y = start_y; y < end_y; y += (int)box_size)
	{
		for (int x = start_x; x < end_x; x += (int)box_size)
		{
			acumm = y + y_offset;

			unsigned int in_x = x < 0 ? origin_x : x * pixel_division + origin_x,
			             in_y = y < 0 ? origin_y : y * pixel_division + origin_y;

			c = img.getPixel(in_x, in_y);

			if (c.a < 127) text.setFillColor(sf::Color::Black);
			else text.setFillColor(0.2126 * c.r + 0.7152 * c.g + 0.0722 * c.b > 127 ? sf::Color::Black : sf::Color::White);

			if (red)
			{
				text.setString("R:" + std::to_string(c.r));
				text.setPosition((float)(x + x_offset), (float)(acumm));
				window.draw(text);
				acumm += text_char_size;
			}

			if (green)
			{
				text.setString("G:" + std::to_string(c.g));
				text.setPosition((float)(x + x_offset), (float)(acumm));
				window.draw(text);
				acumm += text_char_size;
			}

			if (blue)
			{
				text.setString("B:" + std::to_string(c.b));
				text.setPosition((float)(x + x_offset), (float)(acumm));
				window.draw(text);
				acumm += text_char_size;
			}

			if (alpha)
			{
				text.setString("A:" + std::to_string(c.a));
				text.setPosition((float)(x + x_offset), (float)(acumm));
				window.draw(text);
				acumm += text_char_size;
			}

			if (x_pos)
			{
				text.setString("X:" + std::to_string(in_x));
				text.setPosition((float)(x + x_offset), (float)(acumm));
				window.draw(text);
				acumm += text_char_size;
			}

			if (y_pos)
			{
				text.setString("Y:" + std::to_string(in_y));
				text.setPosition((float)(x + x_offset), (float)(acumm));
				window.draw(text);
				acumm += text_char_size;
			}
		}
	}
}

void SFML::set_origin_from_bar_x()
{
	float scale = x_bar_big.getSize().x / img_size_x;

	if (mouse_down && mouse_pressed_x >= x_bar_small.getPosition().x && mouse_pressed_x <= x_bar_small.getPosition().x + x_bar_small.getSize().x && mouse_pressed_y >= x_bar_small.getPosition().y && !clicked_x_bar)
	{
		clicked_x_bar = true;
		click_bar_offset_x = mouse_pressed_x - x_bar_small.getPosition().x;
	}
	if (mouse_down && clicked_x_bar)
	{
		origin_x = ((float)sf::Mouse::getPosition(window).x - (float)click_bar_offset_x) / scale;
	}
}

void SFML::set_origin_from_bar_y()
{
	float scale = y_bar_big.getSize().y / img_size_y;

	if (mouse_down && mouse_pressed_y >= y_bar_small.getPosition().y && mouse_pressed_y <= y_bar_small.getPosition().y + y_bar_small.getSize().y && mouse_pressed_x >= y_bar_small.getPosition().x && !clicked_y_bar)
	{
		clicked_y_bar = true;
		click_bar_offset_y = mouse_pressed_y - y_bar_small.getPosition().y;
	}
	if (mouse_down && clicked_y_bar)
	{
		origin_y = ((float)sf::Mouse::getPosition(window).y - (float)click_bar_offset_y) / scale;
	}
}

void SFML::set_box_s()
{
	pixel_division = 1 / (float)box_size;
}

void SFML::set_origins()
{
	if (origin_x < 0) origin_x = 0;
	if ((unsigned int)(win_size_x * pixel_division + origin_x) >= img_size_x) origin_x = img_size_x - win_size_x * pixel_division;
	if (img_size_x * box_size <= win_size_x) origin_x = 0;

	if (origin_y < 0) origin_y = 0;
	if ((unsigned int)(win_size_y * pixel_division + origin_y) >= img_size_y) origin_y = img_size_y - win_size_y * pixel_division;
	if (img_size_y * box_size <= win_size_y) origin_y = 0;
}

void SFML::show_hide_bar_x()
{
	if (sf::Mouse::getPosition(window).y >= x_bar_big.getPosition().y - 10 && !y_bar )
	{
		sf::Color c = x_bar_big.getFillColor();
		if (c.a + 20 < 255)
		{
			c.a += 20;
			x_bar = true;
		}
		else c.a = 255;
		x_bar_big.setFillColor(c);

		c = x_bar_small.getFillColor();
		if (c.a + 20 < 255) c.a += 20;
		else c.a = 255;
		x_bar_small.setFillColor(c);
	}
	else if (!clicked_x_bar)
	{
		sf::Color c = x_bar_big.getFillColor();
		if (c.a - 20 > 0) c.a -= 20;
		else
		{
			c.a = 0;
			x_bar = false;
		}
		x_bar_big.setFillColor(c);

		c = x_bar_small.getFillColor();
		if (c.a - 20 > 0) c.a -= 20;
		else c.a = 0;
		x_bar_small.setFillColor(c);
	}
}

void SFML::show_hide_bar_y()
{
	if (sf::Mouse::getPosition(window).x >= y_bar_big.getPosition().x - 10 && !x_bar)
	{
		sf::Color c = y_bar_big.getFillColor();
		if (c.a + 20 < 255)
		{
			c.a += 20;
			y_bar = true;
		}
		else c.a = 255;
		y_bar_big.setFillColor(c);

		c = y_bar_small.getFillColor();
		if (c.a + 20 < 255) c.a += 20;
		else c.a = 255;
		y_bar_small.setFillColor(c);
	}
	else if (!clicked_y_bar)
	{
		sf::Color c = y_bar_big.getFillColor();
		if (c.a - 20 > 0) c.a -= 20;
		else
		{
			c.a = 0;
			y_bar = false;
		}
		y_bar_big.setFillColor(c);

		c = y_bar_small.getFillColor();
		if (c.a - 20 > 0) c.a -= 20;
		else c.a = 0;
		y_bar_small.setFillColor(c);
	}
}

void SFML::set_bar_x()
{
	float scale = ((float)win_size_x / (float)box_size) / (float)img_size_x;

	x_bar_small.setSize(sf::Vector2f(scale * x_bar_big.getSize().x, x_bar_big.getSize().y));

	scale = x_bar_big.getSize().x / img_size_x;

	x_bar_small.setPosition(sf::Vector2f(origin_x * scale, x_bar_big.getPosition().y));
}

void SFML::set_bar_y()
{
	float scale = ((float)win_size_y / (float)box_size) / (float)img_size_y;

	y_bar_small.setSize(sf::Vector2f(y_bar_big.getSize().x, scale * y_bar_big.getSize().y));

	scale = y_bar_big.getSize().y / img_size_y;

	y_bar_small.setPosition(sf::Vector2f(y_bar_big.getPosition().x, origin_y * scale));
}

void SFML::set_sprite()
{
	for (unsigned int y = 0; y < win_size_y; y++)
	{
		for (unsigned int x = 0; x < win_size_x; x++)
		{
			unsigned int im_x = (unsigned int)(x * pixel_division + origin_x),
			             im_y = (unsigned int)(y * pixel_division + origin_y);

			if (im_y >= img_size_y || im_x >= img_size_x)
			{
				n_img.setPixel(x, y, sf::Color::White);
			}
			else
			{
				n_img.setPixel(x, y, img.getPixel(im_x, im_y));
			}
		}
	}
	texture.loadFromImage(n_img);
	sprite.setTexture(texture);
}

void SFML::render()
{
	this->set_origin_from_bar_x();
	this->set_origin_from_bar_y();

	this->set_box_s();
	this->set_origins();

	this->show_hide_bar_x();
	this->show_hide_bar_y();

	this->set_bar_x();
	this->set_bar_y();

	this->set_sprite();
}

void SFML::update()
{
	window.clear(sf::Color::White);
	window.draw(sprite);

	if (print_text) this->draw_text();

	if (img_size_x * box_size > win_size_x)
	{
		window.draw(x_bar_big);
		window.draw(x_bar_small);
	}
	if (img_size_y * box_size > win_size_y)
	{
		window.draw(y_bar_big);
		window.draw(y_bar_small);
	}

	window.display();
}
