--[[ 
test
]]--
function init()
	print ("Test::init");
	setVal ("10.temperature", 3) ;
	setVal ("10.humidity", 30) ;
	
end

function action()
	temp_10 = getVal("10.temperature") 
	humid_10 = getVal("10.humidity")		
	print ("temperature node 10:", temp_10,"humidity node 10:", humid_10)	
end
