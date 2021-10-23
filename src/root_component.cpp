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

#include <algorithm>

#include <logmich/log.hpp>
#include <wstinput/controller.hpp>

#include "root_component.hpp"

namespace gui {

RootComponent::RootComponent(const geom::frect& rect_, Style& style) :
  Component(rect_, nullptr),
  focus(nullptr),
  children(),
  m_style(style)
{
  set_active(true);
}

RootComponent::~RootComponent()
{
}

void
RootComponent::draw(wstdisplay::GraphicsContext& gc)
{
  for (auto i = children.begin(); i != children.end(); ++i)
  {
    (*i)->draw(gc);
  }
}

void
RootComponent::update(float delta, const Controller& controller)
{
  for (auto i = children.begin(); i != children.end(); ++i)
  {
    if (i->get() == focus)
      (*i)->update(delta, controller);
    else
      (*i)->update(delta, Controller());
  }
}

bool
RootComponent::is_active() const
{
  if (focus)
    return focus->is_active();
  else
    return false;
}

void
RootComponent::add_child(std::unique_ptr<Component> child)
{
  focus = child.get();
  children.emplace_back(std::move(child));
}

void
RootComponent::set_focus(Component* child_)
{
  auto const i = std::find_if(children.begin(), children.end(),
                              [child_](std::unique_ptr<Component> const& it){ return it.get() == child_; });
  if (i != children.end())
  {
    focus = child_;
    focus->set_active(true);
  }
  else
  {
    log_error("Error: Need to add_child() first befor calling set_focus()");
  }
}

Style&
RootComponent::get_style() const
{
  return m_style;
}

} // namespace gui

/* EOF */
