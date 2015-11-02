local isActivated = true
--[[ 
Test
]]--


function init()
	print ("Test_Xylerk::init");
	setVal ("123.temperature", 20) ;
	setVal ("123.humidity", 40) ;
end

function test()
	temp_123 = getVal("123.temperature")
	humid_123 = getVal("123.humidity")
	print ("temperature node 123:", temp_123, "humidity: node 123", humid_123)
end

function action()

	if isActivated == true then
		test ()
	end
end
