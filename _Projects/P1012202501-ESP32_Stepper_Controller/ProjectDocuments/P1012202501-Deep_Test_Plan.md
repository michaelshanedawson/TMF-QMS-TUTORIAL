### Product Deep Test Test Plan

**Project:** ESP32 + DRV8825 Development Kit  
**Document ID:** P1012202501-Deep_Test_Plan.md
**Owner:** Project Design Lead  
**Version:** 1.0  
**Date:** 2025-12-28

---

### Purpose and Scope

**Purpose:** Define the testing requirements designed to validate the extreme operating conditions and safety features of the project assembly.
**Scope:** Applies to the ESP32 based DRV8825 stepper motor driver with RS-485 interface.

---

### Required Materials
* `P1012202501-01 Deep Test Plan Log.xlsx` file located in `/ProjectDocuments/test-logs/` to store the results of the testing process. Use 1 test plan log file per PCB serial number tested.
* Schematic and BOM for the device.
* Fully assembled device(s) for testing.
* Bench top power supply capable of current limiting with the ability to deliver up to 30V @ 5A.
* Multi-Meter capable of resistance, voltage, current and temperature reading.
* Infrared temperature gauge.
* Thermocouples and materials to affix them to the PCB.
* Basic hand tools such as screwdrivers.
* Computer system with USB connectors and software to program the ESP32.
* Appropriate USB-C cable with power and data to connect to the PCB assembly.
* Terminal emulator software on PC capable of communication over serial UART interfaces. An example would be PuTTY.
* USB to UART interface cable such as an RS-232 FTDI assembly.
* USB to RS-485 adapter and two small lengths of wire for interfacing to the RS-485.
* Assembled and tested momentary pushbutton for limit and control input testing.
* Click PLC `pn here` with testing program `P1012202501InputTest` installed.
* The Click PLC should have the `pn here` discreet input/output module installed and working.
* Appropriate 4 wire, bipolar stepper motor.
* Desktop thermometer capable of reading °C ambient temperature values.
* Hot air gun with temperature control.
* Oscilloscope with at least 2 channels.
* Proper functioning PPE.

---

### Prior to Testing
* Open a fresh copy of `P1012202501-01 Deep Test Plan Log.xlsx` and then save it as `P1012202501-01 Deep Test Plan Log xxxxxxx.xlsx` where xxxxxxx is the serial number of the board that the test log is associated with in the `\ProjectDocuments\test-logs\` folder. Ensure that the measurement equipment is recorded in the test plan log.

---

**For any test, note the reason for a fail condition and stop testing to investigate the issue and note any resolutions**

---

### Performance Requirements
* PR-001: With the bench top power supply output disabled, set the output voltage to 24VDC and the current limit to 3.5A. Connect the red positive output to CN1 Terminal 1 and the black negative output to CN1 Terminal 2 on the PCB assembly. `Connect the pre-wired motor driver loading assembly` to CN7. Enable the power supply output and flash the ESP32 with the `STEPPERCURRENT` firmware. Connect the USB to FTDI cable to J4 observing proper polarity. Load up PuTTY and open the appropriate COM port with the following settings, 115200 baud, 8 data bits, 1 stop bit, and no parity. Reset the PCB assembly by pressing and releasing the `ENABLE` button and the terminal console should display the following message: `P1012202501 Stepper Current Testing`. Place the multi-meter into current measuring mode and attach the probes to the correct input ports then connect the red positive lead to the #1 connection on the motor driver loading assembly and the black negative lead to the #2 connection on the motor driver loading assembly. In the terminal window, type in the command `start` and press enter. This will start the testing process and load down the motor driver IC. Observe the multi-meter for current measured. The driver IC should be able to deliver 2.5A of current to a motor. `Possibly observe for fault conditions?`. Once this test is completed, disable the power supply output and disconnect the `Connect the pre-wired motor driver loading assembly` from CN7.
* PR-002: Enable the power supply output and flash the ESP32 with the `PCBTESTRISE` firmware. Connect the `stepper motor test rig` to CN7 and CN3 as indicated by labels on the test rig. `add more here` Disable the power supply output and then disconnect the `stepper motor test rig` from the PCB assembly.
* PR-003: 3.3V loading and ripple test. With the power supply output disabled, connect the `3v power supply test unit` negative (black) lead to TP3 (GND) and the positive (red) lead to TP1 (3.3V). Connect the oscilloscope probe to the 3.3V connection and the probe ground clip to the GND connection on the test unit. Set the volts/division to 20mV and verify that it is configured for a 1x probe and DC coupling.
* PR-004: 5.0V loading and ripple test.

