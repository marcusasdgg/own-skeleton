import sys
import os
import subprocess
import shutil

argv = sys.argv

compile_directories = [os.getcwd(),"tty","string", "serial", "stdio", "interrupts", "pic", "queue","keyboard"]
assemble_directories = [os.getcwd(), "io", "interrupts","basic_intrinsics"]

env = os.environ.copy()
env["PATH"] = f"{os.path.expanduser('~')}/opt/cross/bin:" + env["PATH"]

if len(argv) !=  2:
    print("not supported")
    exit(0)

command = str(argv[1])

def COMPILE_ALL():
    for directory in compile_directories:
        dir = os.listdir(directory)
        for file in dir:
            if file.endswith(".c"):
                filename = file.removesuffix(".c")
                subprocess.run(["i686-elf-gcc", "-c", f"{directory}/{filename}.c", "-o", f"build/{filename}.o", "-std=gnu99", "-ffreestanding", "-O2", "-Wall", "-Wextra"],
                               env = env)

def ASSEMBLE_ALL():
    for directory in assemble_directories:
        dir = os.listdir(directory)
        for file in dir:
            if file.endswith(".asm"):
                filename = file.removesuffix(".asm")
                subprocess.run(["nasm", "-felf32", f"{directory}/{file}", "-o", f"build/{filename}.o"],
                               env = env)
                
def LINK_ALL():
    dir = os.listdir("build")
    dir = [f"build/{x}" for x in dir]
    command = ["i686-elf-gcc","-T", "linker.ld", "-o", "myos.bin" ,"-ffreestanding", "-O2", "-nostdlib"] + dir + ["-lgcc"]
    subprocess.run(command, env=env)

def CREATE_IMAGE():
    subprocess.run(["mkdir", "-p" ,"isodir/boot/grub"], env=env)
    subprocess.run(["cp","myos.bin","isodir/boot/myos.kernel"])
    subprocess.run(["cp","grub.cfg","isodir/boot/grub/grub.cfg"])
    subprocess.run(["grub-mkrescue", "-o" ,"myos.iso", "isodir"])

def CLEAN():
    #try:
        shutil.rmtree("build")
        os.mkdir("build")
        if os.path.exists("isodir"):
            shutil.rmtree("isodir")
        if os.path.exists("myos.bin"):
            os.remove("myos.bin")
        if os.path.exists("myos.iso"):
            os.remove("myos.iso")
    # except:
    #     print("something went wrong")


match command:
    case "clean":
        CLEAN()
    case "build":
        CLEAN()
        COMPILE_ALL()
        ASSEMBLE_ALL()
        LINK_ALL()
    case "image":
        CLEAN()
        COMPILE_ALL()
        ASSEMBLE_ALL()
        LINK_ALL()
        CREATE_IMAGE()
