//yt link --> https://www.youtube.com/watch?v=1uAydhVdMfQ
package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"os"
)

type person struct {
	First string
	Last  string
}

func main() {

	p1 := person{First: "Elyse", Last: "Willems"}
	p2 := person{First: "Matt", Last: "Peake"}

	funhaus := []person{p1, p2} //slice de persons

	fmt.Println(funhaus)

	var buf = new(bytes.Buffer)
	//um lugar aonde posso armazenar o string json que vou criar
	//arquivo json é um string, string é um array de bytes

	enc := json.NewEncoder(buf) //buf ou &buf[0]
	//criando um encoder json
	enc.Encode(p1)
	//trannforma p1 em json e armazena dentro do buffer
	io.Copy(os.Stdout, buf)
	//teste, imprimir o buffer
}
