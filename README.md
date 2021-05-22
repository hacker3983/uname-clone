# uname-clone
Simple Uname clone made in c which works on windows has win_utsname library which can be useful to get system information
# Usage
```
Usage: ./a.out [OPTION]...
Print certain system information.

  -a, --all                     print all information
  -l, --list                    Does the same as -a
  -s, --kernel-name             print the kernel name
  -n, --nodename                print the network node hostname
  -r, --kernel-release          print the kernel release
  -v, --kernel-version          print the kernel version
  -m, --machine                 print the machine hardware name
  -p, --processor               print the processor type (non-portable)
  -i, --hardware-platform       print the hardware platform (non-portable)
  -o, --operating-system        print the operating system
      --help     display this help and exit
      --version  output version information and exit

Note:
Not a official command.
Not made to harm anyone
Made by catsanddogs as a project.
```
# Compiling
* requirements:
* posix regex
# getting posix regex
If you check the `bin`, `lib`, and `include` folder.
You will find the files required for the library
What to do?
Just copy the files in each directory to the compilers path
you can also get it from this link http://gnuwin32.sourceforge.net/packages/regex.htm
# win_utsname
Link to win_utsname library here: https://github.com/hacker3983/Win-Utsname
