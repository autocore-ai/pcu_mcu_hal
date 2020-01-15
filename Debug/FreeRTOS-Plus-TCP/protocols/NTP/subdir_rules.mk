################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Plus-TCP/protocols/NTP/%.obj: ../FreeRTOS-Plus-TCP/protocols/NTP/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"E:/CCS8/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --include_path="F:/mcu-v3/MCU-HalDriver-V3" --include_path="E:/CCS8/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-UDP-Console/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-UART-Console/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-TCP/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-TCP/portable/Compiler/CCS" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-TCP/protocols/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-IO/Include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-IO/Device/tms570ls20x31x/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-IO/Device/tms570ls20x31x/SupportedBoards" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-FAT/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-FAT/portable/common" --include_path="F:/mcu-v3/MCU-HalDriver-V3/FreeRTOS-Plus-CLI/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/include" --include_path="F:/mcu-v3/MCU-HalDriver-V3/source" --include_path="F:/mcu-v3/MCU-HalDriver-V3/User_driver" --include_path="F:/mcu-v3/MCU-HalDriver-V3/User_App" --define=_INLINE -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS-Plus-TCP/protocols/NTP/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS-Plus-TCP/protocols/NTP" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


