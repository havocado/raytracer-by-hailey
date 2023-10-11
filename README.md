# OpenGL side project - Raytracer

TBD

## Coordinates

![image](https://github.com/havocado/obj-raytracer/assets/47484587/4d144417-1e66-4439-a29c-900eeaf34bdc)

### Cube

![image](https://github.com/havocado/obj-raytracer/assets/47484587/2421b359-1cdd-4ec4-9022-957c8e2746dc)



# Instructions from the original repo

## Getting the code

The easiest way to get hold of the starter code is to run the following command using a shell you can run git from:

```
git clone --recursive https://github.com/juliettef/GLFW-CMake-starter
```

If you are on Windows you can download git from [git-scm.com/download/win](https://git-scm.com/download/win) and use the right click menu in Windows File Explorer to "Git Bash here" and then run git commands.

This will create the directory _GLFW-CMake-starter_ and get the latest source code, using the ```--recursive``` option to download the GLFW code which is included in the repository as a submodule. If you want to run further git commands from the command line you'll need to cd into the directory:

```
cd GLFW-CMake-starter
```

Alternatively you can use a git GUI program such as [Fork](https://git-fork.com/) to get the code. Most of these will automatically download the git submodules.

If you download the code from GitHub via the "Download ZIP" approach, you'll also need to download GLFW into the _glfw_ folder. The correct version can be found by clicking on the _glfw_ folder you see on the [front page of the _GLFW-CMake-starter_ GitHub repository](https://github.com/juliettef/GLFW-CMake-starter).

## Using CMake to create the project

From a command prompt in the `GLFW-CMake-starter` directory:
1. `mkdir build`
1. `cd build`
1. `cmake ..` (for MinGW the build system generator needs to be specified using the -G option: `cmake .. -G "MinGW Makefiles"`)
1. Either run `make all` or for Visual Studio open `GLFW-CMake-starter.sln` or for MinGW run `mingw32-make`

# Troubleshooting

## Logs not appearing when using Windows CLion

Using this repo on Windows CLion seems to cause an issue related to runnerw.exe which shows as deprecated.

There were 2 cases where this issue was addressed:
- https://youtrack.jetbrains.com/issue/CPP-25836/runnerw.exe-AttachConsole-failed-with-error-6-The-handle-is-invalid.
- https://youtrack.jetbrains.com/issue/CPP-25818/Logs-not-appearing-in-console-when-running-an-OpenGL-with-GLFW-project

Disabling Registry key 'run.processes.with.pty' seems to solve the problem.
