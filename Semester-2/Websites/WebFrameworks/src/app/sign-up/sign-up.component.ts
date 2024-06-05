import { Component } from '@angular/core';
import {
  FormBuilder,
  FormGroup,
  Validators,
  ReactiveFormsModule,
  FormsModule,
} from '@angular/forms';
import { MatInputModule } from '@angular/material/input';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
import { CommonModule } from '@angular/common';
import { HttpClient } from '@angular/common/http'; // express js
@Component({
  selector: 'app-sign-up',
  templateUrl: './sign-up.component.html',
  styleUrls: ['./sign-up.component.scss'],
  standalone: true,
  imports: [
    MatFormFieldModule,
    MatInputModule,
    ReactiveFormsModule,
    MatButtonModule,
    MatIconModule,
    CommonModule,
    FormsModule,
  ],
})
export class SignUpComponent {
  signUpForm: FormGroup;
  hide: boolean = true;
  errorMessageEmail = '';
  errorMessagePwd = '';
  errorMessagePwd2 = '';
  company: string = 'FH Technikum Wien';
  addr: string = '';
  city: string = '';
  plz: number = 0;

  constructor(
    private fb: FormBuilder,
    private http: HttpClient,
  ) {
    this.signUpForm = this.fb.group({
      email: ['', [Validators.required, Validators.email]],
      password: ['', [Validators.required, Validators.minLength(8)]],
      password2: ['', [Validators.required, Validators.minLength(8)]],
      addr: [''],
      city: [''],
      plz: [''],
    });
  }

  get email() {
    return this.signUpForm.get('email');
  }

  get password() {
    return this.signUpForm.get('password');
  }

  get password2() {
    return this.signUpForm.get('password2');
  }

  updateErrorMessage(controlName: string) {
    const control = this.signUpForm.get(controlName);
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
    } else if (controlName === 'password2') {
      if (control!.hasError('required')) {
        this.errorMessagePwd2 = 'You must repeat the Password';
      } else if (control!.hasError('minlength')) {
        if (control!.errors?.['minlength'].requiredLength === 8) {
          this.errorMessagePwd2 = 'Password must have 8 characters minimum';
        } else {
          this.errorMessagePwd2 = 'Password must have 8 or more Characters';
        }
      } else if (this.password?.value !== this.password2?.value) {
        control!.setErrors({ mismatch: true });
        this.errorMessagePwd2 = "Passwords don't match";
      } else {
        this.errorMessagePwd2 = '';
      }
    }
  }

  togglePasswordVisibility() {
    this.hide = !this.hide;
  }

  async onSubmit(): Promise<void> {
    if (this.signUpForm.valid) {
      console.log('Form is valid');
      const user = {
        email: this.email?.value,
        password: this.password?.value,
        addr: this.addr,
        city: this.city,
        plz: this.plz,
      };
      // try {
      //   const response = await firstValueFrom(
      //     this.http.post('http://localhost:3000/users', user),
      //   );
      //   console.log('User registered successfully:', response); //gets message and authToken
      //   //Maybe this ?
      //   this.router.navigate(['/game']);

      // } catch (error) {
      //   console.error('Error registering user:', error);
      // }
    } else {
      this.updateErrorMessage('email');
      this.updateErrorMessage('password');
      this.updateErrorMessage('password2');
      console.log('Errors still remaining');
      console.log(this.errorMessageEmail);
      console.log(this.errorMessagePwd);
      console.log(this.errorMessagePwd2);
    }
  }
}
