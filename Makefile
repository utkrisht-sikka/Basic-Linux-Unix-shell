externalbin:
	gcc mymkdir2.c -o mymkdir2
	gcc mycat.c -o mycat
	gcc mydate.c -o mydate
	gcc myls.c -o myls
	gcc myrm3.c -o myrm3
compile_link:
	gcc code3.c -o code3
run:
	./code3
cl:
	rm mymkdir2 mycat mydate myls myrm3 code3
