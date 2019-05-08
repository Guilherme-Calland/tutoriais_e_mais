import { Component } from '@angular/core'
import { CoursesService } from './courses.service';

//declarator function, dizemos ao angular como o component funciona
@Component({
    selector: 'courses',
    
     /* forma simples de usar template */
    // template: "<h2>{{ getTitle()  }} </h2>"
    //         //usar {{ }} para inserir uma valor


    /*
    angular lê o let courses of courses como um loop dos elementos
    course do array courses que definimos na classe
    */ 
    template: `
        <h2>{{ title }}</h2>
        <ul>
            <li *ngFor="let course of courses">
                {{course}}
            <\li>
        </ul>
    `

})
//usamos export para o angular ter acesso à classe
export class CoursesComponent{
    title = "List of courses"

    // getTitle(){
    //     return this.title
    // } 
    // se quiser inserir getTitle() no template

    //courses = ["course1", "course2", "course3"]
    //antes de implementar o serviço testar isso com o template
    // e *ngFor
    courses
    
    // calling and HTTP service
    // constructor(){
    //     let service = new CoursesService()
    //     this.courses = service.getCourses()
    // }

    constructor(service: CoursesService) {
               /*^ cria um servico do tipo CoursesService
essa forma de fazer é melhor porque se agente fizer por exemplo 
new CoursesService(var1, var2) ai gerar uma inconsistencia la na 
classe         */
        this.courses = service.getCourses();
    }
}