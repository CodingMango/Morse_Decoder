# Morse_Decoder
Morse code Decoder (using pushbuttons and OLED Screen) with 5wpm speed

I have used two pushbuttons. One pushbutton sends an encrypted Morse Code message to Arduino for decryption; the other pushbutton is used to display the decrypted message(character) through the OLED screen. You have to push the pushbutton for 1sec approx for a "dot" and 2sec for a "dash".

![Image](https://github.com/user-attachments/assets/dbacc7d3-e60c-4093-8351-cb1eabe9d4db)

## Tech Stack

* **Software/Language:** C++ (Arduino Framework)
* **Hardware:** Arduino Uno (or compatible), 2x Pushbuttons, 128x64 I2C OLED Display (SSD1306)
* **Libraries:** `Wire.h` (I2C communication), `Adafruit_GFX.h` (Graphics core), `Adafruit_SSD1306.h` (Hardware-specific display driver)
* **Simulation:** [Wokwi Simulator Link](https://wokwi.com/projects/425214595189811201)

![Image](https://github.com/user-attachments/assets/0ee1e9e6-a509-4bfd-9a17-4793f661536c)

## Demo (click the image below)

[![Morse Code Hardware Demo](https://img.youtube.com/vi/Zestn8epKlw/0.jpg)](https://www.youtube.com/watch?v=Zestn8epKlw)

## Core Logic & Architecture

The system operates at a speed of approximately 5 Words Per Minute (WPM) and relies on manual hardware polling and time-based state tracking.

### 1. Input Processing & Timing
The input mechanism uses Button 1 (connected to Pin 4) to record the Morse sequence. Instead of using standard interrupts, the code continuously polls the button state and calculates the press duration using `millis()`:
* **Dot (`.`):** Button held for approximately 1 second (1000ms – 1500ms).
* **Dash (`-`):** Button held for approximately 2 seconds (2000ms – 2500ms).
These recognised signals are dynamically concatenated into a temporary String variable (`str`).

### 2. Signal Decryption
Button 2 (connected to Pin 5) acts as the "Submit" or "Decode" trigger. Once pressed, the system takes the concatenated Morse sequence (e.g., `...` for 'S' or `---` for 'O') and passes it to the `morse(String s)` function. This function acts as a dictionary, using an `if-else` block to map the Morse string to its corresponding alphanumeric character.

Message: ... (three dots mean 's' in morse)
![Image](https://github.com/user-attachments/assets/5a434ad5-0f73-45bd-bd45-3563d1765809)

Message: ---(three dashes mean 'O' in morse)
![Image](https://github.com/user-attachments/assets/1bfb45a1-7453-4db3-bd72-eeb2c066ca88)

Message: ... (three dots mean 's' in morse)
![Image](https://github.com/user-attachments/assets/5a434ad5-0f73-45bd-bd45-3563d1765809)

### 3. I2C Display Handling
Upon successful decryption, the mapped character is pushed via I2C to the SSD1306 OLED display. The display cursor is managed so that the user sees their decrypted message unfold sequentially on the screen.

![Image](https://github.com/user-attachments/assets/b660b331-d92e-4368-b90a-49445da0e8c3)

## Edge Cases Handled

* **Signal Overlap Prevention:** A specific `goto skip` logic jump is utilised during the hardware polling phase. If a dash (2-second press) is successfully registered, the code bypasses the subsequent dot (1-second press) evaluation block. This prevents a single long press from being erroneously recorded as both a dash *and* a dot when the button is finally released.
* **Buffer Resetting:** After Button 2 is pressed and a character is successfully decoded, the `str` buffer is immediately cleared (`str=""`). This ensures that leftover dots or dashes do not corrupt the next character's sequence.
* **Wait States:** The main `loop()` includes delays during the button polling phase to act as a rudimentary form of software debounce, preventing noisy mechanical button contacts from registering as rapid, multiple inputs.

You can decrypt any message by each character

![Image](https://github.com/user-attachments/assets/70208818-c54e-4df5-a391-21ae963db11e)

Here is the link to the simulation in the Wokwi simulator: https://wokwi.com/projects/425214595189811201

Happy Learning ;)
