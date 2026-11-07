#берем образ с dockerhub
FROM gcc:16.2.0 AS builder

WORKDIR /app
COPY main.c .
# Компилируем программу, подключая библиотеку libfcgi
RUN gcc -o main main.c -lfcgi


FROM nginx:latest
# Устанавливаем утилиту spawn-fcgi и библиотеку для работы C-программы
RUN apt-get update
RUN apt-get install -y --no-install-recommends spawn-fcgi libfcgi0ldbl
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /app
# Копируем скомпилированный бинарник из первого этапа
COPY --from=builder /app/main .
# Копируем наш конфиг Nginx и скрипт запуска
COPY nginx.conf /etc/nginx/nginx.conf

# Говорим Docker, что контейнер слушает порт 81
EXPOSE 81
# Указываем, что при запуске контейнера нужно выполнить
CMD RUN spawn-fcgi -p 8080 ./main && nginx -g 'daemon off'
