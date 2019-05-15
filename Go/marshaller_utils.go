package utils

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
)

//CODIGO DOS CARA

/*
Marshall retorna a versao serializada em JSON de value
*/

func Marshall(value interface{}) ([]byte, error) {
	var buf bytes.Buffer
	enc := json.NewEncoder(&buf)
	enc.Encode(value)

	bs := make([]byte, 4)
	binary.BigEndian.PutUint32(bs, uint32(buf.Len()))
	return append(bs, buf.Bytes()...), nil
}

func Unmarshall(value []byte, ref interface{}) error {
	buf := bytes.NewBuffer(value)
	dec := json.NewDecoder(buf)
	return dec.Decode(ref)
}

//CODIGO DO TUTORIAL YOUTUBE

package main

type User struct{
	Username string
	Password string
	Email string
}

func main(){
	user := User{"John Doe", "change me", "johndoe@gmail.com"}

	fmt.Println(user)
	//vamos agora criar um pacote json
	var buf = new(bytes.Buffer) //buffer para armazenar o documento json
	enc := json.NewEncoder(buf) // criamos um encoder, um buffer para armazenar o documento json
	enc.Encode(user) //armazenamos o user no nosso buffer
	io.Copy(os.Stdout, buf) // imprime na tela oq esta no buffer

}

