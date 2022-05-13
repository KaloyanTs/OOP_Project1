@mainpage Hotel Project Documentation
@subpage Commands <br>
@subpage Bibliography
@tableofcontents

@section Overview

This is information system serving a hotel. The system allows the user to make reservations, receive up-to-date information about the rooms in the hotel, make suggestion which room is most suitable for the guest. The program runs in console mode with several instructions, being printed on startup. The data for the rooms of the hotel is written in file named "h.rooms" in same directory as the executable. Then if data has already been recorded about the hotel (recognized by its name) the data is being read from a binary file called \"\<hotel name\>.dat\". On closing, the data about the hotel is being written again.

@section Achitecture

The main class is Hotel, having name, static date keeping track of today's date and a hotel building. The hotel building is a list of rooms, each of which has unique ID and number of beds as long as lists of reservations in future and past. The reservation is object having strings for the reserver's name, a note and period of reservation. The state of a reservation is determined through the hotel's today date. On a new day the data is updated and reservations from the future list that are expired are moved to the past reservations list.

@subsection cl Supporting classes

I developed several classes to ease the work with the main classes.

* **String** - dynamic string used for the name of the hotel and name of guest and note in a reservation;
* **Date** - class consisting of day, month and year. Used widely in the project to know how the reservations are positioned in time relative to today's date (for the hotel). For these purposes many operators are overloaded;
* **RoomAnalyzer** - utility class, knowing algorithms to be performed on rooms for some results (sorting them or finding best one by criteria);
* **HotelInterface** - utility class, taking care of the UI of the console program. Can show the user available commands.

@subsection Example

>  **reserve: 102 15/7/2022 22/7/2022 Ivan; has dog** 
> > Reservation successfully made!

>  **rooms:** 
> > 101: No reservations.<br>
> > 102: Next reservation is from 15/7/2022 to 22/7/2022.  (*answer depends on current date*)<br>
> > 103: No reservations.<br>
> > ...

>  **report: 1/3/2022 1/4/2022**
> > report "report-2022-03-01.txt" created successfully.

>  **free: 101** 
> > Room is already free!

>  **free: 102** 
> > Room freed successfully!  (*answer depends on current date*) 

>  **request: 4 1/8/2022 7/8/2022** 
> > 1. Number: \<*best room*\> Beds: \<*best room's beds*\> : <available | NOT available> between 1/8/2022 and 7/8/2022 <br>
> > 2. Number: \<*second best room*\> Beds: \<*second best room's beds*\> : <available | NOT available> between 1/8/2022 and 7/8/2022 <br>
> > 3. Number: \<*third best room*\> Beds: \<*third best room's beds*\> : <available | NOT available> between 1/8/2022 and 7/8/2022 <br>
> > 4. Number: \<*fourth best room*\> Beds: \<*fourth best room's beds*\> : <available | NOT available> between 1/8/2022 and 7/8/2022 <br>
> > 5. Number: \<*fifth best room*\> Beds: \<*fifth best room's beds*\> : <available | NOT available> between 1/8/2022 and 7/8/2022 <br>

> **maintenance: 103 \<today\> 20/8/2022 cleaning** 
> > Maintenance planned successfully.<br>
> > > **rooms:** 
> > > > ...
> > > > <br> 103: Next maintenance is from \<today\> to 20/8/2022.<br>
> > > > ...