pub mod compiler;

fn main() {
    let mut compiler = compiler::Compiler::new(
        r#"
    Label XD2
    Label Hello
    SetRegister RI FF00
    Jump Hello
    Jump XD2
    "#,
    );

    compiler.run();

    println!("{:?}", compiler.commands);
}
