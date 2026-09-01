#include <iostream>
#include <cstdint>

using namespace std;


// Prints a 32-bit IP address in normal dotted format
void printIP(uint32_t ip)
{
    cout << ((ip >> 24) & 255) << "."
         << ((ip >> 16) & 255) << "."
         << ((ip >> 8) & 255) << "."
         << (ip & 255);
}


int main()
{
    int a, b, c, d;
    char dot;
    int prefix;


    // Get IP address

    cout << "Enter IP address: ";

    cin >> a >> dot
        >> b >> dot
        >> c >> dot
        >> d;


    // Get CIDR prefix

    cout << "Enter CIDR prefix: /";
    cin >> prefix;


    // Check prefix

    if (prefix < 0 || prefix > 32)
    {
        cout << "Invalid prefix." << endl;
        return 1;
    }


    // Convert four octets into one 32-bit number

    uint32_t ip =
        (static_cast<uint32_t>(a) << 24) |
        (static_cast<uint32_t>(b) << 16) |
        (static_cast<uint32_t>(c) << 8) |
        static_cast<uint32_t>(d);


    // Create subnet mask

    uint32_t mask;

    if (prefix == 0)
    {
        mask = 0;
    }
    else
    {
        mask = 0xFFFFFFFFu << (32 - prefix);
    }


    // Calculate network address

    uint32_t network = ip & mask;


    // Calculate broadcast address

    uint32_t broadcast = network | ~mask;


    // Calculate number of host bits

    int hostBits = 32 - prefix;


    // Total number of addresses

    uint64_t totalAddresses =
        1ULL << hostBits;


    // Calculate usable hosts

    uint64_t usableHosts;

    if (prefix <= 30)
    {
        usableHosts = totalAddresses - 2;
    }
    else if (prefix == 31)
    {
        usableHosts = 2;
    }
    else
    {
        usableHosts = 1;
    }


    // Display results

    cout << endl;

    cout << "------ Subnet Information ------" << endl;


    cout << "IP Address:        ";
    printIP(ip);
    cout << endl;


    cout << "CIDR Prefix:       /"
         << prefix << endl;


    cout << "Subnet Mask:       ";
    printIP(mask);
    cout << endl;


    cout << "Network Address:   ";
    printIP(network);
    cout << endl;


    cout << "Broadcast Address: ";
    printIP(broadcast);
    cout << endl;


    cout << "Host Bits:         "
         << hostBits << endl;


    cout << "Total Addresses:   "
         << totalAddresses << endl;


    cout << "Usable Hosts:      "
         << usableHosts << endl;


    return 0;
}