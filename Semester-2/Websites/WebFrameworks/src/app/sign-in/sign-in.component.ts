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
import { CommonModule } from '@angular/common';

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
  ],
})
export class SignInComponent {
  signInForm: FormGroup;
  hide: boolean = true;

  errorMessageEmail = '';
  errorMessagePwd = '';

  constructor(private fb: FormBuilder) {
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

  onSubmit(): void {
    if (this.signInForm.valid) {
      const { email, password } = this.signInForm.value;
      if (email === 'test@test.at' && password === '12345678') {
        console.log('Sign-In Success');
      } else {
        console.log('Sign-In Error');
      }
    } else {
      this.updateErrorMessage('email');
      this.updateErrorMessage('password');
    }
  }
}
