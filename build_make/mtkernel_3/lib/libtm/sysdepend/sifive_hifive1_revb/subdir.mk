################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/libtm/sysdepend/sifive_hifive1_revb/tm_com.o

C_DEPS += \
./mtkernel_3/lib/libtm/sysdepend/sifive_hifive1_revb/tm_com.d


mtkernel_3/lib/libtm/sysdepend/sifive_hifive1_revb/%.o: ../lib/libtm/sysdepend/sifive_hifive1_revb/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
