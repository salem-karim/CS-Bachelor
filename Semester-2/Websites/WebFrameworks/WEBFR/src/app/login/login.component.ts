import { Component } from '@angular/core';
import {
  Validators,
  ReactiveFormsModule,
  FormGroup,
  FormControl,
} from '@angular/forms';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [ReactiveFormsModule],
  templateUrl: './login.component.html',
  styleUrl: './login.component.css',
})
export class LoginComponent {
  loginForm = new FormGroup({
    email: new FormControl('', [Validators.required, Validators.email]),
    password: new FormControl('', [
      Validators.required,
      Validators.minLength(8),
    ]),
  });

  checkCredentials() {
    const email = this.loginForm.get('email')?.value ?? '';
    const password = this.loginForm.get('password')?.value ?? '';

    if (email === 'test@test.at' && password === '12345678') {
      return true;
    }
    return false;
  }

  handleSubmit() {
    if (this.loginForm.valid && this.checkCredentials()) {
      console.log('Login successful');
    } else {
      console.log('Login failed');
    }
  }
}
