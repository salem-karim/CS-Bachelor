import { Routes } from '@angular/router';
import { LoginComponent } from './login/login.component'; //UE_1
import { RegisterComponent } from './register/register.component'; //UE_2

export const routes: Routes = [
  { path: 'login', component: LoginComponent }, //UE_1
  { path: 'register', component: RegisterComponent }, // UE_2
];
