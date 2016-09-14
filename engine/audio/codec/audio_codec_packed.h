#pragma once

/*!
 * Cross platform 'pack' macro, idea stolen from
 * https://gist.github.com/PhilCK/1534763
 *
 * Example:
 * PACKED(
 * struct Foo
 * {
 *     float bar;
 *     float henk;
 *     float the_borg;
 * }
 * );
 */

#ifdef __GNUC__
#define PACKED(pack_struct) pack_struct __attribute__((__packed__))
#else
#define PACKED(pack_struct) __pragma(pack(push, 1)) pack_struct __pragma(pack(pop))
#endif
