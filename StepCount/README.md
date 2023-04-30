# Pedometer

## Data Ingestion
- Verify that the ESP8266 is connected to the programmed hotspot using the command,  ```ip neigh```. This command gives us the ip addresses of all connected devices. Find the ip of the ESP8266.

- Using this ip and port `8888` as configured in the flashed ESP8266, we begin data transfer over a TCP/IP connection from the ESP8266 to our secondary compute device(in this case, to a file `logfile.txt` in the laptop)

```bash
nc <ip> 8888 > logs/logfile.txt
```

## Data Cleaning
At the start and the end of the data transfer, there could be some incomplete data. To prevent this from affecting our analysis, `logclean.sh` script is run on fresh data to remove the first and last line.

```bash
chmod +x logclean.sh
```

```bash
./logclean.sh -f logs/logfile.txt
```

## Data Pre-Processing, Activity Recognition and Step Counting
All these 3 aspects are taken care of in the `ActivityRecognition.ipynb` notebook by loading the newly created `logs/logfile.txt` into it.

**NOTE**
>At times, due to connectivity issues there is lots of missing data in between. In these cases, the step counting algorithm may make miscalculations.