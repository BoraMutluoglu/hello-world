import turtle
import random

#Create the board to play on
screen = turtle.Screen()
screen.screensize(600, 600)
screen.bgcolor("white")
screen.title("Turtle Feeder")

#Pen to write game over at end of program
finals = turtle.Turtle()
finals.penup()
finals.speed(0)
finals.setposition(-40, 20)
finals.color("white")
finals.hideturtle()

#this block of code draws the board border in which
#the turtle and enemies will be
pens = turtle.Turtle()
pens.speed(0)
pens.hideturtle()
pens.color('black')
pens.penup()
pens.setposition(-300, -300)
pens.pendown()
pens.forward(600)
for x in range(3):
    pens.left(90)
    pens.forward(600)

#number of enemies to create
nenemies = 5

#list that will contain the enemy objects
enemies = []

#for loop to append the enemy turtle objects to
#our aforedmentioned list
for x in range(nenemies):
    enemies.append(turtle.Turtle())

#this block of code creates enemies for the turtle
#within the enemy list
for bots in enemies:
    bots.shape("square")
    bots.color("blue")
    bots.speed(0)
    bots.penup()
    x = random.randint(-250, 250)
    y = random.randint(-250, 250)
    bots.setposition(x, y)

#this variable sets enemy speed
fspeed = 10

#Score variable
score = 0

#creates the pen that'll draw the score on the screen for the
#player to see, also writes the score to the screen
scoree = turtle.Turtle()
scoree.color("black")
scoree.penup()
scoree.speed(0)
scoree.setposition(-20, 280)
sstring = "Score: %s" %score
scoree.write(sstring, False, align="left", font=("Arial", 14, "normal"))
scoree.hideturtle()

#this block of code creates the turtle that player will
#control
attackbot = turtle.Turtle()
attackbot.shape("turtle")
attackbot.color("green")
attackbot.speed(0)
attackbot.penup()
attackbot.setposition(-300, 300)

#this variable is how many positions our turtle
#moves on one move(key press)
speed = 10

#function allows our turtle to move left and
#turn to face that way
def moveleft():
    move = attackbot.xcor()
    move -= speed
    if move < -290:
        move = -290
    attackbot.setx(move)
    attackbot.setheading(180)

#function allows our turtle to move right and
#turn to face that way
def moveright():
    move = attackbot.xcor()
    move += speed
    if move > 290:
        move = 290
    attackbot.setx(move)
    attackbot.setheading(0)

#function allows our turtle to move up and
#turn to face that way
def moveup():
#add docstring in eachf unction definition to explain what it does
    move = attackbot.ycor()
    move += speed
    if move > 290:
        move = 290
    attackbot.sety(move)
    attackbot.setheading(90)

#function allows our turtle to move down and
#turn to face that way
def movedown():
    move = attackbot.ycor()
    print("Is naice")
    move -= speed
    if move < -290:
        move = -290
    attackbot.sety(move)
    attackbot.setheading(270)

#binds keys to the functions created above
turtle.listen()
turtle.onkey(moveleft, "Left")
turtle.onkey(moveright, "Right")
turtle.onkey(moveup, "Up")
turtle.onkey(movedown, "Down")

#count variable to count how many times the enemies touch the
#borders, increments each time an enemy touches the border
count = 0
con = True

#while loop to run the game
while True:
    counter = 0
    for bots in enemies:
        move = bots.xcor()
        move += fspeed
        bots.setx(move)

#if an enemy touches a border send them the other way and increment
#the count variable by one
        if bots.xcor() > 290:
            bots.setposition(290, bots.ycor())
            fspeed *= -1
            count += 1
        if bots.xcor() < -290:
            bots.setposition(-290, bots.ycor())
            fspeed *= -1
            count += 1

#if you touch an enemy you eat him! add one to your score and the
#enemy respawns somewhere else on the map
        if attackbot.distance(bots) < 15:
            x = random.randint(-250, 250)
            y = random.randint(-250, 250)
            bots.setposition(x, y)
            counter += 1
            score += 1
            sstring = "Score: %s" %score
            scoree.clear()
            scoree.write(sstring, False, align="left", font=("Arial", 14, "normal"))
            speed += 1



#if the food touches the right and left side of the game
#a total of 30times the game ends
    if count >= 30:
        screen.clear()
        gameover = turtle.Screen()
        gameover.screensize(600, 600)
        gameover.bgcolor("black")
        gameover.title("Turtle Feeder")
        break;


#prints the game over and score messages for the game over screen
dones = "Game Over! "
finals.write(dones, False, align="left", font=("Arial", 20, "normal"))
finals.setposition(-40, -20)
finals.write(sstring, False, align="left", font=("Arial", 20, "normal"))

turtle.done()