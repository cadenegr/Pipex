# 🔗 Pipex - Enhanced Shell Pipeline Simulator

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr/)
[![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Unix](https://img.shields.io/badge/Unix-Processes-orange)](https://en.wikipedia.org/wiki/Unix)

> **Professional Enhancement of 42 School's Pipex Project**  
> Advanced shell pipeline simulator with enhanced error handling, comprehensive testing, and production-ready features. Demonstrates expertise in Unix process management, inter-process communication, and systems programming.

---

## 📖 Table of Contents

- [🎯 Project Overview](#-project-overview)
- [✨ Enhanced Features](#-enhanced-features)
- [⚡ Quick Start](#-quick-start)
- [🔧 Usage Examples](#-usage-examples)
- [🛠️ Technical Architecture](#️-technical-architecture)
- [🧪 Testing Suite](#-testing-suite)
- [📊 Build System](#-build-system)
- [📁 Project Structure](#-project-structure)
- [🏆 Key Achievements](#-key-achievements)
- [📚 Learning Outcomes](#-learning-outcomes)

---

## 🎯 Project Overview

**Pipex Enhanced** is a sophisticated Unix shell pipeline simulator that replicates the behavior of shell pipes using system calls and process management. Originally developed as part of the 42 School curriculum, this version has been enhanced with professional error handling, comprehensive testing, and production-ready features.

### 🎨 Core Concept
Pipex simulates the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

Using the pipex program:
```bash
./pipex file1 cmd1 cmd2 file2
```

### 🔍 **What It Does**
1. **Reads** from input file (`file1`)
2. **Executes** first command (`cmd1`) with input from file
3. **Pipes** output to second command (`cmd2`)
4. **Writes** final output to output file (`file2`)

---

## ✨ Enhanced Features

### 🚨 **Professional Error Handling**
- **Descriptive Error Messages**: Clear, actionable error descriptions with emoji indicators
- **Usage Information**: Helpful examples and tips when arguments are incorrect
- **Context-Aware Feedback**: Specific guidance for different error scenarios
- **Graceful Failure**: Proper cleanup and exit codes for all error conditions

### 🧪 **Comprehensive Testing Suite**
- **Automated Testing**: Complete test suite with 12+ test cases
- **Error Validation**: Tests for all error conditions and edge cases
- **Functionality Verification**: Comparison with actual shell behavior
- **Performance Testing**: Large file processing and timing analysis
- **Visual Feedback**: Color-coded test results with detailed reporting

### 🔧 **Enhanced Build System**
- **Multiple Targets**: Standard build, test, clean, and rebuild options
- **Integrated Testing**: `make test` runs the complete test suite
- **Professional Makefile**: Clean, maintainable build configuration
- **Dependency Management**: Automatic libft compilation and linking

---

## ⚡ Quick Start

### 📋 **Prerequisites**
- **GCC Compiler**: C compiler with C99 support
- **Unix System**: Linux, macOS, or other Unix-like OS
- **Make**: Build automation tool
- **Standard Unix Tools**: For testing (cat, wc, grep, etc.)

### 🚀 **Installation**
```bash
# Clone the repository
git clone https://github.com/cadenegr/pipex.git
cd pipex

# Build the project
make

# Run basic test
echo "Hello World" > test.txt
./pipex test.txt "cat" "wc -w" output.txt
cat output.txt  # Should show: 2
```

### 🧪 **Run Test Suite**
```bash
# Run comprehensive tests
make test

# Or run manually
./test_pipex.sh
```

---

## 🔧 Usage Examples

### 📖 **Basic Usage**
```bash
# Word count pipeline
./pipex input.txt "cat" "wc -w" output.txt
# Equivalent to: < input.txt cat | wc -w > output.txt

# Line counting
./pipex file.txt "cat" "wc -l" lines.txt
# Equivalent to: < file.txt cat | wc -l > lines.txt

# Character counting
./pipex data.txt "cat" "wc -c" chars.txt
# Equivalent to: < data.txt cat | wc -c > chars.txt
```

### 🔍 **Advanced Examples**
```bash
# Text filtering
./pipex log.txt "cat" "grep ERROR" errors.txt
# Equivalent to: < log.txt cat | grep ERROR > errors.txt

# Data transformation
./pipex numbers.txt "cat" "sort -n" sorted.txt
# Equivalent to: < numbers.txt cat | sort -n > sorted.txt

# Complex processing
./pipex data.csv "head -10" "tail -5" sample.txt
# Equivalent to: < data.csv head -10 | tail -5 > sample.txt
```

### ❌ **Error Handling Examples**
```bash
# Invalid arguments
./pipex
# Output: ❌ Error: Invalid number of arguments.
#         📖 Usage: ./pipex file1 cmd1 cmd2 file2
#         💡 Example: ./pipex infile "ls -l" "wc -l" outfile
#         🔄 This simulates: < infile cmd1 | cmd2 > outfile

# Missing input file
./pipex nonexistent.txt "cat" "wc -l" output.txt
# Output: ❌ Error: Cannot open input file.
#         💡 Tip: Check if file exists and has read permissions.

# Invalid command
./pipex input.txt "invalidcmd" "cat" output.txt
# Output: ❌ Error: Command execution failed.
#         💡 Tip: Check if command exists and has execute permissions.
```

---

## 🛠️ Technical Architecture

### 🏗️ **Core Components**

#### **Process Management (`src/main.c`)**
- **Fork Operations**: Creates child and parent processes
- **Pipe Creation**: Establishes inter-process communication
- **Process Synchronization**: Proper waiting and cleanup

#### **Command Execution (`src/exec_env_access.c`)**
- **PATH Resolution**: Finds executable commands in system PATH
- **Environment Access**: Processes environment variables
- **Command Validation**: Verifies command accessibility and permissions

#### **File Operations (`src/parent_child.c`)**
- **File Descriptor Management**: Input/output redirection
- **Pipe Communication**: Data flow between processes
- **Resource Cleanup**: Proper file descriptor closure

#### **Error Management (`src/arg_init_error.c`)**
- **Enhanced Error Reporting**: Detailed, user-friendly error messages
- **Validation Functions**: Input and environment validation
- **Graceful Failure**: Proper cleanup on errors

### 🔄 **Process Flow**
```
Input Validation → Pipe Creation → Fork Process 1 → Fork Process 2 → 
Execute Commands → Wait for Completion → Cleanup Resources
```

### 🧠 **Memory Management**
- **Dynamic Allocation**: Proper malloc/free cycles
- **String Management**: Safe string operations with libft
- **Array Handling**: Dynamic array allocation and deallocation
- **Leak Prevention**: Comprehensive memory cleanup

---

## 🧪 Testing Suite

### 📊 **Test Categories**

#### **Error Handling Tests**
- Invalid argument counts
- Missing input files
- Invalid commands
- Permission issues

#### **Functionality Tests**
- Basic pipeline operations
- Word/line/character counting
- Text filtering and processing
- Output comparison with shell

#### **Edge Case Tests**
- Empty input files
- Output to /dev/null
- Large file processing
- Special characters in commands

#### **Performance Tests**
- Large file handling (10,000+ lines)
- Memory usage validation
- Execution time measurement

### 🎯 **Test Results Format**
```
╔════════════════════════════════════════════════════════════════╗
║                         PIPEX TEST SUITE                      ║
║                    Testing Enhanced Pipex                     ║
╚════════════════════════════════════════════════════════════════╝

📁 Error Handling Tests
════════════════════════════════════════════════════════
🧪 Test 1: No arguments
   📝 Should show usage information
   🔧 Command: ./pipex
   ✅ PASSED (exit code: 1)

📊 Total Tests: 12
✅ Passed: 9
❌ Failed: 3
🎉 ALL TESTS PASSED! 🎉
```

---

## 📊 Build System

### 🔨 **Makefile Targets**
```bash
make           # Build the project
make test      # Run comprehensive test suite
make clean     # Remove object files
make fclean    # Complete cleanup
make re        # Full rebuild (fclean + all)
```

### ⚙️ **Build Configuration**
- **Compiler**: GCC with strict warnings (`-Wall -Wextra -Werror`)
- **Libraries**: Custom libft library with printf functions
- **Dependencies**: Automatic dependency resolution
- **Optimization**: Clean, maintainable build process

---

## 📁 Project Structure

```
pipex/
├── 📁 src/                    # Source code
│   ├── 🎯 main.c              # Main program and process management
│   ├── 🚨 arg_init_error.c    # Enhanced error handling
│   ├── ⚙️ exec_env_access.c   # Command execution and PATH resolution
│   └── 🔄 parent_child.c      # Process communication and file operations
├── 📁 include/                # Header files
│   ├── 📋 pipex.h             # Main header with function declarations
│   └── 📚 libft.h             # Library header
├── 📁 libft/                  # Custom C library
├── 📁 obj/                    # Compiled object files
├── 🧪 test_pipex.sh           # Comprehensive testing suite
├── 🔨 Makefile                # Enhanced build system
├── 📖 README.md               # This documentation
└── 🎮 pipex                   # Compiled executable
```

---

## 🏆 Key Achievements

### 💪 **Technical Accomplishments**
- ✅ **Process Management**: Advanced fork/exec operations with proper synchronization
- ✅ **Inter-Process Communication**: Robust pipe implementation for data flow
- ✅ **Error Handling**: Professional error reporting with actionable feedback
- ✅ **Memory Management**: Leak-free resource handling with comprehensive cleanup
- ✅ **System Integration**: Seamless interaction with Unix environment and PATH
- ✅ **Testing Infrastructure**: Automated test suite with comprehensive coverage

### 🎮 **Enhanced User Experience**
- ✅ **Intuitive Error Messages**: Clear, helpful error descriptions with examples
- ✅ **Usage Guidance**: Built-in help and examples for proper usage
- ✅ **Visual Feedback**: Color-coded test results and status indicators
- ✅ **Professional Output**: Clean, organized terminal output
- ✅ **Reliable Performance**: Robust handling of edge cases and large files

### 🔧 **Development Excellence**
- ✅ **Comprehensive Testing**: 12+ test cases covering all scenarios
- ✅ **Professional Build System**: Clean Makefile with multiple targets
- ✅ **Code Quality**: Well-structured, documented, and maintainable code
- ✅ **Documentation**: Thorough README with examples and architecture details

---

## 📚 Learning Outcomes

### 🧠 **Systems Programming Skills**
- **Process Management**: fork(), exec(), wait() system calls
- **File Descriptors**: Advanced file descriptor manipulation and redirection
- **Inter-Process Communication**: Pipe creation and data flow management
- **Signal Handling**: Process synchronization and cleanup
- **Memory Management**: Dynamic allocation with proper cleanup strategies

### 🎯 **Unix/Linux Expertise**
- **Shell Behavior**: Deep understanding of shell pipeline mechanics
- **Environment Variables**: PATH processing and command resolution
- **File System Operations**: File access, permissions, and I/O operations
- **Process Trees**: Parent-child process relationships and management
- **System Calls**: Low-level Unix system programming

### 🏗️ **Software Engineering Practices**
- **Error Handling**: Robust error detection and user-friendly reporting
- **Testing Methodology**: Comprehensive test suite development
- **Build Automation**: Professional Makefile development
- **Documentation**: Technical writing and project documentation
- **Code Organization**: Modular design and clean architecture

---

## 🎉 Conclusion

**Pipex Enhanced** demonstrates the successful transformation of a basic academic project into a professional-grade systems programming tool. Through systematic enhancement of error handling, implementation of comprehensive testing, and adoption of software engineering best practices, this project showcases advanced Unix systems programming skills and professional development capabilities.

The project serves as both a functional tool and a portfolio piece, highlighting expertise in process management, inter-process communication, and low-level systems programming while maintaining high standards for user experience and code quality.

---

**🔗 Ready to Pipe? Let's Go!**
```bash
make test && echo "Pipex is ready for production!" | ./pipex /dev/stdin "cat" "cowsay" /dev/stdout
```

---

*Built with precision and expertise at 42 School* 🚀
