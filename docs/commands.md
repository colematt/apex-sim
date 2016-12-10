# User Interface commands

Once execution begins, a command prompt is offered, and the following commands can be used:

|Command            | Action |
|:-----------------:|--------|
| `i`               | Initialize the simulator state |
| `s <n>`           | Simulate _n_ number of cycles |
| `d all`           | Display the full simulator internal state |
| `d cpu`           | Display CPU stage contents |
| `d iq`            | Display IQ entries and status |
| `d map`           | Display Front rename table and back-end register alias table |
| `d mem <a1> <a2>` | Display memory from address _a1_ to _a2_ |
| `d rob`           | Display ROB contents |
| `d stats`         | Display Stats |
| `d urf`           | Display URF contents |
| `urf <n>`         | Set URF Size to _n_ physical registers |
| `q`               | Quit the simulator |
| `h`               | Display this help message |

If an unrecognized command is issued, the UI will print the unrecognized command and display the help message, as though the user had supplied `h` as a command. To protect its internal state, the simulator will not update its state until the user provides a valid command.
