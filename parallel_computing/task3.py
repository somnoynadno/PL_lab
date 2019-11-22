# -*- coding: utf-8 -*-
import random
import time
from threading import Thread
from PIL import Image

ITER_NUM = 10

class MyThread(Thread):
    def __init__(self, start, end):
        """Инициализация потока"""
        Thread.__init__(self)
        self.start = start
        self.end = end
    
    def run(self):
        """Запуск потока"""
        # print("Hello")
        # print(self.start, self.end)
        for y in range(self.start, self.end):
            for x in range(image.width):
                a = list(image.getpixel((x, y)))
                b = image2.getpixel((x, y))

                a[0] = (a[0] + b[0])//2
                a[1] = (a[1] + b[1])//2
                a[2] = (a[2] + b[2])//2

                image.putpixel((x,y), tuple(a))

def do_algo():
    for y in range(image.height):
        for x in range(image.width):
            a = list(image.getpixel((x, y)))
            b = image2.getpixel((x, y))

            a[0] = (a[0] + b[0])//2
            a[1] = (a[1] + b[1])//2
            a[2] = (a[2] + b[2])//2

            image.putpixel((x,y), tuple(a))
    
def create_threads():
    """
    Создаем группу потоков
    """
    for i in range(4):
        start = i*(image.height // 4)
        end = (i+1)*(image.height // 4)
        my_thread = MyThread(start, end)
        my_thread.run()
 

if __name__ == "__main__":
    start_time = time.time()
    for i in range(ITER_NUM):
        image = Image.open('img.bmp').convert("RGB")
        image2 = Image.open('img1.bmp').convert("RGB")
        do_algo()

        image.save('out.bmp')
    print("Algo ended")
    print("--- %s seconds ---" % (time.time() - start_time))

    start_time = time.time()
    for i in range(ITER_NUM):
        image = Image.open('img.bmp').convert("RGB")
        image2 = Image.open('img1.bmp').convert("RGB")
        create_threads()

        image.save('out1.bmp')
    print("Parallel algo ended")
    print("--- %s seconds ---" % (time.time() - start_time))

