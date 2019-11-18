# GraphicsProject
Programming framework for Computer Graphics course at DIKU

## Installing on Mac OS 10.13.6

Remark: Current version numbers we used are shown. The framework may work with other versions.

We used MacPorts (https://www.macports.org/) to install third party dependencies. Afer having installed macport then open a terminal and do write as follows

```console  
  sudo port install glew @2.1.0_0+universal
  sudo port install glfw @3.2.1_0+docs+universal
  sudo port install glm @0.9.9.0_0
  ```

We downloaded CMake ver 3.13.1 from (https://cmake.org/) and installed this.

* Open up CMake gui
* Browse to source folder that contains top-level CMakeLists.txt file
* Specify a folder where to build the binaries. IMPORTANT: Keep binary tree separate from source tree. See figure below for illustration

<center>
<img src="Documentation/macos/cmake_gui.png" width="50%">
</center>

* Click configure

<center>
<img src="Documentation/macos/cmake_first_configure.png" width="50%">
</center>

* Inspect CMake variables to see if you need to specify anything
* Click configure until no pink entries are shown

<center>
<img src="Documentation/macos/cmake_second_configure.png" width="50%">
</center>

* Click generate

<center>
<img src="Documentation/macos/cmake_generate.png" width="50%">
</center>

* Click open project, you should see your IDE open op.

<center>
<img src="Documentation/macos/cmake_open_project.png" width="50%">
</center>

Finally you can build all using your favourite IDE environment

## Installing on Windows
To be done

## Installing on Linux
To be done
