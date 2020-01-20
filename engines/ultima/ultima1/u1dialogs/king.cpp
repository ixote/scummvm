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
 */

#include "ultima/ultima1/u1dialogs/king.h"
#include "ultima/ultima1/game.h"
#include "ultima/ultima1/core/resources.h"
#include "ultima/ultima1/maps/map.h"
#include "ultima/shared/gfx/visual_surface.h"

namespace Ultima {
namespace Ultima1 {
namespace U1Dialogs {

BEGIN_MESSAGE_MAP(King, Dialog)
	ON_MESSAGE(ShowMsg)
	ON_MESSAGE(CharacterInputMsg)
	ON_MESSAGE(TextInputMsg)
END_MESSAGE_MAP()

King::King(Ultima1Game *game) : Dialog(game), _mode(SELECT) {
	_bounds = Rect(31, 23, 287, 127);
}

bool King::ShowMsg(CShowMsg &msg) {
	addInfoMsg(_game->_res->KING_TEXT[0], false);
	getKeypress();
	return true;
}

void King::draw() {
	Dialog::draw();
	Shared::Gfx::VisualSurface s = getSurface();

	if (_mode == SERVICE) {
		// Draw the background and frame
		s.clear();
		s.frameRect(Rect(3, 3, _bounds.width() - 3, _bounds.height() - 3), getGame()->_borderColor);

		// Draw the title
	//	s.writeString(, Point((_bounds.width() - _title.size() * 8) / 2, 9));
	}

}

void King::setMode(KingMode mode) {
	_mode = mode;

	switch (_mode) {
	case PENCE:
		addInfoMsg(_game->_res->KING_TEXT[2]);			// Pence
		addInfoMsg(_game->_res->KING_TEXT[4], false);	// How much?
		getInput();
		break;

	case SERVICE:
		addInfoMsg(_game->_res->KING_TEXT[3]);

	default:
		break;
	}

	setDirty();
}

bool King::CharacterInputMsg(CCharacterInputMsg &msg) {
	switch (_mode) {
	case SELECT:
		if (msg._keyState.keycode == Common::KEYCODE_p)
			setMode(PENCE);
		else if (msg._keyState.keycode == Common::KEYCODE_s)
			setMode(SERVICE);
		else
			neither();
		break;

	default:
		break;
	}

	return true;
}

bool King::TextInputMsg(CTextInputMsg &msg) {
	assert(_mode == PENCE);
	const Shared::Character &c = *_game->_party;
	uint amount = atoi(msg._text.c_str());

	if (msg._escaped || !amount) {
		none();
	} else if (amount > c._coins) {
		notThatMuch();
	} else {
		addInfoMsg(Common::String::format("%u", amount));
		giveHitPoints(amount * 3 / 2);
	}

	return true;
}

void King::neither() {
	addInfoMsg(_game->_res->KING_TEXT[1]);
	_game->endOfTurn();
	hide();
}

void King::none() {
	addInfoMsg(_game->_res->NONE);
	_game->endOfTurn();
	hide();
}

void King::notThatMuch() {
	addInfoMsg(_game->_res->KING_TEXT[5]);
	_game->endOfTurn();
	hide();
}

void King::giveHitPoints(uint amount) {
	Shared::Character &c = *_game->_party;
	assert(amount <= c._coins);
	c._coins -= amount;
	c._hitPoints += amount;

	addInfoMsg(Common::String::format(_game->_res->KING_TEXT[6], amount));
	_game->endOfTurn();
	hide();
}

} // End of namespace U1Dialogs
} // End of namespace Gfx
} // End of namespace Ultima