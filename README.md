# clock-of-knowlage-v2
This project is a network-connected clock built on an **ESP32** and a **GP1294AI 256×48 VFD display**.  
It keeps accurate time using NTP, shows Wi-Fi connection status, and displays both local and external temperature/humidity readings.

## Features
- Time synchronization via NTP (`pool.ntp.org`), with UK timezone and automatic daylight savings adjustment  
- Wi-Fi with auto-reconnect and backoff handling  
- External temperature and humidity fetched from the [Open-Meteo API](https://open-meteo.com/)  
- Local temperature and humidity from a DHT22 sensor (planned upgrade to a more accurate sensor)  
- UI made with [lopaka](https://lopaka.app) and rendered with the [U8g2](https://github.com/olikraus/u8g2) graphics library  
- Error handling and retry logic for NTP and weather fetches  

## Hardware
- ESP32 DevKit board  
- GP1294AI 256×48 Vacuum Fluorescent Display  
- DHT22 sensor (easily swappable for alternatives)  
- Standard jumpers and breadboards

## links
- ESP32 board: [Amazon](https://www.amazon.co.uk/dp/B0D8T5XD3P)
- VFD display: [AliExpress](https://www.aliexpress.com/item/1005004465805347.html)
- DHT22 sensor: [Amazon](https://www.amazon.co.uk/dp/B0DP3XJSXR)
- UI design: [lopaka](https://lopaka.app/gallery/16709/35604)

## Issues and bugs
1. currently no RTC, so it needs a wifi connection to sync and its not very accurate


## images
front display:
![IMG_20251028_153941955](https://github.com/user-attachments/assets/29ca95ea-50e6-4091-9005-27dc5d05cb18)
rear with wiring:
![IMG_20251028_153950273](https://github.com/user-attachments/assets/a1a52a12-4fe7-4d9a-bcfd-3b5f73ceea5f)
v2 on the right with its namesake on the left (not a brand, my parents bought it 20 years ago and named it that)
![IMG_20251028_160213568](https://github.com/user-attachments/assets/26a7bfe2-0278-4893-ad3e-7b4fe969e5b3)





if anyone has the knowlage or ability to make a 3d model for a case/housing for this project then please contact me, create an issue here or message me on discord at `minecrafter8001` and ill provide some messurements
