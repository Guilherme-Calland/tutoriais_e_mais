package main

//aqui criamos um arquivo json

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

func Marshall(value person) {

	var buf = new(bytes.Buffer)
	//um lugar aonde posso armazenar o string json que vou criar
	//arquivo json é um string, string é um array de bytes

	enc := json.NewEncoder(buf) //buf ou &buf[0]
	//criando um encoder json
	enc.Encode(value)
	//trannforma p1 em json e armazena dentro do buffer

	fmt.Println("\narquivo serializado:\n", buf) //ou &buf[0]

	f, err := os.Create("arquivo.json") //create a file
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()
	io.Copy(f, buf) //copia os dados de buffer para f
}

func Unmarshall() person {

	f, err := os.Open("arquivo.json") //opening a json file
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()

	dec := json.NewDecoder(f) //criar decoder para deserializar

	value := person{}  //obj vazio para por o conteudo do json
	dec.Decode(&value) //armazenamos o conteudo de f em db
	//fmt.Println("arquivo deserializado: ", value)

	return value
}

func main() {
	p1 := person{First: "Elyse", Last: "Willems"}
	p2 := person{First: "Matt", Last: "Peake"}
	group := []person{p1, p2}
	Marshall(p1)
	fmt.Println("\narquivo deserializado:\n", Unmarshall())
	fmt.Println(group[0])
}
