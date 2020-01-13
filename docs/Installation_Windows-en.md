# Project installation for Windows

## Prerequisites

- Have a github account, linked with a SSH key.
- Tools:
  - Git for Windows: https://git-scm.com/download/win (activate git bash) or GitExtension
  - **MSVC** compiler and Windows SDK: all included with **Visual Studio 2019** with **Desktop C++** packet.
    - Warning: MinGW may not work because of this issue: https://sourceforge.net/p/mingw-w64/bugs/737/
  - **CMake v3.13** minimum
  - **QtCreator** (recommanded) *(Visual Studio and basic editor + CMake-gui are valid aternatives if Qt libraries are installed)*
- Needed libraries:
  - Lua 5.3 https://sourceforge.net/projects/luabinaries/files/5.3.5/Windows%20Libraries/Static/lua-5.3.5_Win64_vc14_lib.zip/download
  - Boost 1_69 for MSVC https://github.com/dummymeuporg/dummymeuporg.github.io/wiki/Install-boost-on-Windows

## Setup the project

- Open git bash and clone the project
```
    git clone https://github.com/dummymeuporg/dummyeditor.git
```
- Go to cloned directory
```
    cd dummueditor
```
- And then initialize and update submodules
```
    git submodule init
    git submodule update
```

- Configure QtCreator: Tools -> options -> Kits, find or create a kit to compile with MSVC. Selected kit must not have a red icon. If it's the case, hover the icon to know the problem.
![Kit configuration example](Photo/Qt-Config_MSVC_kit.png "Kit configuration example")

- Configure CMake:
    - CMake needs to know some variables to work well. Including where are Boost and Lua. If you are using QtCreator, the best way to do it is to configure the cmake configuration:
    - Tools -> Options -> Kits -> (choose the right one):
      - **CMake generator**: set "Visual studio 16 2019 / none"
    - CMake configuration: add the following variables: (and adapt their values to your configuration)
      - BOOST_INCLUDEDIR:PATH=C:\SDKs\boost_1_69_0
      - BOOST_LIBRARYDIR:PATH=C:\SDKs\boost_1_69_0\lib64-msvc-14.1
      - BOOST_ROOT:PATH=C:\SDKs\boost_1_59_0\boost
      - LUA_INCLUDE_DIR:PATH=C:\SDKs\lua-5.3.5_Win64_vc14_lib\include
      - LUA_LIBRARIES:FILEPATH=C:\SDKs\lua-5.3.5_Win64_vc14_lib\lua53.lib
      - LUA_LIBRARY:FILEPATH=C:\SDKs\lua-5.3.5_Win64_vc14_lib\lua53.lib
    - if you're not using QtCreator you'll need to add one more variable:  CMAKE_PREFIX_PATH:STRING=path/to/Qt/folder

- Load the project:
   - QtCreator -> Open project -> Select dummyeditor/CMakeList.txt
   - Select ONLY the chosen kit previously configured
   - "Configure project" and wait. You should then see the file architecture.
   - Configure build target: Projects (in the left column) -> Build Steps -> details -> check **only** dummyeditor.

- And then you're good to go, compile and run!

## Misc
### I don't know how to link a SSH key to my github account
Account settings -> SSH and GPG keys.
There is a link "guide to generating SSH keys" with details.

### My generated SSH key is not accepted by github
With the command given by github documentation your public SSH key should start with "ssh-rsa".
If it's not the case it may not be accepted by github and it may be caused by the wrong "ssh-keygen" installed.
You may then use Putty to generate SSH keys, to do so follow this link: https://stackoverflow.com/questions/31813080/windows-10-ssh-keys

### Git submodule update says I don't have the permissions to clone...
Verify you have a github account and configured SSH keys registered on your github account
