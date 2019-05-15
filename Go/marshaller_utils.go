package utils

import (
	"bytes"
	"encoding/binary"
	"encoding/gob"
)

//CODIGO DOS CARA

/*
Marshall retorna a versao serializada em gob de value
*/

//marshall transforma o objeto value e retorna um array de bytes
func Marshall(value interface{}) ([]byte, error) {
	var buf bytes.Buffer
	enc := gob.NewEncoder(&buf)
	enc.Encode(value)

	bs := make([]byte, 4)
	binary.BigEndian.PutUint32(bs, uint32(buf.Len()))
	return append(bs, buf.Bytes()...), nil
}

//armazena o array de bytes na variavel ref
func Unmarshall(value []byte, ref interface{}) error {
	buf := bytes.NewBuffer(value)
	dec := gob.NewDecoder(buf)
	return dec.Decode(ref)
}


//json tutorial (importante) --> https://www.youtube.com/watch?v=Osm5SCw6gPU
//  https://www.youtube.com/watch?v=1uAydhVdMfQ   marshall unmarshall code!!!
//veja esse video depois para o projeto --> https://www.youtube.com/watch?v=xyoEqDlokw8&t=270s

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

	//console : "John Doe change me johndoe@gmail.com"   --> do println(user)
	//          {{"UserName":"JohnDoe","password":"change me","email":"johndoe@gmail.com"}} --> json file

}

