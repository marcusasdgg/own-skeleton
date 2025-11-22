# custom build script that links all the objects together, rust prebuild script will compile the c files for us.
import os
import shutil
import subprocess

#todo! make assemble arguments like not hardcoded also compil eargs as well.
# todo remove redzone compile.

build_directories = ["src"]
header_directories = ["src/limine"]
compiler_tool_chain = "x86_64-elf"
temp_output_directory = "build"
build_mode = "debug"
OS_NAME = "own-skeleton"

env = os.environ.copy()

# this just removes the build directory
def clean():
    shutil.rmtree("build")
    os.mkdir("build")
    if os.path.exists("isodir"):
        shutil.rmtree("isodir")
    if os.path.exists("myos.bin"):
        os.remove("myos.bin")
    if os.path.exists("myos.iso"):
        os.remove("myos.iso")

def link_all():
    dir = os.listdir("build")
    dir = [f"build/{x} " for x in dir]
    print(dir)
    command = [f"{compiler_tool_chain}-gcc","-T", "linker.ld", "-o", f"{OS_NAME}.bin" ,"-ffreestanding", "-O2", "-nostdlib"] + dir + ["-lgcc"]
    subprocess.run(command, env=env)

#this places all built objects in /build
def compile_all():
    env["PATH"] = f"{os.path.expanduser('~')}/opt/cross/bin:" + env["PATH"]
    env["INPUT_PATHS"] = ",".join(build_directories)
    env["COMPILER_TARGET"] = compiler_tool_chain
    env["BUILD_DIR"] = temp_output_directory
    env["HEADER_PATHS"] = ",".join(header_directories)
    subprocess.run(["cargo", "build"], env = env)
    shutil.copy(f"target/x86_64-own_skeleton/{build_mode}/libown_skeleton.a", "build/libown_skeleton.a")
    return

def build_all():
    clean()
    compile_all()
    link_all()

build_all()