# Questions

## What's `stdint.h`?

It's a header file that declares sets of integer types having specified widths, and defines corresponding sets of macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It ensures code portability. Types like char, int, etc. can have different sizes in different platforms.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2 respectively.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM in ASCII 0x42 0x4D in hexadecimal.

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the whole file, biSize is the size of the BITMAPINFOHEADER structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative it indicates it's a top-down device-independent bitmap, meaning its top row of pixels will be stored in memory first first and the bottom last.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

In line 24, the file provided may not exist. Both could return NULL if the one executing copy doesn't have the correct permissions or inputs incorrect path.

## Why is the third argument to `fread` always `1` in our code?

Because the buffer isn't an array, so we're always storing only one unit of sizeof(<buffer>).

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It changes our position in a file provided.

## What is `SEEK_CUR`?

Current position.
