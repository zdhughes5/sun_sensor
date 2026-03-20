int connect_socket() {
	int sockfd;
	struct sockaddr_in server_addr;

	// Creating socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
	perror("Couldn't create socket");
	exit(EXIT_FAILURE);
	}

	// Binding the socket to an address
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(LOCAL_PORT);

	if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
	perror("Couldn't bind to address");
	exit(EXIT_FAILURE);
	}

	return sockfd;
}
