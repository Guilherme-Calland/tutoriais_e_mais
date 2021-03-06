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
	p1 := person{
		First: "James",
		Last:  "Willems",
	}

	p2 := person{
		First: "Bruce",
		Last:  "Greene",
	}

	p3 := person{
		First: "Adam",
		Last:  "Kovic",
	}

	p4 := person{
		First: "Lawrence",
		Last:  "Sontagg",
	}

	group := []person{p1, p2, p3, p4} //slice de person

	fmt.Println("\ngo data:\n", group)

	//marshall recebe um "person" slice e retorna um string slice (arquivo json)
	byteSlice, err := json.Marshal(group)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("\njson:\n", string(byteSlice))

}
