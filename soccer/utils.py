""" Docstring:
Description: utils
Author: Henry Zhang
Date:May 09, 2019
"""

# module


# parameters


# classes
class Color(object):
  field = (20,165,20)
  line = (255,255,255)
  ball = (0, 0, 250)
  def __init__(self):
    pass


class Point2D(object):
  def __init__(self, x, y):
    self.x = x
    self.y = y

class Point3D(object):
  def __init__(self, x, y, z):
    self.x = x
    self.y = y
    self.z = z

class Line2D(object):
  def __init__(self, startx, starty, endx, endy):
    self.start = Point2D(startx, starty)
    self.end = Point2D(endx, endy)

class Circle2D(object):
  def __init__(self, centerx, centery, radius):
    self.x = centerx
    self.y = centery
    self.radius = radius

class Rect2D(object):
  def __init__(self, left, top, length, width):
    self.left = left
    self.top = top
    self.length = length
    self.width = width
  
  def bInBox(self, pos):
    if pos.x >= self.left and pos.x <= self.left + self.length and pos.y >= self.top and pos.y <= self.top + self.width:
      return True
    else:
      return False
# functions


# main
def main():
    pass

if __name__ == "__main__":
    main()