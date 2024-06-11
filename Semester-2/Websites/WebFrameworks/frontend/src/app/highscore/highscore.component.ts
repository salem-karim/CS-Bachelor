import { Component } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { MatInputModule } from '@angular/material/input';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
import { CommonModule } from '@angular/common';
import { HttpClient, HttpClientModule } from '@angular/common/http'; // express
import { Router } from '@angular/router';
import { Highscore } from './data'; // import the Highscore interface
import { firstValueFrom } from 'rxjs';

@Component({
  selector: 'app-highscore',
  standalone: true,
  imports: [
    MatFormFieldModule,
    MatInputModule,
    FormsModule,
    ReactiveFormsModule,
    MatButtonModule,
    MatIconModule,
    CommonModule,
    HttpClientModule,
  ],
  templateUrl: './highscore.component.html',
  styleUrl: './highscore.component.scss',
})
export class HighscoreComponent {
  highscores: Highscore[] = [];
  constructor(
    private http: HttpClient,
    private router: Router,
  ) {}
  ngOnInit(): void {
    const token = localStorage.getItem('sessionToken');
    if (!token) {
      // damit man nicht in der url /game eingaben kann und zur seite kommt, ohne gelogged in zu sein
      this.router.navigate(['/sign-in']);
    }
  }

  async sendHighscore() {
    const token = localStorage.getItem('sessionToken');
    const score = 1000; // example score
    try {
      const response = await firstValueFrom(
        this.http.post('http://localhost:3000/highscores', { token, score }),
      );
      console.log('Highscore sent:', response);
    } catch (error) {
      console.error('Error sending highscore:', error);
    }
  }

  async getHighscores() {
    try {
      const response = await firstValueFrom(
        this.http.get<Highscore[]>('http://localhost:3000/highscores'),
      );
      console.log('Highscores retrieved:', response);
      this.highscores = response;
    } catch (error) {
      console.error('Error retrieving highscores:', error);
    }
  }

  async logout() {
    const token = localStorage.getItem('sessionToken');
    try {
      const response = await firstValueFrom(
        this.http.delete('http://localhost:3000/sessions', {
          body: { token },
          headers: { 'Content-Type': 'application/json' },
        }),
      );
      console.log('Logout successful:', response);
      localStorage.removeItem('sessionToken');
      this.router.navigate(['/sign-in']);
    } catch (error) {
      console.error('Error during logout:', error);
    }
  }
}
