pub mod compiler;

fn main() {
    let mut compiler = compiler::Compiler::new(
        r#"
    SetRegister RI 0001
    Label Hello
    StackPush FFFF
    SetRegister RA 6969
    StackPushRegister RA
    StackPop RB
    StackPop RC
    Debug
    Jump Hello
    "#,
    );

    compiler.run();

    println!("{:?}", compiler.commands);
}
