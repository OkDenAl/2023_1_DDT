FROM postgres:15
RUN apt-get update && apt-get -y install pgagent
COPY init.sql /docker-entrypoint-initdb.d/init.sql