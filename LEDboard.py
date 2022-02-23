# Importing Libraries
import serial
import time
import requests
import json

# /dev/cu.usbserial-DJ00S6Z3
arduino = serial.Serial(port='/dev/cu.usbserial-DJ00S6Z3', baudrate=115200, timeout=.1)

# Get an API key from https://openweathermap.org/
API_KEY = "aba237d2ab3bba2d675a6f5788455ec7"

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


def loop():
    while True:
        city = input("Enter a city: ") # Taking input from user
        url = "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s" % (city, API_KEY)
        # value = write_read(num)
        response = requests.get(url)
        data = json.loads(response.text)
        if data["cod"] != "404":
            kelvin = data["main"]["temp"]
            degreees = (kelvin - 273.15) * (9/5) + 32 

            print(int(degreees))
            arduino.write(bytes(str(degreees), 'utf-8'))
        else:
            print("Did not recognize that city. Try again.")

loop()