--[[ 
Test
]]--
local master = require "master"

function init()
	print ("Test time scenario");
end

consigne_20 ={"17:28:00","17:30:00","17:32:00"}
consigne_16 ={"17:29:00","17:31:00","17:33:00"}

function action()
--[[    time = master.getTime()
    for i,v in ipairs(consigne_20) do
        if   v == time then
            master.sendCmdSet(23,20)
        end
    end
    
    for i,v in ipairs(consigne_16) do
        if  v == time then
            master.sendCmdSet(23,16)
        end
    end
]]--
    master.programSet(consigne_20,23,20)
    master.programSet(consigne_16,23,16)
end
