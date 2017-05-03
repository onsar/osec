-- sensor_0_name = "valor_correlativo"
-- sensor_1_name = "medida_analogica"
dofile("configuracion.lua")

ssid="casaelobrero"
pass="lacosamasbonitadelmundo"
site = "aaaaaaa"
value = 0
ciclos = 0
analogico=0
sensor=0


wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pass)
print(wifi.sta.getip())

srv = net.createConnection(net.TCP, 0)

function componer_post(sensor_n)
    print("** componer_post")
    
    if (sensor_n==0) 
        then 
            name = sensor_0_name
            value = ciclos
            ciclos=ciclos+1
        else 
            name = sensor_1_name
            analogico = adc.read(0)
            value = analogico
    end
    
    post_body = "&site="..site.."&name="..name.."&value="..value
    print("** componer_post_end")
    return post_body
end


srv:on("receive", function(sck, c) 
    print("** receive") 
    print(c) 
    -- sck:close()
end)

srv:on("connection", function(sck, c)
  -- Wait for connection before sending.
    print("** connection")
    post_data= componer_post(sensor)
    n=#post_data+2
    print(post_data)
    sck:send("POST / HTTP/1.1\r\nContent-Length:"..n.."\r\n\r\n  ".. post_data)
    print(c)
    print("** connection_end")

end)

srv:on("reconnection", function(sck, c) 
    print("** reconnection") 
    print(c) 
end)

srv:on("disconnection", function(sck, c) 
    print("** disconnection") 
    print(c) 
end)

srv:on("sent", function(sck, c) 
    print("** sent") 
    print(c) 
end)

tmr.alarm(0,5000,1,function() 
    print("** function")  
    srv:connect(7000,"192.168.1.136")
    if (sensor < numero_de_sensores -1) then sensor = sensor + 1
    else sensor= 0
    end
    print("sensor= ".. sensor)  
    print("** function_end")
    
end)
