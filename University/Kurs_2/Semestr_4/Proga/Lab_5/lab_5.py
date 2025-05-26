# 13.Установите на форму кнопку и список. Выбранное значение из списка
# должно отображаться на кнопке. Щелчок по кнопке запускает бегущую
# строку на кнопке. Повторный щелчок останавливает бегущую строку.
# Бегущая строка должна менять цвет в процессе своего движения.

from tkinter import *

root = Tk()


def but_command(event):
    global running, animation_id
    if running:
        # Остановить бегущую строку
        if animation_id:
            root.after_cancel(animation_id)
            animation_id = None
        running = False
        but.config(fg="black")  # вернуть цвет по умолчанию
    else:
        # Запустить бегущую строку
        running = True
        Runing_String()

but_text = StringVar()
but_text.set("Выберете значение")

colors = ["red", "green", "blue", "orange", "purple", "cyan"]

# Состояния бегущей строки
running = False
animation_id = None
color_index = 0
text_position = 0

def Runing_String():
    global running, animation_id, color_index, text_position
    text = but_text.get()
    if len(text) > 0:
        # Создаем бегущую строку с циклическим сдвигом текста
        shifted_text = text[text_position:] + " " + text[:text_position]
        but_text.set(shifted_text)
        # Меняем цвет текста кнопки
        but.config(fg=colors[color_index % len(colors)])
        color_index += 1
        text_position = (text_position + 1) % len(text)
        # Запускаем следующий шаг анимации
        animation_id = root.after(200, Runing_String)


def change():
    # print(var.get())
    selected_value = var.get()
    if selected_value == 0:
        but_text.set("Первая")
    elif selected_value == 1:
        but_text.set("Вторая")
    elif selected_value == 2:
        but_text.set("Третья")
        
    global text_position
    text_position = 0



but = Button(root, textvariable=but_text, font=("Arial", 16))
but.bind("<Button-1>", but_command)
but.bind("<Button-2>", but_command)
but.pack()

var = IntVar()
var.set(1)

rad0 = Radiobutton(root, text="Первая", variable=var,value=0, command=change)
rad0.pack()

rad1 = Radiobutton(root,text="Вторая", variable=var,value=1, command=change)
rad1.pack()

rad2 = Radiobutton(root,text="Третья", variable=var,value=2, command=change)
rad2.pack()

root.mainloop()

