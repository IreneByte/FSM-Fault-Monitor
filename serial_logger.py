import serial
import csv
from datetime import datetime

with serial.Serial() as ser:
    ser.baudrate = 9600
    ser.port = 'COM3'
    ser.open()

    now = datetime.now()
    filename = f"state_log_{now.strftime('%Y%m%d_%H%M%S')}.csv"

    with open(filename, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)

        csvwriter.writerow(['timestamp', 'event'])
        csvfile.flush()

        try:
            while True:
                line = ser.readline().decode('utf-8').strip()
                if line:
                    data = line.split('] ')
                    data[0] = data[0].replace('[', '')
                    data[1] = data[1].replace('STATE: ', '')
                    print(line)
                    csvwriter.writerow(data)
                    csvfile.flush()
        except KeyboardInterrupt:
            print("Logging stopped.")
        except serial.SerialException:
            print("Arduino disconnected.")
        except Exception as e:
            print(f"Unexpected error: {e}")