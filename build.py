# custom build script that links all the objects together, rust prebuild script will compile the c files for us.
import os
import subprocesss

build_directories = [""]
compiler_tool_chain = "x86_64-elf-gcc"
assemble_args = ["-f elf64", "-o"]


def link_all():
    return 

def build_all():
    return