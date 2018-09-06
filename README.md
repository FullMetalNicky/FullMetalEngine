# FullMetalEngine

FullMetalEngine is a wannabe game engine in its early infancy phase. Currently it contains a very basic implementation of a rendering engine, some utilities, and soon to come is a small physics simulation component. The development of the engine started at mid 2017, and since then I lazily work on it on the weekends. 
Huge props to this [guy](https://learnopengl.com/), who taught me most of what I know about OpenGL and inspired me when writing this engine. 
![Engine Demp](https://www.dropbox.com/s/obopp8h84qen31d/jump.JPG?raw=1)

## Future features!
  - Shadow rendering? Hmm...maybe.  
  - Text rendering
  - Widgets, if I'm really feeling masochistic 
  - Physics simulation module - I have started reading a wonderful [book](https://www.amazon.com/Game-Physics-Engine-Development-Commercial-Grade/dp/0123819768) and I plan on coding the basic components soon! 
  
## New Features!
  - Lights are now available for the obj shaders. I'm not sure about adding support for the other shaders because they simply render         geometric objects, but if anyone complains I will fix it.
  - A project containing a simple usage example - I will add a few more in the future, and clarify stuff on the wiki page
  
## Implementation
![Engine UML](https://www.dropbox.com/s/kozetn7mu2ts0qv/UML.JPG?raw=1)
It migh not be 100% up-to-date with all changes, but it should give you a clue about how stuff work in my twisted mind. Loading scenes can be done using a .json file, using the format you may find in scene.json. Right now behaviors are pretty much hard-coded, but I intend to extend it to user-provided callbacks or scripts. 
  
## Installation
 
FullMetalEngine depends on the following libraries:

- [Assimp](http://www.assimp.org/) - An asset loading library

- [glfw](http://www.glfw.org/) - Handles windowing, user input and other non-fun stuff. Use version >= 3.2.1.

- [GLEW](http://glew.sourceforge.net/) - extension loading library. Use version => 2.0.

- [glm](https://glm.g-truc.net/0.9.9/index.html) - math library for OpenGL. . Use version > 0.9.

- [PicoJson](https://github.com/kazuho/picojson) - a tiny (pico) Json parser.

- [SOIL](https://www.lonesock.net/soil.html) - super old library for image loading.

I advise you to download and compile these yourself, because pre-compiled versions are not necessarily the latest. 
For Windows 10, VS build:
  - Currently I just place all the dependecies in one folder, and have an enviromental variable called "Third_Party" pointing at it. 
For Ubuntu 18.04, Eclipse build:
  - I have added project files for Eclipse, so you should be able to compile it without too much hassle, if you have all the dependencies somehwere in your /usr directories.
I will make a proper CMake file for it soon.

## Development
Want to contribute? Great! Send me 6-pack of diet coke :)

## License
MIT, I think. But if you buy me a 6-pack of diet coke I won't complain. 
