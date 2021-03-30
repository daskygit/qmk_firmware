/*
Copyright 2020 Dasky

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "quantum.h"

enum tapdance_ids {
    TD_GAME, //game layer
    TD_QUOT, //f12
    TD_LSFT,
    TD_RSFT
};

#define TDGAME TD(TD_GAME)
#define TDQUOT TD(TD_QUOT)
#define TDLSFT TD(TD_LSFT)
#define TDRSFT TD(TD_RSFT)
