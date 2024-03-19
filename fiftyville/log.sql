-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get details of the theft of the CS50 duck
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = "Humphrey Street" LIMIT 1;
-- Get interviews taken at the time of the crime
SELECT transcript FROM interviews WHERE day = 28 AND month = 7;

-- Get details of the bakery security logs at the time of the crime
SELECT * FROM bakery_security_logs WHERE day = 28 AND activity  = "exit" AND hour = 10 AND minute >= 15 AND minute <= 25;
-- Get license plates of the people that exited the bakery parking lot at the time of the crime
SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND activity  = "exit" AND hour = 10 AND minute >= 15 AND minute <= 25;
-- Get the names of the owner of the license plates
SELECT name AS people_exited_bakery
    FROM people
        WHERE license_plate IN
            (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND activity  = "exit" AND hour = 10 AND minute >= 15 AND minute <= 25);

-- Get ATM withdraw records at the time of the crime
SELECT * FROM atm_transactions WHERE day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- Get account numbers of the people that withdrawed
SELECT account_number FROM atm_transactions WHERE day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- Get the person id's of the account numbers
SELECT bank.person_id
    FROM bank_accounts AS bank
        JOIN atm_transactions AS atm
        ON bank.account_number = atm.account_number
            WHERE atm.day = 28 AND atm.atm_location = "Leggett Street" AND atm.transaction_type = "withdraw";
-- Get the names of the account numbers
SELECT person.name
    FROM people AS person
        JOIN bank_accounts AS bank
        ON person.id = bank.person_id
            JOIN atm_transactions AS atm
            ON bank.account_number = atm.account_number
                WHERE atm.day = 28 AND atm.atm_location = "Leggett Street" AND atm.transaction_type = "withdraw";

-- Get the names of the people that both withdrawed from the ATM and exited the bakery parking lot at the time of the crime
-- Bruce, Diana, Iman, Luca
SELECT person.name AS suspects
    FROM people AS person
        JOIN bank_accounts AS bank
        ON person.id = bank.person_id

        JOIN bakery_security_logs AS bakery
        ON person.license_plate = bakery.license_plate

            JOIN atm_transactions AS atm
            ON bank.account_number = atm.account_number
                WHERE atm.day = 28 AND atm.atm_location = "Leggett Street" AND atm.transaction_type = "withdraw"
                      AND bakery.activity = "exit" AND bakery.hour = 10 AND bakery.minute >= 15 AND bakery.minute <= 25;

-- Get the name/passport number of the suspects that called someone for less than a minute at the day of the crime
-- Bruce, Diana
SELECT person.passport_number AS suspects
    FROM people AS person
        JOIN bank_accounts AS bank
        ON person.id = bank.person_id

        JOIN phone_calls
        ON phone_calls.caller = person.phone_number

        JOIN bakery_security_logs AS bakery
        ON person.license_plate = bakery.license_plate

            JOIN atm_transactions AS atm
            ON bank.account_number = atm.account_number
                WHERE atm.day = 28 AND atm.atm_location = "Leggett Street" AND atm.transaction_type = "withdraw"
                      AND bakery.activity = "exit" AND bakery.hour = 10 AND bakery.minute >= 15 AND bakery.minute <= 25
                      AND phone_calls.day = 28 AND phone_calls.duration < 60;

-- Get flight id of the earliest flight out of Fiftyville the day after the crime
SELECT id FROM flights WHERE day = 29 ORDER BY hour LIMIT 1;
-- Get the passenger list of the flight
SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 ORDER BY hour LIMIT 1);
-- Get the names of the passengers
SELECT people.name AS passenger
    FROM people
        JOIN passengers
        ON people.passport_number = passengers.passport_number
            WHERE passengers.flight_id =
            (SELECT id FROM flights WHERE day = 29 ORDER BY hour LIMIT 1);
-- Get the name of the suspects that were in the first flight
-- Bruce
SELECT name
    FROM people
        WHERE passport_number IN
        (SELECT person.passport_number AS suspects
            FROM people AS person
                JOIN bank_accounts AS bank
                ON person.id = bank.person_id

                JOIN phone_calls
                ON phone_calls.caller = person.phone_number

                JOIN bakery_security_logs AS bakery
                ON person.license_plate = bakery.license_plate

                    JOIN atm_transactions AS atm
                    ON bank.account_number = atm.account_number
                        WHERE atm.day = 28 AND atm.atm_location = "Leggett Street" AND atm.transaction_type = "withdraw"
                              AND bakery.activity = "exit" AND bakery.hour = 10 AND bakery.minute >= 15 AND bakery.minute <= 25
                              AND phone_calls.day = 28 AND phone_calls.duration < 60)

        AND passport_number IN
        (SELECT passport_number
            FROM passengers
                WHERE flight_id =
                    (SELECT id FROM flights WHERE day = 29 ORDER BY hour LIMIT 1));

-- Get the names of the people that the SUSPECTS called at the day of the crime (ACCOMPLICES)
-- Robin
SELECT name
    FROM people
        JOIN phone_calls
        ON people.phone_number = phone_calls.receiver

        WHERE phone_calls.duration < 60 AND phone_calls.day = 28 AND phone_calls.caller =
        (SELECT phone_number
            FROM people
                WHERE passport_number IN
                (SELECT person.passport_number AS suspects
                    FROM people AS person
                        JOIN bank_accounts AS bank
                        ON person.id = bank.person_id

                        JOIN phone_calls
                        ON phone_calls.caller = person.phone_number

                        JOIN bakery_security_logs AS bakery
                        ON person.license_plate = bakery.license_plate

                            JOIN atm_transactions AS atm
                            ON bank.account_number = atm.account_number
                                WHERE atm.day = 28 AND atm.atm_location = "Leggett Street" AND atm.transaction_type = "withdraw"
                                      AND bakery.activity = "exit" AND bakery.hour = 10 AND bakery.minute >= 15 AND bakery.minute <= 25
                                      AND phone_calls.day = 28 AND phone_calls.duration < 60)

        AND passport_number IN
        (SELECT passport_number
            FROM passengers
                WHERE flight_id =
                    (SELECT id FROM flights WHERE day = 29 ORDER BY hour LIMIT 1)));

-- Get the destination of the first flight
-- New York City
SELECT destination_airport_id FROM flights WHERE day = 29 ORDER BY hour LIMIT 1;
SELECT city FROM airports WHERE id =
    (SELECT destination_airport_id FROM flights WHERE day = 29 ORDER BY hour LIMIT 1);