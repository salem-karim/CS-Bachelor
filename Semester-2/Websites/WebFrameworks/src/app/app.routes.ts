import { Routes } from '@angular/router';
import { SignInComponent } from './sign-in/sign-in.component'; //UE_1
import { SignUpComponent } from './sign-up/sign-up.component'; //UE_2

export const routes: Routes = [
  { path: 'sign-in', component: SignInComponent }, //UE_1
  { path: 'sign-up', component: SignUpComponent }, // UE_2
];
