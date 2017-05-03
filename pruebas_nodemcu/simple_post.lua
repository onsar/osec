
ssid="identificador_de_wifi"
pass="contrasena_wifi"
site = "aaaaaaa"
name = "iiii_o"
value = 0


wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pass)
print(wifi.sta.getip())
--192.168.18.110


post_body = "&site="..site.."&name="..name.."&value="

srv = net.createConnection(net.TCP, 0)


srv:on("receive", function(sck, c) 
    print("receive") 
    print(c) 
end)

srv:on("connection", function(sck, c)
  -- Wait for connection before sending.
    print("connection")
    print(post_data)
    print(n)
    post_data = post_body..value
    n=#post_data+2
    sck:send("POST / HTTP/1.1\r\nContent-Length:"..n.."\r\n\r\n  ".. post_data)
    print(c)
end)

srv:on("reconnection", function(sck, c) 
    print("reconnection") 
    print(c) 
end)

srv:on("disconnection", function(sck, c) 
    print("disconnection") 
    print(c) 
end)

srv:on("sent", function(sck, c) 
    print("sent") 
    print(c) 
end)


-- srv:connect(7000,"192.168.1.136")
-- srv:close()a

tmr.alarm(0,5000,1,function() 
    print("alarm 0") 
    srv:connect(7000,"192.168.1.136")
    value=value+1
    print(value)
end)