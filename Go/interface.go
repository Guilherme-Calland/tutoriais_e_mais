package main

import "fmt"

type person struct{
	name string
}

type human interface{ /*todo tipo de objeto que tiver os métodos aqui dentro, será do tipo human*/
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
	p1 := person{"Gui"} 
	p1.speak() 

	c1 := car{"blue"}

	foo(p1)
	foo(c1)
	 
}