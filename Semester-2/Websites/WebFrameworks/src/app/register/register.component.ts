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
  selector: 'app-register',
  standalone: true,
  imports: [
    MatFormFieldModule,
    MatInputModule,
    FormsModule,
    ReactiveFormsModule,
    MatButtonModule,
    MatIconModule,
    CommonModule,
  ],
  templateUrl: './register.component.html',
  styleUrl: './register.component.scss',
})
export class RegisterComponent {
  email = new FormControl('', [Validators.required, Validators.email]);
  password = new FormControl('', [
    Validators.required,
    Validators.minLength(8),
  ]);
  password2 = new FormControl('', [
    Validators.required,
    Validators.minLength(8),
  ]);

  passwordControl = new FormControl('');
  confirmPasswordControl = new FormControl('');

  hide: boolean = true;

  // ausgabe
  errorMessageEmail = '';
  errorMessagePwd = '';
  errorMessagePwd2 = '';

  company: string = 'FH Technikum Wien';
  addr: string = '';
  city: string = '';
  plz: number = 0;

  constructor() {
    merge(this.email.statusChanges, this.email.valueChanges)
      .pipe(takeUntilDestroyed())
      .subscribe(() => this.updateErrorMessageEmail());

    merge(this.password.statusChanges, this.password.valueChanges)
      .pipe(takeUntilDestroyed())
      .subscribe(() => this.updateErrorMessagePwd());

    merge(this.password2.statusChanges, this.password2.valueChanges)
      .pipe(takeUntilDestroyed())
      .subscribe(() => this.updateErrorMessagePwd2());
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
    } else if (this.password.hasError('minlength')) {
      if (this.password.errors?.['minlength'].requiredLength === 8) {
        this.errorMessagePwd = 'Password must have 8 characters minimum';
      } else {
        this.errorMessagePwd = 'Password must have 8 or more Characters';
      }
    } else {
      this.errorMessagePwd = '';
    }
  }

  updateErrorMessagePwd2() {
    if (this.password2.hasError('required')) {
      this.errorMessagePwd2 = 'You must repeat the Password';
    } else if (this.password2.hasError('minlength')) {
      if (this.password2.errors?.['minlength'].requiredLength === 8) {
        this.errorMessagePwd2 = 'Password must have 8 characters minimum';
      } else {
        this.errorMessagePwd2 = 'Password must have 8 or more Characters';
      }
    } else if (this.password.value !== this.password2.value) {
      this.password2.setErrors({ mismatch: true }); // Setze benutzerdefinierten Fehler 'mismatch'
      this.errorMessagePwd2 = "Passwords don't match"; // Fehlermeldung für Passwortübereinstimmung
    } else {
      this.errorMessagePwd2 = '';
    }
  }

  togglePasswordVisibility() {
    this.hide = !this.hide;
  }

  onSubmit(): void {
    if (
      this.errorMessageEmail ||
      this.errorMessagePwd ||
      this.errorMessagePwd2
    ) {
      console.log('Errors still remaining');
      console.log(this.errorMessageEmail);
      console.log(this.errorMessagePwd);
      console.log(this.errorMessagePwd2);
    } else if (
      this.email.value !== 'test@test.at' ||
      this.password.value !== '12345678'
    ) {
      console.log('Login Error');
    } else {
      console.log('Login Success');
    }
  }
}
