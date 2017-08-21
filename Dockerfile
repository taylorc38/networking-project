FROM gcc:4.9
COPY . /NetworkingProject
WORKDIR /NetworkingProject
RUN g++ --o application main.cpp
CMD ["./application"]
