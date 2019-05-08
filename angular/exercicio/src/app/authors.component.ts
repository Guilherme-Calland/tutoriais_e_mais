import { Component } from '@angular/core';
import { AuthorComponent } from './author/author.component';
import { AuthorsService } from './authors.service';


@Component({
    selector: 'authors',

    template:
    `
        <h2>
            <ul>
                <li *ngFor="let author of authors">
                {{ author }}
            </ul>
        </h2>
    `
})

export class AuthorsComponent{
    title = "List of Authors: ";
    authors
    
    constructor(service: AuthorsService){
        this.authors = service.getAuthors()
    }


}