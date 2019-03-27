
all: 
	@g++ -std=c++11 main.cpp graph.cpp bplustree.cpp genericNode.cpp innernode.cpp leafnode.cpp userObject.cpp -o tree
clean: 
	@rm -rf tree output_file.txt
