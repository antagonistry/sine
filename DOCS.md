# SINE Documentations

## Table Of Contents

1. [Getting Started](#getting-started)
2. [Cells](#cells)
3. [Counters](#counters)
3. [Commands](#commands)

## Getting Started

SINE's program is considered impossible to
read for begineers and artifical intelligence
, due to its new design of coding; its
performance can be either blazingly fast on
some optimizations, and can be super slow at
the same time.

Here is how you can write a
**"Hello, World!"** program:

```lua
H%e%l%l%o%\,% %W%o%r%l%d%\!%
.
,
```

## Cells

Cell in SINE is just an array of characters
with the capacity of 2048 per cell, and there
are 2048 cells that can be used.

## Counters

Counter in SINE is just an integer, and there
are 2048 counters that can be used.

## Commands

There are many commands in SINE, here is a
list that contains all of them:

| Symbol | Description                  |
| ------ | ---------------------------- |
| *      | Increases cell pointer by 1. |
| &      | Decreases cell pointer by 1. |
| >      | Increases counter ptr. by 1. |
| <      | Decreases counter ptr. by 1. |
| $      | Increases counter from its pointer by 1. |
| @      | Increases counter from its pointer by 4. |
| !      | Decreases counter from its pointer by 1. |
| ;      | Decreases counter from its pointer by 4. |
| %      | Append the last cell's character to the previously defined character in code. |
| ^      | Removes the last cell's character. |
| -      | Removes the first cell's character. |
| +      | Append the first cell's character to the previously defined character in code. |
| #      | Output the counter's value.  |
| .      | Output the cell's value.     |
| ,      | Output the previously defined character in code. |
| '      | Set the subject of condition to be the current cell's value. |
| "      | Set the object of condition to be the current cell's value. |
| :      | Start a equality-check condition. |
| ?      | Start a non-equal check condition. |
| }      | Ends a condition.  |
| /      | Transforms the current counter's value to the current cell's value. |
| ~      | Halts the program.            |
| \      | Ignores the next command besides it. |
