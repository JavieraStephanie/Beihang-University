from django.views import generic
from django.views.generic.edit import CreateView, UpdateView, DeleteView
from django.urls import reverse_lazy
from django.http import JsonResponse
from django.shortcuts import render, get_object_or_404
from django.contrib.auth import authenticate, login, logout
from django.db.models import Q
from .models import Artist, Album, Song
from .forms import AlbumForm, SongForm, UserForm

AUDIO_FILE_TYPES = ['wav', 'mp3', 'ogg']
IMAGE_FILE_TYPES = ['png', 'jpg', 'jpeg']

def index(request):
    all_artists = Artist.objects.all()
    song_results = Song.objects.all()
    query = request.GET.get("q")
    if query:
        song_results = song_results.filter(
            Q(song_title__icontains=query)
        ).distinct()
        return render(request, 'music/index.html', {
            'all_artists': all_artists,
            'songs': song_results,
        })
    else:
        return render(request, 'music/index.html', {'all_artists': all_artists})

def detail(request, artist_id):
    if not request.user.is_authenticated:
        return render(request, 'music/login.html')
    else:
        user = request.user
        artist = get_object_or_404(Artist, pk=artist_id)
        albums = Album.objects.filter(artist=artist)
        song_results = Song.objects.all()
        query = request.GET.get("q")
        if query:
            albums = albums.filter(
                Q(album_title__icontains=query) |
                Q(artist__icontains=query)
            ).distinct()
            song_results = song_results.filter(
                Q(song_title__icontains=query)
            ).distinct()
            return render(request, 'music/detail.html', {
                'artist': artist,
                'albums': albums,
                'songs': song_results,
            })
        else:
            return render(request, 'music/detail.html', {'artist': artist, 'albums': albums, 'user': user})

def favorite_album(request, artist_id, album_id):
    artist = get_object_or_404(Artist, pk=artist_id)
    album = get_object_or_404(Album, pk=album_id)
    try:
        if album.is_favorite:
            album.is_favorite = False
        else:
            album.is_favorite = True
        album.save()
    except (KeyError, Album.DoesNotExist):
        return JsonResponse({'success': False})
    else:
        return JsonResponse({'success': True})

def albumdetail(request, artist_id, album_id):
    artist = get_object_or_404(Artist, pk=artist_id)
    album = get_object_or_404(Album, pk=album_id)
    return render(request, 'music/albumdetail.html', {'artist': artist, 'album': album})

def create_album(request):
    if not request.user.is_authenticated:
        return render(request, 'music/login.html')
    else:
        form = AlbumForm(request.POST or None)
        if form.is_valid():
            album = form.save(commit=False)
            album.user = request.user
                
            album.save()
            return render(request, 'music/albums.html')
        context = {
            "form": form,
        }
        return render(request, 'music/album_form.html', context)

class AlbumUpdate(UpdateView):
    model = Album
    fields = ['artist', 'album_title', 'genre', 'album_logo']

def favorite(request, song_id):
    song = get_object_or_404(Song, pk=song_id)
    try:
        if song.is_favorite:
            song.is_favorite = False
        else:
            song.is_favorite = True
        song.save()
    except (KeyError, Song.DoesNotExist):
        return JsonResponse({'success': False})
    else:
        return JsonResponse({'success': True})

def create_song(request, artist_id, album_id):
    form = SongForm(request.POST or None)
    artist = get_object_or_404(Artist, pk=artist_id)
    album = get_object_or_404(Album, pk=album_id)
    if form.is_valid():
        albums_songs = album.song_set.all()
        for s in albums_songs:
            if s.song_title == form.cleaned_data.get("song_title"):
                context = {
                    'artist': artist,
                    'album': album,
                    'form': form,
                    'error_message': 'You already added that song',
                }
                return render(request, 'music/create_song.html', context)
        song = form.save(commit=False)
        song.album = album

        song.save()
        return render(request, 'music/detail.html', {'artist': artist, 'album': album})
    context = {
        'artist': artist,
        'album': album,
        'form': form,
    }
    return render(request, 'music/create_song.html', context)

def delete_album(request, artist_id, album_id):
    artist = get_object_or_404(Artist, pk=artist_id)
    album = Album.objects.get(pk=album_id)
    album.delete()
    albums = Album.objects.filter(artist=artist)
    return render(request, 'music/detail.html', {'artist': artist, 'albums': albums})

def delete_song(request, artist_id, album_id, song_id):
    artist = get_object_or_404(Artist, pk=artist_id)
    album = get_object_or_404(Album, pk=album_id)
    song = Song.objects.get(pk=song_id)
    song.delete()
    return render(request, 'music/albumdetail.html', {'artist': artist, 'album': album})

def logout_user(request):
    logout(request)
    form = UserForm(request.POST or None)
    context = {
        "form": form,
    }
    return render(request, 'music/login.html', context)

def register(request):
    form = UserForm(request.POST or None)
    if form.is_valid():
        user = form.save(commit=False)
        username = form.cleaned_data['username']
        password = form.cleaned_data['password']
        user.set_password(password)
        user.save()
        user = authenticate(username=username, password=password)
        if user is not None:
            if user.is_active:
                login(request, user)
                albums = Album.objects.filter(user=request.user)
                return render(request, 'music/index.html', {'albums': albums})
    context = {
        "form": form,
    }
    return render(request, 'music/registration_form.html', context)

def login_user(request):
    if request.method == "POST":
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(username=username, password=password)
        if user is not None:
            if user.is_active:
                login(request, user)
                albums = Album.objects.filter(user=request.user)
                return render(request, 'music/detail.html', {'albums': albums})
            else:
                return render(request, 'music/login.html', {'error_message': 'Your account has been disabled'})
        else:
            return render(request, 'music/login.html', {'error_message': 'Invalid login'})
    return render(request, 'music/login.html')

def albums(request, filter_by):
    album_list = Album.objects.all()
    
    return render(request, 'music/albums.html', {'album_list': album_list})

def songs(request, filter_by):
    users_songs = Song.objects.all()

    return render(request, 'music/songs.html', {'song_list': users_songs})