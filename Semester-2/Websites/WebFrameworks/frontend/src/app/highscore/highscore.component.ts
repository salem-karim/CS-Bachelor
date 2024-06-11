import { Component } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { MatInputModule } from '@angular/material/input';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
import { CommonModule } from '@angular/common';
import { HttpClient, HttpClientModule } from '@angular/common/http';
import { Router } from '@angular/router';

interface Highscore {
  [key: string]: number;
}

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
  styleUrls: ['./highscore.component.scss'],
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
      // Redirect to sign-in if not logged in
      this.router.navigate(['/sign-in']);
    }
  }

  sendHighscore() {
    const token = localStorage.getItem('sessionToken');
    const score = 1000; // example score
    this.http
      .post('http://localhost:3000/highscores', { token, score })
      .subscribe({
        next: (response) => {
          console.log('Highscore sent:', response);
        },
        error: (error) => {
          console.error('Error sending highscore:', error);
        },
      });
  }

  getHighscores() {
    this.http.get<Highscore[]>('http://localhost:3000/highscores').subscribe({
      next: (response) => {
        console.log('Highscores retrieved:', response);
        this.highscores = response;
      },
      error: (error) => {
        console.error('Error retrieving highscores:', error);
      },
    });
  }

  logout() {
    const token = localStorage.getItem('sessionToken');
    this.http
      .delete('http://localhost:3000/sessions', {
        body: { token },
        headers: { 'Content-Type': 'application/json' },
      })
      .subscribe({
        next: (response) => {
          console.log('Logout successful:', response);
          localStorage.removeItem('sessionToken');
          this.router.navigate(['/sign-in']);
        },
        error: (error) => {
          console.error('Error during logout:', error);
        },
      });
  }
}
