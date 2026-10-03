# arduino-lab-5-blocking-code-state-machines-and-analog
## Arduino Lab 05: Blocking Code, State Machines, and Buttons

In this lab, I worked with an Arduino Uno, LEDs, push buttons, resistors, and jumper wires. The purpose of the lab was to practice input and output programming while learning how to avoid blocking code. I created multiple Arduino programs that used buttons to control LEDs, change LED brightness, run light sequences, and count in binary.

The main focus was making the Arduino respond to button input immediately, even while an LED pattern or sequence was running. I used `millis()` timing instead of relying only on `delay()` so the program could continue checking buttons while controlling LEDs.

## Files and Tools Used

- Arduino Uno
- Arduino IDE
- Breadboard
- Jumper wires
- LEDs: red, yellow, green, blue, and white
- 220 Ω or 330 Ω resistors for each LED
- Push buttons
- 10 kΩ resistors for button pull-down wiring when using `INPUT`
- Arduino pin modes: `OUTPUT`, `INPUT`, and `INPUT_PULLUP`
- `digitalWrite()` to turn LEDs on and off
- `digitalRead()` to read button presses
- `analogWrite()` for PWM LED brightness control
- `millis()` for non-blocking timing
- Variables for LED position, speed, button states, press length, and timing
- Debounce timing to prevent one button press from being counted multiple times

The Arduino sketches created for this lab included:

```text
exercise1_blink_and_button.ino
exercise2_short_long_double_press.ino
exercise3_led_brightness_control.ino
exercise4_five_led_sequencer.ino
exercise5_binary_counter.ino
```

## What I Did

For the first exercise, I programmed one LED to blink at a steady rate of one second on and one second off. I also connected a second LED to a push button. The second LED turned on when the button was pressed and turned off when the button was released.

The important requirement was that the button-controlled LED had to react instantly. I could not use a long `delay(1000)` because the Arduino would stop checking the button while waiting. Instead, I used `millis()` to keep track of the one-second blinking interval. This allowed the first LED to blink while the Arduino continued reading the button input. The first LED blinked continuously, and the second LED immediately followed the button state.

For the second exercise, I used one button to recognize different button press patterns. A short press started a stoplight mode, a double press started disco mode, and a long press turned all LEDs off.

The stoplight mode used red, yellow, and green LEDs. The sequence showed red, then yellow, then green, and repeated. The disco mode quickly changed between different LED colors. The long press stopped whichever mode was active and turned every LED off.

To make this work, I recorded when the button was pressed and when it was released. I used the elapsed time to identify whether the press was short or long. I also used a short waiting period after the first press to determine whether another press happened for a double press.

For the third exercise, I used two buttons to control the brightness of an LED. One button increased the brightness, and the other button decreased the brightness. I used a PWM-capable Arduino pin and the `analogWrite()` function.

The LED brightness used values from 0 to 255:

```text
0 = LED completely off
255 = LED at full brightness
```

I divided the brightness into about ten steps. Each press of the brighten button increased the value by about 25 or 26. After approximately ten presses, the LED reached full brightness. The dim button decreased the brightness by the same amount until the LED was fully off.

For the fourth exercise, I used five LEDs as a moving sequencer. The LEDs were arranged from left to right using red, yellow, green, blue, and white LEDs. The green LED in the middle was the starting and reset position.

The LED positions were:

```text
Red       Yellow       Green       Blue       White
Pin 2     Pin 3        Pin 4       Pin 5      Pin 6
```

I used three buttons:

```text
Right button: Speeds up the sequence moving right
Left button: Speeds up the sequence moving left
Reset button: Returns to the center green LED and stops movement
```

The program used a speed variable. A positive speed value moved the sequence to the right, a negative speed value moved it to the left, and a speed of zero stopped the sequence. Each button press changed the speed value. The faster the speed became, the shorter the delay between LED movements. When the sequence reached the end, it wrapped around to the other side.

For the final exercise, I programmed a binary counter using LEDs and buttons. One button counted up, one button counted down, and one button reset the count to zero. The LEDs displayed the number in binary.

For example:

```text
Decimal 0  = 0000
Decimal 1  = 0001
Decimal 2  = 0010
Decimal 3  = 0011
Decimal 15 = 1111
```

The Arduino stored the current number in a variable. When the count-up button was pressed, the number increased. When the count-down button was pressed, the number decreased. When the reset button was pressed, the value returned to zero. The program then updated the LEDs to display the binary version of the number.

## Blocking Code and Timing

One of the main topics in this lab was blocking code. Blocking code stops the Arduino from doing other tasks while it waits. For example, using:

```cpp
delay(1000);
```

pauses the entire program for one second. During that time, the Arduino cannot read a button, respond to input, or update another LED.

I used `millis()` to avoid blocking the program. The `millis()` function keeps track of how many milliseconds have passed since the Arduino started. Instead of pausing the whole program, I checked whether enough time had passed before changing an LED or moving to the next step in a sequence.

For example, the blinking LED checked whether 1,000 milliseconds had passed. If it had, the LED changed from on to off or from off to on. The Arduino could still continue checking all button inputs in the rest of the loop.

This was important for the first exercise because the second LED needed to react instantly to the button. It was also important for the stoplight, disco mode, and five-LED sequencer because the buttons needed to work while the patterns were running.

## Button Debouncing

I also worked with button debouncing. When a physical button is pressed, the metal contacts can briefly bounce between connected and disconnected states. The Arduino may detect several quick presses instead of one press.

To prevent this, I used a debounce time. After the program detected a button press, it ignored additional changes for a short amount of time, such as 50 milliseconds or 200 milliseconds. This made the button readings more reliable.

Without debouncing, one press could accidentally:

- Increase the sequencer speed more than once
- Change the binary counter by multiple numbers
- Activate the wrong button mode
- Make the LED brightness jump several levels

## State Machines

This lab also used simple state-machine ideas. A state machine stores the current state of the program and changes behavior based on that state.

For example, the stoplight program had different states:

```text
Red state
Yellow state
Green state
```

The program stayed in one state for a selected amount of time before moving to the next state.

The five-LED sequencer also used states. The program stored the current LED position and changed it depending on the direction and speed. The sequence could move right, move left, stop, or reset to the center position.

The button modes also acted like states:

```text
Lights off mode
Stoplight mode
Disco mode
```

A short press changed the program to stoplight mode. A double press changed it to disco mode. A long press changed it to the lights-off mode.

## What I Learned

This lab helped me understand how Arduino programs can handle multiple tasks at the same time. I learned that using `delay()` can cause problems when a program needs to respond to buttons or sensors immediately. Using `millis()` made the code more responsive because it allowed the Arduino to keep checking input while LEDs blinked or moved through a sequence.

I learned how to use buttons for more than one simple action. A button can recognize short presses, long presses, double presses, repeated presses, and press sequences. These controls are used in everyday technology, including computer mice, phones, game controllers, television remotes, car controls, and power buttons.

I also learned how PWM can control LED brightness. Even though the Arduino output is digital, `analogWrite()` can rapidly switch the output on and off to make an LED appear dimmer or brighter.

Finally, I learned that organizing code into functions makes Arduino programs easier to understand. Functions such as `checkButtons()`, `runSequencer()`, `showLED()`, `allLightsOff()`, and `displayBinary()` separated the program into smaller parts. This made it easier to test and fix each behavior.

Overall, this lab showed how buttons, timing, LEDs, PWM, debouncing, and state machines can be combined to make interactive Arduino projects.
