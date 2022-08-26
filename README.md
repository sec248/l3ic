<div align="center">

# L3IC

![Logo](/assets/l3ic.png)

L3IC (**L**ow **L**evel **L**anguage for **I**nput **C**ontrolling) allows you to control mouse and keyboard input on Linux (X11).

</div>

## Plans
**NOTE**: I'm unstable in general, so all of these can be changed in 1 minute.

### Library

L3IC-LIB contains everything you need including parser and virtual machine.

Library itself is written in C and has a simple to use api.

### Virtual Machine

L3IC-VM is a bytecode virtual machine for L3IC.

- Has jump table, which means you can jump anywhere in your program at execution time.
- Uses big-endian for multibyte parameters.
- Has seven (7) registers. `A`, `B`, `C`, `X`, `Y`, `Z` and `I`.
  - `A`, `B` and `C` is for general usage.
  - `X`, `Y` and `Z` is for command i/o. 
  - `I` is a special register for jump commands and comparison commands.
- Support stacks. Stack can hold `255` 16-bit unsigned integer.

### IR Compiler

L3IC-IRC is an intermediate representation compiler that converts into L3IC bytecode.

- Planning to write in Rust.
- Planning to use pascal-case (`ThisIsPascalCase`).
- Planning to add pre-processor.

### Bytecode Decompiler

L3IC-BDE is a decompiler for L3IC bytecode that converts your program to intermediate representation.

- Planning to write in Rust.
- Decompiler will not be in focus until L3IC reaches a certain point.

### Macro Creator

L3IC-MC is a macro creator for L3IC that allows you to create macros easily.

- Planning to write in Vala.
- Macro creator will not be in focus until L3IC reaches a certain point.

## Pull Requests

At this point, pull requests are not accepted since the project has not evolved yet. You can contribute to the project on GitHub Issues.

## License

L3IC and subprojects are licensed under the MIT license.
