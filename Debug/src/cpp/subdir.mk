################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cpp/BaseDerived.cpp \
../src/cpp/DeleteFromMap.cpp \
../src/cpp/RVO.cpp 

OBJS += \
./src/cpp/BaseDerived.o \
./src/cpp/DeleteFromMap.o \
./src/cpp/RVO.o 

CPP_DEPS += \
./src/cpp/BaseDerived.d \
./src/cpp/DeleteFromMap.d \
./src/cpp/RVO.d 


# Each subdirectory must supply rules for building sources it contributes
src/cpp/%.o: ../src/cpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/jdave12/git/Modern_cpp/src/common" -I/Users/jdave12/boost_1_68_0 -I/Library/Developer/CommandLineTools/usr/lib/clang/10.0.0/include -O0 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


