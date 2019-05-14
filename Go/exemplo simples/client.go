package main

import(
	"fmt"
	"net"
	"bufio"
	"os"
)


func main(){
	conn, erro := net.Dial("tcp", ":1313")
	if erro!=nil {
		fmt.Println("deu erro!")
	}

	for{
		//le uma msg do teclado
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("Sua mensagem: ")
		text, _ := reader.ReadString('\n')

		//envia uma mensagem para o servidor
		fmt.Fprintf(conn, text + "\n")

		//escuta por uma resposta do servidor
		message, _ := bufio.NewReader(conn).ReadString('\n')
		fmt.Print("Mensagem do Servidor: " + message)
	}

	conn.Close()
}
