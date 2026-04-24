# Airline Management System – DSA Project
This C++ project simulates an airline reservation and management system, designed as part of the **Data Structures and Algorithms (DSA)** course. It allows **customers** to book flights, generate tickets, and view flight details, while **administrators** can manage flights, tickets, and user data efficiently.

## About the Project
This project applies key DSA concepts including:
- **Doubly Linked Lists** – for dynamic ticket records (insert, delete, search)
- **File Handling** – to store and retrieve user and flight data
- **Class-Based Modularity** – for separation of concerns across `Passenger`, `Ticket`, `Admin`, and `Flight` functionalities
- **Console UI Enhancements** – using Windows API for colored text and coordinate-based output

## Features

### Customer Module:
- User signup and login with validation
- View international and domestic flights
- Book tickets with auto-generated PNR
- Check and cancel existing tickets

### Admin Module:
- Secure login for admin
- Add/update/delete international and domestic flight data
- View all passenger tickets
- Modify seat availability and flight schedules

## Technologies Used
- **Language**: C++
- **Concepts**: Doubly Linked Lists, File I/O, OOP
- **Tools**: Windows API (`<windows.h>`), `fstream`

### Requirements:
- Windows OS (due to use of Windows console API)
- C++ compiler (e.g., g++, Visual Studio)


