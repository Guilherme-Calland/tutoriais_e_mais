package main

import(
	"fmt"
	"net"
	"bufio"
	"strings"
)

func main(){
	fmt.Println("inicando servidor...")

	ln, _ := net.Listen("tcp", ":1313")
	conn, _ := ln.Accept()

	for{
		message, _ := bufio.NewReader(conn).ReadString('\n')
		new_message := strings.ToUpper(message)
		conn.Write([]byte(new_message + "\n"))
	}
	conn.Close()
}