import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { CoursesComponent } from './courses.component';
import { CourseComponent } from './course/course.component';
import { CoursesService } from './courses.service';


@NgModule({
  // em declaration addicionamos todos os components que fazem parte 
  // desse modulo
  declarations: [
    AppComponent,
    CoursesComponent,
    CourseComponent
  ],
  imports: [
    BrowserModule
  ],
  providers: //adicionar dependencias 
    [
      CoursesService
    ],
  bootstrap: [AppComponent]
})
export class AppModule { }
