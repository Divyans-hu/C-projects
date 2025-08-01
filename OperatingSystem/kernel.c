/*
 * kernel.c
 * This is the main C file for my simple OS.
 * It will clear the screen and print a message.
 */

// A pointer to the video memory buffer.
// The screen is 80 columns by 25 rows.
volatile unsigned short* video_memory = (unsigned short*)0xB8000;

// The main function for my kernel.
void kmain() {
    const char* message = "Hello, OS World!";
    unsigned int i = 0;
    unsigned int j = 0;

    // Clear the screen (fill it with black spaces).
    // The screen is 80x25 characters.
    while (j < 80 * 25) {
        // Character is a space ' ' with a black background and light grey foreground.
        video_memory[j] = ' ' | (0x07 << 8);
        j++;
    }

    // Write my message to the screen.
    while (message[i] != '\0') {
        // The character is in the low byte, color is in the high byte.
        // We are using color 0x0A: Green on a Black background.
        video_memory[i] = message[i] | (0x0A << 8);
        i++;
    }

    return;
}
