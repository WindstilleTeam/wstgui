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

#include "label.hpp"

#include <surf/color.hpp>

#include "style.hpp"

namespace wstgui {

Label::Label(const std::string& label_, Component* parent_)
  : Component(geom::frect(), parent_),
    label(label_)
{
}

Label::~Label()
{
}

void
Label::draw(wstdisplay::GraphicsContext& gc)
{
  //gc.fill_rect(rect, surf::Color(0.0f, 0.0f, 0.0f, 0.5f));
  //gc.draw_rect(rect, surf::Color(1.0f, 1.0f, 1.0f, 0.5f));

  get_style().get_small_font()->draw(
    gc,
    glm::vec2(m_rect.left() + 5/*+ rect.width()/2*/,
              m_rect.top() + m_rect.height()/2 + 3),
    label,
    surf::Color(1.0f, 1.0f, 1.0f, 1.0f));
}

void
Label::update(float /*delta*/, const Controller& /*controller*/)
{
  set_active(false);
}

} // namespace wstgui

/* EOF */
