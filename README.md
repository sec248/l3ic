<div align="center">

# L3IC

![Logo](/assets/l3ic.png)

L3IC (**L**ow **L**evel **L**anguage for **I**nput **C**ontrolling) allows you to control mouse and keyboard input on Windows.

</div>

## Plans
**NOTE**: I'm unstable in general, so all of these can be changed in 1 minute.

### Virtual Machine

L3IC-VM will be a bytecode virtual machine, I am planning to keep it simple and efficient.

- ~~VM should mess with the bytecode source code only once. Commands will be executed char-by-char.~~
  - VM will process bytecode two times, this is because i am thinking to add jump label support.
- Planning to write in C99. L3IC-VM should directly use `windows.h` without any Wrappers or Libraries.
  -  ~~Planning to rewrite in C# (yes, CSharp). The reason behind this is C# works well with windows api and has high-level features that i want. ~~
- L3IC-VM commands should be easy-to-write and not confuse other people..
- Using `gcc` for C compiler.
- Uses big-endian for multibyte parameters.
- Has five (5) registers. `A`, `B`, `C`, `D` and `E`. These register also made for commands input/output.
  - ~~Planning to remove registers due to complexity and extra byte for commands.~~
- Planning to add stack. Stack can hold `255` 16-bit unsigned integer.

### IR Compiler

L3IC-IR is an intermediate representation compiler for L3IC-VM.

- Planning to write in Rust. Since L3IC-IR will convert the given source to bytecode, it doesn't need to use any windows api related functions.
- Planning to use pascal-case (`ThisIsPascalCase`).
- Planning to add pre-processor.

### Decompiler

L3IC-DE is a decompiler for L3IC-VM. Will decompile given bytecode to an intermediate representation.

- Planning to write in Rust.
- Decompiler will not be in focus until L3IC reaches a certain point.

### Macro Creator

L3IC-MC is a macro creator for L3IC-VM that allows you to create macros easily.

- Planning to write in C# with Winforms.
- Macro creator will not be in focus until L3IC reaches a certain point.

## Arc (Archive)

Arc (`./arc`) folder contains old source codes, like a L3IC-VM written in C99. I wanted to archive them as i don't want to delete things i messed with. Also i think they may be useful for beginner programmers.

**DO NOT** send pull request that changes anything inside arc folder. **ONLY I** will manage this folder.

## Pull Requests

At this point, pull requests are not accepted since the project has not evolved yet. You can contribute to the project on GitHub Issues.

## License

L3IC and subprojects are licensed under the MIT license.
