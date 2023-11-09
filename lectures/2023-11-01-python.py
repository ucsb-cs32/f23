#! /usr/bin/env python3

def adder(inc):
    increment = inc
    def f(value):
        return value + increment
    return f

def multer(scale):
    return lambda x: x * scale

add2 = adder(2)
print(add2(12))
print(adder(100)(7))

mult4 = multer(4)
print(mult4(7))
