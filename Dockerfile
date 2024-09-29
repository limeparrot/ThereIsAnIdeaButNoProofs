FROM ubuntu:24.04

RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y cmake build-essential python3 python3-pip python3-venv curl

ADD ./src /usr/app/src
WORKDIR /usr/app/build
EXPOSE 9000
EXPOSE 8123
#RUN curl 127.0.0.1:8123
RUN cmake ../src/cpp && make -j 8
RUN python3 -m venv env
RUN . ./env/bin/activate
RUN env/bin/pip install -r ../src/py/requirements.txt
RUN ./data_normalizer /usr/app/src/cpp/config.ini
RUN env/bin/python3 ../src/py/lib/__init__.py
#ENTRYPOINT command ./data_normalizer /usr/app/src/cpp/config.ini && env/bin/python3 ../src/py/lib/__init__.py
