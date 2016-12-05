# RSC
Project files for the practical exercises of the Robotic Systems Control (30341EN) course at TU Cluj.

For each exercise, I will add relevant scripts to help you complete and visualise the excersises. The aim is to provide functions in Matlab and python, and other languages that might seem relevant in the future.

## Lab 1
Function for drawing the objects of the first assignment, in order to easily visualise the results of the rotations

### Food for thought
[Ping pong playing robot](https://www.sciencedaily.com/videos/ec585599d52173ea80f346a8d18c9810.htm)

## Lab 2
Functions for calculating homogenius transformation matrices for various transformations and for drawing segments of a robot based on the geometric model described by multiple transformation matrices.

### Food for thought
[Obstacle avoidance](https://www.youtube.com/watch?v=wCbWscjs4DQ)

## Lab 3
Function to draw multiple segments of a robot and change the DH parameters for each of the segments

### Food for thought
[Determining DH parameters](https://www.youtube.com/watch?v=rA9tm0gTln8)

## Embedded programming
For the second part of the laboratory, we will learn a few things about embedded programming. Embedded programming will eventually allow us to control a robotic arm using a dedicated micro-processor. The first examples are rather simple, but it will help us getting started and understanding the underlying principles. If you wish to use your own laptops for this part, you will need to install some specific software to be able to communicate with the development board and the debugger.

* Eclipse CDT (Eclipse for C/C++): https://www.eclipse.org
* GNU Arm embedded toolchain: https://launchpad.net/gcc-arm-embedded
* GNU Arm build tools: https://gnuarmeclipse.github.io/windows-build-tools
* Segger J-Link drivers: https://www.segger.com
* GNU Arm plugins for Eclipse: https://gnuarmeclipse.github.io

You can find the first assignment in the Assignment document

If you want to have a live view of the debugger and print messages in a console, you can use the RTT tools from SEGGER, which you can download from here:

* RTT files: http://download.segger.com/J-Link/RTT/RTT_Implementation_141217.zip

Extract the archive and include the binaries in the path of your project. Then add the 'SEGGER_RTT.h' in the includes of your project and debug your project. You can now print messages in the console and read them using the RTT Viewer software that should be installed by the Segger J-Link Software and Documentation
