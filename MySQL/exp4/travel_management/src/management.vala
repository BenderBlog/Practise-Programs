// 2022 SuperBart, released under SuperBart Public Domain Software License / GPLv3.
// I used the GNU readline library to input string, which should be avoidable.
// Database project, management class. Due to the time is near the deadline, 
// only administration interface is written.

using GLib;
using Gee;
using Readline;

public class Travel_Management.management_admin : Object {

    private Database toUse;

    public management_admin (Database _toUse) {
        toUse = _toUse;
    }

    public void test_data () {
        for (int i = 1; i <= 16; i++) {
            int price = 100 + Random.int_range (0, 7) * 20;
            int seats = 30 + Random.int_range (0, 7) * 5;
            uint from = Random.int_range (0, 8);
            uint to = Random.int_range (0, 8);
            while (from == to) {
                if (from == 0) from += Random.int_range (1, 7);
                else if (to == 7) to -= Random.int_range (1, 7);
                else from = Random.int_range (0, 7);
            }
            toUse.addFlightData ({
                @"A-00000$i", price, seats, seats, CITY[from], CITY[to],
            });
        }

        for (int i = 0; i < 8; i++) {
            int price = 100 + Random.int_range (0, 7) * 20;
            int rooms = 40 + Random.int_range (0, 7) * 5;
            toUse.addHotelData ({
                CITY[i], price, rooms, rooms,
            });
        }

        for (int i = 0; i < 8; i++) {
            int price = 1 + Random.int_range (0, 7);
            int seats = 40 + Random.int_range (0, 7) * 2;
            toUse.addBusData ({
                CITY[i], price, seats, seats,
            });
        }
    }

    private void insert_data () {
        int type = 0;
        stdout.printf ("\n--------------- INSERT DATA --------------\n");
        stdout.printf ("1.Flight   2.Hotel   3.Bus   4.Customer  5.Reservation\nYour Choice: ");
        stdin.scanf ("%d", &type);
        if (type == 1) {
            double price;
            int numberSeats;

            string flightNumber = readline ("Enter FLIGHTNUMBER(text): ");

            stdout.printf ("Enter PRICE(float): ");
            stdin.scanf ("%lf", out price);

            stdout.printf ("Enter NUMBEROFSEATS(int): ");
            stdin.scanf ("%d", out numberSeats);

            string FromCity = readline ("Enter FROMCITY(text): ");

            string ArivCity = readline ("Enter ARRIVECITY(text): ");

            toUse.addFlightData ({
                flightNumber,
                price,
                numberSeats,
                numberSeats,
                FromCity,
                ArivCity,
            });
        } else if (type == 2) {
            int price;
            int numberRooms;

            string location = readline ("Enter LOCATION(text): ");

            stdout.printf ("Enter PRICE(int): ");
            stdin.scanf ("%d", out price);

            stdout.printf ("Enter NUMBEROFROOM(int): ");
            stdin.scanf ("%d", out numberRooms);

            toUse.addHotelData ({
                location,
                price,
                numberRooms,
                numberRooms,
            });
        } else if (type == 3) {
            int price;
            int numberBus;

            string location = readline ("Enter LOCATION(text): ");

            stdout.printf ("Enter PRICE(int): ");
            stdin.scanf ("%d", out price);

            stdout.printf ("Enter NUMBEROFBUS(int): ");
            stdin.scanf ("%d", out numberBus);

            toUse.addBusData ({
                location,
                price,
                numberBus,
                numberBus,
            });
        } else if (type == 4) {
            int id;

            stdout.printf ("Enter id(int): ");
            stdin.scanf ("%d", out id);

            string name = readline ("Enter NAME(text): ");

            toUse.addCustomerData ({
                id,
                name,
            });
        } else if (type == 5) {
            try {
                stdout.printf ("\n--------------- CUSTOMER LIST --------------\n");
                query_data (4);

                int custID;
                int resvKey;
                int restType = 0;
                string restStr = "";
                Customer? cust = null;

                stdout.printf ("Enter custID(int): ");
                stdin.scanf ("%d", out custID);
                cust = toUse.search_customer (custID).index (0);

                stdout.printf ("Enter resvKey(int): ");
                stdin.scanf ("%d", out resvKey);

                stdout.printf ("Enter resvType(int), 1.Flight 2.Hotel 3.Bus: ");
                stdin.scanf ("%d", out restType);

                if (restType == 1) {
                    query_data (1);
                    restStr = readline ("Enter the flight number: ");
                    Flight toChange = toUse.search_flight (restStr).index (0);
                    if (toChange.numberAvail <= 0) {
                        stdout.printf ("Plane full! Abort!\n");
                    } else {
                        toChange.numberAvail -= 1;
                        toUse.changeFlightData (toChange);
                    }
                } else if (restType == 2) {
                    query_data (2);
                    restStr = readline ("Enter the hotel location: ");
                    Hotel toChange = toUse.search_hotel (restStr).index (0);
                    if (toChange.numberAvial <= 0) {
                        stdout.printf ("Hotel full! Abort!\n");
                    } else {
                        toChange.numberAvial -= 1;
                        toUse.changeHotelData (toChange);
                    }
                } else if (restType == 3) {
                    query_data (3);
                    restStr = readline ("Enter the bus location: ");
                    Bus toChange = toUse.search_bus (restStr).index (0);
                    if (toChange.numberAvial <= 0) {
                        stdout.printf ("Bus full! Abort!\n");
                    } else {
                        toChange.numberAvial -= 1;
                        toUse.changeBusData (toChange);
                    }
                } else {
                    stdout.printf ("Invalid type! Abort!\n");
                }

                toUse.addReservationData ({
                    cust,
                    resvKey,
                    restType,
                    restStr,
                });
            } catch (DatabaseError e) {
                stdout.printf (e.message);
            }
        } else {
            stdout.printf ("Unable to understand, rollback...\n");
        }
        return;
    }

    private void delete_data () {
        int type = 0;
        int choice = 0;
        stdout.printf ("\n--------------- DELETE DATA --------------\n");
        stdout.printf ("1.Flight   2.Hotel   3.Bus   4.Customer  5.Reservation\nYour Choice: ");
        stdin.scanf ("%d", &type);
        try {
            if (type >= 1 && type <= 5) {
                bool flag = false;
                query_data (type);
                stdout.printf ("Enter your choice: ");
                stdin.scanf ("%d", out choice);
                if (choice <= 0) {
                    stdout.printf ("Invalid input!\n");
                } else if (type == 1) {
                    Flight toDelete = toUse.search_flight ().index (choice - 1);
                    flag = toUse.removeFlightData (toDelete.flightNumber);
                } else if (type == 2) {
                    Hotel toDelete = toUse.search_hotel ().index (choice - 1);
                    flag = toUse.removeHotelData (toDelete.location);
                } else if (type == 3) {
                    Bus toDelete = toUse.search_bus ().index (choice - 1);
                    flag = toUse.removeBusData (toDelete.location);
                } else if (type == 4) {
                    Customer toDelete = toUse.search_customer ().index (choice - 1);
                    Array<Reservation> toCount = toUse.search_reservation ();
                    int count = 0;
                    foreach (var i in toCount) {
                        if (i.cust == toDelete) count++;
                    }
                    if (count != 0) {
                        stdout.printf ("Cannot del customer, still got reservation.");
                    } else {
                        flag = toUse.removeCustomerData (toDelete.id);
                    }
                } else if (type == 5) {
                    Reservation toDelete = toUse.search_reservation ().index (choice - 1);
                    if (toDelete.reservationType == 1) {
                        Flight toChange = toUse.search_flight (toDelete.reservationString).index (0);
                        toChange.numberAvail += 1;
                        toUse.changeFlightData (toChange);
                    } else if (toDelete.reservationType == 2) {
                        Hotel toChange = toUse.search_hotel (toDelete.reservationString).index (0);
                        toChange.numberAvial += 1;
                        toUse.changeHotelData (toChange);
                    } else if (toDelete.reservationType == 3) {
                        Bus toChange = toUse.search_bus (toDelete.reservationString).index (0);
                        toChange.numberAvial += 1;
                        toUse.changeBusData (toChange);
                    }
                    flag = toUse.removeReservationData (toDelete.reservationKey);
                }
                if (flag) {
                    stdout.printf ("If all avaliable, delete complete.");
                }
            }
        } catch (DatabaseError e) {
            stdout.printf (e.message);
        }
        return;
    }

    private void query_data (int type = 0) throws DatabaseError {
        int num = 0;
        if (type == 0) {
            stdout.printf ("\n--------------- QUERY DATA --------------\n");
            stdout.printf ("1.Flight   2.Hotel   3.Bus   4.Customer  5.Reservation\nYour Choice: ");
            stdin.scanf ("%d", out type);
        }
        if (type == 1) {
            Array<Flight> all = toUse.search_flight ();
            if (all.length > 0) {
                print ("NUM\tFLIGHTNUM\tPRICE\tNUMSEAT\tNUMAVA\tFROM\tARRI\n");
                foreach (var i in all) {
                    num += 1;
                    stdout.printf ("%d\t%s\t%.2lf\t%d\t%d\t%s\t%s\n",
                                   num, i.flightNumber,
                                   i.price, i.numberSeats,
                                   i.numberAvail, i.FromCity, i.ArivCity);
                }
            } else {
                throw new DatabaseError.NOT_FOUND ("It is an empty table.");
            }
        } else if (type == 2) {
            Array<Hotel> all = toUse.search_hotel ();
            if (all.length > 0) {
                print ("NUM\tLOCATE\tPRICE\tNUMROOM\tNUMAVA\n");
                foreach (var i in all) {
                    num += 1;
                    stdout.printf ("%d\t%s\t%d\t%d\t%d\n",
                                   num, i.location, i.price,
                                   i.numberRooms, i.numberAvial);
                }
            } else {
                throw new DatabaseError.NOT_FOUND ("It is an empty table.");
            }
        } else if (type == 3) {
            Array<Bus> all = toUse.search_bus ();
            if (all.length > 0) {
                print ("NUM\tLOCATE\tPRICE\tNUMBUS\tNUMAVA\n");
                foreach (var i in all) {
                    num += 1;
                    stdout.printf ("%d\t%s\t%d\t%d\t%d\n",
                                   num, i.location, i.price,
                                   i.numberBus, i.numberAvial);
                }
            } else {
                throw new DatabaseError.NOT_FOUND ("It is an empty table.");
            }
        } else if (type == 4) {
            Array<Customer> all = toUse.search_customer ();
            if (all.length > 0) {
                print ("NUM\tcustID\tNAME\n");
                foreach (var i in all) {
                    num += 1;
                    stdout.printf ("%d\t%d\t%s\n", num, i.id, i.name);
                }
            } else {
                throw new DatabaseError.NOT_FOUND ("It is an empty table.");
            }
        } else if (type == 5) {
            Array<Reservation> all = toUse.search_reservation ();
            if (all.length > 0) {
                print ("NUM\tCUSTNAME\tRESKEY\tRESTYPE\tRESSTR\n");
                foreach (var i in all) {
                    num += 1;
                    stdout.printf ("%d\t%s\t%d\t%d\t%s\n",
                                   num, i.cust.name, i.reservationKey,
                                   i.reservationType, i.reservationString);
                }
            } else {
                throw new DatabaseError.NOT_FOUND ("It is an empty table.");
            }
        } else {
            stdout.printf ("Unable to understand, rollback...\n");
        }
        return;
    }

    private void update_data () {
        int type = 0;
        int choice = 0;
        stdout.printf ("\n--------------- UPDATE DATA --------------\n");
        stdout.printf ("1.Flight   2.Hotel   3.Bus   4.Customer\nYour Choice: ");
        stdin.scanf ("%d", &type);
        try {
            if (type >= 1 && type <= 4) {
                query_data (type);
                stdout.printf ("Enter your choice: ");
                stdin.scanf ("%d", out choice);
                if (choice <= 0) {
                    stdout.printf ("Invalid input!\n");
                } else if (type == 1) {
                    Flight toChange = toUse.search_flight ().index (choice - 1);
                    double price;
                    int numberSeats;

                    stdout.printf ("Enter PRICE(float), current %.2lf: ".printf (toChange.price));
                    stdin.scanf ("%lf", out price);

                    stdout.printf ("Enter NUMBEROFSEATS(int): , current %d, avaliable %d: ".printf (toChange.numberSeats, toChange.numberAvail));
                    stdin.scanf ("%d", out numberSeats);

                    // FromCity and ArriveCity not changeable!

                    int reserved = toChange.numberSeats - toChange.numberAvail;
                    if (numberSeats - reserved < 0) {
                        stdout.printf ("Unable to change, new numSeats is smaller than reserved.\n");
                    } else {
                        toChange.price = price;
                        toChange.numberSeats = numberSeats;
                        toChange.numberAvail = numberSeats - reserved;
                        toUse.changeFlightData (toChange);
                    }
                } else if (type == 2) {
                    Hotel toChange = toUse.search_hotel ().index (choice - 1);
                    int price, numberRooms;

                    stdout.printf ("Enter PRICE(float), current %d: ".printf (toChange.price));
                    stdin.scanf ("%d", out price);

                    stdout.printf ("Enter NUMBEROFROOM(int), current %d, avaliable %d: ".printf (toChange.numberRooms, toChange.numberAvial));
                    stdin.scanf ("%d", out numberRooms);

                    int reserved = toChange.numberRooms - toChange.numberAvial;
                    if (numberRooms - reserved < 0) {
                        stdout.printf ("Unable to change, new numberRooms is smaller than reserved.\n");
                    } else {
                        toChange.price = price;
                        toChange.numberRooms = numberRooms;
                        toChange.numberAvial = numberRooms - reserved;
                        toUse.changeHotelData (toChange);
                    }
                } else if (type == 3) {
                    Bus toChange = toUse.search_bus ().index (choice - 1);
                    int price, numberBus;

                    stdout.printf ("Enter PRICE(int), current %d: ".printf (toChange.price));
                    stdin.scanf ("%d", out price);

                    stdout.printf ("Enter NUMBEROFBUS(int)current %d, avaliable %d: ".printf (toChange.numberBus, toChange.numberAvial));
                    stdin.scanf ("%d", out numberBus);

                    int reserved = toChange.numberBus - toChange.numberAvial;
                    if (numberBus - reserved < 0) {
                        stdout.printf ("Unable to change, new numberBus is smaller than reserved.\n");
                    } else {
                        toChange.price = price;
                        toChange.numberBus = numberBus;
                        toChange.numberAvial = numberBus - reserved;
                        toUse.changeBusData (toChange);
                    }
                } else if (type == 4) {
                    Customer toChange = toUse.search_customer ().index (choice - 1);

                    string name = readline ("Enter NAME(text), current name %s: ".printf (toChange.name));

                    toChange.name = name;
                    toUse.changeCustomerData (toChange);
                }
                stdout.printf ("Change complete.");
            } else {
                stdout.printf ("Unable to understand, rollback...\n");
            }
        } catch (DatabaseError e) {
            stdout.printf (e.message);
        }
        return;
    }

    private void eval_possibility () {
        HashMap<string, HashSet<string>> Graph = toUse.avaliable ();
        int from, to;
        for (int i = 0; i < CITY.length; ++i) {
            stdout.printf (@"$i $(CITY[i])\n");
        }
        stdout.printf ("Choice a departure: ");
        stdin.scanf ("%d", out from);
        stdout.printf ("Choice a destination: ");
        stdin.scanf ("%d", out to);
        if (from < 0 || from >= CITY.length || to < 0 || to >= CITY.length) {
            stdout.printf ("Unable to find this city.\n");
        } else if (from == to) {
            stdout.printf ("You needn't have to paid for roundabout.\n");
        } else if (!Graph.has_key (CITY[from])) {
            stdout.printf ("Departure is a lonely city.");
        } else {
            HashSet<string> dealt = new HashSet<string>();
            dealt.add (CITY[from]);
            while (!dealt.contains (CITY[to])) {
                HashSet<string> toAppend = new HashSet<string>();
                dealt.foreach ((i) => {
                    if (Graph.has_key (i)) {
                        Graph[i].foreach((i) => {
                            if (!dealt.contains (i)) toAppend.add (i);
                            return true;
                        });
                    }
                    return true;
                });
                if (toAppend.is_empty) {
                    stdout.printf ("Unable to reach!\n");
                    break;
                } else {
                    dealt.add_all (toAppend);
                }
            }
            stdout.printf ("It's able to reach!\n");
        }
    }

    public void print_flights () {
        var Graph = toUse.avaliable ();
        foreach (var key in CITY) {
            stdout.printf (@"$key: ");
            if (!Graph.has_key (key)) {
                stdout.printf ("Lonely city.");
            } else {
                Graph[key].foreach ((j) => {stdout.printf (@"$j,"); return true;});
            }
            stdout.printf ("\n");
        }
    }

    public void management () {
        toUse = new Database ();
        int menu = 0;
        while (true) {
            stdout.printf ("\n--------------- Administer --------------\n");
            stdout.printf ("1.Insert   2.Delete   3.Query   4.Update   5.Generate   6.Display   7.Eval   0.Quit\nYour Choice: ");
            stdin.scanf ("%i", &menu);
            if (menu == 0) {
                stdout.printf ("Bye.\n");
                break;
            } else if (menu == 1) {
                insert_data ();
            } else if (menu == 2) {
                delete_data ();
            } else if (menu == 3) {
                try {
                    query_data ();
                } catch (DatabaseError e) {
                    stdout.printf (e.message);
                }
            } else if (menu == 4) {
                update_data ();
            } else if (menu == 5) {
                test_data ();
            } else if (menu == 6) {
                print_flights ();
            } else if (menu == 7) {
                eval_possibility ();
            } else {
                stdout.printf ("Unable to understand, rollback...\n");
            }
        }
        return;
    }
}