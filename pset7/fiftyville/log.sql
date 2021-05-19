-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE description LIKE "%Chamberlin Street%";
SELECT * FROM interviews WHERE transcript LIKE "%courthouse%";
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour=10 AND activity = 'exit';
SELECT * FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year=2020 AND month=7 and day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw'));
SELECT * FROM flights WHERE year=2020 AND month=7 AND day=29 ORDER BY(hour) LIMIT 1;
SELECT * from passengers WHERE flight_id = 36;
SELECT full_name FROM airports WHERE id IN(SELECT destination_airport_id FROM flights WHERE id=36);
