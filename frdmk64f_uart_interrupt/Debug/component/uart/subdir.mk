################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_uart.c 

OBJS += \
./component/uart/fsl_adapter_uart.o 

C_DEPS += \
./component/uart/fsl_adapter_uart.d 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\board" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\source" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\utilities" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\drivers" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\device" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\component\uart" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\component\lists" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\CMSIS" -I"E:\NXP_Workspace\frdmk64f_uart_interrupt\frdmk64f\driver_examples\uart\interrupt" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


