/********************************
SoftwareDecoding.cpp

Program to output data to control the TDB Module
Programmer's Name: Jose Isaac Martinez Realpe
Date: 03/11/2025
Using the die face on the TDB module breadboard 
you will control the LEDs using software.

********************************/


#include <iostream>     // For console input and output
#include <winsock.h>     // For TCP socket communication
#include <windows.h>     // For Sleep() function
using namespace std;

// TCP I/O command definition
#define IOSet 0x41       // 0x41 is the output command for the TDB module

// Global variables for socket communication
WSADATA wsaData;             // Winsock data structure
SOCKET sock;                 // TCP socket descriptor
struct sockaddr_in serverAddr;  // Server address structure

// Function prototypes
void initializeSocket(int port);   // Initialize and connect TCP socket
void closeSocket();                // Close TCP socket
void outputData(char value);       // Send data to TDB module

int main(int argc, char* argv[])
{
    // Check for correct number of command line arguments
    if (argc != 2)
    {
        cout << "Usage: TDB7Segment <port number>\n";
        return 1; // Exit if port number not provided
    }
}

// Initializes the socket and connects to the TDB module on the specified port
void initializeSocket(int port)
{
    WSAStartup(MAKEWORD(1, 1), &wsaData); // Start Winsock v1.1
    sock = socket(AF_INET, SOCK_STREAM, 0); // Create TCP socket

    memset(&serverAddr, 0, sizeof(serverAddr)); // Clear memory
    serverAddr.sin_family = AF_INET;            // Use IPv4
    serverAddr.sin_port = htons(port);           // Set port number

    // Get IP address for server (hostname resolution)
    struct hostent* hptr = gethostbyname("cst225.dyndns.org");
    memcpy(&serverAddr.sin_addr, hptr->h_addr, hptr->h_length); // Set server IP

    // Connect to the server (TDB module)
    connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    cout << "Connected to port " << port << "\n";
}

// Function to close the socket connection cleanly
void closeSocket()
{
    closesocket(sock); // Close TCP socket
    WSACleanup();      // Cleanup Winsock
}

// Function to send a 7-segment pattern to the TDB module
void outputData(char value)
{
    char commandBuf[2];    // Buffer: [Command Code, Data]
    commandBuf[0] = IOSet; // First byte: Output command (0x41)
    commandBuf[1] = value; // Second byte: 7-segment pattern to display

    send(sock, commandBuf, 2, 0); // Send 2 bytes to server
}
