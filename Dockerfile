FROM gcc:4.9
COPY . /NetworkingProject
ADD ./include/* /NetworkingProject/include/
WORKDIR /NetworkingProject
RUN make
CMD [./application server"]
