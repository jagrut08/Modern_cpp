################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LC/5.4.1.cpp \
../src/LC/5.4.2.cpp \
../src/LC/5.4.3.cpp \
../src/LC/5.4.4.cpp \
../src/LC/5.4.5.cpp \
../src/LC/5.4.7.cpp \
../src/LC/8.4.cpp \
../src/LC/8.5.1.cpp \
../src/LC/8.6.1.cpp \
../src/LC/9.1.cpp \
../src/LC/9.2.cpp \
../src/LC/9.3.cpp 

OBJS += \
./src/LC/5.4.1.o \
./src/LC/5.4.2.o \
./src/LC/5.4.3.o \
./src/LC/5.4.4.o \
./src/LC/5.4.5.o \
./src/LC/5.4.7.o \
./src/LC/8.4.o \
./src/LC/8.5.1.o \
./src/LC/8.6.1.o \
./src/LC/9.1.o \
./src/LC/9.2.o \
./src/LC/9.3.o 

CPP_DEPS += \
./src/LC/5.4.1.d \
./src/LC/5.4.2.d \
./src/LC/5.4.3.d \
./src/LC/5.4.4.d \
./src/LC/5.4.5.d \
./src/LC/5.4.7.d \
./src/LC/8.4.d \
./src/LC/8.5.1.d \
./src/LC/8.6.1.d \
./src/LC/9.1.d \
./src/LC/9.2.d \
./src/LC/9.3.d 


# Each subdirectory must supply rules for building sources it contributes
src/LC/%.o: ../src/LC/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/jdave12/git/Modern_cpp/src/common" -I/Users/jdave12/boost_1_68_0 -I/Library/Developer/CommandLineTools/usr/lib/clang/10.0.0/include -O0 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


