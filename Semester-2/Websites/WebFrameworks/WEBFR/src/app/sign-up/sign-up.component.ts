import { Component } from '@angular/core';
import {
  Validators,
  ReactiveFormsModule,
  FormGroup,
  FormControl,
  FormsModule,
} from '@angular/forms';

@Component({
  selector: 'app-sign-up',
  standalone: true,
  imports: [ReactiveFormsModule, FormsModule],
  templateUrl: './sign-up.component.html',
  styleUrl: './sign-up.component.css',
})
export class SignUpComponent {
  signUpForm = new FormGroup({
    email: new FormControl('', [Validators.required, Validators.email]),
    password: new FormControl('', [
      Validators.required,
      Validators.minLength(8),
    ]),
    password2: new FormControl('', [
      Validators.required,
      Validators.minLength(8),
    ]),
    street: new FormControl(''),
    city: new FormControl(''),
    plz: new FormControl(),
  });
  company: string = 'FH Technikum Wien';

  checkForm() {
    const password = this.signUpForm.get('password')?.value ?? '';
    const password2 = this.signUpForm.get('password2')?.value ?? '';

    if (password === password2) {
      return true;
    }
    return false;
  }

  handleSubmit() {
    if (this.signUpForm.valid && this.checkForm()) {
      console.log('Form is valid');
    } else {
      console.log('Form is invalid');
    }
  }
}
