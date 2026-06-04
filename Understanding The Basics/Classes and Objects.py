
class Triangle:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c 
    
    def perim(self):
        perim = self.a + self.b + self.c 
        return perim
    
    def area(self):
        s = (1/2)*(self.a + self.b + self.c)
        area = (s*(s - self.a)*(s - self.b)*(s - self.c))**(1/2)
        return area

triangle1 = Triangle(2,4,5)
Perimiter = triangle1.perim()
print(Perimiter)
Area = triangle1.area()
print(Area)