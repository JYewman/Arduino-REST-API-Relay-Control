# Arduino REST API Relay Control

## About The Project

This software is a collection that makes up the SmartKit Project, for more information see the SmartKit Repo. This code allows the control of relays using a REST API using an Arduino and Ethernet Hat.

## Getting Started

This project is one in a collection of Repositories for the SmartKit project. All you need is an Arduino, Ethernet Hat and any relay that can be triggered from a minimum of 3.3v


## Usage

When you first run the project, the system will automatically generate a MAC address and store it in EEPROM, you can then use the API get device information and control/monitor the status of the connected relay(s)

### The API
This API has 1 POST route:
- /relayPin which takes the key "active" with "0" for off and "1" for on
And two GET routes
- /relayPin which get's the current relay state
- /getDeviceInfo which returns it's SmartKit device ID.

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


## License

This work is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
