################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Plus-IO/Device/tms570ls20x31x/source/%.obj: ../FreeRTOS-Plus-IO/Device/tms570ls20x31x/source/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"E:/CCS8/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2" --include_path="E:/CCS8/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-UDP-Console/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-UART-Console/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-TCP/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-TCP/portable/Compiler/CCS" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-TCP/protocols/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-IO/Include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-IO/Device/tms570ls20x31x/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-IO/Device/tms570ls20x31x/SupportedBoards" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-FAT/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-FAT/portable/common" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/FreeRTOS-Plus-CLI/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/include" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/source" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/User_driver" --include_path="E:/TMS570/570_exmaple/MCU-HalDriver-V2/User_App" --define=_INLINE -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS-Plus-IO/Device/tms570ls20x31x/source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS-Plus-IO/Device/tms570ls20x31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


