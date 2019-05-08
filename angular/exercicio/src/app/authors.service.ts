import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class AuthorsService {
      getAuthors(){
        return["Alan Watts", "Eckhart Tolle", "Carl Jung"]
      }
}
