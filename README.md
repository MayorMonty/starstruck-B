# StarStruck B
========

This is the source code for Some Assembly Required's StarStruck Robot, written using PROS, a native C compiler for VEX Cortex. The primary files of interest are most likely:
  - subsystem/pid(.c|.h) and strategies. This is a generalized PID implementation, with several strategies implemented:
    - xdrive: This implements multiple PIDs to power an X Drive.
    - maintain: source code to maintain a specific motor speed.
    - move: The most simple PID strategy. Move for a specific direction
