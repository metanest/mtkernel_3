################################################################################
# micro T-Kernel 3.00.06  makefile
################################################################################

S_UPPER_DEPS += \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/dispatch.d \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/int_asm.d \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/start.d \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/vector_tbl.d

C_DEPS += \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/cpu_cntl.d \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/exc_hdl.d \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/interrupt.d \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/reset_main.d

OBJS += \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/dispatch.o \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/int_asm.o \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/start.o \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/vector_tbl.o \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/cpu_cntl.o \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/exc_hdl.o \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/interrupt.o \
./mtkernel_3/kernel/sysdepend/cpu/core/riscv32/reset_main.o


mtkernel_3/kernel/sysdepend/cpu/core/riscv32/%.o: ../kernel/sysdepend/cpu/core/riscv32/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mtkernel_3/kernel/sysdepend/cpu/core/riscv32/%.o: ../kernel/sysdepend/cpu/core/riscv32/%.S
	@echo 'Building file: $<'
	$(AS) $(ASFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
