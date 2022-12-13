// 2022 SuperBart, released under SuperBart Public Domain Software License.
// Database project, database class. Use sqlite because using mysql is a waste.
// Mostly formulas I used are from sqlite C/C++ header, instead of obdc.

using Gee;
using Sqlite;

public class Travel_Management.Database : GLib.Object {

    const string NAME_OF_DB = "travel.db";

    private Sqlite.Database m_db;

    private const string CREATE_FLIGHT_TABLE_QUERY = """
        CREATE TABLE IF NOT EXISTS FLIGHT (
                flightNum   TEXT    PRIMARY KEY NOT NULL UNIQUE,
                price       REAL    NOT NULL,
                numSeats    INT     NOT NULL,
                numAvail    INT     NOT NULL    CHECK (numAvail >= 0),
                FromCity    TEXT    NOT NULL,
                ArivCity    TEXT    NOT NULL
            );
    """;

    private const string CREATE_HOTEL_TABLE_QUERY = """
            CREATE TABLE IF NOT EXISTS HOTEL (
                location    TEXT    PRIMARY KEY NOT NULL,
                price       REAL    NOT NULL,
                numRooms    INT     NOT NULL,
                numAvail    INT     NOT NULL    CHECK (numAvail >= 0)
            );
    """;

    private const string CREATE_BUS_TABLE_QUERY = """
            CREATE TABLE IF NOT EXISTS BUS(
                location    TEXT    PRIMARY KEY NOT NULL,
                price       INT     NOT NULL,
                numBus      INT     NOT NULL,
                numAvail    INT     NOT NULL    CHECK (numAvail >= 0)
            );
    """;

    private const string CREATE_CUSTOMER_TABLE_QUERY = """
            CREATE TABLE IF NOT EXISTS CUSTOMER(
                custID      INT     PRIMARY KEY NOT NULL,
                custName    TEXT    NOT NULL
            );
    """;

    private const string CREATE_RESERVATION_TABLE_QUERY = """
            CREATE TABLE IF NOT EXISTS RESERVATION(
                resvKey     INT     PRIMARY KEY NOT NULL,
                custName    INT     NOT NULL,
                resvType    INT     NOT NULL,
                resvStr     TEXT    NOT NULL,
                FOREIGN KEY(custName) REFERENCES CUSTOMER(custID),
                CHECK (resvType >= 1 and resvType <= 3)
            );
    """;

    private const string ADD_FLIGHT_DATA = """
            INSERT INTO FLIGHT (flightNum, price, numSeats, numAvail, FromCity, ArivCity)
            VALUES ($FLIGHTNUMBER, $PRICE, $NUMBEROFSEATS, $NUMBEROFAVALIABLE, $FROMCITY, $ARRIVECITY);
    """;

    private const string ADD_HOTEL_DATA = """
            INSERT INTO HOTEL (location, price, numRooms, numAvail)
            VALUES ($LOCATION, $PRICE, $NUMBEROFROOMS, $NUMBEROFAVALIABLE);
    """;

    private const string ADD_BUS_DATA = """
            INSERT INTO BUS (location, price, numBus, numAvail)
            VALUES ($LOCATION, $PRICE, $NUMBEROFBUS, $NUMBEROFAVALIABLE);
    """;

    private const string ADD_CUSTOMER_DATA = """
            INSERT INTO CUSTOMER (custID, custName) VALUES ($CUSTOMERID, $CUSTOMERNAME);
    """;

    private const string ADD_RESERVATION_DATA = """
            INSERT INTO RESERVATION (resvKey, custName, resvType, resvStr)
            VALUES ($RESERVATIONKEY, $CUSTOMERNAME, $RESERVATIONTYPE, $RESERVATIONSTRING);
    """;

    private const string UPDATE_FLIGHT_DATA = """
            UPDATE FLIGHT
            SET price       = $PRICE,
                numSeats    = $NUMBEROFSEATS,
                numAvail    = $NUMBEROFAVALIABLE,
                FromCity    = $FROMCITY,
                ArivCity    = $ARRIVECITY
            WHERE flightNum == $FLIGHTNUMBER;
    """;

    private const string UPDATE_HOTEL_DATA = """
            UPDATE HOTEL
            SET price       = $PRICE,
                numRooms    = $NUMBEROFSEATS,
                numAvail    = $NUMBEROFAVALIABLE
            WHERE location  == $LOCATION;
    """;

    private const string UPDATE_BUS_DATA = """
            UPDATE BUS
            SET price    = $PRICE,
                numBus   = $NUMBEROFBUS,
                numAvail = $NUMBEROFAVALIABLE
            WHERE location == $LOCATION;
    """;

    private const string UPDATE_CUSTOMER_DATA = """
            UPDATE CUSTOMER
            SET custName = $CUSTOMERNAME
                WHERE custID == $CUSTOMERID;
    """;

    // TODO: Should not use it!
    private const string UPDATE_RESERVATION_DATA = """
            UPDATE RESERVATION
            SET custName = $CUSTOMERNAME,
                resvType = $RESERVATIONTYPE,
                resvStr  = $RESERVATIONSTRING
            WHERE resvKey == $RESERVATIONKEY;
    """;

    private const string DELETE_FLIGHT_DATA = """
            DELETE FROM FLIGHT
            WHERE flightNum == $FLIGHTNUMBER
            AND numSeats == numAvail;
    """;

    private const string DELETE_HOTEL_DATA = """
            DELETE FROM HOTEL
            WHERE location == $LOCATION
            AND numRooms == numAvail;
    """;

    private const string DELETE_BUS_DATA = """
            DELETE FROM BUS
            WHERE location == $LOCATION
            AND numBus == numAvail;
    """;

    private const string DELETE_CUSTOMER_DATA = """
            DELETE FROM CUSTOMER
            WHERE custID == $CUSTOMERID;
    """;

    private const string DELETE_RESERVATION_DATA = """
            DELETE FROM RESERVATION
            WHERE resvKey == $RESERVATIONKEY;
    """;

    private Sqlite.Statement add_flight;
    private Sqlite.Statement update_flight;
    private Sqlite.Statement delete_flight;

    private Sqlite.Statement add_hotel;
    private Sqlite.Statement update_hotel;
    private Sqlite.Statement delete_hotel;

    private Sqlite.Statement add_bus;
    private Sqlite.Statement update_bus;
    private Sqlite.Statement delete_bus;

    private Sqlite.Statement add_customer;
    private Sqlite.Statement update_customer;
    private Sqlite.Statement delete_customer;

    private Sqlite.Statement add_reservation;
    private Sqlite.Statement update_reservation;
    private Sqlite.Statement delete_reservation;

    private void open () throws DatabaseError {
        int sql_return = Sqlite.Database.open_v2 (NAME_OF_DB, out m_db);
        if (sql_return != Sqlite.OK) {
            throw new DatabaseError.COULDNT_OPEN ("Cannot create database: %d, %s\n", sql_return, m_db.errmsg ());
        }
    }

    private void exec (string exec) throws DatabaseError {
        int sql_result = m_db.exec (exec);
        if (sql_result != Sqlite.OK) {
            throw new DatabaseError.EXECUTION_FAILED ("An error occured while executing %s: %d, %s\n", exec, sql_result, m_db.errmsg ());
        }
        return;
    }

    public Sqlite.Statement prepare (string sql) throws DatabaseError {
        Sqlite.Statement statement;
        int sql_result = m_db.prepare_v2 (sql, sql.length, out statement);
        if (sql_result != Sqlite.OK) {
            throw new DatabaseError.PREPARATION_FAILED ("Cannot prepare satement for %s: %d, %s\n", sql, sql_result, m_db.errmsg ());
        }
        return statement;
    }

    private void bind_text (Sqlite.Statement statement, string stmt, string text) throws DatabaseError {
        int index = statement.bind_parameter_index (stmt);
        if (index <= 0) {
            throw new DatabaseError.BIND_FAILED ("Could not bind %s: %s not found in the statement %s.\n", text, stmt, statement.sql ());
        }

        int sql_result = statement.bind_text (index, text);

        if (sql_result != Sqlite.OK) {
            statement.reset ();
            throw new DatabaseError.BIND_FAILED ("Could not bind %s: %d, %s\n", text, sql_result, m_db.errmsg ());
        }
    }

    private void bind_int (Sqlite.Statement statement, string stmt, int content) throws DatabaseError {
        int index = statement.bind_parameter_index (stmt);
        if (index <= 0) {
            throw new DatabaseError.BIND_FAILED ("Could not bind %d: %s not found in the statement %s.\n", content, stmt, statement.sql ());
        }

        int sql_result = statement.bind_int (index, content);

        if (sql_result != Sqlite.OK) {
            statement.reset ();
            throw new DatabaseError.BIND_FAILED ("Could not bind %s: %d, %s\n", content.to_string (), sql_result, m_db.errmsg ());
        }
    }

    private void bind_double (Sqlite.Statement statement, string stmt, double content) throws DatabaseError {
        int index = statement.bind_parameter_index (stmt);
        if (index <= 0) {
            throw new DatabaseError.BIND_FAILED ("Could not bind %lf: %s not found in the statement %s.\n", content, stmt, statement.sql ());
        }

        int sql_result = statement.bind_double (index, content);

        if (sql_result != Sqlite.OK) {
            statement.reset ();
            throw new DatabaseError.BIND_FAILED ("Could not bind %s: %d, %s\n", content.to_string (), sql_result, m_db.errmsg ());
        }
    }

    // Not support SQLITE_STEP
    private void step (Sqlite.Statement statement) throws DatabaseError {
        int sql_return = statement.step ();
        statement.reset ();
        if (sql_return != Sqlite.DONE) {
            throw new DatabaseError.EXECUTION_FAILED ("Execute failed: %d, %s\n", sql_return, m_db.errmsg ());
        }
        return;
    }

    public void createDatabase () {
        try {
            open ();
            exec (CREATE_FLIGHT_TABLE_QUERY);
            exec (CREATE_HOTEL_TABLE_QUERY);
            exec (CREATE_BUS_TABLE_QUERY);
            exec (CREATE_CUSTOMER_TABLE_QUERY);
            exec (CREATE_RESERVATION_TABLE_QUERY);
        } catch (DatabaseError e) {
            stderr.printf ("%s\n", e.message);
        }
    }

    private void prepare_statements () {
        try {
            add_flight = prepare (ADD_FLIGHT_DATA);
            update_flight = prepare (UPDATE_FLIGHT_DATA);
            delete_flight = prepare (DELETE_FLIGHT_DATA);

            add_hotel = prepare (ADD_HOTEL_DATA);
            update_hotel = prepare (UPDATE_HOTEL_DATA);
            delete_hotel = prepare (DELETE_HOTEL_DATA);

            add_bus = prepare (ADD_BUS_DATA);
            update_bus = prepare (UPDATE_BUS_DATA);
            delete_bus = prepare (DELETE_BUS_DATA);

            add_customer = prepare (ADD_CUSTOMER_DATA);
            update_customer = prepare (UPDATE_CUSTOMER_DATA);
            delete_customer = prepare (DELETE_CUSTOMER_DATA);

            add_reservation = prepare (ADD_RESERVATION_DATA);
            update_reservation = prepare (UPDATE_RESERVATION_DATA);
            delete_reservation = prepare (DELETE_RESERVATION_DATA);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
        }
    }

    public Database () {
        int sql_return;
        // Try to open a existed database.
        sql_return = Sqlite.Database.open_v2 (NAME_OF_DB, out m_db, Sqlite.OPEN_READWRITE);
        if (sql_return != Sqlite.OK) {
            stdout.printf ("Database not exist: %d, %s\n", sql_return, m_db.errmsg ());
            // Try to create a database.
            createDatabase ();
        }
        prepare_statements ();
        stdout.printf ("Statements prepared.\n");
    }

    /*
     *  For Flight Data
     */

    public bool removeFlightData (string id) {
        try {
            bind_text (delete_flight, "$FLIGHTDATA", id);
            step (delete_flight);
        } catch (DatabaseError e) {
            stdout.printf (e.message + "\n");
            return false;
        }
        return true;
    }

    public bool addFlightData (Travel_Management.Flight toAppend) {
        try {
            bind_text (add_flight, "$FLIGHTNUMBER", toAppend.flightNumber);
            bind_double (add_flight, "$PRICE", toAppend.price);
            bind_int (add_flight, "$NUMBEROFSEATS", toAppend.numberSeats);
            bind_int (add_flight, "$NUMBEROFAVALIABLE", toAppend.numberAvail);
            bind_text (add_flight, "$FROMCITY", toAppend.FromCity);
            bind_text (add_flight, "$ARRIVECITY", toAppend.ArivCity);
            step (add_flight);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool changeFlightData (Travel_Management.Flight toChange) {
        try {
            bind_text (update_flight, "$FLIGHTNUMBER", toChange.flightNumber);
            bind_double (update_flight, "$PRICE", toChange.price);
            bind_int (update_flight, "$NUMBEROFSEATS", toChange.numberSeats);
            bind_int (update_flight, "$NUMBEROFAVALIABLE", toChange.numberAvail);
            bind_text (update_flight, "$FROMCITY", toChange.FromCity);
            bind_text (update_flight, "$ARRIVECITY", toChange.ArivCity);
            step (update_flight);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    /*
     *  For Bus Data
     */

    public bool removeBusData (string location) {
        try {
            bind_text (delete_bus, "$LOCATION", location);
            step (delete_bus);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool addBusData (Travel_Management.Bus toAppend) {
        try {
            bind_text (add_bus, "$LOCATION", toAppend.location);
            bind_int (add_bus, "$PRICE", toAppend.price);
            bind_int (add_bus, "$NUMBEROFBUS", toAppend.numberBus);
            bind_int (add_bus, "$NUMBEROFAVALIABLE", toAppend.numberAvial);
            step (add_bus);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool changeBusData (Travel_Management.Bus toChange) {
        try {
            bind_text (update_bus, "$LOCATION", toChange.location);
            bind_int (update_bus, "$PRICE", toChange.price);
            bind_int (update_bus, "$NUMBEROFBUS", toChange.numberBus);
            bind_int (update_bus, "$NUMBEROFAVALIABLE", toChange.numberAvial);
            step (update_bus);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    /*
     *  For Hotel Data
     */

    public bool removeHotelData (string location) {
        try {
            bind_text (delete_hotel, "$LOCATION", location);
            step (delete_hotel);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool addHotelData (Travel_Management.Hotel toAppend) {
        try {
            bind_text (add_hotel, "$LOCATION", toAppend.location);
            bind_int (add_hotel, "$PRICE", toAppend.price);
            bind_int (add_hotel, "$NUMBEROFROOMS", toAppend.numberRooms);
            bind_int (add_hotel, "$NUMBEROFAVALIABLE", toAppend.numberAvial);
            step (add_hotel);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool changeHotelData (Travel_Management.Hotel toChange) {
        try {
            bind_text (update_hotel, "$LOCATION", toChange.location);
            bind_int (update_hotel, "$PRICE", toChange.price);
            bind_int (update_hotel, "$NUMBEROFROOMS", toChange.numberRooms);
            bind_int (update_hotel, "$NUMBEROFAVALIABLE", toChange.numberAvial);
            step (update_hotel);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    /*
     *  For Customer Data
     */

    public bool removeCustomerData (int id) {
        try {
            bind_int (delete_customer, "$CUSTOMERID", id);
            step (delete_customer);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool addCustomerData (Travel_Management.Customer toAppend) {
        try {
            bind_int (add_customer, "$CUSTOMERID", toAppend.id);
            bind_text (add_customer, "$CUSTOMERNAME", toAppend.name);
            step (add_customer);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool changeCustomerData (Travel_Management.Customer toChange) {
        try {
            bind_int (update_customer, "$CUSTOMERID", toChange.id);
            bind_text (update_customer, "$CUSTOMERNAME", toChange.name);
            step (update_customer);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    /*
     *  For Reservation Data
     */

    public bool removeReservationData (int key) {
        try {
            bind_int (delete_reservation, "$RESERVATIONKEY", key);
            step (delete_reservation);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool addReservationData (Travel_Management.Reservation toAppend) {
        try {
            bind_int (add_reservation, "$RESERVATIONKEY", toAppend.reservationKey);
            bind_int (add_reservation, "$CUSTOMERNAME", toAppend.cust.id);
            bind_int (add_reservation, "$RESERVATIONTYPE", toAppend.reservationType);
            bind_text (add_reservation, "$RESERVATIONSTRING", toAppend.reservationString);
            step (add_reservation);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    public bool changeReservationData (Travel_Management.Reservation toChange) {
        try {
            bind_int (update_reservation, "$RESERVATIONKEY", toChange.reservationKey);
            bind_int (update_reservation, "$CUSTOMERNAME", toChange.cust.id);
            bind_int (update_reservation, "$RESERVATIONTYPE", toChange.reservationType);
            bind_text (update_reservation, "$RESERVATIONSTRING", toChange.reservationString);
            step (update_reservation);
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return false;
        }
        return true;
    }

    /*
     * For Search.
     */
    public Array<Flight> search_flight (string id = "") throws DatabaseError {
        try {
            Array<Flight> toReturn = new Array<Flight> ();
            var query = new StringBuilder ("SELECT * FROM FLIGHT;");
            if (id != "") {
                query.insert (-1, @" WHERE flightNum = $id;");
            }

            Sqlite.Statement stmt = prepare (query.str);
            while (stmt.step () == Sqlite.ROW) {
                toReturn.append_val ({
                    stmt.column_text (0),
                    stmt.column_double (1),
                    stmt.column_int (2),
                    stmt.column_int (3),
                    stmt.column_text (4),
                    stmt.column_text (5),
                });
            }

            return toReturn;
        } catch (DatabaseError e) {
            throw e;
        }
    }

    public Array<Hotel> search_hotel (string location = "") throws DatabaseError {
        try {
            Array<Hotel> toReturn = new Array<Hotel> ();
            var query = new StringBuilder ("SELECT * FROM HOTEL;");
            if (location != "") {
                query.insert (-1, @"WHERE location = \"$location\";");
            }

            Sqlite.Statement stmt = prepare (query.str);
            while (stmt.step () == Sqlite.ROW) {
                toReturn.append_val ({
                    stmt.column_text (0),
                    stmt.column_int (1),
                    stmt.column_int (2),
                    stmt.column_int (3),
                });
            }

            return toReturn;
        } catch (DatabaseError e) {
            throw e;
        }
    }

    public Array<Bus> search_bus (string location = "") throws DatabaseError {
        try {
            Array<Bus> toReturn = new Array<Bus> ();
            var query = new StringBuilder ("SELECT * FROM BUS;");
            if (location != "") {
                query.insert (-1, @"WHERE location = \"$location\";");
            }

            Sqlite.Statement stmt = prepare (query.str);
            while (stmt.step () == Sqlite.ROW) {
                toReturn.append_val ({
                    stmt.column_text (0),
                    stmt.column_int (1),
                    stmt.column_int (2),
                    stmt.column_int (3),
                });
            }

            return toReturn;
        } catch (DatabaseError e) {
            throw e;
        }
    }

    public Array<Customer> search_customer (int? custID = null) throws DatabaseError {
        try {
            Array<Customer> toReturn = new Array<Customer> ();
            var query = new StringBuilder ("SELECT * FROM CUSTOMER;");
            if (custID != null) {
                query.insert (-1, @"WHERE custID = \"$custID\";");
            }

            Sqlite.Statement stmt = prepare (query.str);
            while (stmt.step () == Sqlite.ROW) {
                toReturn.append_val ({
                    stmt.column_int (0),
                    stmt.column_text (1),
                });
            }
            return toReturn;
        } catch (DatabaseError e) {
            throw e;
        }
    }

    public Array<Reservation> search_reservation (int resvKey = 0) throws DatabaseError {
        try {
            Array<Reservation> toReturn = new Array<Reservation> ();
            var query = new StringBuilder ("SELECT * FROM RESERVATION;");
            if (resvKey != 0) {
                query.append (@"WHERE resvKey = $resvKey;");
            }

            Sqlite.Statement stmt = prepare (query.str);
            while (stmt.step () == Sqlite.ROW) {
                toReturn.append_val ({
                    search_customer (stmt.column_int (1)).index (0),
                    stmt.column_int (0),
                    stmt.column_int (2),
                    stmt.column_text (3),
                });
            }

            return toReturn;
        } catch (DatabaseError e) {
            throw e;
        }
    }

    public HashMap<string, HashSet<string>> ? avaliable () {
        try {
            var Graph = new HashMap<string, HashSet<string>> ();
            Sqlite.Statement get_flight = this.prepare ("SELECT FromCity,ArivCity FROM FLIGHT;");
            while (get_flight.step () == Sqlite.ROW) {
                string from = get_flight.column_text (0);
                string to = get_flight.column_text (1);
                if (!Graph.has_key (from)) {
                    Graph[from] = new HashSet<string> ();
                }
                Graph[from].add (to);
            }
            return Graph;
        } catch (DatabaseError e) {
            stdout.printf (e.message);
            return null;
        }
    }
}