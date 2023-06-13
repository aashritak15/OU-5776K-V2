pros:ADIDigitalOut pistionPTO1(pistonPTO1Port);
pros:ADIDigitalOut pistionPTO2(pistonPTO2Port);

void pistons(){
    if (controller[okapi::ControllerDigital::up].isPressed()){
        pistonPTO1.set_value(true);
        pros::delay(300);
        pistonPTO1.set_value(false);
    }
    if (controller[okapi::ControllerDigital::down].isPressed()){
        pistonPTO2.set_value(true);
        pros::delay(300);
        pistonPTO2.set_value(false);
    }
}