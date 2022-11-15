#pragma once

#ifdef COFFEELICENSE_EXPORTS
#define COFFEELICENSE_EXPORT   __declspec(dllexport)
#else
#define COFFEELICENSE_EXPORT   __declspec(dllimport)
#endif
