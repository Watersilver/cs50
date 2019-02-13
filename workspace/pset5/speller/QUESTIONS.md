# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

an invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

It stores resource usage measures for 'who'(a variable to describe whose recourse usage we're measuring) in the structure struct rusage.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because it's faster?

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Iterate over every character of the text until we reach end of file. While at it add any alphabetical letters and apostrophes to string word. Make sure it doesn't get too big.
If we encounter a number, skip the rest of the characters that are numbers and letters until reaching something that is neither and restart the process. If we encounter something
that is not a letter or a number, without having encountered numbers before, consider word written and start spellchecking. When done, start process again for the next word.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

To avoid accidentaly reading more characters than LENGTH. Also to leave numbers unchecked and skip more than just whitespace characters.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To communicate that the functions will not alter them, just read them.
