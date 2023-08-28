error_string:
db "Failed to read sectors on disk."

read_string:
db "Reading..."

loadedGDT:
db "Loaded GDT into register..."

pm_string:
db "32 bit mode initialized...",0

;VARS
BOOT_DRIVE: db 0
