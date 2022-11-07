#pragma once

#ifdef COFFEEXCODEC_EXPORTS
#define COFFEEXCODEC_EXPORT __declspec(dllexport)
#else
#define COFFEEXCODEC_EXPORT __declspec(dllimport)
#endif