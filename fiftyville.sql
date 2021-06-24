-- Keep a log of any SQL queries you execute as you solve the mystery.
select * from crime_scene_reports
where year =2020
and month = 7
and street ="Chamberlin Street"
and description like "%duck%";
select  * from interviews where year =2020 and month=7 and day =28 and transcript like "%courthouse%";
select city from airports
where id =(select  destination_airport_id from flights where year =2020 and month =7 and day =29 order by hour  limit 1);
select name,passport_number , license_plate,person_id,phone_number from atm_transactions,bank_accounts,people
where year=2020 and month =7 and day =28 and atm_location="Fifer Street"
and atm_transactions.account_number=bank_accounts.account_number
and people.id=bank_accounts.person_id
and license_plate in (select license_plate from courthouse_security_logs where  year =2020 and month =7 and day = 28 and hour=10 and minute<25 and activity ="exit")
and passport_number in
(select passport_number from passengers where flight_id=
(select  id from flights where year =2020 and month =7 and day =29 order by hour  limit 1));

select name
from people
where phone_number=
(select receiver from phone_calls where year =2020 and month =7 and day = 28 and duration<60 and caller in ("(367) 555-5533","(389) 555-5198"));