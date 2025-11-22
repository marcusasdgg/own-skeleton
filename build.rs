
use std::fs;
use std::env;
use std::process::Command;


// this function builds yuh it assumes that the environment variable COMPILER_TARGET is set to what we want.
// also assumes that env variable INPUT_PATHS are set to comma separated list of paths to compile.
// also assumes an assembler of nasm in path exists and uses the args in ASSEMBLER_TARGET
// also assumes that there is an env variable set for the BUILD_DIR.

// also yeah this prebuild will convert our bindings for us from header files, the env variable HEADER_PATHS will have a comma separated list for that.
fn main(){
    // read through the src directory for any c files I don't think we will need any but just in case 

    let paths = env::var("INPUT_PATHS").unwrap();
    let tool_chain = env::var("COMPILER_TARGET").unwrap();
    let build_directory = env::var("BUILD_DIR").unwrap();



    for i in paths.split(",") {
        let directory = fs::read_dir(i).unwrap();

        for dir_ok in directory {
            if let Ok(dir) = dir_ok {
                let name = dir.file_name().to_str().unwrap().to_string();
                
                if name.ends_with(".c") {   
                    compile_file(i, &name[0..name.len()-2], &tool_chain, &build_directory);
                } else if name.ends_with(".asm") {
                    assemble_file(i, &name[0..name.len()-4], &build_directory);
                } else {
                    println!("Unexpected file: \"{name}\"");
                }

            }
        }
    }

    let header_paths= env::var("HEADER_PATHS").unwrap();
    //directory loop
    for i in header_paths.split(","){
        println!("parsing directory: {i}");
        let directory = fs::read_dir(i).unwrap();

        for dir_ok in directory {
            if let Ok(dir) = dir_ok {
                let name = dir.file_name().to_str().unwrap().to_string();
                if name.ends_with(".h") {
                    header_binding(i, &name[0..name.len()-2]);
                }
            }
        }
    }
    

    
    
}

// for c files
fn compile_file(directory_path: &str, file_name: &str, compiler_target: &str, build_dir: &str) {
    // compiles with given information
    let full_path = format!("{directory_path}/{file_name}.c");
    let build_path = format!("{build_dir}/{file_name}.o");
    println!("full_path: {full_path}\n build_path: {build_path}");
    let mut binding = Command::new(format!("{compiler_target}-gcc"));
    let compiler_comm = binding
        .arg("-c")
        .arg(full_path)
        .arg("-o")
        .arg(build_path)
        .arg("-std=gnu99")
        .arg("-ffreestanding")
        .arg("-O2")
        .arg("-Wall")
        .arg("-Wextra");

    compiler_comm.status().expect(&format!("failed to compile {file_name}"));

    println!();
}

fn assemble_file(directory_path: &str, file_name: &str, build_dir: &str){
    let full_path = format!("{directory_path}/{file_name}.asm");
    let build_path = format!("{build_dir}/{file_name}.o");

    let mut nasm_comm = Command::new("nasm");

    let nasm_comm = nasm_comm
        .arg("-felf32")
        .arg(full_path)
        .arg("-o")
        .arg(build_path);

    nasm_comm.status().expect(&format!("failed to generate bindings for {file_name}"));

    println!();
}

fn header_binding(directory_path: &str, file_name: &str) {
    let bindings = bindgen::Builder::default()
        .header(format!("{directory_path}/{file_name}.h"))
        .use_core()
        .layout_tests(false)
        .generate()
        .expect(&format!("failed to gen bindings for file: {file_name}.h"));

    bindings.write_to_file(format!("{directory_path}/{file_name}_header.rs"))
        .expect(&format!("failed to generate bindings for {file_name}"));

    if fs::exists(format!("{directory_path}/mod.rs")).is_ok_and(|x| x == false) {
        fs::write(format!("{directory_path}/mod.rs"), format!("pub mod {file_name}_header;\n")).expect("failed to create mod.rs for ");
    }
    
}


