use std::{env, fs, io};

pub mod compiler;

fn main() -> Result<(), io::Error> {
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("you must add input and output path to command line.");
        return Ok(());
    }

    let file_input = &args[1];
    let file_output = &args[2];

    let file_content = fs::read_to_string(file_input)?;
    let mut compiler = compiler::Compiler::new(file_content);
    compiler.run();

    if compiler.compiler_status.get() {
        fs::write(file_output, &compiler.commands)?;
        println!(
            "wrote {} bytes to: {}",
            compiler.commands.len(),
            file_output
        );
    }

    Ok(())
}
