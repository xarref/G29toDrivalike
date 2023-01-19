import pyvjoy # import the pyvjoy library
import serial # import the serial library

# Initialize vJoy device
vj = pyvjoy.VJoyDevice(1) # creates an instance of the VJoyDevice class, which allows us to interact with a virtual joystick. 
# The number '1' passed as argument specifies the device number.

# Open serial connection to Arduino
ser = serial.Serial('COM3', 9600) #opens a serial connection to the arduino, with a baudrate of 9600.
# The first argument is the serial port where the arduino is connected.

while True:
    # Get input data from the driving simulator
    x, y = vj.get_axis(pyvjoy.HID_USAGE_X), vj.get_axis(pyvjoy.HID_USAGE_Y)
    brake = vj.get_axis(pyvjoy.HID_USAGE_Z)
    gas = vj.get_axis(pyvjoy.HID_USAGE_RZ)
    clutch = vj.get_axis(pyvjoy.HID_USAGE_SL0)
    shifter_left = vj.get_button(pyvjoy.HID_USAGE_POV1_LEFT)
    shifter_right = vj.get_button(pyvjoy.HID_USAGE_POV1_RIGHT)
    button_1 = vj.get_button(pyvjoy.HID_USAGE_BUTTON1)
    button_2 = vj.get_button(pyvjoy.HID_USAGE_BUTTON2)
    button_3 = vj.get_button(pyvjoy.HID_USAGE_BUTTON3)
    button_4 = vj.get_button(pyvjoy.HID_USAGE_BUTTON4)
    button_5 = vj.get_button(pyvjoy.HID_USAGE_BUTTON5)
    button_6 = vj.get_button(pyvjoy.HID_USAGE_BUTTON6)
    button_7 = vj.get_button(pyvjoy.HID_USAGE_BUTTON7)
    button_8 = vj.get_button(pyvjoy.HID_USAGE_BUTTON8)
    button_9 = vj.get_button(pyvjoy.HID_USAGE_BUTTON9)
    button_10 = vj.get_button(pyvjoy.HID_USAGE_BUTTON10)
    # get_axis() is a method of VJoyDevice class. It takes an argument which is the axis that we want to read.
    # The get_button() is also a method of VJoyDevice class, that takes an argument which is the button that we want to read.
    # We are reading the X, Y, Z, RZ, SL0 axes, the POV1_LEFT and POV1_RIGHT buttons, and the BUTTON1 to BUTTON10 buttons.
    # The values are being assigned to the variables x, y, brake, gas, clutch, shifter_left, shifter_right, button_1 to button_10 respectively

    # Format the data as a compact string
    data = "X:{}Y:{}B:{}G:{}C:{}S_L:{}S_R:{}B1:{}B2:{}B3:{}B4:{}B5:{}B6:{}B7:{}B8:{}B9:{}B10:{}".format(x, y, brake, gas, clutch, shifter_left, shifter_right, button_1, button_2, button_3, button_4, button_5, button_6, button_7, button_8, button_9, button_10)
    # The data is being formatted as a string with the values of all the variables.
    # The curly braces {} are placeholders for the values that we want to insert.
    # In this case we are inserting the values of all the variables.
    # This will give a string like "X:100Y:200B:50G:90C:1S_L:0S_R:1B1:1B2:0B3:1B4:0B5:1B6:0B7:1B8:0B9:1B10:0"

    # Send the data to the Arduino
    ser.write(data.encode())
    # The data is being sent to the arduino using the write() method of the serial object.
    # The data is being encoded so that it can be sent over the serial connection.

    # Print the data to the terminal
    print("Data sent: {}".format(data))
    # Printing the data that we sent to the arduino to the terminal, so that we can check the data.
    # The curly braces {} are placeholders for the values that we want to insert.
    # In this case we are inserting the value of data variable.
