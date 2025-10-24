-- Fiftyville Mystery Investigation Log
-- Solving the CS50 duck theft case step by step

-- Initial facts:
-- - Crime date: July 28, 2021
-- - Location: Humphrey Street

-- First, let's explore the database structure
.tables
.schema 

-- Step 1: Find the crime scene report for July 28th on Humphrey Street
SELECT description 
FROM crime_scene_reports
WHERE day = 28 
    AND month = 'July' 
    AND street = 'Humphrey Street';

-- Result: Duck theft at 10:15am at bakery, 3 witnesses interviewed

-- Step 2: Get witness interviews mentioning the bakery
SELECT name, transcript 
FROM interviews 
WHERE day = 28 
    AND month = 7 
    AND transcript LIKE '%bakery%';

-- Key clues from witnesses:
-- • Car left bakery parking lot within 10 minutes of theft (10:15-10:25am)
-- • ATM withdrawal on Leggett Street earlier that morning  
-- • Phone call under 60 seconds about earliest flight next morning



-- Step 3: Cross-reference all evidence to identify the suspect
-- Using CTEs to organize our investigation into logical components

WITH bank_suspects AS (
    -- People who withdrew money from Leggett Street ATM on July 28
    SELECT DISTINCT pe.name
    FROM people pe
    JOIN bank_accounts ba ON pe.id = ba.person_id
    JOIN atm_transactions at ON ba.account_number = at.account_number
    WHERE at.year = 2021 
        AND at.month = 7 
        AND at.day = 28
        AND at.atm_location LIKE '%Leggett Street%'
        AND at.transaction_type = 'withdraw'
)
, phone_suspects AS (
    -- People who made calls under 60 seconds on July 28
    SELECT name
    FROM people
    WHERE phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2021 
            AND month = 7 
            AND day = 28
            AND duration < 60
    )
)
, car_suspects AS (
    -- People whose cars left bakery parking between 10:15-10:25am
    SELECT name
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021 
            AND month = 7 
            AND day = 28
            AND activity = 'exit'
            AND minute > 15 
            AND minute <= 25
    )
)
, flight_suspects AS (
    -- People on earliest flight out of Fiftyville on July 29
    SELECT name, fl.destination_airport_id
    FROM people pe
    JOIN passengers pa ON pe.passport_number = pa.passport_number
    JOIN flights fl ON pa.flight_id = fl.id
    WHERE fl.id = (
        SELECT id
        FROM flights
        WHERE year = 2021 
            AND month = 7 
            AND day = 29
            AND origin_airport_id = (
                SELECT id FROM airports WHERE city = 'Fiftyville'
            )
        ORDER BY hour, minute
        LIMIT 1
    )
)
, escape_destination AS (
    -- Find where the thief escaped to
    SELECT city, full_name
    FROM airports
    WHERE id = (
        SELECT destination_airport_id
        FROM flights
        WHERE id = (
            SELECT id
            FROM flights
            WHERE year = 2021 
                AND month = 7 
                AND day = 29
                AND origin_airport_id = (
                    SELECT id FROM airports WHERE city = 'Fiftyville'
                )
            ORDER BY hour, minute
            LIMIT 1
        )
    )
)
-- Final analysis: Find who appears in ALL evidence categories
SELECT 
    pe.name AS thief,
    pe.phone_number,
    ed.city AS escape_destination,
    receiver.name AS accomplice
FROM people pe
JOIN bank_suspects bs ON pe.name = bs.name
JOIN phone_suspects ps ON pe.name = ps.name  
JOIN car_suspects cs ON pe.name = cs.name
JOIN flight_suspects fs ON pe.name = fs.name
JOIN escape_destination ed ON fs.destination_airport_id = ed.id
JOIN phone_calls pc ON pe.phone_number = pc.caller
    AND pc.year = 2021 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60
JOIN people receiver ON pc.receiver = receiver.phone_number;
-- Investigation Summary:
-- The thief must appear in all four categories:
-- 1. Made ATM withdrawal on Leggett Street
-- 2. Made short phone call on July 28  
-- 3. Left bakery parking lot between 10:15-10:25am
-- 4. Took earliest flight out of Fiftyville on July 29

-- The query above identifies both the thief and their accomplice (call receiver)

