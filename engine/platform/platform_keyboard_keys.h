/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once


namespace aeon
{
namespace platform
{

enum class keyboard_key_state
{
    released = 0,
    pressed  = 1
};

enum class keyboard_key
{
// Unknown key, the mac "fn" button
// gets picked up as key_unknown.
    key_unknown            = -1,

// Printable keys
    key_space              = 32,
    key_apostrophe         = 39,
    key_comma              = 44,
    key_minus              = 45,
    key_period             = 46,
    key_slash              = 47,
    key_0                  = 48,
    key_1                  = 49,
    key_2                  = 50,
    key_3                  = 51,
    key_4                  = 52,
    key_5                  = 53,
    key_6                  = 54,
    key_7                  = 55,
    key_8                  = 56,
    key_9                  = 57,
    key_semicolon          = 59,
    key_equal              = 61,
    key_a                  = 65,
    key_b                  = 66,
    key_c                  = 67,
    key_d                  = 68,
    key_e                  = 69,
    key_f                  = 70,
    key_g                  = 71,
    key_h                  = 72,
    key_i                  = 73,
    key_j                  = 74,
    key_k                  = 75,
    key_l                  = 76,
    key_m                  = 77,
    key_n                  = 78,
    key_o                  = 79,
    key_p                  = 80,
    key_q                  = 81,
    key_r                  = 82,
    key_s                  = 83,
    key_t                  = 84,
    key_u                  = 85,
    key_v                  = 86,
    key_w                  = 87,
    key_x                  = 88,
    key_y                  = 89,
    key_z                  = 90,
    key_left_bracket       = 91,
    key_backslash          = 92,
    key_right_bracket      = 93,
    key_grave_accent       = 96,
    key_world_1            = 161, // non-us #1
    key_world_2            = 162, // non-us #2

// Function keys
    key_escape             = 256,
    key_enter              = 257,
    key_tab                = 258,
    key_backspace          = 259,
    key_insert             = 260,
    key_delete             = 261,
    key_right              = 262,
    key_left               = 263,
    key_down               = 264,
    key_up                 = 265,
    key_page_up            = 266,
    key_page_down          = 267,
    key_home               = 268,
    key_end                = 269,
    key_caps_lock          = 280,
    key_scroll_lock        = 281,
    key_num_lock           = 282,
    key_print_screen       = 283,
    key_pause              = 284,
    key_f1                 = 290,
    key_f2                 = 291,
    key_f3                 = 292,
    key_f4                 = 293,
    key_f5                 = 294,
    key_f6                 = 295,
    key_f7                 = 296,
    key_f8                 = 297,
    key_f9                 = 298,
    key_f10                = 299,
    key_f11                = 300,
    key_f12                = 301,
    key_f13                = 302,
    key_f14                = 303,
    key_f15                = 304,
    key_f16                = 305,
    key_f17                = 306,
    key_f18                = 307,
    key_f19                = 308,
    key_f20                = 309,
    key_f21                = 310,
    key_f22                = 311,
    key_f23                = 312,
    key_f24                = 313,
    key_f25                = 314,
    key_kp_0               = 320,
    key_kp_1               = 321,
    key_kp_2               = 322,
    key_kp_3               = 323,
    key_kp_4               = 324,
    key_kp_5               = 325,
    key_kp_6               = 326,
    key_kp_7               = 327,
    key_kp_8               = 328,
    key_kp_9               = 329,
    key_kp_decimal         = 330,
    key_kp_divide          = 331,
    key_kp_multiply        = 332,
    key_kp_subtract        = 333,
    key_kp_add             = 334,
    key_kp_enter           = 335,
    key_kp_equal           = 336,
    key_left_shift         = 340,
    key_left_control       = 341,
    key_left_alt           = 342,
    key_left_super         = 343,
    key_right_shift        = 344,
    key_right_control      = 345,
    key_right_alt          = 346,
    key_right_super        = 347,
    key_menu               = 348
};

struct keyboard_modifier_key
{
    enum keyboard_modifier_key_enum
    {
        shift           = 0x0001,
        control         = 0x0002,
        alt             = 0x0004,
        super           = 0x0008
    };
};

} // namespace platform
} // namespace aeon
