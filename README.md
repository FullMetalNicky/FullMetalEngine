# FullMetalEngine

FullMetalEngine is a wannabe game engine. Currently it contains a very basic implementation of a rendering engine, some utilities, and soon to come is a small physics simulation component. 
The development of the engine started at mid 2017, and since then I lazily work on it on the weekends. 

I tried to make it as cross-platform as possible. It was tested on Windows 10 and Ubuntu 16.04, but I can't really vouch for any other OS.

## Future features!
  - Lights!
  - A real pipeline  
  - Text rendering
  - Widgets, if I'm really feeling masochistic 
  - Physics simulation module 
  - A project containing simple usage examples
  
## Installation

FullMetalEngine depends on the following libraries:

- [Assimp](http://www.assimp.org/) - An asset loading library

- [glfw](http://www.glfw.org/) - Handles windowing, user input and other non-fun stuff. Use version >= 3.2.1.

- [GLEW](http://glew.sourceforge.net/) - extension loading library. Use version => 2.0.

- [glm](https://glm.g-truc.net/0.9.9/index.html) - math library for OpenGL. . Use version > 0.9.

- [PicoJson](https://github.com/kazuho/picojson) - a tiny (pico) Json parser.

- [SOIL](https://www.lonesock.net/soil.html) - super old library for image loading.

You may download them and compile them yourself, or you can use the pre-compiled (windows) binaries. 
I will make a proper CMake file for it soon. Currently I just place all the dependecies in one folder, and have an enviromental variable called "Third_Party" pointing at it. It's still quite a mess, so I advise you guys to wait until I sort it out. 

## Development
Want to contribute? Great! Send me 6-pack of diet coke :)

## License
MIT, I think. But if you buy me a 6-pack of diet coke I won't complain. 
