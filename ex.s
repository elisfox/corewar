.name "zork"
.comment "prog"

sti r1, %15, %0
and r1, %0, r1
live %1
zjmp %-5
