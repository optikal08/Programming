from tkinter import *

runMotion = False
runAll = True
grabbed = False
getData = False


def StartStop():
    global runMotion
    runMotion = not runMotion
    if runMotion:
        startBtn['text'] = "Stop"
    else:
        startBtn['text'] = "Restart"
    
def StopAll():
    global runAll
    runAll = False

def GrabBall(event):
    global grabbed, runMotion, x, y, rad
    if not runMotion:
        grabbed = ((x - event.x)**2 + (y - event.y)**2) < rad**2
        
def ReleaseBall(event):
    global grabbed
    grabbed = False
    
def DragBall(event):
    global grabbed, x, y
    if grabbed:
        x = event.x
        y = event.y
        
def ReadData(*arg):
    global getData
    getData = True
    

root = Tk()
root.title("Шарик и GUI")
root.bind('<Return>', ReadData)

cw = 800
ch = 640
cnv = Canvas(root, width = cw, height = ch, background = "white")
cnv.grid(row=1, column = 0)

cnv.bind('<Button-1>', GrabBall)
cnv.bind('<B1-Motion>', DragBall)
cnv.bind('<ButtonRelease-1>', ReleaseBall)

toolbar = Frame(root)
toolbar.grid(row = 0, column = 0, sticky = N)

startBtn = Button(toolbar, text="Start", command = StartStop)
startBtn.grid(row = 0, column = 0)
closeBtn = Button(toolbar, text= "Close", command = StopAll)
closeBtn.grid(row=0, column = 1)

radiusLbl = Label(toolbar, text="Radius")
radiusLbl.grid(row = 1, column = 0)
radiusEnt = Entry(toolbar, bd = 5, width = 8)
radiusEnt.grid(row = 1, column = 1)
accelLbl = Label(toolbar, text="Ay")
accelLbl.grid(row = 2, column = 0)
accelEnt = Entry(toolbar, bd = 5, width = 8)
accelEnt.grid(row = 2, column = 1)

rad = 35
color = 'red'
x = rad
y = ch - rad
vx = 4.0
vy = -7.5
ay = 0.1

radiusEnt.insert(0, '{:.2f}'.format(rad))
accelEnt.insert(0, '{:.2f}'.format(ay))

delay = 20

while runAll:
    cnv.delete(ALL)
    cnv.create_oval(x-rad, y-rad, x+rad, y+rad, fill=color)
    cnv.update()
    
    if runMotion:
        if (x+rad) >= cw:
            vx = -abs(vx)
        elif (y+rad) >= ch:
            vy = -abs(vy)
        elif x <= rad:
            vx = abs(vx)
        elif y <= rad:
            vy = abs(vy)
    
        x += vx
        y += vy + 0.5 * ay
        vy += ay
        
    elif getData:
        try:
            rad = float(radiusEnt.get())
        except ValueError:
            pass
        try:
            ay = float(accelEnt.get())
        except ValueError:
            pass
        
        radiusEnt.delete(0, 'end')
        radiusEnt.insert(0, '{:.2f}'.format(rad))
        accelEnt.delete(0, 'end')
        accelEnt.insert(0, '{:.2f}'.format(ay))
        getData = False
    
    cnv.after(delay)

root.destroy()