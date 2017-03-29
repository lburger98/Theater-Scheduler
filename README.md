# Theater-Scheduler

### Installation 
Download the repository then in terminal cd into its directory.

Enter the command `make` in your terminal.

You're all set!

### Usage

Create a text file and enter your movie information in this format:

`Movie Title, Release Year, MPAA Rating, Run Time`

make sure there are no other commas in the title.

To create the schedule run the command 

`./Scheduler -monday < yourtextfile`

Substitute `yourtextfile` with the title of your input file and change the argument `-monday` to whichever day of the week you are scheduling.

### Design Choices
A large part of creating this program was parsing the input file. To do this, I first gathered the entire input into a string and then separated the string into tokens delimited by commas. The next challenge was to make the schedule. I thought about creating the schedules in a function, storing them, then printing them out at the end, but decided on creating the schedules as I went along looping through all of the tokens because it was simpler and more efficient. The way my program works now is it cycles through the tokens printing them out until it reaches a runtime. Then the program prints the time, creates the schedule, and then moves on to the next movie. The schedule is created by continuously subtracting the runtime from the closing time until it overlaps with the opening time, making sure to create round numbered start times and leaving time for cleaning. This method ended up working well.
