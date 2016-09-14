#pragma once

// al_check function idea borrowed from http://www.sfml-dev.org
void al_check_error(const char *file, unsigned int line);

#ifndef al_check
#define al_check(Func) ((Func), al_check_error(__FILE__, __LINE__))
#endif //  al_check
