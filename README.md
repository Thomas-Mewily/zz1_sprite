# zz1_sprite

in order to compile it, add a `bin` folder with the `.dll`
Also add the `.a` .la `.dll` to `lib`

![image](https://github.com/Thomas-Mewily/zz1_sprite/assets/40406187/f46707bf-7fe6-4a50-ae56-72fa59ff2792)

![image](https://github.com/Thomas-Mewily/zz1_sprite/assets/40406187/e623163d-3302-4a66-927c-426f0a45040f)

Gcc compilation command :

```bash
gcc -O0 -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/graph/*.c -Wall -Wextra -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
```

```bash
./bin/main.exe
```
