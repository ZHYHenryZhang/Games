""" Docstring:
Description: field
Author: Henry Zhang
Date:May 09, 2019
"""

# module
import pygame

from utils import Color, Point2D, Line2D, Rect2D, Circle2D

# parameters


# classes


class Goal(object):
  def __init__(self):
    self.width = 7.32
    self.height = 2.44
    self.leftPoint = Point2D(0,0)
    self.rightPoint = Point2D(0,0)
    self.team = None
    
  
  def setPos(self, leftx, lefty, rightx, righty):
    self.leftPoint.x = leftx
    self.leftPoint.y = lefty
    self.rightPoint.x = rightx
    self.rightPoint.y = righty

class Field(object):
  def __init__(self):
    self.margin = 3.0
    self.boundary = Rect2D(self.margin, self.margin, 105, 68)
    self.penaltyAreas = []
    self.goalAreas = []
    self.centreCircle = None
    self.material = "grass"
    self.goals = []
    self.middleLine = Line2D(self.margin + self.boundary.length/2, self.margin, self.margin + self.boundary.length/2, self.margin + self.boundary.width)

  def setSize(self, length, width):
    self.boundary.length = length
    self.boundary.width = width
  
  def setPitch(self, pitchtype = "standard"):
    if "standard" == pitchtype:
      self.setGoals(pitchtype)
      self.setCentreCircle()
      self.setGoalAreas()
      self.setPenaltyAreas()
  
  def setGoalAreas(self):
    self.goalAreas.append(Rect2D(self.margin, self.boundary.width/2 + self.margin - 40.3/2, 16.5, 40.3))
    self.goalAreas.append(Rect2D(self.margin + self.boundary.length - 16.5, self.boundary.width/2 + self.margin - 40.3/2, 16.5, 40.3))
  
  def setPenaltyAreas(self):
    self.penaltyAreas.append(Rect2D(self.margin, self.boundary.width/2 + self.margin - 18.3/2, 5.5, 18.3))
    self.penaltyAreas.append(Rect2D(self.margin + self.boundary.length - 5.5, self.boundary.width/2 + self.margin - 18.3/2, 5.5, 18.3))

  def setCentreCircle(self):
    theCenter = self.getCenter()
    self.centreCircle = Circle2D(theCenter[0], theCenter[1], 9)
  
  def setGoals(self, goaltype = "standard"):
    if "standard" == goaltype:
      theFirstGoal = Goal()
      theFirstGoal.setPos(self.margin, self.boundary.width/2 + self.margin - theFirstGoal.width/2, self.margin, self.boundary.width/2 + self.margin + theFirstGoal.width/2)
      self.goals.append(theFirstGoal)
      theSecondGoal = Goal()
      theSecondGoal.setPos(self.boundary.length+self.margin, self.boundary.width/2 + self.margin + theSecondGoal.width/2, self.boundary.length+self.margin, self.boundary.width/2 + self.margin - theSecondGoal.width/2)
      self.goals.append(theSecondGoal)
  
  def getCenter(self):
    return (self.boundary.length/2 + self.margin, self.boundary.width/2 + self.margin)
  
  def display(self, screen):
    pygame.display.set_caption('Soccer')
    background_colour = (20,165,20)
    screen.fill(background_colour)
    pygame.draw.circle(screen, Color.line, (int(10*(self.boundary.length/2 + self.margin)), int(10*(self.boundary.width/2 + self.margin))), 90, 1)
    for goal in self.goals:
      pygame.draw.line(screen, Color.line, (int(goal.leftPoint.x*10), int(goal.leftPoint.y*10)), (int(goal.rightPoint.x*10), int(goal.rightPoint.y*10)), 3)
    pygame.draw.rect(screen, Color.line, pygame.Rect(self.margin*10, self.margin*10, self.boundary.length*10, self.boundary.width*10), 1)
    pygame.draw.line(screen, Color.line, (int(10*self.middleLine.start.x), int(10*self.middleLine.start.y)), (int(10*self.middleLine.end.x),int(10*self.middleLine.end.y)))
    for goalArea in self.goalAreas:
      pygame.draw.rect(screen, Color.line, pygame.Rect(int(goalArea.left*10), int(goalArea.top*10), int(goalArea.length*10), int(goalArea.width*10)), 1)
    for penaltyArea in self.penaltyAreas:
      pygame.draw.rect(screen, Color.line, pygame.Rect(int(penaltyArea.left*10), int(penaltyArea.top*10), int(penaltyArea.length*10), int(penaltyArea.width*10)), 1)
    



# functions


# main
def main():
  pass

if __name__ == "__main__":
  main()