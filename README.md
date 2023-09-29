# AD717x-AD411x-Arduino

It supports the following boards.

- AD411x series
  - AD4111
  - AD4112
  - AD4114
  - AD4115
  - AD4116

- AD717x series
  - AD7172
  - AD7173
  - AD7175
  - AD7176
  - AD7177


# Run examples

Currently there is an example with teensy4.1 in the project.

Running the following will write a program to teensy4.1 to configure the AD7177 and read data.

```
pio run -e AD7177-example -t upload
```

Implementation of examples for other boards is undecided. 

If you create a example, please send a Pull request.

# Import

To use this project as a library, add the following line to the platformio.ini file of your project.

```
lib_deps = 
  https://github.com/sgrsn/AD717x-AD411x-Arduino.git
```