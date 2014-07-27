strutil ver. 1.5.0
********************

Minimalistic library improving C++ string support with UTF-8 and string handling functions.

The library is designed to be single cpp file only and as easy as possible to integrate.

Supported (optional) config defines:
STRUTIL_STRING // strutil uses std::string if STRUTIL_STRING not defined
STRUTIL_VECTOR // strutil uses std::vector if STRUTIL_VECTOR not defined
STRUTIL_WSTRING // strutil uses std::wstring if STRUTIL_WSTRING not defined
STRUTIL_WCHAR // strutil uses wchar_t if STRUTIL_WCHAR not defined
STRUTIL_TOLOWER // strutil uses default tolower if STRUTIL_TOLOWER not defined
STRUTIL_TOUPPER // strutil uses toupper if STRUTIL_TOUPPER not defined
STRUTIL_ISSPACE // strutil uses isspace if STRUTIL_STRUTIL not defined

All functions are in str namespace.

strutil library is copyright (C) 2009-2011 Jani Kajala (kajala@gmail.com).
Licensed under BSD/MIT license. See http://code.google.com/p/strutil/

Changes
-------

v1.5.0:
+ added dirname

v1.4.0:
+ added basename

v1.3.0:
+ added replace

v1.2.0:
+ added substr

v1.1.1:
+ couple of optimizations

v1.1.0:
+ added higher level to_utf8/from_utf8

