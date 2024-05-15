import { Component } from '@angular/core';

@Component({
  selector: 'app-sign-up',
  standalone: true,
  imports: [],
  templateUrl: './sign-up.component.html',
  styleUrl: './sign-up.component.css',
})
export class SignUpComponent {
  email: string = 'a@b.com';
  password: string = '12ab';
  company: string = 'FH Technikum Wien';
  street: string = 'Street';
  city: string = 'City';
  plz: string = '1234';
}
