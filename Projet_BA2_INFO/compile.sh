#!/bin/bash

# etant un incroyable flemmard, j'ai fais un vieux script pourris pour compiler tout lol

if [[ -n "$1" ]]
then
    if [[ $1 != "--hard" ]]
    then
        if [[ $1 = "cli" ]] || [[ $1 = "client" ]] || [[ $2 = "cli" ]] || [[ $2 = "client" ]]
        then
            qmake
            make
        fi
        if [[ $1 = "serv" ]] || [[ $1 = "server" ]] || [[ $2 = "serv" ]] || [[ $2 = "server" ]]
        then
            cd Serveur/
            make -B all 
            cd ..
        fi
    else
        qmake
        make -B all
        cd Serveur/
        make -B all
        cd ..
    fi
else
    qmake
    make
    cd Serveur
    make -B all
    cd ..
fi
