#pragma once
#include "animation.h"

class Button
{
public:
	Button();
	~Button();

	void on_input(const SDL_Event& event)
	{
		if (event.motion.x > position.x && event.motion.x<position.x + size.x
			&& event.motion.y > position.y && event.motion.y < position.y + size.y)
		{
			is_idel = true;
		}
		else
		{
			return;
		}

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				if(is_idel)
					on_click();
				break;
			case SDL_BUTTON_RIGHT:
				break;
			case SDL_BUTTON_MIDDLE:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	void on_update(double delta)
	{
		timer_on_click.on_update(delta);
	}

	void on_render(SDL_Renderer* renderer)
	{
		anim_current = &anim_normal;
		if (is_idel)
			anim_current = &anim_idle;
		if (is_show_on_click)
			anim_current = &anim_on_click;

		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;
		rect.w = size.x;
		rect.h = size.y;
		anim_current->on_render(renderer, rect);
	}

protected:
	Vector2 size;
	Vector2 position;
	Timer timer_on_click;

	Animation* anim_current;
	Animation anim_normal;
	Animation anim_idle;
	Animation anim_on_click;
	bool is_show_on_click = false;
	bool is_idel = false;

	virtual void on_click()
	{
		is_show_on_click = true;
		timer_on_click.restart();
	}
};

Button::Button()
{
	timer_on_click.set_wait_time(0.05);
	timer_on_click.set_one_shot(true);
	timer_on_click.set_on_timeout([&]() {
		is_show_on_click = false;
		});
}

Button::~Button()
{
}