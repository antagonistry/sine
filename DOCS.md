# SINE Documentations

## Table Of Contents

1. [Getting Started](#getting-started)
2. [Cells](#cells)
3. [Counters](#counters)
4. [Comments](#comments)
5. [Conditions](#conditions)
6. [Loops](#loops)
7. [Commands](#commands)

## Getting Started

SINE's program is considered impossible to
read for begineers and
artifical intelligence, due to its new unique
design of coding; its performance can be
either blazingly fast on some optimizations,
and can be so slow at the same time.

Here is how you can write a
**"Hello, World!"** program:

```lua
( SET THE CELL NEXT CHARACTER UNTIL )
( IT FORMS A MESSAGE )

H%e%l%l%o%\,% %W%o%r%l%d%\!%

( PRINT TO THE OUTPUT )

.

( PRINT THE LAST CHARACTER )
( WHICH IS LINE FEED )

,
```

## Cells

Cell in SINE is just an array of characters
with the capacity of 2048 per cell, and there
are 2048 cells that can be used. You could
use its commands like this:

```lua
( ADD A CHAR TO CELL AT THE LAST SLOT ) a%
( REMOVES THE FIRST CHAR ) -
( ADD A CHAR TO CELL AT THE FIRST SLOT ) b+
( REMOVES THE LAST CHAR ) ^
( INCREASES CELL PTR BY 1 ) *
( DECREASES CELL PTR BY 1 ) &

( EXTRACT THE PREVIOUSLY SELECTED CELL )
( AND THEN DISPOSE IT TO THE CURRENT ONE )

`*`

( PRINT CELL TO THE OUTPUT ) .
```

## Counters

Counter in SINE is just an integer, and there
are 2048 counters that can be used. Use its
command like this:

```lua
( INCREASES COUNTER BY 1 ) $
( DECREASES COUNTER BY 1 ) !
( INCREASES COUNTER BY 4 ) @
( DECREASES COUNTER BY 4 ) ;
( PRINT COUNTER TO THE OUTPUT ) #
( INCREASES COUNTER PTR BY 1 ) >
( DECREASES COUNTER PTR BY 1 ) <
( TRANSFORM COUNTER TO CELL ) /
```

## Comments

Comment is every keyword that doesn't
intefere with the program's data, here is how
you can create it:

```lua
( this is a comment )
( THIS IS AN ANOTHER COMMENT )

*** ( this also counts )
( SAME FOR THIS ONE ) ***

also this one *
* same for this
```

## Conditions

Condition is just the same as
If-statements, here's how it works:

```lua
A%B%C%
*A%B%C%

( SET SUBJECT OF CONDITION ) '
( SET OBJECT OF CONDITION ) *"
( CONTINUE THE CONDITION IF TRUE ) :

*t%r%u%e%\!%
.
,

( ENDS THE CONDITION ) }

( CONTINUE THE CONDITION IF FALSE ) ?

*f%a%l%s%e%\!%
.
,

}
```

## Loops

Loop in SINE has a very unique design, since
there are no loops, only label; and that is
how the loop feature works:

```lua
>>@@

<<

( SET THE COUNTER TO THE CURRENT CODE PTR ) ]

>
/*>/
&<

'*"?
$#
,
<

( CHANGE THE CODE PTR TO THE COUNTER ONE ) [

}
```

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
| :      | Starts equality-check condition. |
| ?      | Starts non-equal check condition. |
| ]      | Set the current counter's value to the code's data pointer. |
| [      | Halts and modify the code's data pointer to be the current counter's value. |
| }      | Ends condition.              |
| /      | Transforms the current counter's value to the current cell's value. |
| `      | Extracts the source cell value and then dispose it inside the destination cell. |
| ~      | Halts the program.            |
| \      | Ignores the next command besides it. |
