# Photo to Ascii

Photo to Ascii is a C++ utility that converts a photo into ASCII art. It loads an image, converts each pixel to grayscale using standard luminance weighting, maps brightness values to a dense ASCII palette, and scales the result so the final text output keeps a readable shape.

## Features

- Converts RGB images to grayscale with the formula `0.299R + 0.587G + 0.114B`
- Maps brightness values to expressive ASCII characters
- Scales output to a chosen width while preserving aspect ratio
- Averages pixel blocks for smoother, more readable text art
- Saves the final result to a text file

## How it works

1. Load the image using `stb_image.h`
2. Convert pixels to a grayscale brightness value
3. Use the brightness value to select a character from a custom ASCII palette
4. Generate a scaled ASCII representation of the image
5. Optionally save the ASCII art to a file

## Usage

Build the project with a C++ compiler and include `stb_image.h`.

Run the program and specify the output width when prompted. The generated ASCII art can be saved as a `.txt` file.

## Preview

> Example:
>
> `![Preview](preview.png)`

## Notes

This repository is ideal for showcasing C++ image processing, text art generation, and custom ASCII rendering logic. Add a preview file to make the GitHub page more visual and easier to understand at a glance.
