# ESP-IDF-Library

This repository contains all my custom ESP-IDF libraries, types and so on that I've written so far.

> [!IMPORTANT]  
> The libraries/helpers/types are all written in C++, so you will likely need to write your main in C++ too.
> This can be done using `extern "C"` infront of your `app_main()` declaration.

> [!IMPORTANT]  
> It is assumed that all dependencies which are also from this repo are directly includable (`#include "logger.hpp"`).
> In PlatformIO, this can be done by adding a `-I` build flag with the directory to include when searching for headers to `platformio.ini`.
> Example: `build_flags = -Iinclude -Ihelpers -Itypes`

### Folder Structure:
* `libraries` - Contains full libraries useful for many projects
* `helpers` - Contains helper/wrapper functions for frequently used code
* `types` - Contains custom written types

<br><hr>
Licensed under the [MarioS271 Open License](https://license.marios271.net/open)