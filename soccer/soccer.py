""" Docstring:
Description: soccer
Author: Henry Zhang
Date:May 09, 2019
"""

# module
from matplotlib import pyplot as plt
from datetime import datetime
import pygame

from field import Field
from ball import Ball

# parameters


# classes
class Game(object):
  def __init__(self):
    self.bRunning = False
    self.field = Field()
    self.field.setPitch(pitchtype="standard")
    self.teams = []
    self.length = 10
    fieldCenter = self.field.getCenter()
    self.ball = Ball()
    self.ball.setPos(fieldCenter[0], fieldCenter[1],0)
  
  def start(self):
    tmp = datetime.now()
    startTime = tmp.minute * 60 + tmp.second
    timenow = datetime.now()
    endTime = timenow.minute * 60 + timenow.second
    self.bRunning = True
    while (self.bRunning and endTime - startTime < 10 ):
      self.loop()
      self.display()
      for event in pygame.event.get():
        if event.type == pygame.QUIT:
          self.bRunning = False
      timenow = datetime.now()
      endTime = timenow.minute * 60 + timenow.second
    
  def loop(self):
    pass

  def display(self):
    (width, height) = (int((self.field.boundary.length + 2*self.field.margin)*10), int((self.field.boundary.width+2*self.field.margin)*10))
    screen = pygame.display.set_mode((width, height))
    self.field.display(screen)
    self.ball.display(screen)
    pygame.display.update()


    

# functions


# main
def main():
  theSoccerGame = Game()
  theSoccerGame.start()

if __name__ == "__main__":
  main()