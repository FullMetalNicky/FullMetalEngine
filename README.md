# FullMetalEngine

FullMetalEngine is a wannabe game engine in its early infancy phase. Currently it contains a very basic implementation of a rendering engine, some utilities, and soon to come is a small physics simulation component. The development of the engine started at mid 2017, and since then I lazily work on it on the weekends. 
Huge props to this [guy](https://learnopengl.com/), who taught me most of what I know about OpenGL and inspired me when writing this engine. 

## Future features!
  - Lights!
  - A real pipeline  
  - Text rendering
  - Widgets, if I'm really feeling masochistic 
  - Physics simulation module 
  - A project containing simple usage examples
  
## Implementation
![Engine UML](https://www.dropbox.com/s/fcrkp7m6zitiiu9/UML.JPG?raw=1)
It migh not be 100% up-to-date with all changes, but it should give you a clue about how stuff work in my twisted mind. Loading scenes can be done using a .json file, using the format you may find in scene.json. Right now behaviors are pretty much hard-coded, but I intend to extend it to user-provided callbacks or scripts. 
  
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
I tried to make it as cross-platform as possible. It was tested on Windows 10, but I can't really vouch for any other OS. I'll try it on Ubuntu 16.04 soon though. 

## Development
Want to contribute? Great! Send me 6-pack of diet coke :)

## License
MIT, I think. But if you buy me a 6-pack of diet coke I won't complain. 
