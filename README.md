# AD717x-AD411x-Arduino

This library supports the following boards:

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


# Run Examples

Currently, there's an example for the teensy4.1 in the project.

To write a program to the teensy4.1, configure the AD7177, and read data, execute the following command:

```
pio run -e AD7177-example -t upload
```

Implementation of examples for other boards is not currently planned.

If you've created an example, kindly send a Pull Request.

# Import

To use this project as a library, append the following line to the `platformio.ini` file in your project:

```
lib_deps = 
  https://github.com/sgrsn/AD717x-AD411x-Arduino.git
```
