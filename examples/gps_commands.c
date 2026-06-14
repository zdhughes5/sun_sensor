// Function to connect GPS
void connectgps(int baud, const char *dev, int sockfd)
{
    char message[256];
    struct sockaddr_in serveraddr;

    sprintf(message, "gps_connect %d '%s'", baud, dev);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.0.0.2");

    sendto(sockfd,
           message,
           strlen(message),
           MSG_CONFIRM,
           (const struct sockaddr *)&server_addr,
           sizeof(server_addr));
}

// Function to disconnect GPS
void disconnect_gps(int sockfd)
{
    char message[256] = "gps_disconnect";
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.0.0.2");

    sendto(sockfd,
           message,
           strlen(message),
           MSG_CONFIRM,
           (const struct sockaddr *)&server_addr,
           sizeof(server_addr));
}

// Function to force reset of ADC
void force_reset_adc(int x, int sockfd)
{
    char message[256];
    struct sockaddr_in server_addr;

    sprintf(message, "adc%d_force_reset", x);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.0.0.2");

    sendto(sockfd,
           message,
           strlen(message),
           MSG_CONFIRM,
           (const struct sockaddr *)&server_addr,
           sizeof(server_addr));
}