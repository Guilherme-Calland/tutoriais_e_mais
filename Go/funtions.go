
type greeter struct{
	greeting string
	name string
}

//método de greeter, só objetos do tipo greeter podem chamar essa funcao
func(g greeter) greet(){
	fmt.Println(g.greeting, g.name)
}

//com apontador eu posso mudar o valor de g dentro da funcao
func(g2 *greeter) greet_2(){
	fmt.Println(g2.greeting, g2.name)
	g2.greeting = " "
}

func main(){
	g := greeter{
		greeting: "Hello",
		name: "Go",			
	}
	g.greet()

	g2 := greeter{
		greeting: "bye",
		name: "go",
	}
	g2.greet()
	g2.greet()
}

//console : Hello Go
//console : bye go
//console : go