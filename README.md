# Raytracer by Hailey

This is my personal project building a raytracer from scratch (except OpenGL, which I can't make from scratch)

## Currently working on...

- Wanted to do BVH collision detection in GLSL
- Stuck in a rabbit hole of GPU optimization, kernel, thread, and a bunch of terminologies I have no clue about

### Current results

![image](https://github.com/havocado/raytracer-by-hailey/assets/47484587/51c8a59a-578c-466a-b582-05e27a6c6df0)

## Coordinates

![image](https://github.com/havocado/obj-raytracer/assets/47484587/4d144417-1e66-4439-a29c-900eeaf34bdc)


# How to build

## Getting the code

Use the `---recursive` option to download GLFW with the raytracer:

```
git clone --recursive https://github.com/havocado/raytracer-by-hailey.git
```

To build the program, cd into the directory:

```
cd raytracer-by-hailey
```


## Using CMake to create the project

From a command prompt in the `raytracer-by-hailey` directory:
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
