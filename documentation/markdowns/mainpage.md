@mainpage Hotel Project Documentation
@subpage commands
@tableofcontents

@section Overview

This is information system, serving a hotel. The system allows the user to make reservations, receive up-to-date information about the rooms in the hotel, make suggestion which room is most suitable for the guest. The program runs in console mode with several instructions, being printed on startup. The data for the rooms of the hotel is written in file named "h.rooms" in same directory as the executable. Then if data has already been recorded about the hotel (recognized by its name) the data is being read from a binary file called \"\<hotel name\>.dat\". On closing, the data about the hotel is being written again.

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