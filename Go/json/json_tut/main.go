package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

type person struct {
	First string `json: firstName`
	Last  string `json: lastName`
}

type game struct {
	Type string `json: GameType`
}

func serverHandler(w http.ResponseWriter, r *http.Request) {

	//request

	per := person{}                    //objeto vazio p armazenar o json
	jsn, err := ioutil.ReadAll(r.Body) //ler o json
	if err != nil {
		fmt.Println(err)
	}
	err = json.Unmarshal(jsn, &per) //armazenar o json em per
	if err != nil {
		fmt.Println(err)
	}
	log.Printf("Received: %v\n", per)

	//response

	game1 := game{
		Type: "first person",
	}

	gameJson, err := json.Marshal(game1)
	if err != nil {
		fmt.Println(err)
	}
	w.Header().Set("Content-Type", "application/json")
	w.Write(gameJson)
}

func server() {
	http.HandleFunc("/", serverHandler)
	http.ListenAndServe(":8080", nil)
}

func client() {
	locJson, err := json.Marshal(loc{Lat: 35.14326, Lon: -116.104})
	req, err := http.NewRequest("POST", "http://localhost:8080", bytes.NewBuffer(locJson))
	req.Header.Set("Content-Type", "applicaion/json")
	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		log.Fatal(err)
	}
	body, err := ioutil.ReadAll(resp.Body)
	fmt.Println("Response: ", string(body))
	resp.Body.Close()
}

func main() {
	go server()
	client()
}
