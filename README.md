<div align="center">

# L3IC

![Logo](/assets/l3ic.png)

L3IC (**L**ow **L**evel **L**anguage for **I**nput **C**ontrolling) allows you to control mouse and keyboard input on Linux (X11).

</div>

## Plans
**NOTE**: I'm unstable in general, so all of these can be changed in 1 minute.

### Virtual Machine

L3IC-VM will be a bytecode virtual machine, I am planning to keep it simple and efficient.

- ~~VM should mess with the bytecode source code only once. Commands will be executed char-by-char.~~
  - VM will process bytecode two times, this is because i am thinking to add jump label support.
- Planning to write in C99. L3IC-VM should directly use header libs without any Wrappers or Libraries.
  -  ~~Planning to rewrite in C# (yes, CSharp). The reason behind this is C# works well with windows api and has high-level features that i want.~~
- L3IC-VM commands should be easy-to-write and not confuse other people..
- Using `gcc` for C compiler.
- Uses big-endian for multibyte parameters.
- Has seven (7) registers. `A`, `B`, `C`, `X`, `Y`, `Z` and `I`.
  - `A`, `B` and `C` is for general usage.
  - `X`, `Y` and `Z` is for command i/o. 
  - `I` is a special register for jump commands and comparison commands.
  - ~~Planning to remove registers due to complexity and extra byte for commands.~~
- Planning to add stack. Stack can hold `255` 16-bit unsigned integer.

### IR Compiler

L3IC-IR is an intermediate representation compiler for L3IC-VM.

- Planning to write in Rust. Since L3IC-IR will convert the given source to bytecode, it doesn't need to use any m/k input related functions.
- Planning to use pascal-case (`ThisIsPascalCase`).
- Planning to add pre-processor.

### Decompiler

L3IC-DE is a decompiler for L3IC-VM. Will decompile given bytecode to an intermediate representation.

- Planning to write in Rust.
- Decompiler will not be in focus until L3IC reaches a certain point.

### Macro Creator

L3IC-MC is a macro creator for L3IC-VM that allows you to create macros easily.

- Macro creator will not be in focus until L3IC reaches a certain point.
- Planning to write in Vala.

## Pull Requests

At this point, pull requests are not accepted since the project has not evolved yet. You can contribute to the project on GitHub Issues.

## License

L3IC and subprojects are licensed under the MIT license.
