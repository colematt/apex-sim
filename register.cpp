/* FILE INFORMATION
File:     register.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the Registers class, which simulates operation of a register file.
*/

Registers::Registers(){
  this->initialize();
}

//initialize the RF with all registers/flags set to zero
void Registers::initialize(){
  int r;
  std::string reg_name;

  //Set register values and valids
  for (r=0; r<=15; r++){
    reg_name = "R" + std::to_string(r);
    this.values[reg_name] = 0;
  }

  //Set flag values and valids
  this.values["Z"] = 0;
  this.valids["Z"] = true;
}

//display the contents of the registers/flags
void Registers::display(){
  for (auto it = reg_file.begin(); it != reg_file.end(); ++it) {
    std::cout << it->first << ": " << it->second << '\n';
  }
}
