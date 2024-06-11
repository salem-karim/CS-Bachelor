import { Component } from '@angular/core';
import {
  FormBuilder,
  FormGroup,
  Validators,
  ReactiveFormsModule,
} from '@angular/forms';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
import { HttpClient, HttpClientModule } from '@angular/common/http';
import { Router } from '@angular/router';
import { CommonModule } from '@angular/common';

// Define the interface for the response type
interface SignInResponse {
  sessionToken: string;
  message: string;
}

@Component({
  selector: 'app-sign-in',
  templateUrl: './sign-in.component.html',
  styleUrls: ['./sign-in.component.scss'],
  standalone: true,
  imports: [
    MatFormFieldModule,
    MatInputModule,
    ReactiveFormsModule,
    MatButtonModule,
    MatIconModule,
    CommonModule,
    HttpClientModule,
  ],
})
export class SignInComponent {
  signInForm: FormGroup;
  hide: boolean = true;

  errorMessageEmail = '';
  errorMessagePwd = '';

  constructor(
    private fb: FormBuilder,
    private http: HttpClient,
    private router: Router,
  ) {
    this.signInForm = this.fb.group({
      email: ['', [Validators.required, Validators.email]],
      password: ['', [Validators.required, Validators.minLength(8)]],
    });
  }

  get email() {
    return this.signInForm.get('email');
  }

  get password() {
    return this.signInForm.get('password');
  }

  updateErrorMessage(controlName: string) {
    const control = this.signInForm.get(controlName);
    if (controlName === 'email') {
      if (control!.hasError('required')) {
        this.errorMessageEmail = 'You must enter a valid E-Mail';
      } else if (control!.hasError('email')) {
        this.errorMessageEmail = 'Not a valid email';
      } else {
        this.errorMessageEmail = '';
      }
    } else if (controlName === 'password') {
      if (control!.hasError('required')) {
        this.errorMessagePwd = 'You must enter a Password';
      } else if (control!.hasError('minlength')) {
        if (control!.errors?.['minlength'].requiredLength === 8) {
          this.errorMessagePwd = 'Password must have 8 characters minimum';
        } else {
          this.errorMessagePwd = 'Password must have 8 or more Characters';
        }
      } else {
        this.errorMessagePwd = '';
      }
    }
  }

  togglePasswordVisibility() {
    this.hide = !this.hide;
  }

  onSubmit() {
    // express requests
    const user = {
      username: this.signInForm.get('email')?.value,
      password: this.signInForm.get('password')?.value,
    };

    this.http
      .post<SignInResponse>('http://127.0.0.1:3000/sessions', user)
      .subscribe({
        next: (response) => {
          console.log('User signed in successfully:', response);
          console.log('Session Token:', response.sessionToken);
          console.log('Message: ' + response.message);

          localStorage.setItem('sessionToken', response.sessionToken);
          this.router.navigate(['/highscore']);
        },
        error: (error) => {
          console.error('Error signing in user:', error);
        },
      });
  }
}
