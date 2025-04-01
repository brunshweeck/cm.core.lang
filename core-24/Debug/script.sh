#  To enable execution of this file add
#  add-auto-load-safe-path `pwd`/gdbinit
#  to your configuration file "~/.config/gdb/gdbinit".


mkdirs ~/.config/gdb/gdbinit 2> /dev/null 1>&2

# shellcheck disable=SC2046
echo add-auto-load-safe-path `pwd`/gdbinit >> ~/.config/gdb/gdbinit
