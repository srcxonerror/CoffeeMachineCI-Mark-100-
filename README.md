# CoffeeMachineCI-Mark-100-
My CI subject project

WORK COFFEE MACHINE UPC FIB 2023-2024
Names: Adam Sarrate Nejjari, Abel Perelló Vidal

Sidenote: This project was written in C language.

IMPORTANT NOTE:
To run this program the lastest version of the "PROTEUS" simulator is needed.

OPERATION:
The operation of our coffee machine consists of three selector bars. Each bar has three options:
- For temperature values: Cold, Warm, and Hot.
- For coffee type values: Short, Normal, and Long.
- For dose values: Mild, Normal, and Strong.
To change the intensities of each bar, pressing the 'a' key decreases it, and with the 'd' key, it increases. To know which bar is being addressed, it will be selected between two "<>" symbols. You can switch between bars with the 'w' and 's' keys to go up and down, respectively.

Once the coffee configuration is chosen, pressing the 's' key or the "SELECT" button will start the coffee preparation. The preparation time will depend on the coffee configuration (as indicated in the practice statement) but will be indicated by a bar that lasts the same time. When finished, it will be indicated that the coffee is ready to drink, and another request can be made.

CODE STRUCTURE:
Our code is structured into 14 files:
- Main.c: Main functions of the code as well as the description of global variables.
- GLCD.c, .h, ASCII.h, splash.h, config.h: Functions given by the statement.
- dibuix.c, .h: Contains all functions that "draw" on the GLCD screen.
- configuracions.c, .h: Contains all configurations of the PIC18 (ports, PWM, timers...)
- calculs.c, .h: Contains all temperature calculations, time calculations...
- calculinterr.c, .: Contains all calculations and management involving interrupt usage.

