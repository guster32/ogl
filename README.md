# This repo is used simply for tracking my progress of working through the OpenGL tutorials

>All the source code on this site (except third-party libraries) is released under the WTFPL Public Licence 

                DO WHAT THE F*CK YOU WANT TO PUBLIC LICENSE
                          Version 2, December 2004
    Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
          
    Everyone is permitted to copy and distribute verbatim or modified
    copies of this license document, and changing it is allowed as long
    as the name is changed.

    DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
      TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
      0. You just DO WHAT THE FUCK YOU WANT TO.

* Install the following dependencies:
    * Install clang 9 or later (https://justiceboi.github.io/blog/install-clang-9-on-ubuntu/)
    * ```sudo apt install cmake g++ ninja-build glfw3 glew glm```
    * For ubunt 21+ ```sudo apt install cmake g++ ninja-build libglfw3-dev libglew-dev libglm-dev```
* Build:
    * ```mkdir -p build/default```
    * ```cd mkdir -p build/default```
    * ```cmake -GNinja ../..```
    * ```ninja```

# Notes on VSCODE setup issues with lldb:

`sudo dnf install llvm-devel lldb-devel`

https://github.com/lldb-tools/lldb-mi.git

https://github.com/microsoft/vscode-cpptools/issues/5415



