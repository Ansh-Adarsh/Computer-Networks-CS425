# Computer Networks (CS425)

This repository contains implementation projects for Computer Networks (CS425), focusing on data integrity algorithms and custom socket networking protocols.

## Modules

### 1. C++ Cyclic Redundancy Check (CRC) Engine
- **Engine Core:** Implements bitwise XOR polynomial long division for CRC error-detection calculation.
- **CLI Utilities:** Includes an interactive command-line interface with a randomized error-injection simulator to evaluate error detection performance under noisy channel conditions.

### 2. Python UDP Client-Server System
- **Raw Datagram Processing:** Custom client and server socket implementation capable of building, transmitting, and parsing raw UDP datagrams.
- **Packet Handling:** Handles packet headers, payload extraction, and data integrity verification.

## Features
- Hardware-accurate CRC implementation with custom generator polynomials.
- Configurable error injection rate for network simulation.
- Low-level network socket programming in Python.

## Usage
- Compile C++ sources using standard `g++` (`-std=c++17` recommended).
- Execute Python scripts using `python3`.
