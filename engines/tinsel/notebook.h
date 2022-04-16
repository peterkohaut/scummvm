/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * System reel handling.
 */

#ifndef TINSEL_NOTEBOOK_H	// prevent multiple includes
#define TINSEL_NOTEBOOK_H

#include "common/scummsys.h"

#include "events.h"


namespace Tinsel {
// links two clue/title objects together
struct HYPERLINK {
    int32 id_1;
    int32 id_2;
};

// 6 bytes large
struct ENTRY {
    int32 id;
    bool active;
    int32 page;
    int32 index_on_page;
    int32 page2;
    int32 index_on_page2;
};

class Notebook {
  public:
    Notebook() = default;

    // can be a title or clue
    int NotebookAddEntry(int entry_idx, int page1, int page2);
    int NotebookAddHyperlink(int clue_id, int title_id);
    // Called within InventorrProcess loop
    int NotebookRedraw();
    int EventToNotebook(PLR_EVENT event, bool p2, bool p3);

  private:
    const static uint32 MAX_ENTRIES = 99;
    const static uint32 MAX_PAGES = 0x15;
    const static uint32 MAX_HYPERS = 0xf;
    const static uint32 MAX_CLUES_PER_PAGE = 7;

    HYPERLINK hyperlinks[MAX_HYPERS];

    const static uint32 notebook_num_entries = 0;

    ENTRY entries[MAX_ENTRIES];
};

} // End of namespace Tinsel

#endif
