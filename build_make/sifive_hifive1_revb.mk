################################################################################
# micro T-Kernel 3.00.06  makefile
################################################################################

GCC := riscv32-unknown-elf-gcc
AS := riscv32-unknown-elf-gcc
LINK := riscv32-unknown-elf-gcc

CFLAGS := -mabi=ilp32 -mcpu=sifive-e31 -ffreestanding -fno-hosted \
    -std=gnu11 \
    -O0 -g3 \
    -MMD -MP

ASFLAGS := -mabi=ilp32 -mcpu=sifive-e31 -ffreestanding \
    -x assembler-with-cpp \
    -O0 -g3 \
    -MMD -MP

LFLAGS := -mabi=ilp32 -mcpu=sifive-e31 -ffreestanding \
    -nostartfiles -nostdlib \
    -O0 -g3

LNKFILE := "../etc/linker/sifive_hifive1_revb/tkernel_map.ld"

include mtkernel_3/lib/libtm/sysdepend/sifive_hifive1_revb/subdir.mk
include mtkernel_3/lib/libtm/sysdepend/no_device/subdir.mk
include mtkernel_3/lib/libtk/sysdepend/cpu/fe310g002/subdir.mk
include mtkernel_3/lib/libtk/sysdepend/cpu/core/riscv32/subdir.mk
include mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/subdir.mk
include mtkernel_3/kernel/sysdepend/cpu/fe310g002/subdir.mk
include mtkernel_3/kernel/sysdepend/cpu/core/riscv32/subdir.mk
