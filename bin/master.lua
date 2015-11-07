local master = {}

http = require("socket.http")
assert(os.setlocale('fr_FR.UTF8'))

function master.getDay()
day = os.date("%A")
return day
end 

function master.getHour()
hour = os.date("%H")
return hour
end 

function master.getMinute()
minute = os.date("%M")
return minute
end 

function master.getTime()
time = os.date("%X")
return time
end

function master.sendCmdON(target, nid)
target = tostring(target)
nid = tostring(nid)
url = string.format("http://localhost:8888/node/on?target=%s&sender=1&nid=%s",target,nid)
result, statuscode, content = http.request(url)  
end

function master.sendCmdOFF(target, nid)
target = tostring(target)
nid = tostring(nid)
url = string.format("http://localhost:8888/node/off?target=%s&sender=1&nid=%s",target,nid)
result, statuscode, content = http.request(url)  
end

function master.sendCmdAskData(target)
target = tostring(target)
url = string.format("http://localhost:8888/node/askdata?target=%s&sender=1",target)
result, statuscode, content = http.request(url)  
end

function master.sendCmdSet(target, nid)
target = tostring(target)
nid = tostring(nid)
url = string.format("http://localhost:8888/node/set?target=%s&sender=1&nid=%s",target,nid)
result, statuscode, content = http.request(url)  
end

function master.programSet(table,target, value)
    for i,v in ipairs(table) do
        if  v == os.date("%X") then
            master.sendCmdSet(target,value)
        end
    end
end

return master
