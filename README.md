
For now, a template for an embdedded application for the ESP32-S3-Wroom1 module running ESP-IDF
Will update with firmware for the controller board for the WS2812b RGBLED panels

KiCad schematic and PCB layout files can be found in the pcb directory

Scripts are in scripts directory, named appropriately

Development plan: 
    - Build setup, get working hello-world program.
    - Develop 7-segment display driver for the soburg-v2 board, which uses 32-bit shift registers.
      Ensures functional hardware interaction and interface design.
    - Develop WS2812b driver, would be nice to have some kind of testing for this.
    - Develop WS2812b interface. I like the FastLed library for Arduino so might have a lot of similar functionality.
    - Implement proper app structure, with error checking and performance profiling
    - Add a couple LED effects- the random blink and rainbow sweep are easy ones.
    - Create a mock LED panel that executes natively to test LED effects outside of hardware. (SDL2 or something)
      Should use the same interface but a different driver (that's probably integrated into the program)
      Needs to be updated to support the same control interfaces implemented on hardware.
    - Add support for the aforementioned hardware control interfaces.
      (Dedicated control board may vary, main one not even designed yet)
      Buttons for switching effects, potentiometers, rotary encoders, 7 segement displays, OLED panel, etc.
    - Checkpoint at a Conway's Game of Life effect that can be modified by controls (speed, brightness, reset)
    - Design this far out is murky, anything past this point is a future ambition
    - MicroSD card for bitmap effects. Implies custom images and animations, config for which can be in a yaml or something
    - Microphone for sound-based effects like a spectrum analyzer
    
This is basic but hopefully can be good platform for future WS2812b projects.
