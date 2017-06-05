/*
  James' Windows Toolkit (JWT)
  Copyright (C) 2017 James Heggie

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#pragma once

#include "libraries.hpp"
#include "window.hpp"
#include "dialog.hpp"
#include "defer-create.hpp"
#include "event-types.hpp"

namespace jwt {

  struct TreeView
    : Window
  {
    TreeView(Window& parent);
    TreeView(Dialog& parent, int ctrlId);

    template<typename Callable>
    auto On(const SelectTag&, Callable c) -> decltype(onSelect_.connect(c)) {
      return onSelect_.connect(c);
    }

    template<typename Callable>
    auto On(const SelectTag&, int id, Callable c) -> decltype(onSelect_.connect(c)) {
      return onSelect_.connect([id, c](const NMTREEVIEW& n) {
        if (n.itemNew.lParam == id) {
          c();
        }
      });
    }

  protected:
    TreeView(const defer_create_t&);

    void Create(Window& parent);

    LRESULT HandleReflectedMessage(HWND, UINT, WPARAM, LPARAM);

  private:
    boost::signals2::signal<void(const NMTREEVIEW&)> onSelect_;
  };

  HTREEITEM InsertItem(TreeView& tv, HTREEITEM parent, const std::wstring& txt, int id = 0);

  HTREEITEM InsertRootItem(TreeView& tv, const std::wstring& txt, int id = 0);
}