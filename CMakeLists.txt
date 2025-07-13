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
        Commands/BuiltInCommands/Time.h
        Commands/BuiltInCommands/Date.cpp
        Commands/BuiltInCommands/Date.h
        Commands/BuiltInCommands/Touch.cpp
        Commands/BuiltInCommands/Touch.h
        Commands/BuiltInCommands/WC.cpp
        Commands/BuiltInCommands/WC.h
        Commands/BuiltInCommands/Prompt.cpp
        Commands/BuiltInCommands/Prompt.h
        Commands/BuiltInCommands/Truncate.cpp
        Commands/BuiltInCommands/Truncate.h
        Commands/BuiltInCommands/RM.cpp
        Commands/BuiltInCommands/RM.h
        Commands/BuiltInCommands/TR.cpp
        Commands/BuiltInCommands/TR.h)
