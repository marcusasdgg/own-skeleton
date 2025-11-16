use std::fs;
use std::env;
use std::process::Command;

// this function builds yuh it assumes that the environment variable COMPILER_TARGET is set to what we want.
// also assumes that env variable INPUT_PATHS are set to comma separated list of paths to compile.
// also assumes an assembler of nasm exists and uses the args in ASSEMBLER_TARGET
fn main(){
    // read through the src directory for any c files I don't think we will need any but just in case 

    let paths = env::var("INPUT_PATHS").unwrap();
    let tool_chain = env::var("COMPILER_TARGET").unwrap();
    let assemble_targs = env::var("ASSEMBLER_TARGET").unwrap();



    for i in paths.split(",") {
        let directory = fs::read_dir(i).unwrap();

        for dir_ok in directory {
            if let Ok(dir) = dir_ok {
                let name = dir.file_name().to_str().unwrap().to_string();
                compile_file(&name, &name, &tool_chain);
                if name.ends_with(".c") {
                    
                } else if name.ends_with(".a") {

                }
            }
        }
    }

    
    
}


fn compile_file(directory_path: &str, file_name: &str, compiler_target: &str) {
    // compiles with given information

    let compiler_comm = Command::new(compiler_target);
    let nasm_comm = Command::new(compiler_target);
}

fn assemble_file(directory_path: &str, file_name: &str, assemble_args: &str){
    
}