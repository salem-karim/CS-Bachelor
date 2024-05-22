import { Component } from '@angular/core';
import {
  Validators,
  ReactiveFormsModule,
  FormGroup,
  FormControl,
} from '@angular/forms';

@Component({
  selector: 'app-sign-up',
  standalone: true,
  imports: [ReactiveFormsModule],
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
  });
  company: string = 'FH Technikum Wien';
  street: string = 'Street';
  city: string = 'City';
  plz: string = '1234';

  checkPwd() {
    const password = this.signUpForm.get('password')?.value ?? '';
    const password2 = this.signUpForm.get('password2')?.value ?? '';

    if (password === password2) {
      return true;
    }
    return false;
  }

  handleSubmit() {
    console.log(this.signUpForm.value);
    console.log(this.checkPwd());
    if (this.signUpForm.valid && this.checkPwd()) {
      console.log('Form is valid');
    } else {
      console.log('Form is invalid');
    }
  }
}
