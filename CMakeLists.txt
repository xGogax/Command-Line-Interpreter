cmake_minimum_required(VERSION 3.31)
project(CommandLineInterpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(CommandLineInterpreter main.cpp
        Interpreter/Interpreter.cpp
        Interpreter/Interpreter.h
        Commands/Command.cpp
        Commands/Command.h
        Interpreter/Parser.cpp
        Interpreter/Parser.h
        Commands/BuiltInCommands/Echo.cpp
        Commands/BuiltInCommands/Echo.h
        Commands/BuiltInCommands/Time.cpp
        Commands/BuiltInCommands/Time.h)
