from machine import Pin, SPI
from xglcd_font import XglcdFont
import ili9341

spi     = SPI(0, baudrate=51200000, sck=Pin(18), mosi=Pin(19))
display = ili9341.Display(spi, dc=Pin(28), cs=Pin(17), rst=Pin(22))
font    = XglcdFont("fonts/Unispace12x24.py", 12, 24)

display.draw_text(10, 10, "Hello world!", font, ili9341.color565(255, 255, 0))
display.draw_circle(50, 70, 30, ili9341.color565(0, 255, 255))
display.fill_rectangle(100, 100, 80, 50, ili9341.color565(255, 0, 255))