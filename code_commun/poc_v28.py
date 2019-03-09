class Plateau(object):
    def __init__(self):
        self.board = [[0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0],
                      [0,0,0,0,0,0,0,0]]

        self.taille = len(self.board)

        
    def __repr__(self):
        return str(self.board)
    
    def __str__(self):
        #return self.__repr__()

        res = "["
        for l in range(len(self.board)-1,-1,-1):
            res += str(self.board[l])

            if l != 0:
                res += ",\n "
        res += "]"
        return res

    def decode(self,str_coord):
        alph = "ABCDEFGHIJKLMNPQRSTUVWXYZ"
        letter = str_coord[0]
        colonne = alph.index(letter)
        ligne = int(str_coord[1:])-1

        return (colonne,ligne) #x,y

    def set_piece(self,str_coord,piece):
        colonne,ligne = self.decode(str_coord)
        self.board[ligne][colonne] = piece
        piece.set_posi(colonne,ligne)
        piece.set_limit(self.taille)
    
    def move(self,str_coord,str_out):
        print(str_coord,str_out)
        colonne_in,ligne_in = self.decode(str_coord)
        colonne_out,ligne_out = self.decode(str_out)

        pe = self.board[ligne_in][colonne_in]

        moved = False
        if not isinstance(pe,int):
            set_pe = pe.algo()
            
            print((colonne_in,ligne_in),"-->",(colonne_out,ligne_out))
            print("deplacements possibles:",set_pe)
            
            if (colonne_out,ligne_out) in set_pe:
                pe.set_posi(colonne_out,ligne_out)
                self.board[ligne_out][colonne_out] = pe
                self.board[ligne_in][colonne_in] = 0
                moved = True

        return moved

class Abstractpiece(object):
    def __init__(self):
        self.posi = Posi()
        state = False # indique si le pion a droit à 2 déplacements
        self.limit = 0
        self.liste = []
        self.depl = Decoder(self)
        print(self.depl)

    def __repr__(self):
        return "Abstractpiece()"
    
    def __str__(self):
        return self.__repr__()

    def set_posi(self,x,y):
        self.posi.set_x(x)
        self.posi.set_y(y)
        self.depl.maj(self)

    def get_posi(self):
        return self.posi

    def get_liste(self):
        return self.liste

    def set_limit(self,limit):
        self.limit = limit
        self.depl.maj(self)

    def get_limit(self):
        return self.limit

    def update(self):
        nothing = True # ne fait rien

    def algo(self):
        return self.depl.decode()
        
                
class Tour(Abstractpiece):
    def __init__(self):
        super(Tour, self).__init__()
        #self.liste = [(0,1),(1,0)]
        self.liste = [Struct(0,1),Struct(1,0)]
        self.depl.maj(self)

    def __repr__(self):
##        if self.posi == []:
##            res = "Tour()"
##        else:
##            res = f"Tour({self.posi.get_x()}_{self.posi.get_y()})"
##        return res
        return "T"

class Fous(Abstractpiece):
    def __init__(self):
        super(Fous, self).__init__()
        #self.liste = [(1,1)]
        self.liste = [Struct(1,1),Struct(-1,1)]
        self.depl.maj(self)

    def __repr__(self):
        return "Fou"

class Pion(Abstractpiece):
    def __init__(self):
        super(Pion, self).__init__()
        #self.liste = [(0,1,1,"+"),(0,1,2,"u","+")]
        a = Struct(0,1,[0,1,1])
        self.a = a
        b = Struct(0,1,[0,2,1],True)
        self.liste = [a,b]
        self.depl.maj(self)

    def __repr__(self):
        return "P"

    def update(self):
        #self.liste = [(0,1,1,"+")]
        self.liste = [self.a]
        self.depl.maj(self)
        print("update pion!")

class Dame(Abstractpiece):
    def __init__(self):
        super(Dame, self).__init__()
        self.liste = [Struct(1,1),Struct(0,1),Struct(1,0)]
        self.depl.maj(self)

    def __repr__(self):
        return "D"

class Roi(Abstractpiece):
    def __init__(self):
        super(Roi, self).__init__()
        self.liste = [Struct(1,1,[-1,1,1]),Struct(0,1,[-1,1,1]),Struct(1,0,[-1,1,1])]
        self.depl.maj(self)

    def __repr__(self):
        return "R"

class Chevalier(Abstractpiece):
    def __init__(self):
        super(Chevalier, self).__init__()
        self.liste = [Struct(1,2,[-1,1,1]),Struct(2,1,[-1,1,1]),Struct(-2,1,[-1,1,1]),Struct(-1,2,[-1,1,1])]
        self.depl.maj(self)

    def __repr__(self):
        return "Che"

class Fonctionnaire(Abstractpiece):
    def __init__(self):
        super(Fonctionnaire, self).__init__()
        self.liste = [Struct(0,1,[5,None,"prime"]),Struct(1,0,[5,None,"prime"])]
        self.depl.maj(self)

    def __repr__(self):
        return "Fon"

class Garde(Abstractpiece):
    def __init__(self):
        super(Garde, self).__init__()
        self.liste = [Struct(1,1,[-1,1,1]),Struct(0,1,[-1,1,1]),Struct(1,0,[-1,1,1])]
        self.depl.maj(self)

    def __repr__(self):
        return "G"

class Faucon(Abstractpiece):
    def __init__(self):
        super(Faucon, self).__init__()
        self.liste = [Struct(1,1,[2,3,1]),Struct(-1,1,[2,3,1]),Struct(0,1,[2,3,1]),Struct(1,0,[2,3,1]), \
                      Struct(1,1,[-3,-2,1]),Struct(-1,1,[-3,-2,1]),Struct(0,1,[-3,-2,1]),Struct(1,0,[-3,-2,1])]
        self.depl.maj(self)

    def __repr__(self):
        return "Fa"

class Chancellier(Abstractpiece):
    def __init__(self):
        super(Chancellier, self).__init__()
        self.liste = [Struct(1,2,[-1,1,1]),Struct(2,1,[-1,1,1]),Struct(-2,1,[-1,1,1]),Struct(-1,2,[-1,1,1]), \
                      Struct(0,1),Struct(1,0)] # partie Chevalier \ partie Tour
        self.depl.maj(self)

    def __repr__(self):
        return "Cha"

class Posi(object):
    def __init__(self,x=0,y=0):
        self.x = x
        self.y = y

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        #return f"Posi({self.x},{self.y})"
        return "Posi({0},{1})".format(self.x,self.y)

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def set_x(self,x):
        self.x = x

    def set_y(self,y):
        self.y = y

    def __eq__(self,oth):
        return (self.get_x() == oth.get_x()) and (self.get_y() == oth.get_y())

class Struct(object):
    def __init__(self,x=0,y=0,interv_k=[None,None,1],update=False):
        # struct n'est pas une sorte de Posi car devra manipuler des Posi
        # et pas de __equal__ a definir (aucun sens pour struct
        self.x = x
        self.y = y

        #l'ancien k est sub-divisés en 2 parties:
        self.k_min,self.k_max,self.k_pas = interv_k
        if isinstance(self.k_pas,int) and self.k_pas <= 0:
            raise Exception("k_pas tjs strictement positif si entier donné!")
        #
        
        self.update_needed = update

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        #return f"Struct({self.x},{self.y},[{self.k_min},{self.k_max},{self.k_pas}],{self.update_needed})"
        return "Struct({0},{1},[{2},{3},{4}],{5})".format(self.x,self.y,self.k_min,self.k_max,self.k_pas,self.update_needed)

    def intel_min_max(self,val_one,val_two,case):
        if val_one != None and val_two != None:
            if case == "max":
                res = max(val_one,val_two)
                
            elif case == "min":
                res = min(val_one,val_two)

            else:
                raise Exception("PAS de case donné!")
            
        elif val_one == None and val_two != None:
            res = val_two
        
        elif val_one != None and val_two == None:
            res = val_one

        else:
            res = None

        return res

    def is_prime(self,n):
        if n > 9:
            res = True
            a = 2
            while (a < 9 and res == True):
                b = n%a
                if b == 0:
                    res = False
                    
                a+=1
            
        else:
            res = (n in [2,3,5,7])

        return res
            
    def get_res(self,limite,posi):
        px,py = posi.get_x(),posi.get_y()
        x,y = self.x,self.y

        #print("px,py",px,py)
        #print("x,y",x,y)

        k_min = self.intel_min_max(self.k_min,-limite,"max")
        k_max = self.intel_min_max(self.k_max,limite,"min")

        if isinstance(self.k_pas,int):
            vals_de_k = [ i for i in range(k_min,k_max+1,self.k_pas)]

        elif isinstance(self.k_pas,str):
            if self.k_pas == "prime":
                vals_de_k = []
                for i in range(k_min,k_max+1):
                    if self.is_prime(i):
                        vals_de_k.append(i)
            else:
                #raise Exception(f"Pas ({self.k_pas}) inconnu!")
                raise Exception("Pas ({0}) inconnu!".format(self.k_pas))

        #print("vals_de_k : ",vals_de_k)
        
        set_res = set({})
        for k in vals_de_k:
            res_x = x*k + px # x*k = position realtive, +px = transformation en concrètes
            res_y = y*k + py

            if res_x < limite and res_x >= 0 and res_y < limite and res_y >= 0: # positions concrètes
                if (res_x,res_y) != (px,py): # interdit de rester immobiler et de bouger en même temps
                    set_res.add((res_x,res_y))

        return set_res
        

        return set_res

class Decoder(object):
    def __init__(self,pe):
        self.maj(pe)
        
    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        #return f"Decoder({self.pe})"
        return "Decoder({0})".format(self.pe)

    def set_liste(self,liste):
        self.liste = liste

    def maj(self,pe):
        self.pe = pe
        self.liste = pe.get_liste()
        #self.used = 0
        self.limite = pe.get_limit()
        self.posi = pe.get_posi()

    def decode(self):
        print("decodage : ",self.liste)
        limite = self.limite
        updt = False
        res = set({})
        for tup in self.liste:
            res |= tup.get_res(limite,self.posi)
            if updt == False and tup.update_needed == True:
                updt = True

        if updt == True:
            self.pe.update()

        return res

class Tester(object):
    def __init__(self,nom,piece,posi_initial,actions):
        self.pe = piece
        self.name = nom
        self.plateau = Plateau()
        self.actions = actions
        self.posi_ini = posi_initial

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        #return f"Tester({self.name})"
        return "Tester({0})".format(self.name)

    def execute(self):

        print()
        print(self.name,":")
        print(self.pe)

        print()

        print(self.plateau)
        print()
        self.plateau.set_piece(self.posi_ini,self.pe)
        print(self.plateau)
        print()

        for action in self.actions:
            rep = self.plateau.move(action[0],action[1])

            if rep == True:
                print("MOUVEMENT : la piece se déplace!")

            else:
                print("IMMOBILE : pas de mouvement!")

            if action[2] != None:
                print("comportement attendu?",end=" ")
                if action[2] == rep:
                    print("OK!")
                else:
                    print("PAS OK!")
                
            print()
            print(self.plateau)
            print()

        print("\n********************************************************************************************************************\n")
        print()

if __name__ == "__main__":
    
    Tester("Tester Tour",Tour(),"A1",[("A1","B2",False),("A1","B1",True),("B1","B2",True)]).execute()

    Tester("Tester Fous",Fous(),"A1",[("A1","B2",True),("B2","C2",False),("B2","E5",True),("E5","F4",True)]).execute()

    Tester("Tester Pion",Pion(),"D2",[("D2","D4",True),("D4","D6",False),("D4","D5",True),("D5","E5",False)]).execute()

    Tester("Tester Dame",Dame(),"A1",[("A1","B2",True),("B2","B4",True),("B4","D4",True),("D4","B4",True)]).execute()

    Tester("Tester Roi",Roi(),"A1",[("A1","C3",False),("A1","B2",True),("B2","C2",True),("C2","C3",True)]).execute()

    Tester("Tester Chevalier",Chevalier(),"D4",[("D4","E6",True),("E6","F4",True),("F4","F5",False),("F4","E4",False)]).execute()

    Tester("Tester Fonctionnaire",Fonctionnaire(),"B2",[("B2","B7",True),("B7","G7",True),("G7","C7",False),("G7","B2",False)]).execute()

    Tester("Tester Garde",Garde(),"A1",[("A1","C3",False),("A1","B2",True),("B2","C2",True),("C2","C3",True)]).execute()

    Tester("Tester Faucon",Faucon(),"B2",[("B2","B3",False),("B2","B4",True),("B4","B7",True),("B7","B2",False),("B7","C6",False),("B7","E4",True)]).execute()

    Tester("Tester Chancellier",Chancellier(),"D4",[("D4","E6",True),("E6","F4",True),("F4","F5",True),("F5","E5",True)]).execute()
    

    
    
    
