################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Thermo.obj: ../Thermo.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" -vmsp --abi=coffabi --use_hw_mpy=16 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="I:/WNRL/wisard test workspace/SP_ST/core/comm" --include_path="I:/WNRL/wisard test workspace/SP_ST/core" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" -g --define=__MSP430F235__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Thermo.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

irupt.obj: ../irupt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" -vmsp --abi=coffabi --use_hw_mpy=16 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="I:/WNRL/wisard test workspace/SP_ST/core/comm" --include_path="I:/WNRL/wisard test workspace/SP_ST/core" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" -g --define=__MSP430F235__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="irupt.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" -vmsp --abi=coffabi --use_hw_mpy=16 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="I:/WNRL/wisard test workspace/SP_ST/core/comm" --include_path="I:/WNRL/wisard test workspace/SP_ST/core" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" -g --define=__MSP430F235__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


