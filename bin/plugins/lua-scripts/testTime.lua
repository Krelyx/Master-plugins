--[[ 
Scénario pour envoyer valeur au node 23 selon l'heure
]]--
-- Module comportant des fonctions utiles:
local master = require "master"

function init()
	print ("Test time scenario");
end
--Création table "consigne_20"
consigne_20 ={"17:28:00","17:30:00","17:32:00"}
--Création table "consigne_16"
consigne_16 ={"17:29:00","17:31:00","17:33:00"}

function action()
--[[ Appel fonction programSet
argument 1: table
argument 2: code du node 
argument 3: valeur à envoyer
]]--  
    master.programSet(consigne_20,23,20)
    master.programSet(consigne_16,23,16)
end
