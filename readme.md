todo:
we need to change from trying to implement multiboot2 as our boot protocol to just limine this shit is a lot simpler.


current build system:
This runs the rust prebuilds script which does a lot for us like assembling nasm files, compiling c files and 
also creating bindings for c header files such that rust can view them. Furthermore we create a mod.rs for the directory if it doesn't have one 
and links the rust header file to it.

What we plan to do:
When we wrap our heads on the limine protocol we can:
fuck it we ball convert the entire limine header file into rust code and have our rust entry point handle that.


When we eventually go into userspace and syscalls:
RIPOFF REDOX's syscall and driver system.
What that means is lets have a schema setup for the bare read and write syscalls
when we call a syscall from userspace call it directs to the kernel which reads which schema it belongs to file/ tcp, rdp etc. and redirects it to 
