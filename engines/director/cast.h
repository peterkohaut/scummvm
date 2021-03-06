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

#ifndef DIRECTOR_CAST_H
#define DIRECTOR_CAST_H

#include "common/rect.h"
#include "common/substream.h"
#include "director/archive.h"
#include "graphics/surface.h"

namespace Director {

class Stxt;
class CachedMacText;

enum CastType {
	kCastTypeNull = 0,
	kCastBitmap = 1,
	kCastFilmLoop = 2,
	kCastText = 3,
	kCastPalette = 4,
	kCastPicture = 5,
	kCastSound = 6,
	kCastButton = 7,
	kCastShape = 8,
	kCastMovie = 9,
	kCastDigitalVideo = 10,
	kCastLingoScript = 11,
	kCastRTE = 12
};

class Cast {
public:
	CastType _type;
	Common::Rect _initialRect;
	Common::Rect _boundingRect;
	Common::Array<Resource> _children;

	const Graphics::Surface *_surface;

	byte _modified;
};

class BitmapCast : public Cast {
public:
	BitmapCast(Common::ReadStreamEndian &stream, uint32 castTag, uint16 version = 2);

	uint16 _pitch;
	uint16 _regX;
	uint16 _regY;
	uint8 _flags;
	uint16 _someFlaggyThing;
	uint16 _unk1, _unk2;

	uint16 _bitsPerPixel;

	uint32 _tag;
};

enum ShapeType {
	kShapeRectangle,
	kShapeRoundRect,
	kShapeOval,
	kShapeLine
};

class ShapeCast : public Cast {
public:
	ShapeCast(Common::ReadStreamEndian &stream, uint16 version = 2);

	ShapeType _shapeType;
	uint16 _pattern;
	byte _fgCol;
	byte _bgCol;
	byte _fillType;
	byte _lineThickness;
	byte _lineDirection;
};

enum TextType {
	kTextTypeAdjustToFit,
	kTextTypeScrolling,
	kTextTypeFixed
};

enum TextAlignType {
	kTextAlignRight = -1,
	kTextAlignLeft,
	kTextAlignCenter
};

enum TextFlag {
	kTextFlagEditable,
	kTextFlagAutoTab,
	kTextFlagDoNotWrap
};

enum SizeType {
	kSizeNone,
	kSizeSmallest,
	kSizeSmall,
	kSizeMedium,
	kSizeLarge,
	kSizeLargest
};

class TextCast : public Cast {
public:
	TextCast(Common::ReadStreamEndian &stream, uint16 version = 2);

	SizeType _borderSize;
	SizeType _gutterSize;
	SizeType _boxShadow;

	byte _flags1;
	uint32 _fontId;
	uint16 _fontSize;
	TextType _textType;
	TextAlignType _textAlign;
	SizeType _textShadow;
	byte _textSlant;
	Common::Array<TextFlag> _textFlags;
	uint16 _palinfo1, _palinfo2, _palinfo3;

	Common::String _ftext;
	void importStxt(const Stxt *stxt);
	void importRTE(byte* text);
	CachedMacText *_cachedMacText;
};

enum ButtonType {
	kTypeButton,
	kTypeCheckBox,
	kTypeRadio
};

class ButtonCast : public TextCast {
public:
	ButtonCast(Common::ReadStreamEndian &stream, uint16 version = 2);

	ButtonType _buttonType;
};

class ScriptCast : public Cast {
public:
	ScriptCast(Common::ReadStreamEndian &stream, uint16 version = 2);

	uint32 _id;
};



struct CastInfo {
	Common::String script;
	Common::String name;
	Common::String directory;
	Common::String fileName;
	Common::String type;
};

struct Label {
	Common::String name;
	uint16 number;
	Label(Common::String name1, uint16 number1) { name = name1; number = number1; }
};

} // End of namespace Director

#endif
