# Wireless_daq
Objective of this project is to display live and previous data coming from the car into a easy to read dashboard. Details can be found [here](https://docs.google.com/document/d/18gZup02152-K4iaZI4rB0X_Kg-WA4hyAULKxzAbv10M/edit)

# Tech
For the client we are using [Qt 5.15.1](https://www.qt.io/download-open-source)
For the mock server we are using Node.js with a TCP connection

# Running the project
1. Install Qt 5.15.1
2. Clone the repository
3. Run the Qt Creator IDE
4. File -> Open File or Project -> *select repo*
5. Go into the 'mock-server' directory and run the command ```node mock-server.js ```
6. In the bottom left side of the IDE, press the green play button to build / run the project
