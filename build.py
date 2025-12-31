# custom build script that links all the objects together, rust prebuild script will compile the c files for us.
import os
import sys
import shutil
import subprocess

#todo! make assemble arguments like not hardcoded also compil eargs as well.
# todo remove redzone compile.

build_directories = ["src", "src/intrinsics"]
header_directories = []# ["src/limine"]
compiler_tool_chain = "x86_64-elf"
temp_output_directory = "build"
build_mode = "release"
OS_NAME = "own-skeleton"

env = os.environ.copy()

# this just removes the build directory
def clean():
    shutil.rmtree("build")
    os.mkdir("build")
    if os.path.exists("isodir"):
        shutil.rmtree("isodir")
    if os.path.exists(f"{OS_NAME}.bin"):
        os.remove("own-skeleton.bin")

def link_all():
    dir = os.listdir("build")
    dir = [f"build/{x}" for x in dir]
    print(dir)
    command = [f"{compiler_tool_chain}-gcc","-T", "linker.ld", "-o", f"{OS_NAME}.bin" ,"-ffreestanding", "-O2", "-nostdlib", "-g0"] + dir + ["-lgcc"]
    subprocess.run(command, env=env)

#this places all built objects in /build
def compile_all():
    env["PATH"] = f"{os.path.expanduser('~')}/opt/cross/bin:" + env["PATH"]
    env["INPUT_PATHS"] = ",".join(build_directories)
    env["COMPILER_TARGET"] = compiler_tool_chain
    env["BUILD_DIR"] = temp_output_directory
    env["HEADER_PATHS"] = ",".join(header_directories)
    subprocess.run(["cargo", "build", "--release"], env = env)
    shutil.copy(f"target/x86_64-own_skeleton/{build_mode}/libown_skeleton.a", "build/libown_skeleton.a")
    return

def make_image():
    os.mkdir("isodir")
    os.mkdir("isodir/boot")
    shutil.copy(f"{OS_NAME}.bin", f"isodir/boot")
    os.mkdir("isodir/boot/limine")
    subprocess.run(["cp", "-v", "limine.conf", "limine/limine-bios.sys", "limine/limine-bios-cd.bin", "limine/limine-uefi-cd.bin", "isodir/boot/limine/"])

    os.mkdir("isodir/EFI")
    os.mkdir("isodir/EFI/BOOT")
    shutil.copy("limine/BOOTX64.EFI", "isodir/EFI/BOOT/")
    shutil.copy("limine/BOOTIA32.EFI", "isodir/EFI/BOOT/")
    subprocess.run([
        "xorriso","-as","mkisofs","-R","-r","-J","-b","boot/limine/limine-bios-cd.bin",
        "-no-emul-boot","-boot-load-size","4","-boot-info-table","-hfsplus","-apm-block-size",
        "2048","--efi-boot","boot/limine/limine-uefi-cd.bin","-efi-boot-part","--efi-boot-image"
        ,"--protective-msdos-label","isodir","-o",f"{OS_NAME}.iso"
    ])
    subprocess.run([
        "./limine/limine", "bios-install" ,f"{OS_NAME}.iso"
    ])
    return

def build_all():
    clean()
    compile_all()
    link_all()
    make_image()

cliargs = sys.argv


if len(cliargs) < 2:
    build_all()
    exit(1)

if cliargs[1] == "build":
    build_all()
elif cliargs[1] == "clean":
    clean()
elif cliargs[1] == "build_headers": #create rust bindings for header files with given directories
    header_directories = cliargs[2:]
    build_all()
# maybe we need more options in the future

