from django.contrib.auth.models import Permission, User
from django.db import models
from django.urls import reverse

# Create your models here.

class Artist(models.Model):
    artist_name = models.CharField(max_length=250)
    gender = models.CharField(max_length=100)

    def __str__(self):
        return self.artist_name

class Genre(models.Model):
    genre_name = models.CharField(max_length=250)

    def __str__(self):
        return self.genre_name

class Album(models.Model):
    user = models.ForeignKey(User, default=1, on_delete=models.CASCADE)
    artist = models.ForeignKey(Artist, on_delete=models.CASCADE)
    album_title = models.CharField(max_length=500)
    genre = models.ForeignKey(Genre, on_delete=models.CASCADE)
    album_logo = models.CharField(max_length=1000)
    is_favorite = models.BooleanField(default=False)

    def get_absolute_url(self):
        return reverse('index')

    def __str__(self):
        return self.album_title

class Song(models.Model):
    album = models.ForeignKey(Album, on_delete=models.CASCADE)
    file_type = models.CharField(max_length=10)
    song_title = models.CharField(max_length=250)
    is_favorite = models.BooleanField(default=False)

    def __str__(self):
        return self.song_title