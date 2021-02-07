# wolf3d

As a graphic design project, Wolf3D will enable you to solidify your skills in this area:
windows, colors, events, fill shapes etc.
To conclude Wolf3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics. John Carmack is
undoubtedly a genius. He was one of the first programmers to think about these applications and remains famous for them today. With the help of the numerous documents
available on the internet, you will use mathematics as a tool to create elegant and efficient
algorithms. There's multiple sounds effects and light shading so the game look realistic.

#### *How to install SDL2*

The SDL2 framework folder is already in this repo.
But if it didn't work for you, you can install the SDL2 library in you machine.

__*Ubuntu:*__

```bash
sudo apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

__*Fedora:*__

```bash
sudo dnf install SDL2-devel SDL2_mixer-devel SDL2_ttf-devel
```

__*MacOS:*__

All ready for use. Just type **make**.

__*Windows:*__

- [MinGW](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php).
- [Visual Studio](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvsnet2010u/index.php).

## Compiling

Use [make](https://en.wikipedia.org/wiki/Makefile) for compiling all files.

When you have already installed SDL2 library you can use this simple rules:
- **make**: Compile all.
- **make clean**: Delete temporary files.
- **make del**: Delete temporary Wolf3D files only(if you changed code use `make del && make` for re-compile only Wolf3D executable without libft).
- **make fclean**: Delete executable Wolf3D file & libft.
- **make re**: It's rules - **make fclean** & **make** in one.

## Usage:

```bash
./wolf3d maps/map_name.w3d
```

- `[W | S]`: Moving forward | backward.
- `[A | D]`: Rotate left | right.
- `[Space]`: Return to the menu page.
- `[ESC]`: Close Wolf3D.

# Intro page
<img width="1285" alt="Screen Shot 2021-02-06 at 5 49 08 PM" src="https://user-images.githubusercontent.com/44867969/107149413-bc2c7200-6958-11eb-9bf2-8b08d8db2c5b.png">

# Menu page
<img width="1280" alt="Screen Shot 2021-02-06 at 5 45 59 PM" src="https://user-images.githubusercontent.com/44867969/107149415-c0588f80-6958-11eb-9a8a-2b58fd975d3e.png">

# Options page
<img width="1282" alt="Screen Shot 2021-02-06 at 5 46 22 PM" src="https://user-images.githubusercontent.com/44867969/107149419-c484ad00-6958-11eb-9c2f-8eee56da90aa.png">

# Standard mode
<img width="1283" alt="Screen Shot 2021-02-06 at 5 46 39 PM" src="https://user-images.githubusercontent.com/44867969/107149422-ca7a8e00-6958-11eb-9bde-bee1b4ae1fd5.png">
<img width="1282" alt="Screen Shot 2021-02-06 at 5 47 19 PM" src="https://user-images.githubusercontent.com/44867969/107149423-ccdce800-6958-11eb-970d-b108f5cd2249.png">

# Islamic mode
<img width="1282" alt="Screen Shot 2021-02-06 at 5 47 35 PM" src="https://user-images.githubusercontent.com/44867969/107149425-d0706f00-6958-11eb-9ace-3512c08a604b.png">
<img width="1282" alt="Screen Shot 2021-02-06 at 5 47 57 PM" src="https://user-images.githubusercontent.com/44867969/107149426-d1a19c00-6958-11eb-8528-1d55bd511ed4.png">

# Moroccan cha3bi mode
<img width="1283" alt="Screen Shot 2021-02-06 at 5 48 11 PM" src="https://user-images.githubusercontent.com/44867969/107149427-d403f600-6958-11eb-9175-692ee4163e11.png">
<img width="1283" alt="Screen Shot 2021-02-06 at 5 48 24 PM" src="https://user-images.githubusercontent.com/44867969/107149430-d5cdb980-6958-11eb-9210-25fefc294181.png">
