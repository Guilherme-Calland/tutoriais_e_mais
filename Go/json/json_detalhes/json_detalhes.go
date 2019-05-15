package main

import (
	"encoding/json"
	"fmt"
)

type person struct {
	First string `json:"fname"` /*tag, especificar como ta escrito
	no string json*/
	Last string
}

func main() {

	//string
	j := `[
	{"fname":"James","Last":"Willems"},
	{"fname":"Bruce","Last":"Greene"},
	{"fname":"Adam","Last":"Kovic"},
	{"fname":"Lawrence","Last":"Sontagg"}
	]`

	fmt.Println("\njson:\n", j)

	funhaus := []person{}

	err := json.Unmarshal([]byte(j), &funhaus)
	if err != nil {
		fmt.Println(err)
	}
	//unmarshall recebe um byte slice para receber o dado json
	// e um endereço de slice do tipo que agt quer armezenar
	//[]bytes(j) --> cria um slice de bytes a partir do string j,
	// lembrando que um string nada mais é que uma sequencia de bytes

	fmt.Println("\ngo data:\n", funhaus)

	fmt.Println("\nOnly Adam:", funhaus[2])

}
