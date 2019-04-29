--
-- File generated with SQLiteStudio v3.2.1 on Fri Dec 28 00:36:03 2018
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: auth_group
CREATE TABLE "auth_group" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "name" varchar(80) NOT NULL UNIQUE);

-- Table: auth_group_permissions
CREATE TABLE "auth_group_permissions" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "group_id" integer NOT NULL REFERENCES "auth_group" ("id") DEFERRABLE INITIALLY DEFERRED, "permission_id" integer NOT NULL REFERENCES "auth_permission" ("id") DEFERRABLE INITIALLY DEFERRED);

-- Table: auth_permission
CREATE TABLE "auth_permission" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "content_type_id" integer NOT NULL REFERENCES "django_content_type" ("id") DEFERRABLE INITIALLY DEFERRED, "codename" varchar(100) NOT NULL, "name" varchar(255) NOT NULL);
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (1, 1, 'add_logentry', 'Can add log entry');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (2, 1, 'change_logentry', 'Can change log entry');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (3, 1, 'delete_logentry', 'Can delete log entry');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (4, 1, 'view_logentry', 'Can view log entry');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (5, 2, 'add_permission', 'Can add permission');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (6, 2, 'change_permission', 'Can change permission');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (7, 2, 'delete_permission', 'Can delete permission');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (8, 2, 'view_permission', 'Can view permission');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (9, 3, 'add_group', 'Can add group');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (10, 3, 'change_group', 'Can change group');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (11, 3, 'delete_group', 'Can delete group');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (12, 3, 'view_group', 'Can view group');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (13, 4, 'add_user', 'Can add user');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (14, 4, 'change_user', 'Can change user');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (15, 4, 'delete_user', 'Can delete user');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (16, 4, 'view_user', 'Can view user');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (17, 5, 'add_contenttype', 'Can add content type');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (18, 5, 'change_contenttype', 'Can change content type');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (19, 5, 'delete_contenttype', 'Can delete content type');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (20, 5, 'view_contenttype', 'Can view content type');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (21, 6, 'add_session', 'Can add session');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (22, 6, 'change_session', 'Can change session');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (23, 6, 'delete_session', 'Can delete session');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (24, 6, 'view_session', 'Can view session');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (25, 7, 'add_song', 'Can add song');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (26, 7, 'change_song', 'Can change song');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (27, 7, 'delete_song', 'Can delete song');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (28, 7, 'view_song', 'Can view song');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (29, 8, 'add_album', 'Can add album');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (30, 8, 'change_album', 'Can change album');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (31, 8, 'delete_album', 'Can delete album');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (32, 8, 'view_album', 'Can view album');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (33, 9, 'add_genre', 'Can add genre');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (34, 9, 'change_genre', 'Can change genre');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (35, 9, 'delete_genre', 'Can delete genre');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (36, 9, 'view_genre', 'Can view genre');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (37, 10, 'add_artist', 'Can add artist');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (38, 10, 'change_artist', 'Can change artist');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (39, 10, 'delete_artist', 'Can delete artist');
INSERT INTO auth_permission (id, content_type_id, codename, name) VALUES (40, 10, 'view_artist', 'Can view artist');

-- Table: auth_user
CREATE TABLE "auth_user" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "password" varchar(128) NOT NULL, "last_login" datetime NULL, "is_superuser" bool NOT NULL, "username" varchar(150) NOT NULL UNIQUE, "first_name" varchar(30) NOT NULL, "email" varchar(254) NOT NULL, "is_staff" bool NOT NULL, "is_active" bool NOT NULL, "date_joined" datetime NOT NULL, "last_name" varchar(150) NOT NULL);
INSERT INTO auth_user (id, password, last_login, is_superuser, username, first_name, email, is_staff, is_active, date_joined, last_name) VALUES (1, 'pbkdf2_sha256$120000$neaL9ghU0wqa$cEO1EIpftiIoo1OnOoysYDTi5bzQOaILUnocr4UgkFE=', '2018-12-27 15:16:32.652915', 1, 'admin', '', 'admin@example.com', 1, 1, '2018-12-20 18:13:05.381754', '');
INSERT INTO auth_user (id, password, last_login, is_superuser, username, first_name, email, is_staff, is_active, date_joined, last_name) VALUES (2, 'pbkdf2_sha256$120000$U64H1e5P8gLs$e93iIAxlbvCZ1Ziv+/j6/KqoFtdeErEcmTR9hT3J8hg=', '2018-12-20 22:29:35.745367', 0, 'test', '', 'test@example.com', 0, 1, '2018-12-20 22:29:35.018195', '');
INSERT INTO auth_user (id, password, last_login, is_superuser, username, first_name, email, is_staff, is_active, date_joined, last_name) VALUES (3, 'pbkdf2_sha256$120000$eGN4SCBM6cKZ$1F4X71QLh7LRn1ceu4/P3wGXE6ZYPSbLRa66GSZI8P4=', '2018-12-27 15:28:03.310200', 0, 'JavieraStephanie', '', 'javierastephanie@yahoo.com', 0, 1, '2018-12-21 04:35:14.510898', '');

-- Table: auth_user_groups
CREATE TABLE "auth_user_groups" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "user_id" integer NOT NULL REFERENCES "auth_user" ("id") DEFERRABLE INITIALLY DEFERRED, "group_id" integer NOT NULL REFERENCES "auth_group" ("id") DEFERRABLE INITIALLY DEFERRED);

-- Table: auth_user_user_permissions
CREATE TABLE "auth_user_user_permissions" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "user_id" integer NOT NULL REFERENCES "auth_user" ("id") DEFERRABLE INITIALLY DEFERRED, "permission_id" integer NOT NULL REFERENCES "auth_permission" ("id") DEFERRABLE INITIALLY DEFERRED);

-- Table: django_admin_log
CREATE TABLE "django_admin_log" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "action_time" datetime NOT NULL, "object_id" text NULL, "object_repr" varchar(200) NOT NULL, "change_message" text NOT NULL, "content_type_id" integer NULL REFERENCES "django_content_type" ("id") DEFERRABLE INITIALLY DEFERRED, "user_id" integer NOT NULL REFERENCES "auth_user" ("id") DEFERRABLE INITIALLY DEFERRED, "action_flag" smallint unsigned NOT NULL);
INSERT INTO django_admin_log (id, action_time, object_id, object_repr, change_message, content_type_id, user_id, action_flag) VALUES (1, '2018-12-20 18:15:01.371966', '4', 'Shawn Mendes', '[]', 10, 1, 2);
INSERT INTO django_admin_log (id, action_time, object_id, object_repr, change_message, content_type_id, user_id, action_flag) VALUES (2, '2018-12-20 18:15:14.541705', '3', 'Charlie Puth', '[{"changed": {"fields": ["gender"]}}]', 10, 1, 2);
INSERT INTO django_admin_log (id, action_time, object_id, object_repr, change_message, content_type_id, user_id, action_flag) VALUES (3, '2018-12-20 18:15:22.509597', '4', 'Shawn Mendes', '[{"changed": {"fields": ["gender"]}}]', 10, 1, 2);
INSERT INTO django_admin_log (id, action_time, object_id, object_repr, change_message, content_type_id, user_id, action_flag) VALUES (4, '2018-12-20 19:13:50.767908', '2', '1989', '[{"added": {}}]', 8, 1, 1);
INSERT INTO django_admin_log (id, action_time, object_id, object_repr, change_message, content_type_id, user_id, action_flag) VALUES (5, '2018-12-20 19:14:02.574150', '1', 'Fearless', '[{"changed": {"fields": ["album_logo"]}}]', 8, 1, 2);
INSERT INTO django_admin_log (id, action_time, object_id, object_repr, change_message, content_type_id, user_id, action_flag) VALUES (6, '2018-12-20 19:15:35.403246', '1', 'Love Story', '[{"added": {}}]', 7, 1, 1);

-- Table: django_content_type
CREATE TABLE "django_content_type" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "app_label" varchar(100) NOT NULL, "model" varchar(100) NOT NULL);
INSERT INTO django_content_type (id, app_label, model) VALUES (1, 'admin', 'logentry');
INSERT INTO django_content_type (id, app_label, model) VALUES (2, 'auth', 'permission');
INSERT INTO django_content_type (id, app_label, model) VALUES (3, 'auth', 'group');
INSERT INTO django_content_type (id, app_label, model) VALUES (4, 'auth', 'user');
INSERT INTO django_content_type (id, app_label, model) VALUES (5, 'contenttypes', 'contenttype');
INSERT INTO django_content_type (id, app_label, model) VALUES (6, 'sessions', 'session');
INSERT INTO django_content_type (id, app_label, model) VALUES (7, 'music', 'song');
INSERT INTO django_content_type (id, app_label, model) VALUES (8, 'music', 'album');
INSERT INTO django_content_type (id, app_label, model) VALUES (9, 'music', 'genre');
INSERT INTO django_content_type (id, app_label, model) VALUES (10, 'music', 'artist');

-- Table: django_migrations
CREATE TABLE "django_migrations" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "app" varchar(255) NOT NULL, "name" varchar(255) NOT NULL, "applied" datetime NOT NULL);
INSERT INTO django_migrations (id, app, name, applied) VALUES (1, 'contenttypes', '0001_initial', '2018-12-20 17:02:56.240775');
INSERT INTO django_migrations (id, app, name, applied) VALUES (2, 'auth', '0001_initial', '2018-12-20 17:02:56.463376');
INSERT INTO django_migrations (id, app, name, applied) VALUES (3, 'admin', '0001_initial', '2018-12-20 17:02:56.666856');
INSERT INTO django_migrations (id, app, name, applied) VALUES (4, 'admin', '0002_logentry_remove_auto_add', '2018-12-20 17:02:56.952156');
INSERT INTO django_migrations (id, app, name, applied) VALUES (5, 'admin', '0003_logentry_add_action_flag_choices', '2018-12-20 17:02:57.432368');
INSERT INTO django_migrations (id, app, name, applied) VALUES (6, 'contenttypes', '0002_remove_content_type_name', '2018-12-20 17:02:57.685087');
INSERT INTO django_migrations (id, app, name, applied) VALUES (7, 'auth', '0002_alter_permission_name_max_length', '2018-12-20 17:02:57.936597');
INSERT INTO django_migrations (id, app, name, applied) VALUES (8, 'auth', '0003_alter_user_email_max_length', '2018-12-20 17:02:58.169832');
INSERT INTO django_migrations (id, app, name, applied) VALUES (9, 'auth', '0004_alter_user_username_opts', '2018-12-20 17:02:58.491415');
INSERT INTO django_migrations (id, app, name, applied) VALUES (10, 'auth', '0005_alter_user_last_login_null', '2018-12-20 17:02:58.889017');
INSERT INTO django_migrations (id, app, name, applied) VALUES (11, 'auth', '0006_require_contenttypes_0002', '2018-12-20 17:02:59.002119');
INSERT INTO django_migrations (id, app, name, applied) VALUES (12, 'auth', '0007_alter_validators_add_error_messages', '2018-12-20 17:02:59.232325');
INSERT INTO django_migrations (id, app, name, applied) VALUES (13, 'auth', '0008_alter_user_username_max_length', '2018-12-20 17:02:59.477779');
INSERT INTO django_migrations (id, app, name, applied) VALUES (14, 'auth', '0009_alter_user_last_name_max_length', '2018-12-20 17:02:59.752616');
INSERT INTO django_migrations (id, app, name, applied) VALUES (15, 'sessions', '0001_initial', '2018-12-20 17:03:00.062645');
INSERT INTO django_migrations (id, app, name, applied) VALUES (16, 'music', '0001_initial', '2018-12-20 17:46:58.599272');
INSERT INTO django_migrations (id, app, name, applied) VALUES (17, 'music', '0002_auto_20181221_0156', '2018-12-20 17:57:10.451422');
INSERT INTO django_migrations (id, app, name, applied) VALUES (18, 'music', '0003_auto_20181221_0200', '2018-12-20 18:00:35.497850');
INSERT INTO django_migrations (id, app, name, applied) VALUES (19, 'music', '0004_song_is_favorite', '2018-12-20 19:46:08.800798');
INSERT INTO django_migrations (id, app, name, applied) VALUES (20, 'music', '0005_album_is_favorite', '2018-12-21 04:14:57.311687');
INSERT INTO django_migrations (id, app, name, applied) VALUES (21, 'music', '0006_album_user', '2018-12-21 04:37:45.890788');

-- Table: django_session
CREATE TABLE "django_session" ("session_key" varchar(40) NOT NULL PRIMARY KEY, "session_data" text NOT NULL, "expire_date" datetime NOT NULL);
INSERT INTO django_session (session_key, session_data, expire_date) VALUES ('x6mow4xtvw8ptwimm2dh2n3zyvi1mipw', 'ZDY2NjM4YjNmYWYxNWM5NDZhMjJkMDIxYTliYzNhZDdjYTcwYmQ3Nzp7fQ==', '2019-01-04 04:38:21.309142');
INSERT INTO django_session (session_key, session_data, expire_date) VALUES ('7a91nnfvwb3wcsqc72bnhba4g34nzcj0', 'ZDY2NjM4YjNmYWYxNWM5NDZhMjJkMDIxYTliYzNhZDdjYTcwYmQ3Nzp7fQ==', '2019-01-04 04:53:37.608615');
INSERT INTO django_session (session_key, session_data, expire_date) VALUES ('4gzqz3fpo0e1tqoq8zle6253zcoif8xx', 'ZDY2NjM4YjNmYWYxNWM5NDZhMjJkMDIxYTliYzNhZDdjYTcwYmQ3Nzp7fQ==', '2019-01-04 04:56:20.528113');
INSERT INTO django_session (session_key, session_data, expire_date) VALUES ('eudhgfp4rqjis1dzvagi95i5nkqbugrs', 'ZDY2NjM4YjNmYWYxNWM5NDZhMjJkMDIxYTliYzNhZDdjYTcwYmQ3Nzp7fQ==', '2019-01-04 04:58:47.106670');
INSERT INTO django_session (session_key, session_data, expire_date) VALUES ('3z9bscnbyycpkm1gm4tkftbm71da1mea', 'ZDY2NjM4YjNmYWYxNWM5NDZhMjJkMDIxYTliYzNhZDdjYTcwYmQ3Nzp7fQ==', '2019-01-04 04:59:17.510203');
INSERT INTO django_session (session_key, session_data, expire_date) VALUES ('n08v4yewxwaoqbl5j2p62d6ulny7z8fn', 'ZDY2NjM4YjNmYWYxNWM5NDZhMjJkMDIxYTliYzNhZDdjYTcwYmQ3Nzp7fQ==', '2019-01-04 05:03:34.780707');
INSERT INTO django_session (session_key, session_data, expire_date) VALUES ('qcvga1e9yzlxluar9uazx9zbmyxmu76f', 'NTgzNWJmM2QwZWZlM2MzZWMxZmU4ZWQ3YzdmMjUzNzVhZjllYjhhMjp7Il9hdXRoX3VzZXJfaWQiOiIzIiwiX2F1dGhfdXNlcl9iYWNrZW5kIjoiZGphbmdvLmNvbnRyaWIuYXV0aC5iYWNrZW5kcy5Nb2RlbEJhY2tlbmQiLCJfYXV0aF91c2VyX2hhc2giOiIxM2ViYmQzZDhiYTYzNzJkZDIwNWE1YjNjYTlkNzliNWU2ZGRlMTY2In0=', '2019-01-10 15:28:03.411147');

-- Table: music_album
CREATE TABLE "music_album" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "artist_id" integer NOT NULL REFERENCES "music_artist" ("id") DEFERRABLE INITIALLY DEFERRED, "album_title" varchar(500) NOT NULL, "genre_id" integer NOT NULL REFERENCES "music_genre" ("id") DEFERRABLE INITIALLY DEFERRED, "album_logo" varchar(1000) NOT NULL, "is_favorite" bool NOT NULL, "user_id" integer NOT NULL REFERENCES "auth_user" ("id") DEFERRABLE INITIALLY DEFERRED);
INSERT INTO music_album (id, artist_id, album_title, genre_id, album_logo, is_favorite, user_id) VALUES (1, 1, 'Fearless', 1, 'https://upload.wikimedia.org/wikipedia/en/thumb/8/86/Taylor_Swift_-_Fearless.png/220px-Taylor_Swift_-_Fearless.png', 0, 1);
INSERT INTO music_album (id, artist_id, album_title, genre_id, album_logo, is_favorite, user_id) VALUES (5, 1, '1989', 1, 'https://upload.wikimedia.org/wikipedia/en/thumb/f/f6/Taylor_Swift_-_1989.png/220px-Taylor_Swift_-_1989.png', 0, 1);
INSERT INTO music_album (id, artist_id, album_title, genre_id, album_logo, is_favorite, user_id) VALUES (13, 2, 'Give Your Heart a Break', 1, 'https://upload.wikimedia.org/wikipedia/en/thumb/f/f6/Taylor_Swift_-_1989.png/220px-Taylor_Swift_-_1989.png', 0, 1);
INSERT INTO music_album (id, artist_id, album_title, genre_id, album_logo, is_favorite, user_id) VALUES (14, 4, 'Stiches', 1, 'https://t2.genius.com/unsafe/220x220/https%3A%2F%2Fimages.rapgenius.com%2F3b4e501efa5af6642e9f15e1452b8026.600x600x1.jpg', 0, 1);
INSERT INTO music_album (id, artist_id, album_title, genre_id, album_logo, is_favorite, user_id) VALUES (15, 1, 'Red', 1, 'https://upload.wikimedia.org/wikipedia/en/thumb/c/c0/Taylor_Swift_-_Red_%28Single%29.png/220px-Taylor_Swift_-_Red_%28Single%29.png', 0, 1);
INSERT INTO music_album (id, artist_id, album_title, genre_id, album_logo, is_favorite, user_id) VALUES (17, 3, 'Nine Track Mind', 1, 'https://direct.rhapsody.com/imageserver/images/Alb.243008322/500x500.jpg', 0, 1);

-- Table: music_artist
CREATE TABLE "music_artist" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "gender" varchar(100) NOT NULL, "artist_name" varchar(250) NOT NULL);
INSERT INTO music_artist (id, gender, artist_name) VALUES (1, 'Female', 'Taylor Swift');
INSERT INTO music_artist (id, gender, artist_name) VALUES (2, 'Female', 'Demi Lovato');
INSERT INTO music_artist (id, gender, artist_name) VALUES (3, 'Male', 'Charlie Puth');
INSERT INTO music_artist (id, gender, artist_name) VALUES (4, 'Male', 'Shawn Mendes');

-- Table: music_genre
CREATE TABLE "music_genre" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "genre_name" varchar(250) NOT NULL);
INSERT INTO music_genre (id, genre_name) VALUES (1, 'Pop');
INSERT INTO music_genre (id, genre_name) VALUES (2, 'Classical');
INSERT INTO music_genre (id, genre_name) VALUES (3, 'Jazz');
INSERT INTO music_genre (id, genre_name) VALUES (4, 'Country');

-- Table: music_song
CREATE TABLE "music_song" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "file_type" varchar(10) NOT NULL, "song_title" varchar(250) NOT NULL, "album_id" integer NOT NULL REFERENCES "music_album" ("id") DEFERRABLE INITIALLY DEFERRED, "is_favorite" bool NOT NULL);
INSERT INTO music_song (id, file_type, song_title, album_id, is_favorite) VALUES (4, '', 'You Belong With Me', 1, 0);
INSERT INTO music_song (id, file_type, song_title, album_id, is_favorite) VALUES (6, '', 'Give Your Heart A Break', 13, 0);
INSERT INTO music_song (id, file_type, song_title, album_id, is_favorite) VALUES (7, '', 'Stitches', 14, 0);
INSERT INTO music_song (id, file_type, song_title, album_id, is_favorite) VALUES (8, '', 'Love Story', 1, 0);

-- Index: auth_group_permissions_group_id_b120cbf9
CREATE INDEX "auth_group_permissions_group_id_b120cbf9" ON "auth_group_permissions" ("group_id");

-- Index: auth_group_permissions_group_id_permission_id_0cd325b0_uniq
CREATE UNIQUE INDEX "auth_group_permissions_group_id_permission_id_0cd325b0_uniq" ON "auth_group_permissions" ("group_id", "permission_id");

-- Index: auth_group_permissions_permission_id_84c5c92e
CREATE INDEX "auth_group_permissions_permission_id_84c5c92e" ON "auth_group_permissions" ("permission_id");

-- Index: auth_permission_content_type_id_2f476e4b
CREATE INDEX "auth_permission_content_type_id_2f476e4b" ON "auth_permission" ("content_type_id");

-- Index: auth_permission_content_type_id_codename_01ab375a_uniq
CREATE UNIQUE INDEX "auth_permission_content_type_id_codename_01ab375a_uniq" ON "auth_permission" ("content_type_id", "codename");

-- Index: auth_user_groups_group_id_97559544
CREATE INDEX "auth_user_groups_group_id_97559544" ON "auth_user_groups" ("group_id");

-- Index: auth_user_groups_user_id_6a12ed8b
CREATE INDEX "auth_user_groups_user_id_6a12ed8b" ON "auth_user_groups" ("user_id");

-- Index: auth_user_groups_user_id_group_id_94350c0c_uniq
CREATE UNIQUE INDEX "auth_user_groups_user_id_group_id_94350c0c_uniq" ON "auth_user_groups" ("user_id", "group_id");

-- Index: auth_user_user_permissions_permission_id_1fbb5f2c
CREATE INDEX "auth_user_user_permissions_permission_id_1fbb5f2c" ON "auth_user_user_permissions" ("permission_id");

-- Index: auth_user_user_permissions_user_id_a95ead1b
CREATE INDEX "auth_user_user_permissions_user_id_a95ead1b" ON "auth_user_user_permissions" ("user_id");

-- Index: auth_user_user_permissions_user_id_permission_id_14a6b632_uniq
CREATE UNIQUE INDEX "auth_user_user_permissions_user_id_permission_id_14a6b632_uniq" ON "auth_user_user_permissions" ("user_id", "permission_id");

-- Index: django_admin_log_content_type_id_c4bce8eb
CREATE INDEX "django_admin_log_content_type_id_c4bce8eb" ON "django_admin_log" ("content_type_id");

-- Index: django_admin_log_user_id_c564eba6
CREATE INDEX "django_admin_log_user_id_c564eba6" ON "django_admin_log" ("user_id");

-- Index: django_content_type_app_label_model_76bd3d3b_uniq
CREATE UNIQUE INDEX "django_content_type_app_label_model_76bd3d3b_uniq" ON "django_content_type" ("app_label", "model");

-- Index: django_session_expire_date_a5c62663
CREATE INDEX "django_session_expire_date_a5c62663" ON "django_session" ("expire_date");

-- Index: music_album_artist_id_f633b817
CREATE INDEX "music_album_artist_id_f633b817" ON "music_album" ("artist_id");

-- Index: music_album_genre_id_86340b86
CREATE INDEX "music_album_genre_id_86340b86" ON "music_album" ("genre_id");

-- Index: music_album_user_id_5762717f
CREATE INDEX "music_album_user_id_5762717f" ON "music_album" ("user_id");

-- Index: music_song_album_id_62a413c8
CREATE INDEX "music_song_album_id_62a413c8" ON "music_song" ("album_id");

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
