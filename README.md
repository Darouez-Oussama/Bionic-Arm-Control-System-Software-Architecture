# Bionic Arm Control System

## Overview
This project implements a sophisticated control system for a bionic arm with two main applications:
1. **Full Arm Control**: Complete bionic arm operation and control
2. **EMG Dataset Generation**: Application for collecting and generating EMG (Electromyography) datasets

## Software Architecture

### System Architecture
The system follows a modular, layered architecture designed with scalability, maintainability, reusability, and portability in mind. The architecture is structured as follows:

```
src/
├── Apps/                 # Application layer
│   ├── App.cpp          # Base application class
│   ├── FullArm.cpp      # Full arm control application
│   └── DatasetGeneration.cpp  # EMG dataset generation application
├── Modules/             # Core functionality modules
├── Factories/           # Factory pattern implementations
├── Interfaces/          # Abstract interfaces
├── esp32/              # ESP32 specific implementations
└── stm32/              # STM32 specific implementations
```

### Design Patterns Used

#### 1. Singleton Pattern
- **Implementation**: Used in the base `BionicArmApp` class
- **Purpose**: Ensures only one instance of the application runs at a time
- **Benefits**:
  - Centralized application state management
  - Controlled access to shared resources
  - Memory efficiency

#### 2. Factory Pattern
- **Implementation**: Used for creating hardware-specific components
- **Purpose**: Abstracts the creation of platform-specific implementations
- **Benefits**:
  - Encapsulates object creation logic
  - Enables easy platform switching
  - Supports future hardware additions

### SOLID Principles Implementation

#### 1. Single Responsibility Principle (SRP)
- Each class has one specific responsibility
- Applications are separated into distinct modules
- Clear separation between data collection and arm control functionality

#### 2. Open/Closed Principle (OCP)
- New functionality can be added without modifying existing code
- Platform-specific implementations can be added through interfaces
- Extensible module system for new features

#### 3. Liskov Substitution Principle (LSP)
- Hardware abstractions are properly substitutable
- Platform-specific implementations follow common interfaces
- Consistent behavior across different implementations

#### 4. Interface Segregation Principle (ISP)
- Interfaces are specific to client needs
- Modular design prevents interface pollution
- Clear separation of concerns in the API

#### 5. Dependency Inversion Principle (DIP)
- High-level modules depend on abstractions
- Hardware implementations depend on interfaces
- Loose coupling between components

## Architecture Benefits

### 1. Scalability
- Modular design allows easy addition of new features
- Factory pattern enables support for new hardware platforms
- Independent scaling of data collection and control systems

### 2. Maintainability
- Clear separation of concerns
- Well-defined interfaces
- Organized code structure
- Easy to locate and fix issues

### 3. Reusability
- Common components are abstracted and reusable
- Platform-independent code
- Modular design allows component reuse in other projects

### 4. Portability
- Hardware abstraction layer
- Platform-specific code is isolated
- Easy to port to new microcontrollers

## Current Implementation Status
- Architecture and design patterns implemented
- EMG readings and dataset generation functionality tested
- Framework ready for full arm control implementation

## UML Class Diagram

```mermaid
classDiagram
    %% Abstract Classes and Interfaces
    class IHardwareInterface {
        <<interface>>
        +initialize(): void
        +readSensors(): void
        +controlActuators(): void
    }

    class IAdc {
        <<interface>>
        +setup(): bool
        +read(value: uint16_t&): bool
    }

    class ICommunication {
        <<interface>>
        +setup(): bool
        +writeData(data: uint8_t[], size: size_t, bytesWritten: size_t&): bool
        +readData(buffer: uint8_t[], size: size_t, bytesRead: size_t&): bool
    }

    %% Base Application Class (Singleton)
    class BionicArmApp {
        -static instance: BionicArmApp*
        -hardware: IHardwareInterface*
        #BionicArmApp()
        +static getInstance(): BionicArmApp&
        +run(): void
        +~BionicArmApp()
    }

    %% Concrete Applications
    class FullArmApp {
        -bionicArm: BionicArm*
        +setup(): void
        +loop(): void
    }

    class DatasetGenerationApp {
        -emgSensor: EmgSensor*
        -communication: Communication*
        +setup(): void
        +loop(): void
        -collectData(): void
        -saveData(): void
    }

    %% Core Modules
    class BionicArm {
        -emg: EmgSensor*
        -motors: MotorDriver[]*
        -buttonMatrix: ButtonMatrix*
        -communication: Communication*
        +BionicArm(emgPin: uint8_t, motorPins: uint8_t[], rowPins: uint8_t[], colPins: uint8_t[])
        +setup(): bool
        +doGesture(): bool
        -processEmgSignal(emgValue: uint16_t&): bool
        -executeGesture(gestureId: uint8_t): bool
        -sendGestureData(gestureId: uint8_t, emgValue: uint16_t): bool
    }

    class EmgSensor {
        -adc: IAdc*
        +EmgSensor(pin: uint8_t)
        +setup(): bool
        +read(value: uint16_t&): bool
    }

    class MotorDriver {
        -pinForward: uint8_t
        -pinBackward: uint8_t
        +MotorDriver(pinFwd: uint8_t, pinBwd: uint8_t)
        +setup(): bool
        +forward(speed: uint8_t): bool
        +backward(speed: uint8_t): bool
        +stop(): bool
    }

    class ButtonMatrix {
        -rowPins: uint8_t[]
        -colPins: uint8_t[]
        -numRows: uint8_t
        -numCols: uint8_t
        +ButtonMatrix(rowPins: uint8_t[], numRows: uint8_t, colPins: uint8_t[], numCols: uint8_t)
        +setup(): bool
        +read(row: uint8_t&, col: uint8_t&): bool
    }

    class Communication {
        -protocol: ICommunication*
        +Communication()
        +setup(): bool
        +writeData(data: uint8_t[], size: size_t, bytesWritten: size_t&): bool
        +readData(buffer: uint8_t[], size: size_t, bytesRead: size_t&): bool
    }

    %% Factory Classes
    class HardwareFactory {
        +static createHardware(): IHardwareInterface*
    }

    class AdcFactory {
        +static createAdc(pin: uint8_t): IAdc*
    }

    %% Platform-Specific Implementations
    class ESP32Implementation {
        +initialize(): void
        +readSensors(): void
        +controlActuators(): void
    }

    class STM32Implementation {
        +initialize(): void
        +readSensors(): void
        +controlActuators(): void
    }

    class ESP32Adc {
        -pin: uint8_t
        +setup(): bool
        +read(value: uint16_t&): bool
    }

    class STM32Adc {
        -pin: uint8_t
        +setup(): bool
        +read(value: uint16_t&): bool
    }

    %% Relationships
    BionicArmApp <|-- FullArmApp
    BionicArmApp <|-- DatasetGenerationApp
    BionicArmApp --> HardwareFactory
    IHardwareInterface <|.. ESP32Implementation
    IHardwareInterface <|.. STM32Implementation
    IAdc <|.. ESP32Adc
    IAdc <|.. STM32Adc
    HardwareFactory ..> IHardwareInterface
    AdcFactory ..> IAdc
    EmgSensor --> IAdc
    BionicArm *-- EmgSensor
    BionicArm *-- MotorDriver
    BionicArm *-- ButtonMatrix
    BionicArm *-- Communication
    FullArmApp *-- BionicArm
    DatasetGenerationApp *-- EmgSensor
    DatasetGenerationApp *-- Communication
    Communication --> ICommunication
```

## UML Diagram Description

The UML class diagram above shows the complete architecture of the Bionic Arm project, including:

1. **Application Layer**
   - Abstract `BionicArmApp` base class (Singleton)
   - Concrete applications: `FullArmApp` and `DatasetGenerationApp`

2. **Core Modules**
   - `BionicArm`: Main control module
   - `EmgSensor`: EMG signal processing
   - `MotorDriver`: Motor control
   - `ButtonMatrix`: Input handling
   - `Communication`: Data transmission

3. **Interfaces**
   - `IHardwareInterface`: Hardware abstraction
   - `IAdc`: ADC operations
   - `ICommunication`: Communication protocols

4. **Factories**
   - `HardwareFactory`: Creates platform-specific implementations
   - `AdcFactory`: Creates ADC implementations

5. **Platform-Specific Implementations**
   - ESP32 implementations
   - STM32 implementations

The diagram shows all relationships between components:
- Inheritance (extends) relationships
- Implementation relationships
- Composition relationships
- Dependencies

This architecture demonstrates the application of:
- SOLID principles
- Factory pattern for hardware abstraction
- Singleton pattern for application management
- Modular design for maintainability and extensibility 

## Testing
- EMG readings functionality has been tested
- Dataset generation system verified
- Ready for further implementation of arm control features 