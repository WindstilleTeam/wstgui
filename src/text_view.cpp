/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
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

#include "text_view.hpp"

#include <wstinput/controller.hpp>

#include "controller_def.hpp"
#include "slider.hpp"

namespace wstgui {

TextView::TextView(Component* component) :
  Component(component),
  text_area(m_parent->get_style().get_font(), geom::frect(), false)
{
}

TextView::~TextView()
{
}

void
TextView::draw(wstdisplay::GraphicsContext& gc)
{
  text_area.draw(gc);
}

void
TextView::update(float delta, const Controller& controller)
{
  text_area.update(delta);

  text_area.set_scroll_offset(text_area.get_scroll_offset() + 500.0f * controller.get_axis_state(Y2_AXIS) * delta);

  for(auto i = controller.get_events().begin(); i != controller.get_events().end(); ++i)
  {
    if (i->type == wstinput::BUTTON_EVENT && i->button.down)
    {
      if (i->button.name == OK_BUTTON || i->button.name == ENTER_BUTTON)
      {
        set_active(false);
      }
      else if (i->button.name == CANCEL_BUTTON || i->button.name == ESCAPE_BUTTON)
      {
        set_active(false);
      }
    }
  }
}

void
TextView::set_geometry(const geom::frect& rect_)
{
  Component::set_geometry(rect_);
  text_area.set_rect(geom::grow(rect_, -16.0f, -4.0f));
}

void
TextView::set_text(const std::string& text)
{
  text_area.set_text(text);
}

void
TextView::set_font(wstdisplay::TTFFont* font)
{
  text_area.set_font(font);
}

} // namespace wstgui

/* EOF */

