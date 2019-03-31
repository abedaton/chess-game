#!/usr/bin/python3
class Library():
    def __init__(self, name, version):
        self.name = name
        self.version = version
    def get_name(self):
        return self.name
    def get_version(self):
        return self.version
    

class LibraryTree():
    def __init__(self, root_library = "Application", root_library_version = 0):
        self.root = Library(root_library, root_library_version)
        self.childs = []
    
    def get_library(self):
        return self.root
    
    def get_children(self):
        return self.childs

    def insert_library(self, new_library_name, new_library_version, parent_library_name, parent_library_version): 
        if self.root.name == parent_library_name and self.root.version == parent_library_version:
            if self.childs == []:
                self.childs.append(LibraryTree(new_library_name,new_library_version))
            else:
                deja = False
                i = 0
                while i < len(self.childs) and not deja:
                    if self.childs[i].root.name == new_library_name and self.childs[i].root.version == new_library_version:
                        deja = True
                    i+=1
                if not deja:
                    self.childs.append(LibraryTree(new_library_name,new_library_version))
        else:
            if self.childs != []:
                for tree in self.childs:
                    tree.insert_library(new_library_name, new_library_version, parent_library_name, parent_library_version)
        
        return len(self.check_conflit(self)) != 0
            
    def __str__(self):
        return self.root.name + " -v" + str(self.root.version)
    
    def check_conflit(self, parent, liste_conf = [], version = 0):
        if version == 0:
            for tree in self.childs:
                if parent.root.name == tree.root.name and tree.root.version == parent.root.version and tree.root.name not in liste_conf:
                    liste_conf.append(tree.root.name)
                tree.check_conflit(self, liste_conf)
            return liste_conf
        else:
            liste_all = self.preorder()
            for elem in liste_all:
                for to_check in liste_all:
                    if elem[0] == to_check[0] and elem[1] != to_check[1] and elem[0] not in liste_conf:
                        liste_conf.append(elem[0])
            return liste_conf


    def get_version_conflict(self):
        return self.check_conflit(self, version = 1)


    def get_import_conflict(self):
        return self.check_conflit(self)

    
    def preorder(self, liste =[]):
        print(self)
        liste.append((self.root.name, self.root.version))
        if self.childs != []:
            for i in self.childs:
                i.preorder(liste)
        return liste

    def postorder(self, liste = []):
        if self.childs != []:
            for i in self.childs:
                i.postorder(liste)

        if self.root.name not in liste : 
            liste.append(self.root.get_name())
        print(self)
        return liste
        

    def clear_bro_conflicts(self):   
        if self.childs != []:
            i = 0
            while i < len(self.childs):
                j = 0
                while j < len(self.childs):
                    if(i != j):
                        if(self.childs[i].root.name == self.childs[j].root.name) and (self.childs[i].root.version == self.childs[j].root.version):
                            self.childs[i].childs += self.childs[j].childs
                            del(self.childs[j])
                            j-=1
                    j+=1
                self.childs[i].clear_bro_conflicts()
                i+=1

    def clear_imp_conflicts(self,liste_conf):
        if self.childs !=[]:
            i = 0
            while i < len(self.childs):
                if liste_conf != []:
                    for elem in liste_conf:
                        if(elem == self.childs[i].root.name):
                            for fils in self.childs[i].childs:
                                self.childs.insert(i+1, fils)
                            del(self.childs[i])
                            liste_conf.remove(elem)
                            i-=1
                self.childs[i].clear_imp_conflicts(liste_conf)
                i+=1



    def clear_tree(self):
        liste_conf = self.get_import_conflict()
        self.clear_imp_conflicts(liste_conf)
        self.clear_bro_conflicts()

    def get_import_order(self):
        return self.postorder()


        
if __name__ == "__main__":
    bob = LibraryTree()
    bob.childs = [LibraryTree("lib1", 1), LibraryTree("lib2", 3), LibraryTree("lib3", 5)]
    bob.childs[0].childs = [LibraryTree("lib3",3), LibraryTree("lib2", 3)]
    bob.childs[0].childs[1].childs = [LibraryTree("lib1", 1)]

    bob.childs[1].childs = [LibraryTree("lib4", 7)]
    bob.childs[1].childs[0].childs = [LibraryTree("lib5", 3)]

    bob.childs[2].childs = [LibraryTree("lib5", 1)] 
    
    bob.preorder()
    bob.clear_tree()
    print("\n#####################################################\n")
    bob.preorder()
    print(bob.get_import_order())