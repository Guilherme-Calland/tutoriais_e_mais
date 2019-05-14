package utils

import (
	"bytes"
	"encoding/binary"
	"encoding/gob"
)

/*
Marshall retorna a versao serializada em JSON de value
*/

func Marshall(value interface{}) ([]byte, error) {
	var buf bytes.Buffer
	enc := gob.NewEncoder(&buf)
	err := enc.Encode(value)
	if err != nil {
		return nil, err
	}

	bs := make([]byte, 4)
	binary.BigEndian.PutUint32(bs, uint32(buf.Len()))
	return append(bs, buf.Bytes()...), nil
}

func Unmarshall(value []byte, ref interface{}) error {
	buf := bytes.NewBuffer(value)
	dec := gob.NewDecoder(buf)
	return dec.Decode(ref)
}
