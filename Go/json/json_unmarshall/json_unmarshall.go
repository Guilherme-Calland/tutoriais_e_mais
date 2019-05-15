//yt link --> https://www.youtube.com/watch?v=h6aj8CRSuIc
//para a conversao json to go va para site json-to-go

package main

import (
	"encoding/json"
	"fmt"
)

type person struct {
	First string
	Last  string
}

func main() {

	//string
	j := `[
	{"First":"James","Last":"Willems"},
	{"First":"Bruce","Last":"Greene"},
	{"First":"Adam","Last":"Kovic"},
	{"First":"Lawrence","Last":"Sontagg"}
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

}
