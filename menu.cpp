/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2009 Ingo Ruhnke <grumbel@gmx.de>
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

#include "component.hpp"
#include "root_component.hpp"
#include "gui_manager.hpp"
#include "menu_item.hpp"
#include "menu_component.hpp"
#include "group_component.hpp"
#include "screen/screen_manager.hpp"
#include "menu.hpp"
#include "font/fonts.hpp"

namespace gui {

Menu::Menu(const std::string& name, const Rectf& rect)
{
  manager.reset(new GUIManager());
  group.reset(new GroupComponent(rect, name, manager->get_root()));
  menu.reset(new MenuComponent(group->get_child_rect(), true, group.get()));

  menu->set_font(Fonts::vera20);
}

Menu::~Menu()
{
}

EnumMenuItem&
Menu::add_enum(const std::string& name, int index,
               const boost::function<void (int)>& callback)
{
  std::auto_ptr<EnumMenuItem> enum_item(new EnumMenuItem(menu.get(), name));
  EnumMenuItem& obj = *enum_item;
  menu->add_item(enum_item.release());
  return obj;
}

void
Menu::add_slider(const std::string& name, 
                 int value, int min_value, int max_value, int step,
                 const boost::function<void (int)>& callback)
{
  std::auto_ptr<SliderMenuItem> slider(new SliderMenuItem(menu.get(), name, value, min_value, max_value, step));
  slider->sig_change().connect(callback);
  menu->add_item(slider.release());
}

void
Menu::add_button(const std::string& name,
                 const boost::function<void ()>& callback)
{
  std::auto_ptr<ButtonMenuItem> scenario_button(new ButtonMenuItem(menu.get(), name));
  scenario_button->sig_click().connect(callback);
  menu->add_item(scenario_button.release());
}

void
Menu::push_screen()
{
  group->pack(menu.release());
  manager->get_root()->add_child(group.release());
  screen_manager.push_overlay(manager.release());
}

} // namespace gui

/* EOF */
