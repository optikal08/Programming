from tkinter import *
root = Tk() # явно создать корневое окно

pict=Frame(root)
manage=Frame(root)

pict.pack(side=LEFT)
manage.pack(side=RIGHT)

#----------------- Место под рисунок ------------------------------------

canvas=Canvas(pict, width=400, height=400)
canvas.create_rectangle(0,0, 400,
                    400, outline='#fff', fill = '#fff')
canvas.pack(fill=BOTH, expand=1)

#-------------------Добавим всякие кнопки--------------------------------

rdVar=IntVar()
rdVar.set(0)

rad0 = Radiobutton(manage,text="Кривая Коха",
          variable=rdVar,value=0)
rad1 = Radiobutton(manage,text="Салфетка Серпинского",
          variable=rdVar,value=1)
rad2 = Radiobutton(manage,text="Драконова ломаная",
          variable=rdVar,value=2)

rad0.pack(side=TOP, anchor=W)
rad1.pack(side=TOP, anchor=W)
rad2.pack(side=TOP, anchor=W)

myColor="#000"
from tkinter.colorchooser import askcolor
def setColor(event):
    global myColor
    (RGB, myColor)=askcolor()

butColor=Button(manage, text="Цвет")
butColor.bind('<Button-1>', setColor)
butColor.pack()

myPenWidth=IntVar()
myPenWidth.set(1)

penWidth = Scale(manage, label="Толщина линии", orient=HORIZONTAL, length=150,
             from_=1, to=10, tickinterval=1, resolution=1, variable=myPenWidth)

myCurvePower=IntVar()
myCurvePower.set(0)

curvePower = Scale(manage, label="Порядок кривой", orient=HORIZONTAL, length=150,
             from_=0, to=20, tickinterval=5, resolution=1, variable=myCurvePower)

penWidth.pack()
curvePower.pack()

#------------------------Собственно функция для прорисовки кривой Коха--------------------------
import math
def Koch(order, x1, y1, x2, y2):
    if (order==0):
        canvas.create_line(x1,y1,x2,y2,fill=myColor, width=myPenWidth.get())
    else:
        alpha=math.atan2(y2-y1, x2-x1)
        R=math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))
        # вычислим xA, yA, xB, yB, xC, yC
        xA=x1+(R/3)*math.cos(alpha)
        yA=y1+(R/3)*math.sin(alpha)
        xC=xA+R*math.cos(alpha-math.pi/3)/3
        yC=yA+R*math.sin(alpha-math.pi/3)/3
        xB=x1+2*R*math.cos(alpha)/3
        yB=y1+2*R*math.sin(alpha)/3

        #рекурсивные вызовы
        Koch(order-1, x1, y1, xA, yA)
        Koch(order-1, xA, yA, xC, yC)
        Koch(order-1, xC, yC, xB, yB)
        Koch(order-1, xB, yB, x2, y2)

#------------------ обработчик события для клика по кнопке "Рисовать"---------------------------------------
def draw(event):
    if (rdVar.get()==0): # кривая Коха
        x1=0
        y1=canvas.winfo_height()
        x2=canvas.winfo_width()
        y2=0
        # рекурсия для Коха
        Koch(myCurvePower.get(),x1, y1, x2, y2)
    elif (rdVar.get()==1):
        #рекурсия для Серпинского
        pass
    else:
        #рекурсия для драконовой ломаной
        pass

butDraw=Button(manage, text="Рисовать", width=12)
butDraw.bind("<Button-1>", draw)
butDraw.pack()

def clear(event):
    canvas.create_rectangle(0, 0, canvas.winfo_width(), canvas.winfo_height(), outline='#fff', fill='#fff')

butClear=Button(manage, text="Стереть", width=12)
butClear.bind("<Button-1>", clear)
butClear.pack()

root.mainloop()
