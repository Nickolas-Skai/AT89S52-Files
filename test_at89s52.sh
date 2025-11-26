#!/bin/bash
# AT89S52 Testing Script
# Uploads ArduinoISP and runs AVRDUDE test

echo "=================================="
echo "AT89S52 Testing Script"
echo "=================================="
echo ""

# Check if Arduino is connected
if ! ls /dev/ttyUSB0 &> /dev/null; then
    echo "ERROR: Arduino not found on /dev/ttyUSB0"
    echo "Available ports:"
    ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null || echo "  None found"
    exit 1
fi

echo "Step 1: Uploading ArduinoISP sketch..."
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:uno AdruinoISP_AT89S52
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to upload ArduinoISP"
    exit 1
fi
echo "✓ ArduinoISP uploaded successfully"
echo ""

echo "Step 2: Waiting for Arduino to stabilize..."
sleep 2
echo ""

echo "Step 3: Running AVRDUDE to detect AT89S52..."
avrdude -C +at89s52.conf -c stk500v1 -p 89s52 -P /dev/ttyUSB0 -b 19200
AVRDUDE_EXIT=$?
echo ""

if [ $AVRDUDE_EXIT -eq 0 ]; then
    echo "=================================="
    echo "✓ SUCCESS: AT89S52 detected!"
    echo "=================================="
else
    echo "=================================="
    echo "✗ FAILED: AT89S52 not responding"
    echo "=================================="
    echo ""
    echo "Common issues:"
    echo "  - Crystal oscillator not running (check 12MHz crystal + 22pF caps)"
    echo "  - Wiring error (verify Pin 10→RST, 11→MOSI, 12→MISO, 13→SCK)"
    echo "  - Power issue (check 5V on Pin 40 and Pin 31 EA/VPP)"
    echo "  - Faulty chip (try different AT89S52)"
    echo ""
    echo "Run diagnostic: arduino-cli upload AT89S52_CompactDiag && arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=19200"
fi

exit $AVRDUDE_EXIT
