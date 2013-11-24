//-----------------------------
// James Payor - Evolution RTS
// Created 30/05/13
//-----------------------------
//
//-------------------
// GLB_Keycodes.hpp |
//-------------------------------------------
// Lists the codes assigned to each key by
// GLBasic.
//-------------------------------------------


// IGNORE!!


#ifndef GLB_KEYCODES_H
#define GLB_KEYCODES_H

namespace GLB {

	const int
		vk_escape          = 0x01,
		vk_1               = 0x02,
		vk_2               = 0x03,
		vk_3               = 0x04,
		vk_4               = 0x05,
		vk_5               = 0x06,
		vk_6               = 0x07,
		vk_7               = 0x08,
		vk_8               = 0x09,
		vk_9               = 0x0A,
		vk_0               = 0x0B,
		vk_minus           = 0x0C,   // - on main keyboard
		vk_equals          = 0x0D,
		vk_back            = 0x0E,   // backspace
		vk_tab             = 0x0F,
		vk_q               = 0x10,
		vk_w               = 0x11,
		vk_e               = 0x12,
		vk_r               = 0x13,
		vk_t               = 0x14,
		vk_y               = 0x15,
		vk_u               = 0x16,
		vk_i               = 0x17,
		vk_o               = 0x18,
		vk_p               = 0x19,
		vk_lbracket        = 0x1A,
		vk_rbracket        = 0x1B,
		vk_return          = 0x1C,   // Enter on main keyboard
		vk_lcontrol        = 0x1D,
		vk_a               = 0x1E,
		vk_s               = 0x1F,
		vk_d               = 0x20,
		vk_f               = 0x21,
		vk_g               = 0x22,
		vk_h               = 0x23,
		vk_j               = 0x24,
		vk_k               = 0x25,
		vk_l               = 0x26,
		vk_semicolon       = 0x27,
		vk_apostrophe      = 0x28,
		vk_grave           = 0x29,   // accent grave
		vk_lshift          = 0x2A,
		vk_backslash       = 0x2B,
		vk_z               = 0x2C,
		vk_x               = 0x2D,
		vk_c               = 0x2E,
		vk_v               = 0x2F,
		vk_b               = 0x30,
		vk_n               = 0x31,
		vk_m               = 0x32,
		vk_comma           = 0x33,
		vk_period          = 0x34,   // . on main keyboard
		vk_slash           = 0x35,   // / on main keyboard
		vk_rshift          = 0x36,
		vk_multiply        = 0x37,   // * on numeric keypad
		vk_lmenu           = 0x38,   // left Alt
		vk_space           = 0x39,
		vk_capital         = 0x3A,
		vk_f1              = 0x3B,
		vk_f2              = 0x3C,
		vk_f3              = 0x3D,
		vk_f4              = 0x3E,
		vk_f5              = 0x3F,
		vk_f6              = 0x40,
		vk_f7              = 0x41,
		vk_f8              = 0x42,
		vk_f9              = 0x43,
		vk_f10             = 0x44,
		vk_numlock         = 0x45,
		vk_scroll          = 0x46,   // Scroll Lock
		vk_numpad7         = 0x47,
		vk_numpad8         = 0x48,
		vk_numpad9         = 0x49,
		vk_subtract        = 0x4A,   // - on numeric keypad
		vk_numpad4         = 0x4B,
		vk_numpad5         = 0x4C,
		vk_numpad6         = 0x4D,
		vk_add             = 0x4E,   // + on numeric keypad
		vk_numpad1         = 0x4F,
		vk_numpad2         = 0x50,
		vk_numpad3         = 0x51,
		vk_numpad0         = 0x52,
		vk_decimal         = 0x53,   // . on numeric keypad
		vk_oem_102         = 0x56,   // < > | on UK/Germany keyboards
		vk_f11             = 0x57,
		vk_f12             = 0x58,
		vk_f13             = 0x64,   //                     (NEC PC98)
		vk_f14             = 0x65,   //                     (NEC PC98)
		vk_f15             = 0x66,   //                     (NEC PC98)
		vk_kana            = 0x70,   // (Japanese keyboard)
		vk_abnt_c1         = 0x73,   // / ? on Portugese (Brazilian) keyboards
		vk_convert         = 0x79,   // (Japanese keyboard)
		vk_noconvert       = 0x7B,   // (Japanese keyboard)
		vk_yen             = 0x7D,   // (Japanese keyboard)
		vk_abnt_c2         = 0x7E,   // Numpad . on Portugese (Brazilian) keyboards
		vk_numpadequals    = 0x8D,   // = on numeric keypad (NEC PC98)
		vk_prevtrack       = 0x90,   // Previous Track (vk_CIRCUMFLEX on Japanese keyboard)
		vk_at              = 0x91,   //                     (NEC PC98)
		vk_colon           = 0x92,   //                     (NEC PC98)
		vk_underline       = 0x93,   //                     (NEC PC98)
		vk_kanji           = 0x94,   // (Japanese keyboard)
		vk_stop            = 0x95,   //                     (NEC PC98)
		vk_ax              = 0x96,   //                     (Japan AX)
		vk_unlabeled       = 0x97,   //                        (J3100)
		vk_nexttrack       = 0x99,   // Next Track
		vk_numpadenter     = 0x9C,   // Enter on numeric keypad
		vk_rcontrol        = 0x9D,
		vk_mute            = 0xA0,   // Mute
		vk_calculator      = 0xA1,   // Calculator
		vk_playpause       = 0xA2,   // Play / Pause
		vk_mediastop       = 0xA4,   // Media Stop
		vk_volumedown      = 0xAE,   // Volume -
		vk_volumeup        = 0xB0,   // Volume +
		vk_webhome         = 0xB2,   // Web home
		vk_numpadcomma     = 0xB3,   // , on numeric keypad (NEC PC98)
		vk_divide          = 0xB5,   // / on numeric keypad
		vk_sysrq           = 0xB7,
		vk_rmenu           = 0xB8,   // right Alt
		vk_pause           = 0xC5,   // Pause
		vk_home            = 0xC7,   // Home on arrow keypad
		vk_up              = 0xC8,   // UpArrow on arrow keypad
		vk_prior           = 0xC9,   // PgUp on arrow keypad
		vk_left            = 0xCB,   // LeftArrow on arrow keypad
		vk_right           = 0xCD,   // RightArrow on arrow keypad
		vk_end             = 0xCF,   // End on arrow keypad
		vk_down            = 0xD0,   // DownArrow on arrow keypad
		vk_next            = 0xD1,   // PgDn on arrow keypad
		vk_insert          = 0xD2,   // Insert on arrow keypad
		vk_delete          = 0xD3,   // Delete on arrow keypad
		vk_lwin            = 0xDB,   // Left Windows key
		vk_rwin            = 0xDC,   // Right Windows key
		vk_apps            = 0xDD,   // AppMenu key
		vk_power           = 0xDE,   // System Power
		vk_sleep           = 0xDF,   // System Sleep
		vk_wake            = 0xE3,   // System Wake
		vk_websearch       = 0xE5,   // Web Search
		vk_webfavorites    = 0xE6,   // Web Favorites
		vk_webrefresh      = 0xE7,   // Web Refresh
		vk_webstop         = 0xE8,   // Web Stop
		vk_webforward      = 0xE9,   // Web Forward
		vk_webback         = 0xEA,   // Web Back
		vk_mycomputer      = 0xEB,   // My Computer
		vk_mail            = 0xEC,   // Mail
		vk_mediaselect     = 0xED;   // Media Select

	const char* const vk_label[] = {
		"ESC",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"-",
		"=",
		"BACKSPACE",
		"TAB",
		"Q",
		"W",
		"E",
		"R",
		"T",
		"Y",
		"U",
		"I",
		"O",
		"P",
		"[",
		"]",
		"RETURN",
		"LEFT CTRL",
		"A",
		"S",
		"D",
		"F",
		"G",
		"H",
		"J",
		"K",
		"L",
		";",
		"'",
		"`",
		"LEFT SHIFT",
		"#",
		"Z",
		"X",
		"C",
		"V",
		"B",
		"N",
		"M",
		",",
		".",
		"/",
		"RIGHT SHIFT",
		"* NUMPAD",
		"LEFT ALT",
		"SPACE",
		"CAPS LOCK",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"NUM LOCK",
		"SCROLL LOCK",
		"7 NUMPAD",
		"8 NUMPAD",
		"9 NUMPAD",
		"- NUMPAD",
		"4 NUMPAD",
		"5 NUMPAD",
		"6 NUMPAD",
		"+ NUMPAD",
		"1 NUMPAD",
		"2 NUMPAD",
		"3 NUMPAD",
		"0 NUMPAD",
		", NUMPAD",
		"		87=F11",
		"F12",
		"NEXT TRACK",
		"RETURN NUMPAD",
		"RIGHT CTRL",
		"MUTE",
		"CALCULATOR",
		"PLAY/PAUSE",
		"STOP",
		"VOLUME -",
		"VOLUME +",
		"HOMEPAGE",
		"/ NUMPAD",
		"PRINT SCREEN",
		"RIGHT ALT",
		"PAUSE BREAK",
		"HOME",
		"CURSOR UP",
		"PAGE UP",
		"CURSOR LEFT",
		"CURSOR RIGHT",
		"END",
		"CURSOR DOWN",
		"PAGE DOWN",
		"INSERT",
		"DELETE",
		"WINDOWS LEFT",
		"WINDOWS RIGHT",
		"MENU",
		"POWER",
		"SLEEP",
		"WAKE",
		"SEARCH",
		"FAVORITES",
		"REFRESH",
		"STOP",
		"FORWARD",
		"BACK",
		"COMPUTER",
		"E-MAIL",
		"MEDIA" };

}

#endif
