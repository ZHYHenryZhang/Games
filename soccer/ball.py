""" Docstring:
Description: ball
Author: Henry Zhang
Date:May 10, 2019
"""

# module
import pygame
from utils import Point3D, Color

# parameters


# classes
class Ball(object):
  def __init__(self):
    self.radius = 0.11 #m
    self.weight = 0.43 #kg
    self.pos = Point3D(0,0,0)
  
  def setPos(self,x,y,z):
    self.pos = Point3D(x,y,z)
  
  def display(self, screen):
    pygame.draw.circle(screen, Color.ball, (int(10*self.pos.x), int(10*self.pos.y)), int(20*self.radius), 1)

# functions


# main
def main():
  pass

if __name__ == "__main__":
  main()