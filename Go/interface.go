package main

import "fmt"

type person struct{
	name string
}

type human interface{
    speak()
}

//método de person
func (p person) speak(){ /*esse metodo faz com que todo objeto do tipo person tambem é do tipo human*/
	fmt.Println(p.name)
}

func foo(h human){
	fmt.Println(h)
}

type car struct{
	color string
}

func (c car) speak(){ //agora todo objeto car é do tipo human
	fmt.Println(c.color)
}

func main(){
	p1 := person{"Gui"} //p1 agora é do tipo person
	p1.speak() //p1 agora é do tipo human (além de ser person)

	foo(p1) 
}