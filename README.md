# IoTAssignment2  
Description:  
  
An IoT Thermometer will display the reading of the temperature on an LCD screen and  a web browser. This will be accomplished by utilizing the NodeMCU board by connecting it to the temperature and humidity sensor. This sensor will collect the temperature and humidity of the room, and we will program it to display that information on the LCD screen. The NodeMCU board will be powered via USB cable and will be programmed by using Arduino IDE. Appropriate libraries and tools will be used to program the sensor and LCD screen. The values will be shown in real-time and provide accurate results of the temperature and humidity in the room. The user can view previous temperature/humidity values on a web browser application along with the date and time recorded. The software used to collect and store the previous measurement by MySQL and Django python will be used to retrieve the data through Django REST API.   
  
How to download and run:  
  
1. clone repository:  
```bash
git clone https://github.com/raveen15/IoTAssignment2
```
2. ensure python, pipenv, and django are installed  
```bash
python --version
pipenv --version
django-admin --version
```  
  if you need to download pipenv or django, use:
```bash
pip install pipenv
pipenv install django
```  
3. run virtual environment, and then run app on desired port:  
```bash
pipenv shell
python manage.py runserver <port>
``` 

