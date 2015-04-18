# leansand

Falling sand game with a tiny core and Lua everything.

The purpose of this project is to develop a very lightweight but extensible C application, which defines some Lua bindings that make it into a falling sand game.

## Building

2. Extract the correct include/ and lib/ directories into ./SDL2/ [x][correct]
3. Patch the SDL2.0.3 SDL_platform.h file with the patch file in `.`
4. Run `make debug`
5. Pray
6. `build/leansand-debug` should work

[sdl]: https://libsdl.org/download-2.0.php
[correct]: http://stackoverflow.com/a/23242705/2278637

## Usage

To be decided

## Contribution

Pull requests, yo

## Contributors

* boxmein
* Ristovski
* nucular?

## License

There's a LICENSE file. I'll ease your trouble, it's the MIT license. Attribution, but do what you want. 2015 whatever.
