FROM ubuntu:24.04

RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y cmake build-essential python3 python3-pip python3-venv curl clickhouse-client

ADD ./src /usr/app/src
WORKDIR /usr/app/build
RUN cmake ../src/cpp && make 
RUN python3 -m venv env
RUN . ./env/bin/activate
RUN env/bin/pip install -r ../src/py/requirements.txt
RUN ./data_normalizer /usr/app/src/cpp/config.ini
RUN set -e 
RUN clickhouse-client --query="create or replace table table_dataset1 ( uid UUID, full_name String, email String, address String, sex String, birthdate String, phone String) engine = MergeTree() partition by murmurHash3_32(uid) % 8 order by uid;"
RUN set -e 
RUN clickhouse-client --query="create or replace table table_dataset2 ( uid UUID, first_name String, middle_name String, last_name String, birthdate String, phone String, address String) engine = MergeTree() partition by murmurHash3_32(uid) % 8 order by uid;"
RUN set -e 
RUN clickhouse-client --query="create or replace table table_dataset3 ( uid UUID, name String, email String, birthdate String, sex String) engine = MergeTree() partition by murmurHash3_32(uid) % 8 order by uid;"
RUN clickhouse-client --query="INSERT INTO  clean_dataset1 FORMAT CSV" < /usr/app/src/cpp/clear_csv1.csv
RUN clickhouse-client --query="INSERT INTO  clean_dataset2 FORMAT CSV" < /usr/app/src/cpp/clear_csv2.csv
RUN clickhouse-client --query="INSERT INTO  clean_dataset3 FORMAT CSV" < /usr/app/src/cpp/clear_csv3.csv
RUN env/bin/python3 ../src/py/lib/__init__.py
#ENTRYPOINT command ./data_normalizer /usr/app/src/cpp/config.ini && env/bin/python3 ../src/py/lib/__init__.py
