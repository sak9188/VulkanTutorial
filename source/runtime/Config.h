#if defined(SOLIS_SO)
#	if defined(_MSC_VER)
#		if defined(SOLIS_API_EXPORT)
#			define SOLIS_API __declspec(dllexport)
#		else
#			define SOLIS_API __declspec(dllimport)
#		endif
#	elif defined (__clang__) || defined (__GNUC__)
#		if defined(SOLIS_API_EXPORT)
#		    define SOLIS_API __attribute__ ((__visibility__ ("default")))
#       else
#           define SOLIS_API __attribute__ ((__visibility__ ("default")))
#       endif
#	else
#		define SOLIS_API
#	endif
#else
#		define SOLIS_API
#endif