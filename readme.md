# Donations Management System

## Project Overview

This project is a Donations Management System developed for an Object-Oriented Programming (OOP) course. The system is implemented in C++ and provides functionalities to manage donations, including donor registration, donation tracking, and generating reports. The aim of the project is to demonstrate the application of OOP principles in designing and implementing a real-world system.

## Table of Contents

1. [Introduction](#introduction)
2. [Setup and Requirements](#setup-and-requirements)
3. [Implementation Details](#implementation-details)
4. [Running the Code](#running-the-code)
5. [Conclusion](#conclusion)

## Introduction

The Donations Management System is designed to facilitate the management of donations for non-profit organizations. It allows for the registration of donors, tracking of donations, and generation of reports. The system is built using object-oriented programming principles, making it modular, maintainable, and extensible.

## Setup and Requirements

### Prerequisites

- C++ compiler (e.g., GCC)
- Basic knowledge of object-oriented programming in C++

### Installation

1. Ensure a C++ compiler is installed on your system. You can install GCC on Unix-based systems using:
    ```sh
    sudo apt-get install g++
    ```

2. Clone this repository to your local machine:
    ```sh
    git clone https://github.com/syed-mohd-fasih/Donations-Management-System.git
    cd Donations-Management-System
    ```

## Implementation Details

### Object-Oriented Design

The system is designed using object-oriented principles:

- **Encapsulation**: The data and methods related to donors and donations are encapsulated within their respective classes.
- **Inheritance**: The system can be extended by creating subclasses for different types of donations or reports.
- **Polymorphism**: Methods related to generating reports or processing donations can be overridden in subclasses for specific behaviors.

## Running the Code

1. Compile the code using the provided Makefile:
    ```sh
    g++ main.cpp -o donations_management_system
    ```

2. Run the executable:
    ```sh
    ./donations_management_system
    ```

## Conclusion

The Donations Management System demonstrates the application of object-oriented programming principles in designing and implementing a system to manage donations. This project highlights the benefits of OOP in creating modular, maintainable, and extensible software and provides a practical example of applying these concepts to solve real-world problems.
