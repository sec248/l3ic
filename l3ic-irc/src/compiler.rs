use core::panic;
use std::{collections::HashMap, mem, num::ParseIntError};

#[derive(Debug)]
pub enum Command {
    None,
    Label,
    Jump,
    SetRegister,
}

#[derive(Default, Debug)]
pub struct Compiler {
    source: String,
    current_command: Command,
    arg_count: usize,
    jump_table_id_calculated: u16,
    collected_arguments: Vec<String>,
    pub commands: Vec<u8>,
    pub jump_table: HashMap<String, u16>,
}

impl Default for Command {
    fn default() -> Self {
        Command::None
    }
}

impl Compiler {
    pub fn new<T>(source: T) -> Self
    where
        T: ToString,
    {
        Self {
            source: source.to_string(),
            ..Default::default()
        }
    }

    pub fn run(&mut self) {
        let splitted: Vec<String> = self
            .source
            .split_ascii_whitespace()
            .map(|t| t.to_string())
            .collect();

        for keyword in splitted {
            if let Command::None = self.current_command {
                self.command_collector(keyword);
            } else {
                self.arg_collector(keyword);
            }
        }
    }

    fn command_collector(&mut self, keyword: String) {
        (self.arg_count, self.current_command) = match keyword.as_str() {
            "Jump" => (1, Command::Jump),
            "Label" => (1, Command::Label),
            "SetRegister" => (2, Command::SetRegister),
            _ => (0, Command::None),
        };
    }

    fn arg_collector(&mut self, keyword: String) {
        self.collected_arguments.push(keyword);

        if self.collected_arguments.len() == self.arg_count {
            self.transpile_command();
            self.collected_arguments.clear();
            self.current_command = Command::None;
        }
    }

    fn transpile_command(&mut self) {
        match self.current_command {
            Command::Jump => {
                let label_name = &self.collected_arguments[0];
                
                match self.jump_table.get(label_name) {
                    Some(table_id) => {
                        self.commands.push(10);
                        self.commands.push((table_id >> 8) as u8);
                        self.commands.push((table_id & 0xFF) as u8);
                    }
                    None => panic!("unknown jump id."),
                }
            }
            Command::Label => {
                let label_name = mem::take(&mut self.collected_arguments[0]);
                self.jump_table
                    .insert(label_name, self.jump_table_id_calculated);

                self.commands.push(9);
                self.commands
                    .push((self.jump_table_id_calculated >> 8) as u8);
                self.commands
                    .push((self.jump_table_id_calculated & 0xFF) as u8);

                self.jump_table_id_calculated += 1;
            }
            Command::SetRegister => {
                let register = self.register_as_byte(&self.collected_arguments[0]);
                let to_bytes = self.calculate_int(&self.collected_arguments[1]);

                self.commands.push(1);
                self.commands.push(register);
                self.commands.push(to_bytes.0);
                self.commands.push(to_bytes.1);
            }
            _ => {}
        }
    }

    fn register_as_byte(&self, reg_str: &str) -> u8 {
        match reg_str {
            "RA" => 0,
            "RB" => 1,
            "RC" => 2,
            "RX" => 3,
            "RY" => 4,
            "RZ" => 5,
            "RI" => 6,
            _ => panic!("unknown register id."),
        }
    }

    fn calculate_int(&self, hex_v: &str) -> (u8, u8) {
        if hex_v.len() != 4 {
            panic!("numbers must be 2 byte.");
        }

        let res: Result<Vec<u8>, ParseIntError> = (0..hex_v.len())
            .step_by(2)
            .map(|i| u8::from_str_radix(&hex_v[i..i + 2], 16))
            .collect();

        match res {
            Ok(bytes) => {
                (bytes[0], bytes[1])
            }
            Err(_) => panic!("unknown hex value."),
        }
    }
}
