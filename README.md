<div align="center">

# L3IC

![Logo](/assets/l3ic.png)

L3IC (**L**ow **L**evel **L**anguage for **I**nput **C**ontrolling) allows you to control mouse and keyboard input on Windows.

</div>

## Plans

### Virtual Machine

L3IC-VM will be a bytecode virtual machine, I am planning to keep it simple and efficient.

- VM should mess with the bytecode source code only once. Commands will be executed char-by-char.
- Planning to write in C99. L3IC-VM should directly use `Windows.h` without any Wrappers or Libraries.
- L3IC-VM commands should be easy-to-write and not confuse other people. Because i also think this is useful for Desktop/CLI Apps.
- Using `gcc` for C compiler.
- Uses big-endian for multibyte parameters.
- ~~Has three (3) registers. `A`, `B` and `C`. These register also made for commands input/output.~~
    - Planning to remove registers due to complexity and extra byte for commands.
- Planning to add stack. Stack can hold `128` 16-bit unsigned integer.

### IR Compiler

L3IC-IR is an intermediate representation compiler for L3IC-VM.

- Planning to write in Rust. Since L3IC-IR will convert the given source to bytecode, it doesn't need to use `windows.h`.
- Planning to use pascal-case (`ThisIsPascalCase`).
- Planning to support macros with parameters.

### Decompiler

L3IC-DE is a decompiler for L3IC-VM. Will decompile given bytecode to an intermediate representation.

- Planning to write in Rust.
- Decompiler will not be in focus until L3IC reaches a certain point.

## Pull Requests

At this point, pull requests are not accepted since the project has not evolved yet. You can contribute to the project on GitHub Issues.

## License

L3IC and subprojects are licensed under the MIT license.
