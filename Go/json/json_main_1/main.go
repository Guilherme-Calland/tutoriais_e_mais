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

type UserDataBase struct {
	Group []person
	Name  string
}

func main() {

	p1 := person{First: "Elyse", Last: "Willems"}
	p2 := person{First: "Matt", Last: "Peake"}

	funhaus := []person{p1, p2} //slice de persons

	db := UserDataBase{funhaus, "Funhaus Gaming"}

	// fmt.Println(funhaus)

	var buf = new(bytes.Buffer)
	//um lugar aonde posso armazenar o string json que vou criar
	//arquivo json é um string, string é um array de bytes

	enc := json.NewEncoder(buf) //buf ou &buf[0]
	//criando um encoder json
	enc.Encode(db)
	//trannforma p1 em json e armazena dentro do buffer

	f, err := os.Create("user.db.json") //create a file
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()
	io.Copy(f, buf)
}
