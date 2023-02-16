################################################################################
# micro T-Kernel 3.00.06  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/libtk/sysdepend/cpu/core/riscv32/int_riscv32.o \
./mtkernel_3/lib/libtk/sysdepend/cpu/core/riscv32/wusec_riscv32.o

C_DEPS += \
./mtkernel_3/lib/libtk/sysdepend/cpu/core/riscv32/int_riscv32.d \
./mtkernel_3/lib/libtk/sysdepend/cpu/core/riscv32/wusec_riscv32.d


mtkernel_3/lib/libtk/sysdepend/cpu/core/riscv32/%.o: ../lib/libtk/sysdepend/cpu/core/riscv32/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
