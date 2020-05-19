To process and add event data to the database:

(0. To wipe current database, delete from the build folder).
1. Place desired UDP data file into process_messages subfolder in the build.
2. Copy the desired file name into line 8 of <bumblebee/process_messages/main.cpp>.
3. Run <bumblebee/process_messages/main.cpp>.

To query into database:

1. Write in the desired paramaters (startDate, endDate, hiveNumber) into line 48 in <bumblebee/database/main.cpp>.
2. Run <bumblebee/database/main.cpp>.

Data files information:

First line: n, mu1, sd1, mu2, sd2

Where:

n = number of data points
mu1 = mean of morning peak
sd1 = standard deviation of morning peak
mu2 = mean of evening peak
sd2 = standard deviation of evening peak

Data is generated using two normal curves to represent activity peaks in the morning and evening (actually: truncated normal, which gives bounds so the points are always within the day). Data points have unit: minutes, and are all between 0 and 1440 (minutes in a 24hr day).