#берем образ с dockerhub
#1 этап: Сборка
FROM gcc:16.2.0 AS builder
# Устанавливаем утилиту spawn-fcgi и библиотеку для работы C-программы
RUN apt-get update && \
    apt-get install -y --no-install-recommends libfcgi-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY main.c .
# Компилируем программу, подключая библиотеку libfcgi
RUN gcc -o main main.c -lfcgi

#2 этап: Финальный образ
FROM nginx:latest
RUN apt-get update && \
    apt-get install -y --no-install-recommends spawn-fcgi libfcgi0ldbl && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
# Копируем скомпилированный бинарник из первого этапа
COPY --from=builder /app/main .
# Копируем наш конфиг Nginx и скрипт запуска
COPY nginx.conf /etc/nginx/nginx.conf

# Говорим Docker, что контейнер слушает порт 81
EXPOSE 81

# Создаем группу и пользователя (если они еще не созданы в базовом образе)
# Переключаемся на созданного пользователя
RUN groupadd -r myuser && useradd -r -g myuser myuser
USER myuser

HEALTHCHECK --interval=30s --timeout=30s --start-period=5s --retries=3 CMD curl -f http://localhost:81/ || exit 1

# Запускаем оба процесса (используем JSON-формат, чтобы убрать warning)
CMD ["sh", "-c", "spawn-fcgi -p 8080 ./main && nginx -g 'daemon off;'"]
