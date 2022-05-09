@page commands User commands
@tableofcontents

# The UI works with the following commands:
(*They are displayed on startup in the console*)

@note all dates must be input in format D/M/Y
@note parameters with [] are mandatory and these with {} are optional

# Adding new reservation

> **reserve**: [Room number] [Accomodation date] [Departure date] {Guest name[;]} {Note}

# Free rooms on particular date

> **available**: [date]

# Free particular room

> **free**: [Room number]

# Create report about the usage of the rooms in particular period

> **report**: [From date] [To date]

# Suggest room for a group of guests and partcular period

> **request**: [minimal number of beds] [Accomodation date] [Departure date]

# Close a room for maintenance

> **maintenance**: [room number] [From date] [To date] [Note]

# See current state of all the rooms

> **rooms**:

# See when a room is free for certain number of days

> **plan**: [Room number] [Number of nights]