from django.urls import path
from . import views

urlpatterns = [
    # /music/
    path('', views.index, name='index'),

    path('register/', views.register, name='register'),

    path('login_user/', views.login_user, name='login_user'),

    path('logout_user/', views.logout_user, name='logout_user'),

    # /music/1
    path('<int:artist_id>/', views.detail, name='detail'),

    path('<int:artist_id>/<int:album_id>/', views.albumdetail, name='albumdetail'),

    path('albums/<filter_by>/', views.albums, name='albums'),

    path('songs/<filter_by>/', views.songs, name='songs'),

    path('<int:song_id>/favorite/', views.favorite, name='favorite'),

    path('<int:artist_id>/<int:album_id>/create_song/', views.create_song, name='create_song'),

    path('<int:artist_id>/<int:album_id>/delete_song/<int:song_id>/', views.delete_song, name='delete_song'),

    path('album_add/', views.create_album, name='album-add'),

    path('<int:artist_id>/<int:pk>/edit', views.AlbumUpdate.as_view(), name='album-update'),

    path('<int:artist_id>/<int:album_id>/favorite_album/', views.favorite_album, name='favorite_album'),

    path('<int:artist_id>/<int:album_id>/delete_album/', views.delete_album, name='album-delete'),
]
