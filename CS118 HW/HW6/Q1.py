import itertools

#Question seems to want us to hard-code their specific graph, so let's do that
class Vertex:
    def __init__(self, vertex):
        self.vertex = vertex
        self.adj = [] #Stores tuple with vertex object and distance

class Graph: #Not a full implementation, just what is needed for question
    def __init__(self):
        self.vertices = []
        
    def insert(self, vertex): #Expects string
        self.vertices.append(Vertex(vertex))
        
    def connect(self, vertex1, vertex2, dist=1): #Expects string
        vertex1 = self.search(vertex1)
        vertex2 = self.search(vertex2)
                
        vertex1.adj.append((vertex2,dist))
        vertex2.adj.append((vertex1,dist))
        
    def search(self,vertex): #Matches string name to actual Vertex object
        for i in self.vertices: 
            if (i.vertex == vertex):
                return i

#I mix around the vertex key and objects a lot here, this implementation is not at all well done
#Oh well, as long as it works for now, I can tweak it with hindsight some other time
def Dijkstra(graph, vertex1, vertex2): #Expects strings for vertices
    unvisited = [] #Sets would be more efficient but this is easier. Stores vertex key
    state = {} #Contains tuples with vertex object, distance, and prior vertex object
    for i in graph.vertices:
        unvisited.append(i.vertex)
        state[i.vertex] = (i, float('inf'), None)
    
    if (vertex1 not in unvisited) or (vertex2 not in unvisited): #Checks for valid input
        print("Invalid Vertices!")
        return
    
    state[vertex1] = (state[vertex1][0],0,state[vertex1][2]) #Initialize first vertex
    #[i[0] for i in state]
    
    while unvisited:
        #Find which to visit next
        min = float('inf')
        closest = None
        for i in unvisited:
            if state[i][1] < min:
                min = state[i][1]
                closest = state[i][0] #Stores vertex object
                
        for v in closest.adj: #adj has tuples with vertex object and distance
            if (v[1] + state[closest.vertex][1] < state[v[0].vertex][1]):
                state[v[0].vertex] = (state[v[0].vertex][0], v[1] + state[closest.vertex][1], closest)
                
        unvisited.remove(closest.vertex)
    
    path = [vertex2]
    if (state[vertex2][2] != None):
        prior = state[vertex2][2].vertex 
        while True:
            path = [prior] + path
            if (state[prior][2] != None):
                prior = state[prior][2].vertex
            else:
                break

    
    return path

#Now to hard-code in the graph
graph = Graph()
graph.insert("Idris")
graph.insert("Talia")
graph.insert("Ken")
graph.insert("Marco")
graph.insert("Sasha")
graph.insert("Lina")
graph.insert("Kamil")

graph.connect("Idris","Talia")
graph.connect("Talia","Ken")
graph.connect("Ken","Marco")
graph.connect("Marco","Sasha")
graph.connect("Sasha","Lina")
graph.connect("Lina","Kamil")
graph.connect("Kamil","Idris")

while True:
    print(f'Path = {Dijkstra(graph, input("Starting point: "), input("Ending Point: "))}\n')