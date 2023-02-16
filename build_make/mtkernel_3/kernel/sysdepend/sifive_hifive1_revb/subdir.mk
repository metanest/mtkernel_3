################################################################################
# micro T-Kernel 3.00.06  makefile
################################################################################

OBJS += \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/cpu_clock.o \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/hw_setting.o \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/devinit.o \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/power_save.o

C_DEPS += \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/cpu_clock.d \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/hw_setting.d \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/devinit.d \
./mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/power_save.d


mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/%.o: ../kernel/sysdepend/sifive_hifive1_revb/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#mtkernel_3/kernel/sysdepend/sifive_hifive1_revb/%.o: ../kernel/sysdepend/sifive_hifive1_revb/%.S
#	@echo 'Building file: $<'
#	$(AS) $(ASFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '
