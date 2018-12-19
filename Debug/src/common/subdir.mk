################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/misc.cpp \
../src/common/print.cpp 

OBJS += \
./src/common/misc.o \
./src/common/print.o 

CPP_DEPS += \
./src/common/misc.d \
./src/common/print.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/%.o: ../src/common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/jdave12/git/Modern_cpp/src/common" -I/Users/jdave12/boost_1_68_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


