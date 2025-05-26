from tkinter import *
import threading
import queue
import random, time

class ThreadGUI(Canvas): #граф компонент для рисования овалов
    def __init__(self, parent = None):
        Canvas.__init__(self, parent)
        self.dataQueue = queue.Queue() #получаем ссылку на очередь
        self.consumer() #вызываем метод-потребитель, чтобы сразу при создании компоненета читать из очереди

    def producer(self, color): #производитель - что делает наш поток
        for i in range(10):
            time.sleep(2) # усыпляем на 2 секунды
            self.dataQueue.put(color, True) #блокирующая запись

    def consumer(self): #потребитель
        try:
            color = self.dataQueue.get(False) #неблокирующее чтение
        except queue.Empty:
            pass
        else:
            self.create_oval(random.randint(1,20), random.randint(1,20),
                             random.randint(80,250), random.randint(80, 250),
                             outline = color, fill = color, width = 2)
        self.after(1000, self.consumer) #отложенный вызов

colors = ["red", "green", "blue", "cyan", "magenta", "yellow", "black", "white", "grey"]
i=0 #глобальный счетчик числа потоков

def makethreads(widget, counter): # здесь будем создавать потоки
    global i
    while i<counter:
        color = colors[i%len(colors)]
        threading.Thread(target = widget.producer, args = (color, )).start()
        print(i,"->", color)
        i+=1

#main
root = Tk()
widget = ThreadGUI(root)
widget.pack(side = TOP, expand = YES, fill=BOTH)

makethreads(widget, 5)

root.mainloop()