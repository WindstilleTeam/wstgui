/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_WINDSTILLE_GUI_MENU_COMPONENT_HPP
#define HEADER_WINDSTILLE_GUI_MENU_COMPONENT_HPP

#include <wstdisplay/fwd.hpp>

#include "component.hpp"

namespace gui {

class MenuItem;

/** */
class MenuComponent : public Component
{
private:
  typedef std::vector<std::unique_ptr<MenuItem>> Items;
  Items items;

  int   current_item;
  wstdisplay::TTFFont* font;
  bool allow_cancel;

  bool scroll_mode;
  int  scroll_offset;
  int  num_displayable_items;

  /** Calculate how much height will be needed for the menu */
  float calc_height();

  /** Return the height of a single item */
  float item_height() const;

  void adjust_scroll_offset();

public:
  MenuComponent(const geom::frect& rect, bool allow_cancel_, Component* parent);
  ~MenuComponent() override;

  void add_item(std::unique_ptr<MenuItem> item);
  void draw(wstdisplay::GraphicsContext& gc) override;
  void update(float delta, const Controller& controller) override;

  float get_prefered_width() const override;
  float get_prefered_height() const override;

  void     set_font(wstdisplay::TTFFont* font_);
  wstdisplay::TTFFont* get_font();

  void set_screen_rect(const geom::frect& rect) override;

private:
  MenuComponent (const MenuComponent&);
  MenuComponent& operator= (const MenuComponent&);
};

} // namespace gui

#endif

/* EOF */
