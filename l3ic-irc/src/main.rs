pub mod compiler;

fn main() {
    let mut compiler = compiler::Compiler::new(
        r#"
    SetRegister RX 0005
    Sleep
    GetMousePosition
    Debug 
    "#,
    );

    compiler.run();

    println!("{:?}", compiler.commands);
}
