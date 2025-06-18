package main

import (
	"fmt"
	"reflect"
)

func main() {
	// Go won't let this run unless it's actually a boolean
	a := true
	for a {
		fmt.Println("karo")
		a = false // or it’ll be an actual infinite loop
	}

	x := "false"
	fmt.Println(reflect.TypeOf(x)) // string

	// This will not compile — Go forces boolean types only
	// if x {
	//     fmt.Println("runs")
	// }
}
