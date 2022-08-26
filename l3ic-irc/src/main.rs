pub mod compiler;

fn main() {
    let mut compiler = compiler::Compiler::new(
        r#"
    SetRegister RX 02FA
    SetRegister RY 00FF
    SetMousePosition
    Debug 
    "#,
    );

    compiler.run();

    println!("{:?}", compiler.commands);
}
