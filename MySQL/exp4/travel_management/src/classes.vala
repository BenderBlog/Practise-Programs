// 2022 SuperBart, released under SuperBart Public Domain Software License.
// Database project, define important structure for program.

using GLib;

// Ariv stand for avaliable
public struct Travel_Management.Flight {
    string flightNumber; // Main key
    double price;
    int numberSeats;
    int numberAvail;
    string FromCity;
    string ArivCity;
}

public struct Travel_Management.Hotel {
    string location; // Main key
    int price;
    int numberRooms;
    int numberAvial;
}

public struct Travel_Management.Bus {
    string location; // Main key
    int price;
    int numberBus;
    int numberAvial;
}

public struct Travel_Management.Customer {
    int id;
    string name;
}

public struct Travel_Management.Reservation {
    Travel_Management.Customer cust;
    int reservationKey;
    // 1 Flight, 2 Hotel, 3 Bus
    int reservationType;
    string reservationString;
}

const string CITY[8] = {
    "Tianjin", "Urumqi", "Hohhot", "Wuhan",
    "Xi'an", "Beijing", "Shanghai", "Shenzhen"
};
