**Go here to download binaries and code**

https://github.com/LinuxBeaver/Royal_Text_Gimp_Plugin/releases

## GEGL Royal - a text styling plugin for Gimp

![Alt text](https://i.imgur.com/QOogLex.png)

![image](https://github.com/LinuxBeaver/Royal_Text_Gimp_Plugin/assets/78667207/f2be1d99-325c-4001-b03c-8676d4f2b9c6)



## OS specific location to put GEGL Filter binaries 

**Windows**

`C:\Users\USERNAME\AppData\Local\gegl-0.4\plug-ins`
 
**Linux**

`~/.local/share/gegl-0.4/plug-ins`
 
**Linux (Flatpak)**

 `~/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins`



## Compiling and Installing

### Linux

To compile and install you will need the GEGL header files (`libgegl-dev` on
Debian based distributions or `gegl` on Arch Linux) and meson (`meson` on
most distributions).

```bash
meson setup --buildtype=release build
ninja -C build

```

If you have an older version of gegl you may need to copy to `~/.local/share/gegl-0.3/plug-ins`
instead (on Ubuntu 18.04 for example).

### Windows

The easiest way to compile this project on Windows is by using msys2.  Download
and install it from here: https://www.msys2.org/

Open a msys2 terminal with `C:\msys64\mingw64.exe`.  Run the following to
install required build dependencies:

```bash
pacman --noconfirm -S base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-meson mingw-w64-x86_64-gegl
```

Then build the same way you would on Linux:

```bash
meson setup --buildtype=release build
ninja -C build
```
## another preview of this based plugin

![image](https://github.com/LinuxBeaver/Royal_Text_Gimp_Plugin/assets/78667207/4f159808-5b82-40ef-bf09-7fa6c7247056)

![image](https://github.com/LinuxBeaver/Royal_Text_Gimp_Plugin/assets/78667207/401e361d-a1cc-4e90-9d59-19d1e9425c8c)



