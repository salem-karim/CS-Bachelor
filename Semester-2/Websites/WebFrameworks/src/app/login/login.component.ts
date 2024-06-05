import { Component } from '@angular/core';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';
import {
  FormControl,
  Validators,
  FormsModule,
  ReactiveFormsModule,
} from '@angular/forms';
import { MatInputModule } from '@angular/material/input';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
import { CommonModule } from '@angular/common';
import { merge } from 'rxjs';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss'],
  standalone: true,
  imports: [
    MatFormFieldModule,
    MatInputModule,
    FormsModule,
    ReactiveFormsModule,
    MatButtonModule,
    MatIconModule,
    CommonModule,
  ], // Include FormsModule
})
export class LoginComponent {
  email = new FormControl('', [Validators.required, Validators.email]);
  password = new FormControl('', [Validators.required]);

  passwordControl = new FormControl('');
  confirmPasswordControl = new FormControl('');

  hide: boolean = true;

  // ausgabe
  errorMessageEmail = '';
  errorMessagePwd = '';
  errorMessagePwd2 = '';

  constructor() {
    merge(this.email.statusChanges, this.email.valueChanges)
      .pipe(takeUntilDestroyed())
      .subscribe(() => this.updateErrorMessageEmail());

    merge(this.password.statusChanges, this.password.valueChanges)
      .pipe(takeUntilDestroyed())
      .subscribe(() => this.updateErrorMessagePwd());
  }

  // Error-Messages
  updateErrorMessageEmail() {
    if (this.email.hasError('required')) {
      this.errorMessageEmail = 'You must enter a valid E-Mail';
    } else if (this.email.hasError('email')) {
      this.errorMessageEmail = 'Not a valid email';
    } else {
      this.errorMessageEmail = '';
    }
  }
  updateErrorMessagePwd() {
    if (this.password.hasError('required')) {
      this.errorMessagePwd = 'You must enter a Password';
    } else {
      this.errorMessagePwd = '';
    }
  }

  togglePasswordVisibility() {
    this.hide = !this.hide;
  }

  onSubmit(): void {
    if (
      this.email.value === 'test@test.at' &&
      this.password.value === '12345678'
    ) {
      console.log('Login Success');
    } else {
      console.log('Login Error');
    }
  }
}
