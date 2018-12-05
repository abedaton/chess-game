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

        
    def __repr__(self):
        return str(self.board)
    
    def __str__(self):
        #return self.__repr__()

        res = "["
        for l in range(len(self.board)):
            res += str(self.board[l])

            if l != len(self.board)-1:
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
    
    def move(self,str_coord,str_out):
        print(str_coord,str_out)
        colonne_in,ligne_in = self.decode(str_coord)
        colonne_out,ligne_out = self.decode(str_out)

        pe = self.board[ligne_in][colonne_in]
        
        if not isinstance(pe,int):
            set_pe = pe.algo(8)

            #col_res = colonne_in+colonne_out
            #lig_res = ligne_in+ligne_out
            col_res = colonne_out
            lig_res = ligne_out
            
            print((colonne_in,ligne_in),"-->",(colonne_out,ligne_out))
            print("res:",(col_res,lig_res))
            print("deplacements possibles:",set_pe)
            
            if (col_res,lig_res) in set_pe:
                print("OK!")
                pe.set_posi(col_res,lig_res)
                self.board[lig_res][col_res] = pe
                self.board[ligne_in][colonne_in] = 0
            else:
                print("PAS OK!")

class Abstractpiece(object):
    def __init__(self):
        self.depl = []
        self.posi = [0,0]
        state = False # indique si le pion a droit à 2 déplacements

    def __repr__(self):
        return "Abstractpiece()"
    
    def __str__(self):
        return self.__repr__()

    def set_posi(self,x,y):
        self.posi = [x,y]

    def update(self):
        nothing = True # ne fait rien

    def algo(self,limite=8):
        res = set({})
        for tup in self.depl:
            if len(tup) == 2:
                for k in range(-limite,limite+1):
                    res.add((self.posi[0] + tup[0]*k,self.posi[1] + tup[1]*k))
                    
            elif len(tup) >= 3:

                lim_inf = -(tup[2]+1)
                lim_sup = tup[2]+1

                if "+" in tup:
                    lim_inf = 0

                if "-" in tup:
                    lim_sup = 1

                print("limites:",lim_inf,lim_sup)
                
                for k in range(lim_inf,lim_sup):
                    res.add((self.posi[0] + tup[0]*k,self.posi[1] + tup[1]*k))
                    
                if "u" in tup:
                    self.update()

        return res
                
class Tour(Abstractpiece):
    def __init__(self):
        super(Tour, self).__init__()
        self.depl = [(0,1),(1,0)]

    def __repr__(self):
##        if self.posi == []:
##            res = "Tour()"
##        else:
##            res = f"Tour({self.posi[0]}_{self.posi[1]})"
##        return res
        return "T"

class Fous(Abstractpiece):
    def __init__(self):
        super(Fous, self).__init__()
        self.depl = [(1,1)]

    def __repr__(self):
        return "F"

class Pion(Abstractpiece):
    def __init__(self):
        super(Pion, self).__init__()
        self.depl = [(0,1,1,"+"),(0,1,2,"u","+")]

    def __repr__(self):
        return "P"

    def update(self):
        self.depl = [(0,1,1,"+")]
        print("update pion!")

def test_tour():
    plateau = Plateau()
    piece = Fous()
    
    print()
    print(piece)

    print()

    print(plateau)
    print()
    plateau.set_piece("A1",piece)
    print(plateau)
    print()
    plateau.move("A1","B2")
    print()
    print(plateau)
    print()
    plateau.move("A1","B1")
    print()
    print(plateau)
    print()
    plateau.move("B1","B2")
    print()
    print(plateau)

def test_fous():
    plateau = Plateau()
    piece = Tour()
    
    print()
    print(piece)

    print()

    print(plateau)
    print()
    plateau.set_piece("A1",piece)
    print(plateau)
    print()
    plateau.move("A1","B2")
    print()
    print(plateau)
    print()
    plateau.move("B2","C2")
    print()
    print(plateau)

def test_pion():
    plateau = Plateau()
    piece = Pion()
    
    print()
    print(piece)

    print()

    print(plateau)
    print()
    plateau.set_piece("D2",piece)
    print(plateau)
    print()
    plateau.move("D2","D4")
    print()
    print(plateau)
    print()
    plateau.move("D4","D6")
    print()
    print(plateau)
    print()
    plateau.move("D4","D5")
    print()
    print(plateau)
    print()
    plateau.move("D5","E5")
    print()
    print(plateau)


if __name__ == "__main__":
    
    test_tour()
    print("*****************************************")
    test_fous()
    print("*****************************************")
    test_pion()


